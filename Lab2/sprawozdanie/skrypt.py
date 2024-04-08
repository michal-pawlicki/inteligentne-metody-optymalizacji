import os
import glob

# Funkcja do obliczenia statystyk z plików
def calculate_statistics(folder_path):
    # Inicjalizacja listy na wartości, czasy obliczeń i nazwy plików
    values = []
    computation_times = []
    filenames = []

    # Pętla przez wszystkie pliki w folderze zgodne z wzorcem
    for filename in glob.glob(os.path.join(folder_path, "out_*.txt")):
        with open(filename, "r") as file:
            lines = file.readlines()
            # Sprawdzenie, czy plik zawiera co najmniej 4 linie
            if len(lines) >= 4:
                # Odczytanie pierwszej i czwartej linii z pliku
                value = int(lines[0].strip())
                computation_time = float(lines[3].strip())

                # Dodanie wartości do listy
                values.append(value)
                computation_times.append(computation_time)
                filenames.append(filename)

    # Obliczenie wartości minimalnej, maksymalnej i średniej
    min_value = min(values)
    max_value = max(values)
    average_value = sum(values) / len(values)

    min_computation_time = min(computation_times)
    max_computation_time = max(computation_times)
    average_computation_time = sum(computation_times) / len(computation_times)

    # Znalezienie nazwy pliku dla minimalnej wartości
    min_value_index = values.index(min_value)
    filename_min_value = filenames[min_value_index]

    # Wyświetlenie wyników
    print("Wartość minimalna:", min_value, "(plik:", filename_min_value, ")")
    print("Wartość maksymalna:", max_value)
    print("Średnia wartość:", average_value)

    print("Minimalny czas obliczeń:", min_computation_time)
    print("Maksymalny czas obliczeń:", max_computation_time)
    print("Średni czas obliczeń:", average_computation_time)

# Wywołanie funkcji dla aktualnego folderu
calculate_statistics(".")
