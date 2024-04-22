import heapq
import queue
from time import time

import NodArbore


def aStarLab(gr, euristica):

    OPEN = [gr.start]
    CLOSED = []
    while OPEN:
        nodCurent = OPEN.pop(0)
        CLOSED.append(nodCurent)
        if gr.scop(nodCurent.informatie):
            print(repr(nodCurent))
            return
        lSuccesori=gr.succesori(nodCurent, euristica)
        for s in lSuccesori:
            gasitOpen = False
            for nodC in OPEN:
                if s.informatie == nodC.informatie:
                    gasitOpen = True
                    if s < nodC:
                        OPEN.remove(nodC)
                    else:
                        lSuccesori.remove(s)
                    break
            if not gasitOpen:
                for nodC in CLOSED:
                    if s.informatie == nodC.informatie:
                        if s < nodC:
                            CLOSED.remove(nodC)
                        else:
                            lSuccesori.remove(s)
                        break
        OPEN += lSuccesori
        OPEN.sort()
    print("Nu avem solutii")

def a_star(graf):
    print("A-star (pseudocod)")
    open = []
    closed = []
    np_start = graf.start
    open.append(np_start)

    while open:
        nod_curent = open[0]
        open.remove(open[0])
        if graf.scop(nod_curent.informatie):
            print(repr(nod_curent))
            break

        succesori = graf.succesori(nod_curent)
        closed.append(nod_curent)

        for s in succesori:
            nod_nou = None
            if not nod_curent.inDrum(s.informatie):
                sOpen = None
                for o in open:
                    if o.informatie == s.informatie:
                        sOpen = o
                        break


                if sOpen is not None:
                    if sOpen.f > s.f or (sOpen.f == s.f and sOpen.g < s.g):
                        open.remove(sOpen)
                        nod_nou = s

                sClosed = None
                for c in closed:
                    if c.informatie == s.informatie:
                        sClosed = c
                        break

                if sClosed is not None:
                    if sClosed.f > s.f or (sClosed.f == s.f and sClosed.g < s.g):
                        closed.remove(sClosed)
                        nod_nou = s
                    else:
                        nod_nou = sClosed


                if sOpen is None and sClosed is None:
                    nod_nou = s

                if nod_nou is not None:
                    open.append(nod_nou)
                    open.sort()








def aStarPQ(graf, nsol):
    print("a-Star (pq)")
    startTime = time()
    pq = queue.PriorityQueue()
    pq.put(graf.start)
    while pq and nsol:
        nodCurent = pq.get()
        if graf.scop(nodCurent.informatie):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                break
        succesori = graf.succesori(nodCurent)

        for s in succesori:
            pq.put(s)
    print(f"Time to run: {time() - startTime}")

def aStarHeapQ(graf, nsol):
    startTime = time()
    print("a-Star (heapq)")
    pq = []
    heapq.heappush(pq, graf.start)
    while pq and nsol:
        nodCurent = heapq.heappop(pq)
        if graf.scop(nodCurent.informatie):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                break
        succesori = graf.succesori(nodCurent)

        for s in succesori:
            heapq.heappush(pq, s)

    print(f"Time to run: {time() - startTime}")
def aStarSolMultiple(graf, nsol, euristica):

    startTime = time()
    print("a-Star")
    coada = [NodArbore(graf.start)]
    while coada and nsol:
        nodCurent = coada.pop(0)
        if graf.scop(nodCurent.informatie):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                break
        succesori = graf.succesori(nodCurent, euristica)

        coada += succesori
        coada.sort()

    print(f"Time to run: {time() - startTime}")

def binarySearch(list, value):
    if len(list) == 0:
        return 0
    left = 0
    right = len(list) - 1
    while left <= right:
        mid = (left + right) // 2
        if list[mid] < value:
            left = mid + 1
        else :
            right = mid - 1
    return right

def aStarSolMultipleBSearch(graf, nsol):

    startTime = time()
    print("a-Star binary search")
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        if graf.scop(nodCurent.informatie):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                break
        succesori = graf.succesori(nodCurent)

        for s in succesori:
            pos = binarySearch(coada, s)
            coada.insert(pos, s)

    print(f"Time to run: {time() - startTime}")


def breadthFirst(graf, nsol):
    print("BF")
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        # if graf.scop(nodCurent.informatie):
        #     print(repr(nodCurent))
        #     nsol -= l1
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