# David Trimino
# 1001659459

import sys

HYPH_PROB = [0.1, 0.20, 0.40, 0.20, 0.10]   # P(h)
CHRY_PROB = [1, 0.75, 0.50, 0.25, 0]        # P(Q | h)
LIME_PROB = [0, 0.25, 0.50, 0.75, 1]        # P(Q | h)

def saveResult(PQ_C, PQ_L, x, observation):
    with open('result.txt', 'a') as file:
        file.write(f'After Observation {x + 1} = {observation} \n\n')
        file.write(f'P(h1 | Q) = {HYPH_PROB[0] : 0.5f} \n')
        file.write(f'P(h2 | Q) = {HYPH_PROB[1] : 0.5f} \n')
        file.write(f'P(h3 | Q) = {HYPH_PROB[2] : 0.5f} \n')
        file.write(f'P(h4 | Q) = {HYPH_PROB[3] : 0.5f} \n')
        file.write(f'P(h5 | Q) = {HYPH_PROB[4] : 0.5f} \n\n')
        file.write(f'Probability that the next candy we pick be C, given Q: {PQ_C : 0.5f} \n')
        file.write(f'Probability that the next candy we pick be L, given Q: {PQ_L : 0.5f} \n\n\n')


def cal_PQ():
    newSumCherry = 0
    for x in range(5):
        newSumCherry += HYPH_PROB[x] * CHRY_PROB[x]
    
    PQ_C = newSumCherry
    PQ_L = 1 - PQ_C

    return PQ_C, PQ_L

def cal_Ph(observation):
    PQ_C, PQ_L = cal_PQ()
    PQ  = PQ_C if observation == 'C' else PQ_L

    for x in range(5):
        PQh = CHRY_PROB[x] if observation == 'C' else LIME_PROB[x]
        Ph  = HYPH_PROB[x]
        HYPH_PROB[x] = (PQh * Ph) / PQ
    
    return PQ_C, PQ_L

def main():
    if len(sys.argv) != 2:
        sys.exit("PROGRAM NEEDS ONLY ONE ARGUMENT")

    Q = sys.argv[1]
    Q_LEN = len(Q)

    with open('result.txt', 'w') as file:
        file.write(f'Observation sequence Q: {Q} \n')
        file.write(f'Length of Q: {Q_LEN} \n\n\n')

    for x in range(Q_LEN):
        PQ_C, PQ_L = cal_Ph(Q[x])
        saveResult(PQ_C, PQ_L, x, Q[x])
    
if __name__ == '__main__':
    main() 