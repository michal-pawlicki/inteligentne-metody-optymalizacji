### Compile using

```bash
g++ -o out/main src/main.cpp src/reader.cpp src/cycle_augmentation.cpp
```

### Run using

```bash
cd out
./main <starting_node> <dataSet(kroA/kroB)> <algorithm(cycle/steepest/cache/candidates)
```

### Plot using

```bash
cd src
python3 TCP_drawer.py <nameOfOutputFile> <instance_file>
```
