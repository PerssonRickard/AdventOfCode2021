
file = open("day25/input.txt", "r")

mapWidth = 139 # 139 # 10
mapHeight = 137 # 137 # 9
currentMap = [None for y in range(mapHeight)]

line = 'temp'
i = 0
while line != '':
    line = file.readline()
    #print(line)

    if line == '':
        break

    currentMap[i] = [char for char in line.rstrip('\n')]
    i = i + 1


def printMap(m):
    for row in m:
        print("".join(row))


#printMap(currentMap)
#print()

nSteps = 0
mapWasChanged = True
while mapWasChanged:

    mapWasChanged = False
    nMovements = 0
    nextMap = [['.' for x in range(mapWidth)] for y in range(mapHeight)]

    # Iterate east-facing
    for y in range(mapHeight):
        for x in range(mapWidth):
            currentElement = currentMap[y][x]

            if currentElement == '>':
                if x < mapWidth - 1:
                    rightPos = x + 1
                else:
                    rightPos = 0
                
                rightElement = currentMap[y][rightPos]
                if rightElement == '.':
                    # Move
                    nextMap[y][rightPos] = '>'
                    nMovements = nMovements + 1
                    mapWasChanged = True
                else:
                    # Stay
                    nextMap[y][x] = '>'

    # Iterate south-facing
    for y in range(mapHeight):
        for x in range(mapWidth):
            currentElement = currentMap[y][x]

            if currentElement == 'v':
                if y < mapHeight - 1:
                    downPos = y + 1
                else:
                    downPos = 0
                
                downElementCurrent = currentMap[downPos][x]
                downElementNext = nextMap[downPos][x]
                if downElementCurrent == '.':
                    if downElementNext == '.':
                        # Move
                        nextMap[downPos][x] = 'v'
                        nMovements = nMovements + 1
                        mapWasChanged = True
                    else:
                        # Stay
                        nextMap[y][x] = 'v'
                else:
                    # If it is east-facing then it might have moved out of the way
                    if downElementCurrent == '>' and downElementNext == '.':
                        # Move
                        nextMap[downPos][x] = 'v'
                        nMovements = nMovements + 1
                        mapWasChanged = True
                    else:
                        # Stay
                        nextMap[y][x] = 'v'

    nSteps = nSteps + 1
    currentMap = nextMap
    #printMap(currentMap)
    #print()
    print(nSteps, nMovements)



file.close()