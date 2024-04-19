
class NodArbore:
    def __init__(self, informatie, parinte=None):
        self.parinte = parinte
        self.informatie = informatie

    def __str__(self):
        return str(self.informatie)

    def __repr__(self):
        return str(self.informatie) + " (" + "->".join([str(x) for x in self.drumRadacina()]) + ")"

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

    def afisSolFisier(self, graf, fout):
        fout.write("####################################################################################\n")
        drum = self.drumRadacina()
        for i in range(len(drum)):
            nod = drum[i]
            if i > 0:
                prev = drum[i-1]
                dir = "malul stang la malul drept"
                if prev.informatie[2] == "right":
                    dir = "malul drept la malul stang"

                can = abs(prev.informatie[1] - nod.informatie[1])
                mis = abs(prev.informatie[0] - nod.informatie[0])

                msg = f">>> Barca s-a deplasat de la {dir} cu {can} canibali si {mis} misionari."
                fout.write(msg + "\n")

            mis_stanga = nod.informatie[0]
            can_stanga = nod.informatie[1]
            mis_dreapta = graf.n - mis_stanga
            can_dreapta = graf.n - can_stanga
            barca_stanga = ""
            barca_dreapta = ""
            if nod.informatie[2] == "left":
                barca_stanga = ":<barca>"
            else:
                barca_dreapta = ":<barca>"
            msg = f"(Stanga{barca_stanga}) {can_stanga} canibali {mis_stanga} misionari ........ (Dreapta{barca_dreapta}) {can_dreapta} canibali {mis_dreapta} misionari"
            fout.write(msg + "\n")


class Graf:
    def __init__(self, n, m, start):
        self.n = n
        self.m = m
        self.start = start

    def scop(self, informatieNod):
        return informatieNod == (0, 0, "right")

    def succesori(self, nod):
        s = []

        for (m, c, b) in [(m, c, b) for m in range(self.n+1) for c in range(self.n+1) for b in ["left", "right"]]:
            if nod.inDrum((m, c, b)):
                continue
            if b == nod.informatie[2]:
                continue

            bmis = nod.informatie[0] - m
            bcan = nod.informatie[1] - c
            if nod.informatie[2] == "right":
                bmis = -bmis
                bcan = -bcan

            if bmis >= 0 and bcan >= 0 and (bmis + bcan > 0) and (bmis >= bcan or bmis == 0) and (m >= c or m == 0) and bmis + bcan <= self.m:
                s.append(NodArbore((m, c, b), nod))

        return s

def breadthFirst(graf, nsol, fout):
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        # if graf.scop(nodCurent.informatie):
        #     print(repr(nodCurent))
        #     nsol -= l1
        succesori = graf.succesori(nodCurent)
        for s in succesori:
            if graf.scop(s.informatie):
                s.afisSolFisier(graf, fout)
                nsol -= 1
        coada += succesori

def depthFirst(graf, nsol, fout):
    coada = [graf.start]
    while coada and nsol:
        nodCurent = coada.pop(0)
        succesori = graf.succesori(nodCurent)
        for s in succesori:
            if graf.scop(s.informatie):
                s.afisSolFisier(graf, fout)
                nsol -= 1
        coada = succesori + coada

def depthFirstRec(graf, nsol, nod, fout):
    if graf.scop(nod.informatie):
        nod.afisSolFisier(graf, fout)
        nsol -= 1

    if nsol == 0:
        return nsol

    succesori = graf.succesori(nod)
    for s in succesori:
        nsol = depthFirstRec(graf, nsol, s, fout)
        if nsol == 0:
            return nsol
    return nsol


n = 0
m = 0

with open("lab2.txt") as file:
    n = int(file.readline())
    m = int(file.readline())

graf = Graf(n, m, NodArbore((n, n, "left")))
# print(graf.succesori(graf.start))

bf_out = open("bf.txt", "w")
df_out = open("df.txt", "w")
df_rec_out = open("df-rec.txt", "w")

breadthFirst(graf, 1, bf_out)
depthFirst(graf, 10, df_out)
depthFirstRec(graf, 10, graf.start, df_rec_out)