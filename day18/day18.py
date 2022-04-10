import math
from copy import deepcopy

file = open("day18/input.txt", "r")
line = 'temp'


class node:

    def __init__(self, parent=None, left=None, right=None, number=None, isRightOrLeftChild=None):
        self.parent = parent
        #self.depth = depth
        self.left = left
        self.right = right
        self.number = number
        self.isRightOrLeftChild = isRightOrLeftChild # 0 = left, 1 = right

    def __str__(self):
        string = ""

        currentNode = self
        prevNode = None
        prevNodeWasParent = True

        while currentNode is not None:

            if currentNode.number is None: # Not a regular number
                if prevNode is not None and not prevNodeWasParent and prevNode.isRightOrLeftChild == 1: # Already visited
                    string = string + "]"
                    prevNode = currentNode
                    currentNode = currentNode.parent
                    prevNodeWasParent = False
                    continue
                elif prevNodeWasParent: # Not already visited
                    string = string + "["

                if prevNodeWasParent:
                    prevNode = currentNode
                    currentNode = currentNode.left
                    prevNodeWasParent = True
                elif prevNode.isRightOrLeftChild == 0:
                    string = string + ","
                    prevNode = currentNode
                    currentNode = currentNode.right
                    prevNodeWasParent = True

            else: # A regular number
                if currentNode.isRightOrLeftChild == 0:
                    string = string + str(currentNode.number)
                    prevNode = currentNode
                    currentNode = currentNode.parent
                    prevNodeWasParent = False
                else:
                    string = string + str(currentNode.number)
                    prevNode = currentNode
                    currentNode = currentNode.parent
                    prevNodeWasParent = False

        return string


def getList(depth, positionAtDepthRef, number):
    currentList = number
    for iDepth in range(depth):
        pos = positionAtDepthRef[iDepth]
        currentList = currentList[pos]
    return currentList


def explode(explodingPair, firstNumberToLeftPair):
    # Add to first regular number to the left
    if firstNumberToLeftPair is not None:
        if firstNumberToLeftPair.right.number is not None:
            firstNumberToLeftPair.right.number = firstNumberToLeftPair.right.number + explodingPair.left.number
        else:
            firstNumberToLeftPair.left.number = firstNumberToLeftPair.left.number + explodingPair.left.number


    # Continue iterating to the right from the exploding pair and stop at first regular number
    firstNumberToRightPair = None
    prevNode = explodingPair
    prevNodeWasParent = False
    currentNode = explodingPair.parent

    while firstNumberToRightPair is None and currentNode is not None:

        if currentNode.number is None: # Not a regular number
            if prevNode is not None and not prevNodeWasParent and prevNode.isRightOrLeftChild == 1: # Already visited
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
                continue

            if prevNodeWasParent:
                prevNode = currentNode
                currentNode = currentNode.left
                prevNodeWasParent = True
            elif prevNode.isRightOrLeftChild == 0:
                prevNode = currentNode
                currentNode = currentNode.right
                prevNodeWasParent = True

        else: # A regular number
            firstNumberToRightPair = currentNode.parent

    # Add to first regular number to the right
    if firstNumberToRightPair is not None:
        if currentNode.isRightOrLeftChild == 0:
            firstNumberToRightPair.left.number = firstNumberToRightPair.left.number + explodingPair.right.number
        else:
            firstNumberToRightPair.right.number = firstNumberToRightPair.right.number + explodingPair.right.number
    
    # Replace the exploding pair with 0
    if explodingPair.isRightOrLeftChild == 0:
        explodingPair.parent.left.number = 0
    else:
        explodingPair.parent.right.number = 0

def split(number):
    number.left = node(number, number=math.floor(number.number / 2.0), isRightOrLeftChild=0)
    number.right = node(number, number=math.ceil(number.number / 2.0), isRightOrLeftChild=1)
    number.number = None

def reduceNumber(number):

    depth = 0
    shouldReduce = False

    currentNode = number
    prevNode = None
    prevNodeWasParent = True

    lastRegularNumberPair = None

    while currentNode is not None:

        if currentNode.number is None: # Not a regular number
            if prevNode is not None and not prevNodeWasParent and prevNode.isRightOrLeftChild == 1: # Already visited
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
                depth = depth - 1
                continue

            if prevNodeWasParent:
                prevNode = currentNode
                currentNode = currentNode.left
                prevNodeWasParent = True
                depth = depth + 1
            elif prevNode.isRightOrLeftChild == 0:
                prevNode = currentNode
                currentNode = currentNode.right
                prevNodeWasParent = True
                depth = depth + 1


        else: # A regular number

            if depth >= 5 and currentNode.parent.left.number is not None and currentNode.parent.right.number is not None:
                shouldReduce = True
                explodingPair = currentNode.parent
                explode(explodingPair, lastRegularNumberPair)
                return shouldReduce

            if currentNode.isRightOrLeftChild == 0:
                lastRegularNumberPair = currentNode.parent
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
                depth = depth - 1 
            else:
                lastRegularNumberPair = currentNode.parent
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
                depth = depth - 1
    

    # Check for splits
    currentNode = number
    prevNode = None
    prevNodeWasParent = True

    while currentNode is not None:

        if currentNode.number is None: # Not a regular number
            if prevNode is not None and not prevNodeWasParent and prevNode.isRightOrLeftChild == 1: # Already visited
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
                continue

            if prevNodeWasParent:
                prevNode = currentNode
                currentNode = currentNode.left
                prevNodeWasParent = True
            elif prevNode.isRightOrLeftChild == 0:
                prevNode = currentNode
                currentNode = currentNode.right
                prevNodeWasParent = True

        else: # A regular number

            if currentNode.number >= 10:
                shouldReduce = True
                split(currentNode)
                return shouldReduce


            if currentNode.isRightOrLeftChild == 0:
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False
            else:
                prevNode = currentNode
                currentNode = currentNode.parent
                prevNodeWasParent = False



    return shouldReduce


def addNumbers(firstNumber, secondNumber):
    sumResult = node(None, firstNumber, secondNumber)
    firstNumber.isRightOrLeftChild = 0
    secondNumber.isRightOrLeftChild = 1

    firstNumber.parent = sumResult
    secondNumber.parent = sumResult

    return sumResult

def calculateMagnitude(number):

    if number.number is None:
        leftMagnitude = calculateMagnitude(number.left)
        rightMagnitude = calculateMagnitude(number.right)
        magnitude = 3*leftMagnitude + 2*rightMagnitude
    else:
        magnitude = number.number
        
    return magnitude

line = file.readline()
sumResult = None
originalInput = []

while line != '':
    #print(line)

    number = None
    listResult = []
    currentDepth = 0
    positionAtDepth = [0]
        
    # Read the number
    for i, char in enumerate(line):
        
        if char == '[': # More depth
            if number is None:
                listResult = []
                number = node()
                currentDepth = 0
            else:
                currentList = getList(currentDepth, positionAtDepth, listResult)
                currentList.append([])

                if positionAtDepth[currentDepth] == 0:
                    number.left = node(number, isRightOrLeftChild = 0)
                    number = number.left
                else:
                    number.right = node(number, isRightOrLeftChild = 1)
                    number = number.right

                currentDepth = currentDepth + 1
                if len(positionAtDepth) <= currentDepth:
                    positionAtDepth.append(0)
        
        elif char == ']':
            if currentDepth > 0:
                number = number.parent
            positionAtDepth[currentDepth] = 0
            currentDepth = currentDepth - 1
        elif char == ',':
            positionAtDepth[currentDepth] = positionAtDepth[currentDepth] + 1
        else:
            # Regular number

            if char != '\n':
                currentList = getList(currentDepth, positionAtDepth, listResult)
                if positionAtDepth[currentDepth] == 0:
                    number.left = node(number, currentDepth, number=int(char), isRightOrLeftChild = 0)
                else:
                    number.right = node(number, currentDepth, number=int(char), isRightOrLeftChild = 1)
                
                currentList.append(int(char))



    originalInput.append(deepcopy(number))
    print(number)
    line = file.readline()


    if sumResult == None:
        # Start with the first number
        sumResult = number
    else:
        # Do the addition
        sumResult = addNumbers(sumResult, number)

    shouldReduce = True
    while shouldReduce:
        #print("Before:", sumResult)
        shouldReduce = reduceNumber(sumResult)
        #print("After:", sumResult)



magnitude = calculateMagnitude(sumResult)

print("Answer problem 1:", magnitude)


largestIndex1 = None
largestIndex2 = None
largestMagnitude = 0
for i in range(len(originalInput)):
    for j in range(i+1, len(originalInput)):
        if i == j:
            print("Happened")
            continue

        sumResult = addNumbers(deepcopy(originalInput[i]), deepcopy(originalInput[j]))
        shouldReduce = True
        while shouldReduce:
            shouldReduce = reduceNumber(sumResult)
        magnitude1 = calculateMagnitude(sumResult)

        sumResult = addNumbers(deepcopy(originalInput[j]), deepcopy(originalInput[i]))
        shouldReduce = True
        while shouldReduce:
            shouldReduce = reduceNumber(sumResult)
        magnitude2 = calculateMagnitude(sumResult)

        if magnitude1 > largestMagnitude:
            largestIndex1 = i
            largestIndex2 = j
            largestMagnitude = magnitude1

        if magnitude2 > largestMagnitude:
            largestIndex1 = j
            largestIndex2 = i
            largestMagnitude = magnitude2

print("Answer problem 2:", largestMagnitude, largestIndex1, largestIndex2)




file.close()