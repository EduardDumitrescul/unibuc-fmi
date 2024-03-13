
from l3.NodArbore import NodArbore
from l3.graf import Graf
from l3.parcurgeri import aStarSolMultiple, aStarHeapQ, aStarPQ

m = [
[0, 3, 5, 10, 0, 0, 100],
[0, 0, 0, 4, 0, 0, 0],
[0, 0, 0, 4, 9, 3, 0],
[0, 3, 0, 0, 2, 0, 0],
[0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 4, 0, 5],
[0, 0, 3, 0, 0, 0, 0],
]

start = 0
scopuri = [4,6]
h=[0,1,6,2,0,3,0]


graf = Graf(m, NodArbore(start, g=0, h=h[start]), scopuri, h)
nsol = 10

aStarSolMultiple(graf, nsol=nsol) # nsol=10 timp = 0.0001499652862548828 secunde
aStarHeapQ(graf, nsol=nsol) # nsol=10,      timp = 0.00009441375732421875 secunde
aStarPQ(graf, nsol=nsol) # nsol = 10        timp = 0.00021266937255859375 secounde