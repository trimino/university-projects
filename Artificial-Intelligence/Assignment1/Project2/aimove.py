
class AIMove(object):
    def __init__(self, row=-1, col=-1, score=0):
        self.row = row
        self.col = col
        self.score = score

    def __repr__(self):
        return f"AIMOVE: [{self.row}, {self.col}] score move is {self.score}"

    def __lt__(self, other):
        return self.score < other.score

    def __le__(self, other):
        return self.score <= other.score

    def __gt__(self, other):
        return self.score > other.score

    def __ge__(self, other):
        return self.score <= other.score

    def __eq__(self, other):
        return self.score == other.score

    def __ne__(self, other):
        return self.score != other.score
