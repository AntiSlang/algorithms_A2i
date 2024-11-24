import matplotlib.pyplot as plt
import numpy as np

step = 100
start_points = 500
max_points = 10100
points = np.arange(start_points, max_points, step)

files = [
    "random.txt",
    "random_hybrid.txt",
    "reversed.txt",
    "reversed_hybrid.txt",
    "swap.txt",
    "swap_hybrid.txt"
]

data = {}
for filename in files:
    with open(filename, "r") as file:
        data[filename] = [float(line.strip()) for line in file]

for i in range(0, len(files), 2):
    merge_file = files[i]
    hybrid_file = files[i + 1]

    merge_data = data[merge_file]
    hybrid_data = data[hybrid_file]

    plt.figure(figsize=(10, 6))
    plt.plot(points, merge_data, label="Merge Sort", color="blue")
    plt.plot(points, hybrid_data, label="Merge+Insertion Sort", color="green")
    plt.xlabel("Длина массива, элементы")
    plt.ylabel("Время, мс")
    plt.title(f"Сравнение времени сортировки для MERGE SORT и MERGE+INSERTION SORT ({merge_file.split('.')[0]})")
    plt.legend()
    plt.grid(True)
    plt.show()
