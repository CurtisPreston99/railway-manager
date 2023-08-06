class Motor:
    spd: int = 0
    forward: bool = True

    def ToDict(self):
        return {"spd": self.spd, "forward": self.forward}
