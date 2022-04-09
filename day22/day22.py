import re

file = open("day22/input.txt", "r")

line = 'temp'

minGridCoord = -100000
maxGridCoord = 100000
gridSize = maxGridCoord - minGridCoord
cubesOn = [[[0 for x in range(101)] for y in range(101)] for z in range(101)]

def coordToIndex(coord):
    return coord+50

while line != '':
    line = file.readline()

    if line == '':
        continue

    #print(line)

    onOff = re.search('on', line)
    matches = re.findall(r'-?\d+', line)
    xRange = [int(matches[0]), int(matches[1])]
    yRange = [int(matches[2]), int(matches[3])]
    zRange = [int(matches[4]), int(matches[5])]

    for z in range(max(-50, zRange[0]), min(50, zRange[1])+1):
        for y in range(max(-50, yRange[0]), min(50, yRange[1])+1):
            for x in range(max(-50, xRange[0]), min(50, xRange[1])+1):
                xCoord = coordToIndex(x)
                yCoord = coordToIndex(y)
                zCoord = coordToIndex(z)

                if onOff is not None:
                    cubesOn[zCoord][yCoord][xCoord] = 1
                else:
                    cubesOn[zCoord][yCoord][xCoord] = 0
        

# Count the number of cubes that are turned on
nCubesOn = 0
for z in range(-50, 51):
    for y in range(-50, 51):
        for x in range(-50, 51):
            xCoord = coordToIndex(x)
            yCoord = coordToIndex(y)
            zCoord = coordToIndex(z)

            if cubesOn[zCoord][yCoord][xCoord] == 1:
                nCubesOn = nCubesOn + 1

print("Answer problem 1:", nCubesOn)


file.close()


# Problem 2
file = open("day22/input.txt", "r")
line = 'temp'

rangesTurnedOn = []

def checkForCollision(candidateRange, existingRange):
    collidingInX = False
    collidingInY = False
    collidingInZ = False

    if candidateRange[0][0] <= existingRange[0][1] and candidateRange[0][1] >= existingRange[0][1] or \
        candidateRange[0][1] >= existingRange[0][0] and candidateRange[0][0] <= existingRange[0][0] or \
        candidateRange[0][0] >= existingRange[0][0] and candidateRange[0][1] <= existingRange[0][1]:
        collidingInX = True
    if candidateRange[1][0] <= existingRange[1][1] and candidateRange[1][1] >= existingRange[1][1] or \
        candidateRange[1][1] >= existingRange[1][0] and candidateRange[1][0] <= existingRange[1][0] or \
        candidateRange[1][0] >= existingRange[1][0] and candidateRange[1][1] <= existingRange[1][1]:
        collidingInY = True
    if candidateRange[2][0] <= existingRange[2][1] and candidateRange[2][1] >= existingRange[2][1] or \
        candidateRange[2][1] >= existingRange[2][0] and candidateRange[2][0] <= existingRange[2][0] or \
        candidateRange[2][0] >= existingRange[2][0] and candidateRange[2][1] <= existingRange[2][1]:
        collidingInZ = True

    return collidingInX and collidingInY and collidingInZ

def resolveCollision(candidateRange, existingRange):
    newRanges = []

    x1 = candidateRange[0]
    y1 = candidateRange[1]
    z1 = candidateRange[2]
    x2 = existingRange[0]
    y2 = existingRange[1]
    z2 = existingRange[2]

    # Check all 7 directions
    # x
    if x1[1] > x2[1]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # y
    if y1[1] > y2[1]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if y1[0] < y2[0]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # z
    if z1[1] > z2[1]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if z1[0] < z2[0]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # xy
    if x1[1] > x2[1] and y1[1] > y2[1]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[0] < y2[0]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[1] > x2[1] and y1[0] < y2[0]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[1] > y2[1]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [max(z1[0], z2[0]), min(z1[1], z2[1])]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # xz
    if x1[1] > x2[1] and z1[1] > z2[1]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and z1[0] < z2[0]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[1] > x2[1] and z1[0] < z2[0]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and z1[1] > z2[1]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [max(y1[0], y2[0]), min(y1[1], y2[1])]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # yz
    if y1[1] > y2[1] and z1[1] > z2[1]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if y1[0] < y2[0] and z1[0] < z2[0]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if y1[1] > y2[1] and z1[0] < z2[0]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if y1[0] < y2[0] and z1[1] > z2[1]:
        newRangeX = [max(x1[0], x2[0]), min(x1[1], x2[1])]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])

    # xyz
    if x1[1] > x2[1] and y1[1] > y2[1] and z1[1] > z2[1]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[0] < y2[0] and z1[0] < z2[0]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[1] > x2[1] and y1[0] < y2[0] and z1[0] < z2[0]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[1] > x2[1] and y1[1] > y2[1] and z1[0] < z2[0]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[1] > x2[1] and y1[0] < y2[0] and z1[1] > z2[1]:
        newRangeX = [x2[1]+1, x1[1]]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[1] > y2[1] and z1[0] < z2[0]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z1[0], z2[0]-1]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[1] > y2[1] and z1[1] > z2[1]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y2[1]+1, y1[1]]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    if x1[0] < x2[0] and y1[0] < y2[0] and z1[1] > z2[1]:
        newRangeX = [x1[0], x2[0]-1]
        newRangeY = [y1[0], y2[0]-1]
        newRangeZ = [z2[1]+1, z1[1]]
        newRanges.append([newRangeX, newRangeY, newRangeZ])
    
    return newRanges

def removeRange(xRange, yRange, zRange, existingRanges):
    # Pretend that the cuboid to remove already exists and that the colliding
    # cuboid should be added using resolveCollision. The returned cuboids will
    # be the result of removing the cuboid to be removed.
    # result = existing - toRemove = {existing = toRemove + resolveCollision} =
    # = (toRemove + resolveCollision) - toRemove = resolveCollision

    removeRange = [xRange, yRange, zRange]
    collision = True
    indicesToRemove = []
    newRangesTotal = []

    for i, existingRange in enumerate(existingRanges):
        collision = checkForCollision(existingRange, removeRange)
        if collision:
            indicesToRemove.append(i)
            newRangesCurrent = resolveCollision(existingRange, removeRange)
            for newRange in newRangesCurrent:
                newRangesTotal.append(newRange)

    # Remove the ranges which have been replaced
    for iRemove in reversed(indicesToRemove):
        existingRanges.pop(iRemove)

    # Add the new range(s)
    for newRange in newRangesTotal:
        existingRanges.append(newRange)


def addRange(xRange, yRange, zRange, existingRanges):

    candidateRanges = [[xRange, yRange, zRange]]

    for i, existingRange in enumerate(existingRanges):
        newRanges = []
        candidateIndicesToRemove = []
        for iCandidate, candidate in enumerate(candidateRanges):
            collision = checkForCollision(candidate, existingRange)
            if collision:
                candidateIndicesToRemove.append(iCandidate)
                newRangesCurrent = resolveCollision(candidate, existingRange)
                for newRange in newRangesCurrent:
                    newRanges.append(newRange)

        for iRemove in reversed(candidateIndicesToRemove):
            candidateRanges.pop(iRemove)
        for newRange in newRanges:
            candidateRanges.append(newRange)

    # Add the new range(s)
    for candidateRange in candidateRanges:
        existingRanges.append(candidateRange)


while line != '':
    line = file.readline()

    if line == '':
        continue

    #print(line)

    onOff = re.search('on', line)
    matches = re.findall(r'-?\d+', line)
    xRange = [int(matches[0]), int(matches[1])]
    yRange = [int(matches[2]), int(matches[3])]
    zRange = [int(matches[4]), int(matches[5])]

    if onOff is not None:
        addRange(xRange, yRange, zRange, rangesTurnedOn)
    else:
        removeRange(xRange, yRange, zRange, rangesTurnedOn)





'''
nCubesOn2 = 0
for i, rangeOn in enumerate(rangesTurnedOn):
    xRange = rangeOn[0]
    yRange = rangeOn[1]
    zRange = rangeOn[2]

    if xRange[0] >= -50 and xRange[1] <= 50 and yRange[0] >= -50 and yRange[1] <= 50 and zRange[0] >= -50 and zRange[1] <= 50:
        for x in range(max(-50, min(50, xRange[0])), max(-50, min(50, xRange[1]))+1):
            for y in range(max(-50, min(50, yRange[0])), max(-50, min(50, yRange[1]))+1):
                for z in range(max(-50, min(50, zRange[0])), max(-50, min(50, zRange[1]))+1):

                    nCubesOn2 = nCubesOn2 + 1

print("nCubesOn2", nCubesOn2)
'''

nCubesOn = 0
for rangeOn in rangesTurnedOn:
    xRange = rangeOn[0]
    yRange = rangeOn[1]
    zRange = rangeOn[2]
    
    xLength = xRange[1] - xRange[0] + 1
    yLength = yRange[1] - yRange[0] + 1
    zLength = zRange[1] - zRange[0] + 1
    
    currentRangeNCubesOn = xLength*yLength*zLength

    nCubesOn = nCubesOn + currentRangeNCubesOn

print("Answer problem 2:", nCubesOn)


file.close()