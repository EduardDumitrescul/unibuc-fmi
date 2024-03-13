

class Graf:
    def __init__(self, matriceAdiacenta, start, scopuri, h):
        self.matriceAdiacenta = matriceAdiacenta
        self.start = start
        self.scopuri = scopuri
        self.h = h

    def scop(self, informatieNod):
        return informatieNod in self.scopuri

    def estimeaza_h(self, infoNod):
        return self.h[infoNod]

    def succesori(self, nod):
        s = []
        for infoSuccesori in range(len(self.matriceAdiacenta)):
            dist = self.matriceAdiacenta[nod.informatie][infoSuccesori]
            if dist != 0 and not nod.inDrum(infoSuccesori):
                s.append(NodArbore(infoSuccesori, nod.g + dist,self.estimeaza_h(infoSuccesori), nod))

        return s

class NodArbore:
    def __init__(self, informatie, g=0, h=0, parinte=None):
        self.parinte = parinte
        self.informatie = informatie
        self.g = g
        self.h = h
        self.f = g + h

    def __str__(self):
        return f"{str(self.informatie)} (g: {self.g}, f:{self.f})"

    def __repr__(self):
        return str(self.informatie)  + " (" + "->".join([str(x) for x in self.drumRadacina()]) + ")"

    def __eq__(self, other):
        return self.f == other.f and self.h == other.h

    def __lt__(self, other):
        if self.f == other.f:
            return self.h < other.h
        return self.f < other.f


    def drumRadacina(self):
        if self.parinte is None:
            return [self]
        return self.parinte.drumRadacina() + [self]

    def inDrum(self, infonod):
        if self.informatie == infonod:
            return True
        if self.parinte is None:
            return False
        return self.parinte.inDrum(infonod)


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
aStarSolMultiple(graf, nsol=3)