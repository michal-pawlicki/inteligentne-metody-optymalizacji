### Compile using

```bash
g++ -o out/main src/main.cpp src/reader.cpp src/helpers.cpp src/steepest.cpp src/cycle_augmentation.cpp src/hybrid_evolution.cpp
```

### Run using

```bash
cd out
./main <startingNode> <dataSet(kroA/kroB)> <doLocalSearch(0/1)>
```

### Plot using

```bash
cd src
python3 TCP_drawer.py <nameOfOutputFile> <instance_file>
```
