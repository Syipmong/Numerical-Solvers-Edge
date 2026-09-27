"""Plot Hamiltonian energy drift from the numerical solver benchmark."""

from __future__ import annotations

import argparse
import csv
from pathlib import Path

import matplotlib.pyplot as plt


PROJECT_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_DATA = PROJECT_ROOT / "drift_data.csv"
DEFAULT_OUTPUT = PROJECT_ROOT / "drift_plot.png"


def read_drift_data(data_path: Path) -> tuple[list[float], list[float], list[float]]:
    """Read time, RK4 drift, and symplectic Euler drift from CSV output."""
    with data_path.open(newline="", encoding="utf-8") as data_file:
        rows = csv.DictReader(data_file, skipinitialspace=True)
        time: list[float] = []
        rk4_drift: list[float] = []
        symplectic_drift: list[float] = []

        for row in rows:
            time.append(float(row["Time"]))
            rk4_drift.append(float(row["RK4_EnergyDRift"]))
            symplectic_drift.append(float(row["SE_EnergyDrift"]))

    if not time:
        raise ValueError(f"No data rows found in {data_path}")

    return time, rk4_drift, symplectic_drift


def create_plot(
    time: list[float],
    rk4_drift: list[float],
    symplectic_drift: list[float],
    output_path: Path,
) -> None:
    """Create and save the energy-drift comparison plot."""
    plt.style.use("dark_background")
    figure, axis = plt.subplots(figsize=(8, 4.5), dpi=300)

    axis.plot(time, rk4_drift, color="#00E5FF", linewidth=2, label="RK4")
    axis.plot(
        time,
        symplectic_drift,
        color="#FFB74D",
        linewidth=2,
        label="Symplectic Euler",
    )
    axis.axhline(0.0, color="#888888", linewidth=1, linestyle="--", alpha=0.7)
    axis.set_xlabel("Time")
    axis.set_ylabel("Energy Drift ($H(t) - H(0)$)")
    axis.set_title("Hamiltonian Energy Drift Comparison")
    axis.grid(True, linestyle="--", alpha=0.3)
    axis.legend()

    figure.tight_layout()
    figure.savefig(output_path)
    plt.close(figure)


def main() -> None:
    parser = argparse.ArgumentParser(description="Plot solver energy drift from CSV data.")
    parser.add_argument("--data", type=Path, default=DEFAULT_DATA)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    arguments = parser.parse_args()

    if not arguments.data.exists():
        raise SystemExit(
            f"Simulation data not found: {arguments.data}\n"
            "Run the benchmark first, then run this script."
        )

    data = read_drift_data(arguments.data)
    arguments.output.parent.mkdir(parents=True, exist_ok=True)
    create_plot(*data, arguments.output)
    print(f"Saved plot to {arguments.output}")


if __name__ == "__main__":
    main()
