import re

file = open("day17/input.txt", "r")
line = file.readline()
print(line)
matches = re.findall(r'-?\d+', line)
minX = int(matches[0])
maxX = int(matches[1])
minY = int(matches[2])
maxY = int(matches[3])

# Since x and y are completely decoupled, if there exista a starting x-velocity in which
# the probe reaches a 0 x-velocity in the x-range of the target area then y can be 
# considered independently

xVelocity = 0
finalXPos = xVelocity*(xVelocity + 1)/2
while finalXPos < minX or finalXPos > maxX:
    xVelocity = xVelocity + 1
    finalXPos = xVelocity*(xVelocity + 1)/2

# The y-velocity will be the (same + 1) but negative as starting velocity once y reaches 0
# on the downward path. Therefore yVelocity can be abs(minY)-1 as maximum
yVelocity = abs(minY) - 1
maxYPosition =  yVelocity*(yVelocity + 1)/2

print("Answer problem 1:", maxYPosition)


# Possible initial velocity ranges
minXV = xVelocity       # minimum x-velocity to reach target in x-domain
minYV = minY            # minimum y-velocty since it reaches maximum target in y-domain in one step
maxXV = maxX           # maximum x-velcity since it reaches maximum target in x-domain in one step
maxYV = abs(minY) - 1   # same reasoning as in problem 1


distinctInitialVelocities = []

# Simulate all possible initial velocities
for xvInit in range(minXV, maxXV+1):
    for yvInit in range(minYV, maxYV+1):

        xPos = 0
        yPos = 0
        xVel = xvInit
        yVel = yvInit

        reachedTargetArea = False

        while yPos > minY:
            xPos = xPos + xVel
            yPos = yPos + yVel
            if xVel > 0:
                xVel = xVel - 1
            elif xVel < 0:
                xVel = xVel + 1
            yVel = yVel - 1

            if xPos >= minX and xPos <= maxX and yPos >= minY and yPos <= maxY:
                reachedTargetArea = True
                break
        
        if reachedTargetArea:
            distinctInitialVelocities.append((xvInit, yvInit))

print("Answer problem 2:", len(distinctInitialVelocities))

file.close()