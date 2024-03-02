from NodArbore import NodArbore
from graf import Graf

m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
]

start = 0
scopuri = [5, 9]

graf = Graf(m, NodArbore(start), scopuri)


# Tema DFS, recursiv, coada
# schimba bfs cu verificare scop la aduagrea in coada
def breadthFirst(graf, nsol):
    print("BF")
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        # if graf.scop(nodCurent.informatie):
        #     print(repr(nodCurent))
        #     nsol -= 1
        succesori = graf.succesori(nodCurent)
        for s in succesori:
            if graf.scop(s.informatie):
                print(repr(s))
                nsol -= 1
        coada += succesori

def depthFirst(graf, nsol):
    print("DF iterativ")
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        succesori = graf.succesori(nodCurent)
        for s in succesori:
            if graf.scop(s.informatie):
                print(repr(s))
                nsol -= 1
        coada = succesori + coada

def depthFirstRec(graf, nsol, nod):
    if graf.scop(nod.informatie):
        print(repr(nod))
        nsol -= 1

    if nsol == 0:
        return nsol

    succesori = graf.succesori(nod)
    for s in succesori:
        nsol = depthFirstRec(graf, nsol, s)
        if nsol == 0:
            return nsol
    return nsol


depthFirst(graf, 10)
breadthFirst(graf, 40)

print("DF - rec")
depthFirstRec(graf, 2, graf.start)
