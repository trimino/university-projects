# David Trimino
# 1001659459

import sys
import itertools

class BayesianNetwork:
    def __init__(self):
        self.B      = 0.001
        self.E      = 0.002
        self.A_BE   = 0.95
        self.A_BEf  = 0.94
        self.A_BfE  = 0.29
        self.A_BfEf = 0.001
        self.J_A    = 0.90
        self.J_Af   = 0.05
        self.M_A    = 0.70
        self.M_Af   = 0.01
    
    def computeProbability(self, b, e, a, j, m):
        valueB = self.B if b else 1 - self.B
        valueE = self.E if e else 1 - self.E
        valueA = self.A_BE if b and e else self.A_BfE if not b and e else self.A_BEf if b and not e else self.A_BfEf
        valueJ = self.J_A if a else self.J_Af
        valueM = self.M_A if a else self.M_Af

        valueA = valueA if a else 1 - valueA
        valueJ = valueJ if j else 1 - valueJ 
        valueM = valueM if m else 1 - valueM
    
        return valueB * valueE * valueA * valueJ * valueM

def cal(mylist, mydict, bnet):
    prob = 0
    table = list(itertools.product([True, False], repeat=len(mylist)))

    for x in table:
        for y in range(len(mylist)):
            mydict[mylist[y]] = x[y]
        prob  += bnet.computeProbability(mydict['B'], mydict['E'], mydict['A'], mydict['J'], mydict['M'])
    return prob

def main():
    given_flag = False
    bnet = BayesianNetwork()
    numer = {
        'B': None,
        'E': None,
        'A': None,
        'J': None,
        'M': None
    }
    denom = {
        'B': None,
        'E': None,
        'A': None,
        'J': None,
        'M': None
    }

    if len(sys.argv) > 6:
        sys.exit('PROGRAM SHOULD NOT EXCEED 6 ARGUMENTS')

    for x in range(1, len(sys.argv)):
        if sys.argv[x] == 'given':
            given_flag = True

        if not given_flag:
            numer[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 

        elif given_flag and sys.argv[x] != 'given':
            denom[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 
            numer[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 

    n_nones = [x for x in numer if numer[x] is None]
    d_nones = [x for x in denom if denom[x] is None]

    n_prob = cal(n_nones, numer, bnet)
    d_prob = cal(d_nones, denom, bnet)
    
    prob = n_prob / d_prob
    
    print('bnet ', end='')
    for x in range(1, len(sys.argv)):
        print(sys.argv[x], end=' ')
    print(f'\nProbability = {prob : 0.10f}')
    
if __name__ == '__main__':
    main()