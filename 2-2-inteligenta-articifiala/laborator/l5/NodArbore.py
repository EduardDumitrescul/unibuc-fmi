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

    def __le__(self, other):
        if self.f == other.f:
            return self.h <= other.h
        return self.f <= other.f


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
