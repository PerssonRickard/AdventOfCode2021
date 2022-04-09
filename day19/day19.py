import re

file = open("day19/input.txt", "r")

#matches = re.findall(r'-?\d+', line)

scanners = []

line = 'temp'
while line != '':
    line = file.readline()
    print(line)
    scannerMatch = re.search(r'scanner \d?', line)
    if scannerMatch is not None:
        temp = re.search(r'\d{1,2}', line)
        scanners.append([])
    elif line != '\n' and line != '':
        coordinates = re.split(r',', line.rstrip())
        scanners[-1].append([None for i in range(3)])
        for i in range(3):
            coordinate = coordinates[i]
            scanners[-1][-1][i] = int(coordinate)



def rotateToZeroSystem(coordinates, rotationAndUp, iScanner):
    iRotation = rotationAndUp[iScanner][0]
    iUp = rotationAndUp[iScanner][1]

    rotatedCoordinates = rotateCoordinates(coordinates, iRotation)
    zeroSystemCoordinates = switchUpDirection(rotatedCoordinates, iUp)

    return zeroSystemCoordinates

def rotateCoordinates(coordinates, iRotation):
    rotatedCoordinates = [[None, None, None] for i in range(len(coordinates))]

    for i, coordinate in enumerate(coordinates):
        if iRotation == 0:
            # positive x-axis, do nothing
            rotatedCoordinates[i][0] = coordinate[0]
            rotatedCoordinates[i][1] = coordinate[1]
            rotatedCoordinates[i][2] = coordinate[2]
        elif iRotation == 1:
            # negative x-axis, x = -x, y = -y
            rotatedCoordinates[i][0] = -coordinate[0]
            rotatedCoordinates[i][1] = -coordinate[1]
            rotatedCoordinates[i][2] = coordinate[2]
        elif iRotation == 2:
            # positive y-axis, x = -y, y = x
            rotatedCoordinates[i][0] = -coordinate[1]
            rotatedCoordinates[i][1] = coordinate[0]
            rotatedCoordinates[i][2] = coordinate[2]
        elif iRotation == 3:
            # negative y-axis, x = y, y = -x
            rotatedCoordinates[i][0] = coordinate[1]
            rotatedCoordinates[i][1] = -coordinate[0]
            rotatedCoordinates[i][2] = coordinate[2]
        elif iRotation == 4:
            # positive z-axis, x = -z, z = x
            rotatedCoordinates[i][0] = -coordinate[2]
            rotatedCoordinates[i][1] = coordinate[1]
            rotatedCoordinates[i][2] = coordinate[0]
        elif iRotation == 5:
            # negative z-axis, x = z, z = -x
            rotatedCoordinates[i][0] = coordinate[2]
            rotatedCoordinates[i][1] = coordinate[1]
            rotatedCoordinates[i][2] = -coordinate[0]

    return rotatedCoordinates

def switchUpDirection(coordinates, iUp):
    switchedCoordinates = [[None, None, None] for i in range(len(coordinates))]

    for i, coordinate in enumerate(coordinates):
        if iUp == 0:
            # rotate y and z axis 0 degrees to the left around x axis, do nothing
            switchedCoordinates[i][0] = coordinate[0]
            switchedCoordinates[i][1] = coordinate[1]
            switchedCoordinates[i][2] = coordinate[2]
        elif iUp == 1:
            # rotate y and z axis 90 degrees to the left around x axis,, y = z, z = -y
            switchedCoordinates[i][0] = coordinate[0]
            switchedCoordinates[i][1] = coordinate[2]
            switchedCoordinates[i][2] = -coordinate[1]
        elif iUp == 2:
            # rotate y and z axis 180 degrees to the left around x axis,y = -y, z = -z
            switchedCoordinates[i][0] = coordinate[0]
            switchedCoordinates[i][1] = -coordinate[1]
            switchedCoordinates[i][2] = -coordinate[2]
        elif iUp == 3:
            # rotate y and z axis 270 degrees to the left around x axis, y = -z, z = y
            switchedCoordinates[i][0] = coordinate[0]
            switchedCoordinates[i][1] = -coordinate[2]
            switchedCoordinates[i][2] = coordinate[1]

    return switchedCoordinates

def checkIfConsistent(coordinates1, coordinates2):
    for coordinate2 in coordinates2:
        for coordinate1 in coordinates1:
            # Let coordinate1 be assumed to be consistent
            nConsistent = 0
            deltaX = coordinate2[0] - coordinate1[0]
            deltaY = coordinate2[1] - coordinate1[1]
            deltaZ = coordinate2[2] - coordinate1[2]

            for coordinate1_2 in coordinates1:
                # Check if other coordinates are consistent
                if [coordinate1_2[0]+deltaX, coordinate1_2[1]+deltaY, coordinate1_2[2]+deltaZ] in coordinates2:
                    nConsistent = nConsistent + 1
                    if nConsistent >= 12:
                        return True, deltaX, deltaY, deltaZ

    return False, None, None, None


def findScanner(coordinates1, coordinates2):

    # Try all 24 orientations and see if at least 12 coordinates agree

    for iRotation in range(6):
        rotatedCoordinates = rotateCoordinates(coordinates2, iRotation)
        for iUp in range(4):
            candidateCoordinates = switchUpDirection(rotatedCoordinates, iUp)
            conistent, deltaX, deltaY, deltaZ = checkIfConsistent(coordinates1, candidateCoordinates)
            if conistent:
                return conistent, iRotation, iUp, deltaX, deltaY, deltaZ, candidateCoordinates

    return False, None, None, None, None, None, None


# Since the absolute coordinate system is from the perspective of scanner 0
# it can be considered found
foundScanners = [0]
rotationAndUp = [[None, None] for i in range(len(scanners))]
rotationAndUp[0][0] = 0
rotationAndUp[0][1] = 0

scannerPositions = [[None, None, None] for i in range(len(scanners))]
scannerPositions[0][0] = 0
scannerPositions[0][1] = 0
scannerPositions[0][2] = 0

beaconPositions = [x for x in scanners[0]]

while len(foundScanners) < len(scanners):
    
    for foundScanner in foundScanners:

        coordinates1 = rotateToZeroSystem(scanners[foundScanner], rotationAndUp, foundScanner)
        #coordinates1 = scanners[foundScanner]

        for i in range(len(scanners)):
            if i in foundScanners:
                continue

            coordinates2 = scanners[i]

            conistent, iRotation, iUp, deltaX, deltaY, deltaZ, coordinates = findScanner(coordinates1, coordinates2)
            if conistent:
                foundScanners.append(i)
                rotationAndUp[i][0] = iRotation
                rotationAndUp[i][1] = iUp

                scannerPositions[i][0] = scannerPositions[foundScanner][0] - deltaX
                scannerPositions[i][1] = scannerPositions[foundScanner][1] - deltaY
                scannerPositions[i][2] = scannerPositions[foundScanner][2] - deltaZ

                for coordinate in coordinates:
                    beaconPos = [scannerPositions[i][0] + coordinate[0], scannerPositions[i][1] + coordinate[1], scannerPositions[i][2] + coordinate[2]]
                    if beaconPos not in beaconPositions:
                        beaconPositions.append(beaconPos)
                break



print("Answer problem 1:", len(beaconPositions))


largestDistance = 0
for i in range(len(scannerPositions)):
    for j in range(i+1, len(scannerPositions)):
        manhattanDistance = abs(scannerPositions[i][0] - scannerPositions[j][0]) + \
            abs(scannerPositions[i][1] - scannerPositions[j][1]) + \
            abs(scannerPositions[i][2] - scannerPositions[j][2])

        if manhattanDistance > largestDistance:
            largestDistance = manhattanDistance

print("Answer problem 2:", largestDistance)

file.close()