import copy

from NodArbore import NodArbore


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, informatieNod):
        return informatieNod in self.scopuri

    def valideaza(self):
        matrDesfasurata = self.start[0] + self.start[1] + self.start[2]
        nrInvers = 0
        for i, placuta in enumerate(matrDesfasurata):
            for placuta2 in matrDesfasurata[i + 1:]:
                if placuta > placuta2 and placuta2:
                    nrInvers += 1
        return nrInvers % 2 == 0

    def estimeaza_h(self, infoNod, euristica):
        if infoNod in self.scopuri:
            return 0
        if euristica == "banala":
            return 1
        if euristica == "euristica mutari":
            minh = float('inf')
            for scop in self.scopuri:
                h = 0
                for iStiva, stiva in enumerate(scop):
                    for iBloc, bloc in enumerate(stiva):
                        try:
                            if infoNod[iStiva][iBloc] != bloc:
                                h += 1  
                minh = min(minh, h)
            return minh

    def succesori(self, nod, euristica):
        lSuccesori = []
        gasitGol = False
        for lGol in range(3):
            for cGol in range(3):
                if nod.informatie[lGol][cGol] == 0:
                    gasitGol = True
                    break
            if gasitGol:
                break

        directii=[[-1, 0], [1, 0], [0, -1], [0, 1]]
        for d in directii:
            lPlacuta = lGol + d[0]
            cPlactura = cGol + d[1]
            if not (0 <= lPlacuta <= 2 and 0 <= cPlactura <= 2):
                continue
            infoSuccesor = copy.deepcopy(nod.informatie)
            infoSuccesor[lGol][cGol], infoSuccesor[lPlacuta][cPlactura] = infoSuccesor[lPlacuta][cPlactura], infoSuccesor[lGol][cGol]

            if not nod.inDrum(infoSuccesor):
                lSuccesori.append(NodArbore(infoSuccesor, nod.g+1, self.estimeaza_h(infoSuccesor, euristica), nod))


        return lSuccesori
