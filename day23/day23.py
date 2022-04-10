
file = open("day23/input.txt", "r")


class Burrow:

    def __init__(self, firstRoom=None, secondRoom=None, thirdRoom=None, fourthRoom=None, hallway=None, energyCost=None, roomSize=2):
        self.roomSize = roomSize

        if firstRoom is None:
            self.firstRoom = ['.' for i in range(roomSize)]
        else:
            for i, pos in enumerate(firstRoom):
                self.firstRoom[i] = pos
        if secondRoom is None:
            self.secondRoom = ['.' for i in range(roomSize)]
        else:
            for i, pos in enumerate(secondRoom):
                self.secondRoom[i] = pos
        if thirdRoom is None:
            self.thirdRoom = ['.' for i in range(roomSize)]
        else:
            for i, pos in enumerate(thirdRoom):
                self.thirdRoom[i] = pos
        if fourthRoom is None:
            self.fourthRoom = ['.' for i in range(roomSize)]
        else:
            for i, pos in enumerate(fourthRoom):
                self.fourthRoom[i] = pos

        if hallway is None:
            self.hallway = ['.' for i in range(11)]
        else:
            for i, pos in enumerate(hallway):
                self.hallway[i] = pos

        if energyCost is None:
            self.energyCost = 0
        else:
            self.energyCost = energyCost

    def __str__(self):
        string = '\n#############\n'
        string = string + '#'
        for pos in self.hallway:
            string = string + pos
        string = string + '#\n'

        i = self.roomSize - 1
        string = string + '###' + self.firstRoom[i] + '#' + self.secondRoom[i] + '#' + \
                    self.thirdRoom[i] + '#' + self.fourthRoom[i] + '###\n'
        while i > 0:
            i = i - 1
            string = string + '  #' + self.firstRoom[i] + '#' + self.secondRoom[i] + '#' + \
                    self.thirdRoom[i] + '#' + self.fourthRoom[i] + '#  \n'

        string = string + '  #########  \n'

        return string

solveProblem1 = False # Change depending on if solving problem 1 or 2 !
if solveProblem1:
    roomSize = 2
else:
    roomSize = 4

burrow = Burrow(roomSize=roomSize)

line = file.readline()
i = 0
while line != '':

    if i > 1 and i <= roomSize + 1:
        burrow.firstRoom[roomSize + 1 - i]  = line[3]
        burrow.secondRoom[roomSize + 1 - i] = line[5]
        burrow.thirdRoom[roomSize + 1 - i]  = line[7]
        burrow.fourthRoom[roomSize + 1 - i] = line[9]
    i = i + 1

    line = file.readline()

assert (i < 7 and solveProblem1) or (i >= 7 and not solveProblem1), \
    "Input does not agree with problem being solved. Does the solveProblem1 flag agree with the input?"

print(burrow)

def copyPath(dstPath, srcPath):
    for i, pos in enumerate(srcPath.hallway):
        dstPath.hallway[i] = pos
    for i, pos in enumerate(srcPath.firstRoom):
        dstPath.firstRoom[i] = pos
    for i, pos in enumerate(srcPath.secondRoom):
        dstPath.secondRoom[i] = pos
    for i, pos in enumerate(srcPath.thirdRoom):
        dstPath.thirdRoom[i] = pos
    for i, pos in enumerate(srcPath.fourthRoom):
        dstPath.fourthRoom[i] = pos

def createIdString(prevRoom, iPrev, newRoom, iNew, path):
    idString = ""
    for pos in path.hallway:
        idString = idString + pos
    for pos in path.firstRoom:
        idString = idString + pos
    for pos in path.secondRoom:
        idString = idString + pos
    for pos in path.thirdRoom:
        idString = idString + pos
    for pos in path.fourthRoom:
        idString = idString + pos

    room1Start = 11
    room2Start = room1Start + roomSize
    room3Start = room2Start + roomSize
    room4Start = room3Start + roomSize

    if prevRoom == 0:
        idString = idString[:iPrev] + '.' + idString[iPrev+1:]
    elif prevRoom == 1:
        idString = idString[:room1Start+iPrev] + '.' + idString[room1Start+iPrev+1:]
    elif prevRoom == 2:
        idString = idString[:room2Start+iPrev] + '.' + idString[room2Start+iPrev+1:]
    elif prevRoom == 3:
        idString = idString[:room3Start+iPrev] + '.' + idString[room3Start+iPrev+1:]
    elif prevRoom == 4:
        idString = idString[:room4Start+iPrev] + '.' + idString[room4Start+iPrev+1:]

    if newRoom == 0:
        idString = idString[:iNew] + amphipod + idString[iNew+1:]
    elif newRoom == 1:
        idString = idString[:room1Start+iNew] + amphipod + idString[room1Start+iNew+1:]
    elif newRoom == 2:
        idString = idString[:room2Start+iNew] + amphipod + idString[room2Start+iNew+1:]
    elif newRoom == 3:
        idString = idString[:room3Start+iNew] + amphipod + idString[room3Start+iNew+1:]
    elif newRoom == 4:
        idString = idString[:room4Start+iNew] + amphipod + idString[room4Start+iNew+1:]

    return idString

def addNewPath(prevRoom, iPrev, newRoom, iNew, nSteps, path, newPaths, paths, energyMin, seenPaths, amphipod):

    # Check if has been visited before with lower cost
    idString = createIdString(prevRoom, iPrev, newRoom, iNew, path)

    # Calculate energy cost
    if amphipod == 'A':
        stepCost = 1
    elif amphipod == 'B':
        stepCost = 10
    elif amphipod == 'C':
        stepCost = 100
    elif amphipod == 'D':
        stepCost = 1000
    energyCost = path.energyCost + nSteps*stepCost

    if idString in seenPaths and energyCost >= seenPaths[idString]:
        return None
    else:
        seenPaths[idString] = energyCost

    if energyMin is not None:
        if energyCost >= energyMin:
            # A cheaper path has already been found
            # so this path is not interesting and
            # should not be added
            return None

    # Initialize new path
    newPath = Burrow(roomSize=path.roomSize)

    # Copy over from previous path
    copyPath(newPath, path)

    # Remove amphipod from prev position and add to new position
    if prevRoom == 0:
        newPath.hallway[iPrev] = '.'
    elif prevRoom == 1:
        newPath.firstRoom[iPrev] = '.'
    elif prevRoom == 2:
        newPath.secondRoom[iPrev] = '.'
    elif prevRoom == 3:
        newPath.thirdRoom[iPrev] = '.'
    elif prevRoom == 4:
        newPath.fourthRoom[iPrev] = '.'

    if newRoom == 0:
        newPath.hallway[iNew] = amphipod
    elif newRoom == 1:
        newPath.firstRoom[iNew] = amphipod
    elif newRoom == 2:
        newPath.secondRoom[iNew] = amphipod
    elif newRoom == 3:
        newPath.thirdRoom[iNew] = amphipod
    elif newRoom == 4:
        newPath.fourthRoom[iNew] = amphipod

    # Check if the current path is a solution
    isSolution = True
    for currentAmphipod in newPath.firstRoom:
        if currentAmphipod != 'A':
            isSolution = False
            break
    if isSolution:
        for currentAmphipod in newPath.secondRoom:
            if currentAmphipod != 'B':
                isSolution = False
                break
    if isSolution:
        for currentAmphipod in newPath.thirdRoom:
            if currentAmphipod != 'C':
                isSolution = False
                break
    if isSolution:
        for currentAmphipod in newPath.fourthRoom:
            if currentAmphipod != 'D':
                isSolution = False
                break

    if isSolution:
        # If the path is a solution then the path
        # should not be added (since this path is over) 
        # but it's result (i.e. energy cost) should 
        # be returned
        return energyCost

    # Set the energy cost and add the newPath to the paths
    newPath.energyCost = energyCost
    newPaths.append(newPath)

    return None


def checkIfCanVisitDestination(iHall, currentAmphipod, path):

    visitedDestination = False
    iNew = None
    nExtraSteps = None

    if iHall == 2:
        room = path.firstRoom
        desiredAmphipod = 'A'
    elif iHall == 4:
        room = path.secondRoom
        desiredAmphipod = 'B'
    elif iHall == 6:
        room = path.thirdRoom
        desiredAmphipod = 'C'
    elif iHall == 8:
        room = path.fourthRoom
        desiredAmphipod = 'D'

    for i in range(path.roomSize):
        # Check that the amphipod is not blocking another
        # amphipod which is not at its destination
        if i > 0:
            if room[i - 1] != desiredAmphipod:
                break

        # If there is a space open then move there
        if room[i] == '.':
            iNew = i
            nExtraSteps = path.roomSize - i
            visitedDestination = True
            break

    return visitedDestination, iNew, nExtraSteps

def possiblyVisitDestination(iHall, prevRoom, currentAmphipod, path):
    newRoom = 0
    iNew = None
    visitedDestination = False
    nExtraSteps = 0

    if iHall == 2 and currentAmphipod == 'A' and prevRoom != 1:
        newRoom = 1
        visitedDestination, iNew, nExtraSteps = checkIfCanVisitDestination(iHall, currentAmphipod, path)

    elif iHall == 4 and currentAmphipod == 'B' and prevRoom != 2:
        newRoom = 2
        visitedDestination, iNew, nExtraSteps = checkIfCanVisitDestination(iHall, currentAmphipod, path)

    elif iHall == 6 and currentAmphipod == 'C' and prevRoom != 3:
        newRoom = 3
        visitedDestination, iNew, nExtraSteps = checkIfCanVisitDestination(iHall, currentAmphipod, path)

    elif iHall == 8 and currentAmphipod == 'D' and prevRoom != 4:
        newRoom = 4
        visitedDestination, iNew, nExtraSteps = checkIfCanVisitDestination(iHall, currentAmphipod, path)

    return visitedDestination, newRoom, iNew, nExtraSteps

def takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, currentAmphipod):

    if i < path.roomSize - 1:
        # If the current amphipod is blocked by
        # another amphipod in a room then there
        # is no valid path
        if room == 1:
            if path.firstRoom[i+1] != '.':
                return
        if room == 2:
            if path.secondRoom[i+1] != '.':
                return
        if room == 3:
            if path.thirdRoom[i+1] != '.':
                return
        if room == 4:
            if path.fourthRoom[i+1] != '.':
                return
    if i > 0 and room != 0:
        # If the current amphipod is in its
        # destination and the other amphipods
        # in the room is also in the correct
        # destination then this amphipod is done
        if room == 1:
            roomList = path.firstRoom
        elif room == 2:
            roomList = path.secondRoom
        elif room == 3:
            roomList = path.thirdRoom
        elif room == 4:
            roomList = path.fourthRoom

        iCurrent = i
        isDone = True
        while iCurrent >= 0:
            iCurrent = iCurrent - 1
            if roomList[iCurrent] != currentAmphipod:
                isDone = False
                if not isDone:
                    break
        if isDone:
            return


    if room == 0:
        # If currently in hall can only move if moving fully into a room

        iHallInitial = i

        iHall = iHallInitial
        blocked = False
        nSteps = 0
        visitedDestination = False

        # Go left
        while iHall > 0 and not blocked and not visitedDestination:
            newRoom = 0
            iHall = iHall - 1
            nSteps = nSteps + 1

            if path.hallway[iHall] != '.':
                blocked = True
            elif iHall == 2 or iHall == 4 or iHall == 6 or iHall == 8:
                if not visitedDestination:
                    # Can not visit space above room but can possibly visit room
                    visitedDestination, newRoom, iNew, nExtraSteps = possiblyVisitDestination(iHall, room, currentAmphipod, path)
                    if visitedDestination:
                        energyCost = addNewPath(room, i, newRoom, iNew, (nSteps + nExtraSteps), path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                        if energyMin is None:
                            energyMin = energyCost
                        elif energyCost is not None:
                            if energyCost < energyMin:
                                energyMin = energyCost
        # Go right
        iHall = iHallInitial
        blocked = False
        nSteps = 0
        while iHall < 10 and not blocked and not visitedDestination:

            newRoom = 0
            iHall = iHall + 1
            nSteps = nSteps + 1

            if path.hallway[iHall] != '.':
                blocked = True
            elif iHall == 2 or iHall == 4 or iHall == 6 or iHall == 8:
                if not visitedDestination:
                # Can not visit space above room but can possibly visit room
                    visitedDestination, newRoom, iNew, nExtraSteps = possiblyVisitDestination(iHall, room, currentAmphipod, path)
                    if visitedDestination:
                        energyCost = addNewPath(room, i, newRoom, iNew, (nSteps + nExtraSteps), path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                        if energyMin is None:
                            energyMin = energyCost
                        elif energyCost is not None:
                            if energyCost < energyMin:
                                energyMin = energyCost

    else:
        visitedDestination = False

        # Leave room
        nStepsLeaveRoom = path.roomSize - i
 
        if room == 1:
            iHallInitial = 2
        elif room == 2:
            iHallInitial = 4
        elif room == 3:
            iHallInitial = 6
        elif room == 4:
            iHallInitial = 8


        # Go left
        iHall = iHallInitial
        blocked = False
        nSteps = nStepsLeaveRoom
        while iHall > 0 and not blocked:

            newRoom = 0
            iHall = iHall - 1
            nSteps = nSteps + 1

            if iHall == 2 or iHall == 4 or iHall == 6 or iHall == 8:
                if not visitedDestination:
                    # Can not visit space above room but can possibly visit room
                    visitedDestination, newRoom, iNew, nExtraSteps = possiblyVisitDestination(iHall, room, currentAmphipod, path)
                    if visitedDestination:
                        energyCost = addNewPath(room, i, newRoom, iNew, (nSteps + nExtraSteps), path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                        if energyMin is None:
                            energyMin = energyCost
                        elif energyCost is not None:
                            if energyCost < energyMin:
                                energyMin = energyCost
            else:
                # Visit space in hallway if not blocked
                if path.hallway[iHall] != '.':
                    blocked = True
                else:
                    energyCost = addNewPath(room, i, newRoom, iHall, nSteps, path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                    if energyMin is None:
                        energyMin = energyCost
                    elif energyCost is not None:
                        if energyCost < energyMin:
                            energyMin = energyCost

            
        # Go right
        iHall = iHallInitial
        blocked = False
        nSteps = nStepsLeaveRoom
        while iHall < 10 and not blocked:

            newRoom = 0
            iHall = iHall + 1
            nSteps = nSteps + 1

            if iHall == 2 or iHall == 4 or iHall == 6 or iHall == 8:
                if not visitedDestination:
                # Can not visit space above room but can possibly visit room
                    visitedDestination, newRoom, iNew, nExtraSteps = possiblyVisitDestination(iHall, room, currentAmphipod, path)
                    if visitedDestination:
                        energyCost = addNewPath(room, i, newRoom, iNew, (nSteps + nExtraSteps), path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                        if energyMin is None:
                            energyMin = energyCost
                        elif energyCost is not None:
                            if energyCost < energyMin:
                                energyMin = energyCost
            else:
                # Visit space in hallway if not blocked
                if path.hallway[iHall] != '.':
                    blocked = True
                else:
                    energyCost = addNewPath(room, i, newRoom, iHall, nSteps, path, newPaths, paths, energyMin, seenPaths, currentAmphipod)
                    if energyMin is None:
                        energyMin = energyCost
                    elif energyCost is not None:
                        if energyCost < energyMin:
                            energyMin = energyCost

    return energyMin



paths = [burrow]
energyMin = None
seenPaths = {}
while len(paths) != 0:
    newPaths = []

    # Consider all current paths/configurations
    for iPath, path in enumerate(paths):

        # Iterate over all positions to find the amphipod to consider
        for i in range(11):
            if path.hallway[i] != '.':
                room = 0
                amphipod = path.hallway[i]
                energyMinTemp = takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, amphipod)
                if energyMinTemp is not None:
                    energyMin = energyMinTemp

        for i in range(roomSize):
            if path.firstRoom[i] != '.':
                room = 1
                amphipod = path.firstRoom[i]
                energyMinTemp = takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, amphipod)
                if energyMinTemp is not None:
                    energyMin = energyMinTemp

        for i in range(roomSize):
            if path.secondRoom[i] != '.':
                room = 2
                amphipod = path.secondRoom[i]
                energyMinTemp = takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, amphipod)
                if energyMinTemp is not None:
                    energyMin = energyMinTemp

        for i in range(roomSize):
            if path.thirdRoom[i] != '.':
                room = 3
                amphipod = path.thirdRoom[i]
                energyMinTemp = takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, amphipod)
                if energyMinTemp is not None:
                    energyMin = energyMinTemp

        for i in range(roomSize):
            if path.fourthRoom[i] != '.':
                room = 4
                amphipod = path.fourthRoom[i]
                energyMinTemp = takeAllNewValidPaths(room, i, path, paths, newPaths, energyMin, seenPaths, amphipod)
                if energyMinTemp is not None:
                    energyMin = energyMinTemp

    paths = newPaths


if solveProblem1:
    print("Answer problem 1:", energyMin)
else:
    print("Answer problem 2:", energyMin)

file.close()
