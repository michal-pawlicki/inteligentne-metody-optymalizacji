import matplotlib.pyplot as plt

def read_solution(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()


    distance = lines[0] 
    pathA = [tuple(map(int, point.strip('()').split(','))) for point in lines[1].strip().split()[2:] if point.strip('()')]
    pathB = [tuple(map(int, point.strip('()').split(','))) for point in lines[2].strip().split()[2:] if point.strip('()')]

    return pathA, pathB, distance

def plot_solution(pathA, pathB, name):
    plt.figure(figsize=(10, 5))

    plt.plot(*zip(*pathA), marker='o', label='Path A')
    plt.plot(*zip(*pathB), marker='o', label='Path B')

    plt.title(name)
    plt.legend()

    plt.show()

def main():
  pathA, pathB, distance = read_solution('../out/solution_nearest_neighbour.txt')
  plot_solution(pathA, pathB, 'Nearest Neighbour' + ' - ' + distance)
  pathA2, pathB2, distance2 = read_solution('../out/solution_cycle_augmentation.txt')
  plot_solution(pathA2, pathB2, 'Cycle Augmentation' + ' - ' + distance2)
  pathA3, pathB3, distance3 = read_solution('../out/solution_two_regret.txt')
  plot_solution(pathA3, pathB3, 'Two Regret' + ' - ' + distance3)

if __name__ == '__main__':
  main()