import sys
import math
import matplotlib.pyplot as plt



def read_instance(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    coordinates = []
    for line in lines[:-1]:
        _, x, y = map(int, line.split())
        coordinates.append((x, y))

    return coordinates

def read_solution(solution_filename, instance_filename):
    with open(solution_filename, 'r') as file:
        lines = file.readlines()

    distance = lines[0]
    instance = read_instance(instance_filename)
    pathA = [instance[int(index)] for index in lines[1].strip().split() if index]
    pathA.append(pathA[0])
    pathB = [instance[int(index)] for index in lines[2].strip().split() if index]
    pathB.append(pathB[0])

    return pathA, pathB, distance

def plot_solution(pathA, pathB, name):
    plt.figure(figsize=(10, 5))

    plt.plot(*zip(*pathA), marker='o', label='Path A')
    plt.plot(*zip(*pathB), marker='o', label='Path B')

    plt.title(name)
    plt.legend()

    plt.show()


def calculate_distance(point1, point2):
    return round(math.sqrt((point1[0] - point2[0])**2 + (point1[1] - point2[1])**2))

def calculate_path_length(path):
    return sum(calculate_distance(path[i], path[i+1]) for i in range(len(path) - 1))

def main():
  if len(sys.argv) != 3:
    print("Usage: python TCP_drawer.py <solution_file> <instance_file>")
    return

  solution_filename = sys.argv[1]
  instance_filename = sys.argv[2]

  pathA, pathB, distance = read_solution(solution_filename, instance_filename)
  plot_solution(pathA, pathB, 'Distance: ' + distance)

if __name__ == '__main__':
  main()
