import copy

from NodArbore import NodArbore


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, informatieNod):
        return informatieNod in self.scopuri

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
                        except:
                            h += 1
                minh = min(minh, h)
            return minh


    def succesori(self, nod, euristica):
        s = []
        for i, stiva in enumerate(nod.informatie):
            if not stiva:
                continue
            copie_stive = copy.deepcopy(nod.informatie)
            bloc = copie_stive[i].pop()
            for j in range(len(nod.informatie)):
                if j == i:
                    continue
                infoSuccesor = copy.deepcopy(copie_stive)
                infoSuccesor[j].append(bloc)
                s.append(NodArbore(infoSuccesor, nod.g+1, self.estimeaza_h(infoSuccesor, euristica), nod))
        return s
