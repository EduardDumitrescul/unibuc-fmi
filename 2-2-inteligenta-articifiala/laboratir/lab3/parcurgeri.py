

def aStarSolMultiple(graf, nsol):
    print("a-Star")
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        if graf.scop(nodCurent.informatie):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                return
        succesori = graf.succesori(nodCurent)

        coada += succesori
        coada.sort()


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
