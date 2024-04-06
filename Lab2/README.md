### Compile using

```bash
g++ -o out/main src/main.cpp src/reader.cpp src/steepest.cpp src/helpers.cpp src/random_walk.cpp src/greedy.cpp
```

### Run using

```bash
cd out
./main <starting_node> <dataSet(kroA/kroB)> <startingAlgorithm(cycle/random)> <typeOfNeighbourhood(edges/vertices)> <typeOfLocalSearch(steepest/greedy/random_walk)> <nameOfOutputFile>
```

### Plot using

```bash
cd src
python3 TCP_drawer.py <nameOfOutputFile> <instance_file>
```
