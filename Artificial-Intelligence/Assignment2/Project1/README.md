# Posterior Probabilities

The task in this part is to implement a system that:

* Can determine the posterior probability of different hypotheses, given priors for these hypotheses, and given a sequence of observations.

* Can determine the probability that the next observation will be of a specific type, priors for different hypotheses, and given a sequence of observations

As in the slides that we saw in class, there are five types of bags of candies. Each bag has an infinite amount of candies. We have one of those bags, and we are picking candies out of it. We don't know what type of bag we have, so we want to figure out the probability of each type based on the candies that we have picked.
<b/>

The five possible hypotheses for our bag are:

* h1 (prior: 10%): This type of bag contains 100% cherry candies.
* h2 (prior: 20%): This type of bag contains 75% cherry candies and 25% lime candies.
* h3 (prior: 40%): This type of bag contains 50% cherry candies and 50% lime candies.
* h4 (prior: 20%): This type of bag contains 25% cherry candies and 75% lime candies.
* h5 (prior: 10%): This type of bag contains 100% lime candies.

# Code Structure

The code is structued by spliting up the forumula (function for numerator and denominator). The function **cal_Ph** calculates the numerator and the other function **calPQ** calculates the denominator. The formula for that I am referring is:

[P(Q_j | h_i) * P_j-1(h_i)] / P_j-1(Q_j)
<b/>

The code below calculates the numerator portion

```
def cal_Ph(observation):
    PQ_C, PQ_L = cal_PQ()
    PQ  = PQ_C if observation == 'C' else PQ_L

    for x in range(5):
        PQh = CHRY_PROB[x] if observation == 'C' else LIME_PROB[x]
        Ph  = HYPH_PROB[x]
        HYPH_PROB[x] = (PQh * Ph) / PQ
    
    return PQ_C, PQ_L
```

<b/>

The code below calculates the denomintator portion
```
def cal_PQ():
    newSumCherry = 0
    for x in range(5):
        newSumCherry += HYPH_PROB[x] * CHRY_PROB[x]
    
    PQ_C = newSumCherry
    PQ_L = 1 - PQ_C

    return PQ_C, PQ_L
```


# Run code

> python compute_a_posterior.py CCLCCLC
