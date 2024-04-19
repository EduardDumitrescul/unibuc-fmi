from l5.NodArbore import NodArbore
from l5.graf import Graf
from l5.parcurgeri import aStarLab

with open("input.txt") as f:
    linii = f.read().strip().split("\n")
    start = [list(map(int, linie.strip().split())) for linie in linii]
    scopuri = [
        [[1, 2, 3], [4, 5, 6], [7, 8, 0]]
    ]

graf = Graf(NodArbore(start), scopuri)
aStarLab(graf, "euristica mutari")

# aStarSolMultiple(graf, 4, "euristica mutari")


