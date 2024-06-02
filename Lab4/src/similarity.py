import os
import matplotlib.pyplot as plt
import numpy as np
from itertools import combinations

directory = "../out/kroA/steepest"

distances = []
similarities = []
solutions = []

class Solution:
    def __init__(self, distance, pathA, pathB):
        self.distance = distance
        self.pathA = pathA
        self.pathB = pathB

    def edges(self):
        return edges_from_nodes(self.pathA) + edges_from_nodes(self.pathB)

def edges_from_nodes(nodes):
    return [(nodes[i], nodes[i + 1]) for i in range(len(nodes) - 1)] + [(nodes[-1], nodes[0])]

def edge_similarity(solutionA, solutionB):
    edgesA = solutionA.edges()
    edgesB = solutionB.edges()
    common_edges = set(edgesA).intersection(edgesB)
    return len(common_edges) 

def node_similarity(solutionA, solutionB):
    nodesAA = set(solutionA.pathA)
    nodesAB = set(solutionA.pathB)
    nodesBA = set(solutionB.pathA)
    nodesBB = set(solutionB.pathB)
    common_nodes1 = nodesAA.intersection(nodesBA)
    common_nodes2 = nodesAA.intersection(nodesBB)
    common_nodes3 = nodesAB.intersection(nodesBA)
    common_nodes4 = nodesAB.intersection(nodesBB)

    return max(len(common_nodes1), len(common_nodes2), len(common_nodes3), len(common_nodes4))
    


def read_solution(file):
    with open(file, 'r') as f:
        lines = f.readlines()
        distance = float(lines[0].strip())
        pathA = list(map(int, lines[1].split()))
        pathB = list(map(int, lines[2].split()))
        return Solution(distance, pathA, pathB)


best_solution = read_solution("../out/kroA/ils2-2/4.txt")


for filename in os.listdir(directory):
    if filename.endswith(".txt"):
        filepath = os.path.join(directory, filename)
        with open(filepath, 'r') as file:
            solution = read_solution(filepath)
            solutions.append(solution)

for solutionA in solutions:
    distances.append(solutionA.distance)
    local_similarities = []
    for solutionB in solutions:
        if solutionA != solutionB:
            local_similarities.append(edge_similarity(solutionA, solutionB))
    similarities.append(np.mean(local_similarities))
    

correlation_matrix = np.corrcoef(distances, similarities)

print("Correlation coefficient:", correlation_matrix[0, 1])

plt.figure(figsize=(10, 6))
plt.scatter(distances, similarities)
plt.xlabel('Distance')
plt.ylabel('Similarity to Best Solution')
plt.title('Distance vs Similarity to Best Solution')
plt.grid(True)
plt.show()