"""
David Trimino
1001659459
"""

import sys

class Node:
    def __init__(self, parent, state, cumCost, depth, evaluation, uSearch, cost):
        """
        Constructor for Node class

        Args:
            parent      (Node): Parent node for this current node
            state       (String): current state of the problem 
            cumCost     (Double): cummulative cost of reaching this node from root node
            depth       (int): depth of node 
            evaluation  (double): evalutation value of the current node f(n) = g(n) + h(n) (A* algo)
            uSearch     (boolean): whether to use informed or uninformed search
            cost        (double): Cost to get to this node (not cummulative)
            next        (Node): Pointer use to find the patht o destination
        """
        self.parent     = parent
        self.state      = state
        self.depth      = depth
        self.cumCost    = cumCost
        self.depth      = depth
        self.evaluation = evaluation
        self.uSearch    = uSearch
        self.cost       = cost
        self.next       = None

    def __str__(self):
        """
        Overloading stream/print operator for class Node to make a string representation for this class

        Returns:
            String: String representation for class node
        """
        if self.uSearch:
            return f'State = {self.state}, g(n) = {self.cumCost}, d = {self.depth}, Parent = ( {self.parent} )'
        else: 
            return f'State = {self.state}, g(n) = {self.cumCost}, d = {self.depth}, f(n) = {self.evaluation}, Parent = {self.parent}'

    def __lt__(self, other):
        if self.uSearch:
            return self.cumCost < other.cumCost
        else:
            return self.evaluation < other.evaluation

    def __le__(self, other):
        if self.uSearch:
            return self.cumCost <= other.cumCost
        else:
            return self.evaluation <= other.evaluation

    def __gt__(self, other):
        if self.uSearch:
            return self.cumCost > other.cumCost
        else:
            return self.evaluation > other.evaluation

    def __ge__(self, other):
        if self.uSearch:
            return self.cumCost <= other.cumCost
        else:
            return self.evaluation <= other.evaluation

    def __eq__(self, other):
        if self.uSearch:
            return self.cumCost == other.cumCost
        else:
            return self.evaluation == other.evaluation

    def __ne__(self, other):
        if self.uSearch:
            return self.cumCost != other.cumCost
        else:
            return self.evaluation != other.evaluation
    


def readInputFile(filename):
    """
    Reads input file describing the problem description into the program

    Args:
        filename (String): the name of the file to read that has the problem description 

    Returns:
        dictionary: contains the problem description in it
    """
    d = {}
    with open(filename, 'r') as file:
        for line in file:
            line = line.rstrip('\n').rstrip('\r')
            if line == 'END OF INPUT':
                return d
            else:
                x = line.split(' ')
                if x[0] in d:
                    d[ x[0] ].append([ x[1], float(x[2]) ]) 
                else:
                    d[ x[0] ] = [[ x[1], float(x[2]) ]]

                if x[1] in d:
                    d[ x[1] ].append([ x[0], float(x[2]) ])
                else:
                    d[ x[1] ] = [[ x[0], float(x[2]) ]]


def readHeuristicFile(filename):
    """
    Reads in the heuristic file into the program 

    Args:
        filename (String): File name of the heuristic file 

    Returns:
        dictionary: contains the heuristic function
    """
    h = {}
    with open(filename, 'r') as file:
        for line in file:
            line = line.rstrip('\n').rstrip('\r')
            if line == 'END OF INPUT':
                return h
            x = line.split(' ')
            h[ x[0] ] = float( x[1] )

def expand(node, d, h):
    """
    Expands a node to generate a list of successors/children for a given node (current/parent node)

    Args:
        node (Node): Parent node information
        d (dictionary): contains the problem description in it
        h (dictionary): contains the heuristic function

    Returns:
        list: succesors/children of all of the parent's node
    """
    successors = []
    actions = d[ node.state ]
    for action in actions:
        cost = node.cumCost + action[1]
        if node.uSearch:
            successors.append( Node(node, action[0], cost, node.depth + 1, 0, node.uSearch, action[1]) )
        else:
            successors.append( Node(node, action[0], cost, node.depth + 1, cost + h[action[0]], node.uSearch, action[1]) )
    return successors

def route(node):
    """
    Reverse's the path while creating a link list path to take to the goal node

    Args:
        node (Node): The GOAL node of the problem

    Returns:
        Node: Returns the beginning node of the path
    """
    while node.parent is not None:
        tempNode = node
        node = node.parent
        node.next = tempNode

    while node.next is not None:
        print(f'{node.state} to {node.next.state}: {node.next.cost} km')
        node = node.next

def main():
    h = {}
    fringe = []
    visited = []
    uSearch = False
    GOAL = sys.argv[3]
    argLength = len(sys.argv)
    d = readInputFile(sys.argv[1])

    if argLength == 4:
        uSearch = True
        fringe.append( Node(None, sys.argv[2], 0, 0, 0, uSearch, 0) )
    elif argLength == 5:
        uSearch = False
        h = readHeuristicFile(sys.argv[4])
        fringe.append( Node(None, sys.argv[2], 0, 0, h[sys.argv[2]], uSearch, 0) )
    else:
        print('Invalid arguments')
        sys.exit()
    
    countPop = 0
    countExp = 0
    countGen = 1
	
    while len(fringe) > 0:
        node = fringe.pop(0)
        countPop = countPop + 1

        if node.state == GOAL:
            print(f'nodes  expanded: {countExp}')
            print(f'nodes generated: {countGen}')
            print(f'distance: {node.cumCost} km')
            print('route:')
            route(node)
            sys.exit()
        else:
            if node.state not in visited:
                countExp = countExp + 1
                visited.append(node.state)
                successors = expand(node, d, h)
                for x in successors:
                    countGen = countGen + 1
                    fringe.append(x)
                fringe.sort()
   
    print(f'nodes  expanded: {countExp}')
    print(f'nodes generated: {countGen}')
    print(f'distance: infinity')
    print('route:' + '\n' + 'none')


if __name__ == '__main__':
    main()
