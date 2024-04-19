from l4 import NodArbore
from l4.graf import Graf
from l4.parcurgeri import aStarSolMultiple


def calculeazaStiva(sir):
    return [linie.strip().split() if linie != "#" else [] for linie in sir.strip().split('\n')]



with open("l4/input.txt") as f:
    (sirStart, sirScopuri) = f.read().split("=========")
    start = calculeazaStiva(sirStart)
    scopuri = [calculeazaStiva(sir) for sir in sirScopuri.split("---")]

graf = Graf(start, scopuri)
aStarSolMultiple(graf, 4, "euristica mutari")


