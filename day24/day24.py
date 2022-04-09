import re
import math

file = open("day24/input.txt", "r")


# Store all instructions
line = 'temp'
iInput = -1
instructions = []
pushPullPairs = []
while line != '':
    line = file.readline()
    if line == '':
        break
    #print(line)

    match = re.findall('\S+', line)

    if match[0] == 'inp':
        iInput = iInput + 1
        instructions.append([[], []])
        iInstruction = 0

    instructions[iInput][0].append(match)

    if iInstruction == 4:
        temp = int(match[2])
        instructions[iInput][1].append(temp)
        if temp == 1:
            # Push
            pushPullPairs.append([iInput, None])
        else:
            # Pull
            for pushPullPair in reversed(pushPullPairs):
                if pushPullPair[1] is None:
                    pushPullPair[1] = iInput
                    break

    elif iInstruction == 5:
        instructions[iInput][1].append(int(match[2]))
    elif iInstruction == 15:
        instructions[iInput][1].append(int(match[2]))
    iInstruction = iInstruction + 1


file.close()

modelNumberMax = [None for i in range(14)]
modelNumberMin = [None for i in range(14)]

# Find the model numbers by ensuring that there are
# 7 pulls since z will only be zero in that case.
# Choose the digits that give the largest/smallest
# model number while confirming to the constraints
for pushPullPair in pushPullPairs:

    pushedIndex = pushPullPair[0]
    pulledIndex = pushPullPair[1]

    currentPulledValue = instructions[pushedIndex][1][2]
    currentValue = instructions[pulledIndex][1][1]

    currentSum = currentPulledValue + currentValue

    if currentSum >= 0:
        pushedValueMax = 9 - currentSum
        pulledValueMax = 9

        pushedValueMin = 1
        pulledValueMin = 1 + currentSum
    else:
        pushedValueMax = 9
        pulledValueMax = 9 + currentSum

        pushedValueMin = 1 - currentSum
        pulledValueMin = 1

    modelNumberMax[pushedIndex] = str(pushedValueMax)
    modelNumberMax[pulledIndex] = str(pulledValueMax)

    modelNumberMin[pushedIndex] = str(pushedValueMin)
    modelNumberMin[pulledIndex] = str(pulledValueMin)

inputModelNumberMax = "".join(modelNumberMax)
inputModelNumberMin = "".join(modelNumberMin)


# Confirm that the model numbers are valid
for inputModelNumber in [inputModelNumberMax, inputModelNumberMin]:
    w = 0
    x = 0
    y = 0
    z = 0
    for index in range(14):


        p1 = instructions[index][1][0]
        p2 = instructions[index][1][1]
        p3 = instructions[index][1][2]

        w = int(inputModelNumber[index])
        
        # There are 7 inputs where p1 is 1 and there is no way of avoiding an increase for z
        # and the rest of the 7 inputs p1 is 26 and all of them must therefore be used to 
        # reduce z. Also p3 is always < 17 which means that w + p3 < 26 so we never have to
        # worry that w + p3 will add an extra multiple of 26.


        # If p1 is 26 then choose digit so that (z % 26 + p2) == w. z will be given by the
        # previous input and p3: z = previousZ * 26 + previousW + previousP3 => (z % 26 + p2) = 
        # previousW + previousP3 + p2

        if (z % 26 + p2) != w:
            temp = z / p1 # p1 is either 1 or 26, in all cases where p1 is 1 then p2 is > 9
            z = math.floor(temp) if temp >= 0 else math.ceil(temp)

            z = z * 26 + w + p3 # both w and p3 is always non-negative
        else:
            temp = z / p1 # p1 is either 1 or 26, in all cases where p1 is 1 then p2 is > 9
            z = math.floor(temp) if temp >= 0 else math.ceil(temp)

    if z == 0:
        print("Valid!", inputModelNumber)

