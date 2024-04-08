@echo off
setlocal enabledelayedexpansion

REM Usunięcie plików wyjściowych, jeśli istnieją
for %%G in (out_*.txt) do if exist %%G del %%G

REM Loop through starting nodes from 0 to 99
FOR /L %%G IN (0,1,99) DO (
    REM Utworzenie nazwy pliku wyjściowego
    set output_file=out_%%G.txt
    REM Uruchomienie main.exe z odpowiednimi parametrami i przekierowanie wyniku do odpowiedniego pliku wyjściowego
    main.exe %%G %1 %2 %3 %4 !output_file!
)
