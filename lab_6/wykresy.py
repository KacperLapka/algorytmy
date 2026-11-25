import csv
import os
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

BASE_DIR = Path(__file__).resolve().parent
CSV_FILE = BASE_DIR / "wyniki_zad3.csv"
OUT_DIR = BASE_DIR / "wykresy"

ALGORITHMS = ["insertion", "merge", "quick"]
LABELS = {
    "insertion": "Insertion Sort",
    "merge": "Merge Sort",
    "quick": "Quick Sort (losowy pivot)",
}
COLORS = {
    "insertion": "#d62728",
    "merge": "#1f77b4",
    "quick": "#2ca02c",
}
MARKERS = {"insertion": "o", "merge": "s", "quick": "^"}
DATA_ORDER = ["losowe", "rosnace", "malejace", "prawie posortowane"]
DATA_LABELS = {
    "losowe": "losowe",
    "rosnace": "rosnące",
    "malejace": "malejące",
    "prawie posortowane": "prawie posortowane",
}


def read_rows():
    with open(CSV_FILE, newline="", encoding="utf-8") as file:
        return list(csv.DictReader(file))


def rows_for(rows, experiment, algorithm=None, data_type=None):
    result = [
        row
        for row in rows
        if int(row["eksperyment"]) == experiment
        and (algorithm is None or row["algorytm"] == algorithm)
        and (data_type is None or row["dane"] == data_type)
    ]
    return result


def plot_vs_n(rows, value_key, ylabel, title, filename):
    plt.figure(figsize=(8, 5.5))
    for algorithm in ALGORITHMS:
        selected = sorted(
            rows_for(rows, 1, algorithm=algorithm), key=lambda row: int(row["n"])
        )
        x = [int(row["n"]) for row in selected]
        y = [float(row[value_key]) for row in selected]
        plt.plot(
            x,
            y,
            marker=MARKERS[algorithm],
            color=COLORS[algorithm],
            linewidth=2,
            markersize=6,
            label=LABELS[algorithm],
        )

    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Rozmiar tablicy n")
    plt.ylabel(ylabel)
    plt.title(title)
    plt.grid(True, which="both", linestyle="--", alpha=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(OUT_DIR, filename), dpi=160)
    plt.close()


def plot_bars(rows, value_key, ylabel, title, filename, log_scale):
    categories = DATA_ORDER
    width = 0.25
    positions = list(range(len(categories)))

    plt.figure(figsize=(9, 5.5))
    for index, algorithm in enumerate(ALGORITHMS):
        values = []
        for category in categories:
            selected = rows_for(rows, 2, algorithm=algorithm, data_type=category)
            values.append(float(selected[0][value_key]) if selected else 0.0)

        offsets = [position + (index - 1) * width for position in positions]
        bottom = 0.001 if log_scale else 0
        plt.bar(
            offsets,
            values,
            width=width,
            bottom=bottom,
            color=COLORS[algorithm],
            label=LABELS[algorithm],
        )

    plt.xticks(positions, [DATA_LABELS[category] for category in categories])
    plt.xlabel("Charakter danych (n = 50000)")
    plt.ylabel(ylabel)
    plt.title(title)
    if log_scale:
        plt.yscale("log")
        plt.ylim(bottom=0.001)
    plt.grid(True, axis="y", linestyle="--", alpha=0.4)
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(OUT_DIR, filename), dpi=160)
    plt.close()


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    rows = read_rows()

    plot_vs_n(
        rows,
        "czas_ms",
        "Czas [ms]",
        "Czas sortowania w zależności od n (dane losowe)",
        "wykres_czas_vs_n.png",
    )
    plot_vs_n(
        rows,
        "porownania",
        "Liczba porównań",
        "Liczba porównań w zależności od n (dane losowe)",
        "wykres_porownania_vs_n.png",
    )
    plot_bars(
        rows,
        "czas_ms",
        "Czas [ms] (skala logarytmiczna)",
        "Czas sortowania dla różnych charakterów danych (n = 50000)",
        "wykres_czas_wg_danych.png",
        log_scale=True,
    )
    plot_bars(
        rows,
        "porownania",
        "Liczba porównań (skala logarytmiczna)",
        "Liczba porównań dla różnych charakterów danych (n = 50000)",
        "wykres_porownania_wg_danych.png",
        log_scale=True,
    )

    print("Wygenerowano wykresy w katalogu:", OUT_DIR)


if __name__ == "__main__":
    main()
