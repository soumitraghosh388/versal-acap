#!/usr/bin/env python3
# Copyright Soumitra Ghosh, IIIT Hyderabad, India, 2025
#
# SPDX-License-Identifier: MIT

import random
import os
import argparse
import subprocess
import sys

REF_LEN    = 128
READ_LEN   = 128
NREF       = 10          # references per kernel
NK         = 9           # kernels excluding master
N          = 39          # number of parallel PLIO lanes
PACKETLEN  = 16          # bases per int32  ( min(REF_LEN, 16) )
NPACKET    = REF_LEN // PACKETLEN   # int32s per sequence = 8
TOTAL_REFS = (NK + 1) * NREF        # 100 references per lane

BASE_MAP = {'A': 0, 'C': 1, 'G': 2, 'T': 3}
BASES    = ['A', 'C', 'G', 'T']

def to_signed32(val: int) -> int:
    """Reinterpret an unsigned 32-bit integer as a signed int32."""
    val &= 0xFFFFFFFF
    if val >= (1 << 31):
        val -= (1 << 32)
    return val


def encode_sequence(seq: str) -> list:
    words = []
    for pkt in range(NPACKET):
        word = 0
        for j in range(PACKETLEN - 1, -1, -1):
            base_idx = pkt * PACKETLEN + (PACKETLEN - 1 - j)
            base_val = BASE_MAP[seq[base_idx]]
            word |= (base_val << (j * 2))
        words.append(to_signed32(word))
    return words


def seq_to_digits(seq: str) -> str:
    return ''.join(str(BASE_MAP[b]) for b in seq)


def random_dna(length: int) -> str:
    return ''.join(random.choices(BASES, k=length))


def write_seq_file(path: str, words: list) -> None:
    """Write one signed int32 value per line."""
    with open(path, 'w') as f:
        for w in words:
            f.write(f"{w}\n")


def run_swg(exe: str, query_digits: str, ref_digits: str) -> int:
    """Run the baseline SWG executable and return the alignment score."""
    result = subprocess.run(
        [exe, query_digits, ref_digits],
        capture_output=True, text=True
    )
    # Output format: "Best alignment score: <N>\n"
    for line in result.stdout.splitlines():
        if "Best alignment score:" in line:
            return int(line.split(":")[-1].strip())
    raise RuntimeError(
        f"Unexpected output from {exe}:\n{result.stdout}\n{result.stderr}"
    )



def main():
    parser = argparse.ArgumentParser(
        description="Generate AIE simulation input data and ground truth for SWG accelerator")
    parser.add_argument("--exe", type=str, required=True,
                        help="Path to compiled swg_enc_in_2array_args executable")
    parser.add_argument("--seed", type=int, default=42,
                        help="Random seed for reproducibility (default: 42)")
    parser.add_argument("--outdir", type=str,
                        default=os.path.dirname(os.path.abspath(__file__)),
                        help="Output directory (default: script directory)")
    parser.add_argument("--verbose", action="store_true",
                        help="Print generated DNA sequences")
    args = parser.parse_args()

    # Validate executable
    exe = os.path.abspath(args.exe)
    if not os.path.isfile(exe):
        print(f"Error: executable not found: {exe}", file=sys.stderr)
        print("Compile with: gcc -O2 -o swg_enc_in_2array_args "
              "SWG/baseline/swg_enc_in_2array_args.c", file=sys.stderr)
        sys.exit(1)

    random.seed(args.seed)
    os.makedirs(args.outdir, exist_ok=True)


    query = random_dna(READ_LEN)
    query_digits = seq_to_digits(query)
    query_words  = encode_sequence(query)

    out0 = os.path.join(args.outdir, "input_0.seq")
    write_seq_file(out0, query_words)
    print(f"[input_0.seq]  {len(query_words):4d} words  (query, {READ_LEN} bases)")
    if args.verbose:
        print(f"  query: {query}")

    gt_path = os.path.join(args.outdir, "output_ref.txt")
    gt_file = open(gt_path, 'w')

    total_pairs = N * TOTAL_REFS
    computed    = 0

    for lane in range(N):
        ref_words = []
        refs      = []

        for r in range(TOTAL_REFS):
            seq = random_dna(REF_LEN)
            refs.append(seq)
            ref_words.extend(encode_sequence(seq))

        # Write per-lane reference file
        fname = f"input_{lane + 1}.seq"
        write_seq_file(os.path.join(args.outdir, fname), ref_words)
        print(f"[{fname}]  {len(ref_words):4d} words  "
              f"({TOTAL_REFS} refs x {NPACKET} words, {REF_LEN} bases each)")

        if args.verbose:
            print(f"  lane {lane} references:")
            for r, seq in enumerate(refs):
                print(f"    ref[{r:3d}]: {seq}")

        # Ground truth: run baseline executable for each (query, ref) pair
        print(f"  Computing ground truth for lane {lane} ...", end='', flush=True)
        for r, seq in enumerate(refs):
            score = run_swg(exe, query_digits, seq_to_digits(seq))
            gt_file.write(f"{score}\n")
            computed += 1
        print(f" done  ({computed}/{total_pairs})")

    gt_file.close()

    print(f"\nDone. Files written to: {args.outdir}")
    print(f"  input_0.seq              : {NPACKET} words  (query)")
    print(f"  input_1..{N}.seq     : {TOTAL_REFS * NPACKET} words each  "
          f"({N} lanes x {TOTAL_REFS} refs)")
    print(f"  output_ref.txt           : {total_pairs} scores  "
          f"({N} lanes x {TOTAL_REFS} refs, 1 score/line)")


if __name__ == "__main__":
    main()
