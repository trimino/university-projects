# Posterior Probabilities

<img src='bnet_image.gif' title='Bayesian Network' width='' alt='Bayesian Network' />

For the Bayesian network of Figure 1, implement a program that computes and prints out the probability of any combination of events given any other combination of events. If the executable is called bnet, here are some example invocations of the program:

1. To print out the probability P(Burglary=true and Alarm=false | MaryCalls=false).
    
    > bnet Bt Af given Mf
    
2. To print out the probability P(Alarm=false and Earthquake=true).
    > bnet Af Et

3. To print out the probability P(JohnCalls=true and Alarm=false | Burglary=true and Earthquake=false).
    > bnet Jt Af given Bt Ef

4. To print out the probability P(Burglary=true and Alarm=false and MaryCalls=false and JohnCalls=true and Earthquake=true).
    > bnet Bt Af Mf Jt Et

# Code Structure

The code below reads in the arguments and transition them into the program.
It puts them into two different dictionaries, one for the numerator and the other for the denominator.

```
for x in range(1, len(sys.argv)):
    if sys.argv[x] == 'given':
        given_flag = True

    if not given_flag:
        numer[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 

    elif given_flag and sys.argv[x] != 'given':
        denom[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 
        numer[sys.argv[x][0]] = True if sys.argv[x][1] == 't' else False 
````

<b/>

The Code below helps calculate all the different possibiities for the variables not specified in the argument list. It also calls the <i>computeProbability</i> method to help compute the probabilites.

```
def cal(mylist, mydict, bnet):
    prob = 0
    table = list(itertools.product([True, False], repeat=len(mylist)))

    for x in table:
        for y in range(len(mylist)):
            mydict[mylist[y]] = x[y]
        prob  += bnet.computeProbability(mydict['B'], mydict['E'], mydict['A'], mydict['J'], mydict['M'])
    return prob
 ```

<b/>

The code below helps compute the probabilities.

```
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
```
