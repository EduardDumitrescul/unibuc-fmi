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
