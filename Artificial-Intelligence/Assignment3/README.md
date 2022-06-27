The task in this programming assignment is to design appropriate descriptions of facts, actions, and goals, using the PDDL language, for two planning problems: the Tower of Hanoi problem, and the 7-puzzle problem (a variation of the 8-puzzle problem where two squares are clear instead of one). You will use your descriptions as inputs to a Graphplan implementation. If your descriptions are correct, Graphplan will produce appropriate plans


## Compiling and Running Program
The Graphplan software can be downloaded from graphplan.zip. See the README file in that package for additional information. To compile the software on omega, unzip the directory, and, from that directory, type
```
make graphplan
```
Once the program compiles, it can be invoked from the commandline as follows:
```
graphplan -o [operators_file] -f [facts_file]
```

For example:
```
graphplan -o block_ops.txt -f block_facts3.txt
```

Argument operators_file specifies the location of a text file containing definitions of actions. For example, see block_ops.txt for definitions of actions appropriate for the blocks world.
<br>
<br>
Argument facts_file specifies the location of a text file containing definitions of facts about the environment, including objects (and types for those objects), general predicates that are always true, initial state description, and goal description. For example, see block_facts2.txt, block_facts3.txt, and block_facts4.txt for example fact descriptions for the blocks world.
<br>
<br>
Once you start running the software, it will ask you three questions. Just hit enter for each question, so as to use the default settings. If your descriptions of actions and facts are correct, the program will print out a plan achieving the stated goal.
<br>
<br>
Note that the preconds in each fact file will contain both statements that are always true in that domain (i.e., in the Tower of Hanoi domain or the 7-puzzle domain), and statements that simply describe the initial state for that specific planning problem. In addition to the facts files for the specific planning problems you are given, you will have to create a separate text file that includes all the statements that must be present in ANY facts file for that domain.


## DISCLAMER
**graphplan.zip** is code that I have not written and I do not take credit for
