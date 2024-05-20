### Compile using

```bash
g++ -o out/main src/main.cpp src/reader.cpp src/helpers.cpp src/steepest.cpp src/iterated_local_search.cpp src/large_scale_neighbourhood_search.cpp src/multiple_start_local_search.cpp src/cycle_augmentation.cpp
```

### Run using

```bash
cd out
./main <dataSet(kroA/kroB)> <algorithm(msls/ils1/ils2-1/ils2-2)
```

### Plot using

```bash
cd src
python3 TCP_drawer.py <nameOfOutputFile> <instance_file>
```
