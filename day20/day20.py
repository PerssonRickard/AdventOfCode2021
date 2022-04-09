
file = open("day20/input.txt", "r")

enhancementAlgorithm = file.readline().rstrip()

#print("algorithm:", enhancementAlgorithm)

def printImage(image):
    for y in range(len(image)):
        row = ''
        for x in range(len(image[0])):
            row = row + mapBinaryToChar(image[y][x])
        print(row)

def mapCharToBinary(character):
    if character == '.':
        return 0
    elif character == '#':
        return 1
    else:
        print("ERROR!")
        return None

def mapBinaryToChar(binary):
    if binary == 0:
        return '.'
    elif binary == 1:
        return '#'
    else:
        print("ERROR!")
        return None

# Read the image input
image = []
line = 'temp'
while line != '':
    line = file.readline()
    if line == '\n' or line == '':
        continue
    #print(line)
    image.append(list(map(mapCharToBinary, line.rstrip())))

def binaryToDec(binaryNumber):
    dec = 0
    powerOfTwo = 1

    for i in range(len(binaryNumber)-1, -1, -1):
        dec = dec + binaryNumber[i]*powerOfTwo
        powerOfTwo = powerOfTwo*2

    return dec

def getIndexFrom3Times3Grid(x, y, image):
    binaryNumber = [None for i in range(9)]

    # Iterate over the 3x3 grid centered at x, y
    i = 0
    for yOffset in range(-1, 2):
        for xOffset in range(-1, 2):
            binaryNumber[i] = image[y + yOffset][x + xOffset]
            i = i + 1

    dec = binaryToDec(binaryNumber)

    return dec

def applyAlgorithm(image, enhancementAlgorithm, paddingValue, algorithmZeroIndexValue):
    newImage = [[paddingValue for x in range(len(image[0])+2)] for y in range(len(image)+2)]

    if algorithmZeroIndexValue == 1:
        paddingValue = (paddingValue + 1) % 2
    
    # Pad the input image with paddingValue
    image.insert(0, [paddingValue for x in range(len(image[0]))])
    image.insert(0, [paddingValue for x in range(len(image[0]))])
    image.append([paddingValue for x in range(len(image[0]))])
    image.append([paddingValue for x in range(len(image[0]))])
    for row in image:
        row.insert(0, paddingValue)
        row.insert(0, paddingValue)
        row.append(paddingValue)
        row.append(paddingValue)
    
    # Apply the algorithm to each pixel in the original input image
    for y in range(1, len(image)-1):
        for x in range(1, len(image[0])-1):
            index = getIndexFrom3Times3Grid(x, y, image)
            newImage[y-1][x-1] = mapCharToBinary(enhancementAlgorithm[index])

    return newImage


printImage(image)
print()
algorithmZeroIndexValue = mapCharToBinary(enhancementAlgorithm[0])
paddingValue = algorithmZeroIndexValue
for i in range(2):
    image = applyAlgorithm(image, enhancementAlgorithm, paddingValue, algorithmZeroIndexValue)
    if algorithmZeroIndexValue == 1:
        paddingValue = (paddingValue + 1) % 2
    printImage(image)
    print()

nLitPixels = 0
for y in range(len(image)):
    for x in range(len(image[0])):
        if image[y][x] == 1:
            nLitPixels = nLitPixels + 1

print("Answer problem 1:", nLitPixels)

# The image has already been enhanced 2 times so do it 48 more times to reach 50
for i in range(48):
    image = applyAlgorithm(image, enhancementAlgorithm, paddingValue, algorithmZeroIndexValue)
    if algorithmZeroIndexValue == 1:
        paddingValue = (paddingValue + 1) % 2

nLitPixels = 0
for y in range(len(image)):
    for x in range(len(image[0])):
        if image[y][x] == 1:
            nLitPixels = nLitPixels + 1

print("Answer problem 2:", nLitPixels)

file.close()