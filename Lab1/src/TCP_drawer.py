import matplotlib.pyplot as plt

def read_solution(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    pathA = [tuple(map(int, point.strip('()').split(','))) for point in lines[0].strip().split()[2:] if point.strip('()')]
    pathB = [tuple(map(int, point.strip('()').split(','))) for point in lines[1].strip().split()[2:] if point.strip('()')]

    return pathA, pathB

def plot_solution(pathA, pathB):
    plt.figure(figsize=(10, 5))

    plt.plot(*zip(*pathA), marker='o', label='Path A')
    plt.plot(*zip(*pathB), marker='o', label='Path B')

    plt.title('Paths A and B')
    plt.legend()

    plt.show()

def main():
  pathA, pathB = read_solution('../out/solution_nearest_neighbour.txt')
  plot_solution(pathA, pathB)

if __name__ == '__main__':
  main()