"""Command-line helper to process the Strength-Sence dataset and save as numpy arrays.

Usage examples:
  python process_dataset_cli.py /path/to/dataset /path/to/outdir
  python process_dataset_cli.py /path/to/dataset /path/to/outdir --sensor-location CHS --sensor Acc

If the output path is a file (has a suffix), its parent directory will be used. If it's a
directory path it will be created (parents=True) if missing. The saved files will be
`samples.npy` and `labels.npy` inside that directory.
"""
from __future__ import annotations

import argparse
from pathlib import Path

from datasets.realworld.processing.dataset_processor import DatasetProcessor
from utils.numpy_array_processor import NumpyArrayProcessor


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Process strength-sence dataset and save as numpy arrays (samples.npy, labels.npy)"
    )

    p.add_argument("dataset_path", help="Path to dataset root (e.g. dataset-csv/)")
    p.add_argument(
        "out",
        help=(
            "Output directory or file path. Directory will be created if it doesn't exist."
        ),
    )

    p.add_argument("-sl", "--sensor-location", default="CHS", help="Sensor location code (default: upperarm)")
    p.add_argument("-s", "--sensors", nargs='+', default=["acc"], help="Sensor names (default: acc). Can specify multiple: -s acc gyr")
    p.add_argument("-wl", "--window-length", type=int, help="Window length")
    p.add_argument("-or", "--overlap-ratio", type=float, default=0, help="Ration deffining how much windows will overlap (default: 0)")

    return p.parse_args()


def main() -> int:
    args = parse_args()

    dataset_path = args.dataset_path
    out_path = Path(args.out)


    out_dir = out_path

    try:
        out_dir.mkdir(parents=True, exist_ok=True)
    except Exception as exc:
        print(f"Failed to create output directory '{out_dir}': {exc}")
        return 2

    print(f"Processing dataset at: {dataset_path}")
    print(f"Sensor location: {args.sensor_location}, sensors: {args.sensors}")

    samples, labels = DatasetProcessor.process_dataset(
        path_to_dataset=dataset_path,
        sensor_location=args.sensor_location,
        sensors=args.sensors,
        window_length=args.window_length,
        overlap_ratio=args.overlap_ratio
    )

    NumpyArrayProcessor.save_dataset(str(out_dir), samples, labels)

    print(f"Saved dataset to: {out_dir} (files: samples.npy, labels.npy)")
    print(f"Samples shape: {getattr(samples, 'shape', None)}, Labels shape: {getattr(labels, 'shape', None)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
