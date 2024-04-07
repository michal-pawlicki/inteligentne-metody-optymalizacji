# Laboratorium 2 - Lokalne przeszukiwane

## Autorzy: Michał Pawlicki, Mateusz Noworolnik

## Opis zadania

Zadanie lokalnego przeszukiwania polega na znalezieniu optymalnej ścieżki dla problemu komiwojażera. W tym celu zaimplementowano trzy algorytmy przeszukiwania lokalnego: przeszukiwanie strome, przeszukiwanie zachłanne oraz przeszukiwanie losowe. Wszystkie algorytmy jako rozwiązanie początkowe przyjmują rozwiązanie zwrócone przez algorytm rozbudowy cyklu lub algorytm tworzący losowe rozwiązanie. Dla każdego algorytmu przeprowadzono eksperymenty dla dwóch różnych typów sąsiedztwa, gdzie pierwsze z nich obejmowało ruchy polegające na zamianie dwóch krawędzi między trasami oraz zamianie dwóch krawędzi wewnątrz trasy, a drugie obejmowało ruchy polegające na zamianie dwóch krawędzi między trasami oraz zamianie dwóch wierzchołków wewnątrz trasy.

## Opis algorytmów i funkcji pomocniczych

### Znajdź najleprzy ruch międzytrasowy

```
Wygeneruj wszystkie pary indeksów, w których jeden pochodzi z jednej trasy a drugi z drugiej.
Dla każdej pary indeksów:
  Oblicz deltę, która powstanie po dodaniu i odjęciu odpowiednich krawędzi
  Jeżeli delta jest mniejsza od najlepszej znalezionej dotychczas to zapisz dany ruch jako najlepszy
Zwróć najlepszy ruch
```

### Znajdź najlepszy ruch wewnątrztrasowy

```
Wygeneruj wszystkie pary indeksów, w których oba indeksy pochodzą z tej samej trasy.
Dla każdej pary indeksów:
  Oblicz deltę, która powstanie po dodaniu i odjęciu odpowiednich krawędzi, w zależności od typu sąsiedztwa
  Jeżeli delta jest mniejsza od najlepszej znalezionej dotychczas to zapisz dany ruch jako najlepszy
Zwróć najlepszy ruch
```

### Przeszykiwanie w wersji stromej

```
Wczytaj rozwiązanie początkowe
Powtarzaj dopóki delta najlepszego ruchu mniejsza od 0:
  Znajdź najlepszy ruch międzytrasowy
  Znajdź najlepszy ruch wewnątrztrasowy
  Jeżeli najlepszy ruch międzytrasowy jest lepszy niż wewnątrztrasowy to wykonaj go
  W przeciwnym wypadku wykonaj ruch wewnątrztrasowy
  Zaktualizuj długość trasy
  Jeżeli oba ruchy są gorsze od obecnego rozwiązania to zakończ
```

### Znajdź pierwszy ruch międzytrasowy

```
Wygeneruj wszystkie pary indeksów, w których jeden pochodzi z jednej trasy a drugi z drugiej.
Dla każdej pary indeksów:
  Oblicz deltę, która powstanie po dodaniu i odjęciu odpowiednich krawędzi
  Jeżeli delta jest mniejsza od 0 to zwróć dany ruch
```

### Znajdź pierwszy ruch wewnątrztrasowy

```
Wygeneruj wszystkie pary indeksów, w których oba indeksy pochodzą z tej samej trasy.
Dla każdej pary indeksów:
  Oblicz deltę, która powstanie po dodaniu i odjęciu odpowiednich krawędzi, w zależności od typu sąsiedztwa
  Jeżeli delta jest mniejsza od 0 to zwróć dany ruch
```

### Przeszukiwanie w wersji zachłannej

```
Wczytaj rozwiązanie początkowe
Powtarzaj dopóki delta najlepszego ruchu mniejsza od 0:
  Wylosuj czy ruch ma być międzytrasowy czy wewnątrztrasowy
  Jeżeli ruch ma być międzytrasowy to:
    Znajdź pierwszy ruch międzytrasowy
    Jeżeli delta ruchu jest większa od 0:
      Znajdź pierwszy ruch wewnątrztrasowy
  W przeciwnym wypadku:
    Znajdź pierwszy ruch wewnątrztrasowy
    Jeżeli delta ruchu jest większa od 0:
      Znajdź pierwszy ruch międzytrasowy
  Jeżeli delta zwróconege ruchu jest mniejsza od 0:
    Wykonaj ten ruch
    Zaktualizuj długość trasy
  W przeciwnym wypadku zakończ
```

### Przeszukiwanie w sposób losowy

```
Wczytaj rozwiązanie początkowe
Powtarzaj dopóki nie skończy się limit czasu:
  Wylosuj czy ruch ma być międzytrasowy czy wewnątrztrasowy
  Jeżeli ruch ma być międzytrasowy to:
    Wykonaj losowy ruch międzytrasowy
  W przeciwnym wypadku:
    Wykonaj losowy ruch wewnątrztrasowy
  Zaktualizuj długość trasy
  Jeżeli aktualna długość trasy jest mniejsza od najlepszej to zapisz rozwiązanie jako najlepsze
```

## Wynik eksperymentów

| Algorytm             | kroA                  | kroB                  |
| -------------------- | --------------------- | --------------------- |
| cycle edges steepest | 25625(20326-27953)24  | 28420.27(26393-31106) |
| cycle edges greedy   | 25693(17480-27860)67  | 28171.18(26435-30700) |
| Two Regret           | 32338.45(30703-33659) | 33524.22(32184-35386) |

## Kod programu

https://github.com/michal-pawlicki/inteligentne-metody-optymalizacji/tree/main/Lab2
