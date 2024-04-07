@echo off
setlocal enabledelayedexpansion

REM Usunięcie plików wyjściowych, jeśli istnieją
if exist values.txt del values.txt

REM Inicjalizacja zmiennych dla obliczeń statystyk
set sum=0
set min=9999999
set max=0

REM Loop through starting nodes from 0 to 99
FOR /L %%G IN (0,1,99) DO (
    REM Uruchomienie main.exe z odpowiednimi parametrami i przekierowanie wyniku do pliku tymczasowego
    main.exe %%G %1 %2 %3 %4 temp_output.txt
    
    REM Odczytanie pierwszej linii pliku tymczasowego
    set /p value=<temp_output.txt
    
    REM Dodanie wartości do pliku values.txt
    echo !value! %%G >> values.txt
    
    REM Dodanie wartości do sumy dla obliczenia średniej
    set /a sum+=value
    
    REM Sprawdzenie minimalnej wartości
    if !value! lss !min! set min=!value!
    
    REM Sprawdzenie maksymalnej wartości
    if !value! gtr !max! set max=!value!
)

REM Obliczenie średniej wartości
set /a average=sum/100

REM Znalezienie węzła początkowego dla minimalnej wartości
for /F "tokens=1,2" %%C in (values.txt) do (
    if %%C==!min! set min_starting_node=%%D
)

REM Wyświetlenie wyników
echo Minimum value: !min!, starting node: !min_starting_node!
echo Maximum value: !max!
echo Average value: !average!

REM Usunięcie plików tymczasowych
del temp_output.txt
