from NodArbore import NodArbore


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
