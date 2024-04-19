from NodArbore import NodArbore


class Graf:
    def __init__(self, matriceAdiacenta, start, scopuri):
        self.matriceAdiacenta = matriceAdiacenta
        self.start = start
        self.scopuri = scopuri

    def scop(self, informatieNod):
        return informatieNod in self.scopuri

    def succesori(self, nod):
        s = []
        for infoSuccesori in range(len(self.matriceAdiacenta)):
            if self.matriceAdiacenta[nod.informatie][infoSuccesori] == 1 and not nod.inDrum(infoSuccesori):
                s.append(NodArbore(infoSuccesori, nod))

        return s
