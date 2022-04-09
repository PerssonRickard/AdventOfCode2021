

file = open("day16/input.txt", "r")
hexString = file.readline()
print(hexString)

binary = [i for i in range(4*len(hexString))]

# Map hexadecimal to binary
for i in range(len(hexString)):
    if hexString[i] == '0':
        binary[4*i:4*(i+1)] = [0, 0, 0, 0]
    elif hexString[i] == '1':   
        binary[4*i:4*(i+1)] = [0, 0, 0, 1]
    elif hexString[i] == '2':   
        binary[4*i:4*(i+1)] = [0, 0, 1, 0]
    elif hexString[i] == '3':   
        binary[4*i:4*(i+1)] = [0, 0, 1, 1]
    elif hexString[i] == '4':   
        binary[4*i:4*(i+1)] = [0, 1, 0, 0]
    elif hexString[i] == '5':   
        binary[4*i:4*(i+1)] = [0, 1, 0, 1]
    elif hexString[i] == '6':   
        binary[4*i:4*(i+1)] = [0, 1, 1, 0]
    elif hexString[i] == '7':   
        binary[4*i:4*(i+1)] = [0, 1, 1, 1]
    elif hexString[i] == '8':   
        binary[4*i:4*(i+1)] = [1, 0, 0, 0]
    elif hexString[i] == '9':   
        binary[4*i:4*(i+1)] = [1, 0, 0, 1]
    elif hexString[i] == 'A':   
        binary[4*i:4*(i+1)] = [1, 0, 1, 0]
    elif hexString[i] == 'B':   
        binary[4*i:4*(i+1)] = [1, 0, 1, 1]
    elif hexString[i] == 'C':   
        binary[4*i:4*(i+1)] = [1, 1, 0, 0]
    elif hexString[i] == 'D':   
        binary[4*i:4*(i+1)] = [1, 1, 0, 1]
    elif hexString[i] == 'E':   
        binary[4*i:4*(i+1)] = [1, 1, 1, 0]
    elif hexString[i] == 'F':   
        binary[4*i:4*(i+1)] = [1, 1, 1, 1]

def binaryToDec(binaryNumber):
    dec = 0
    powerOfTwo = 1
    for i in range(len(binaryNumber), 0, -1):
        dec = dec + binaryNumber[i-1]*powerOfTwo
        powerOfTwo = powerOfTwo*2

    return dec

class packet:
    def __init__(self, data):
        self.version = binaryToDec(data[0:3])
        self.typeID = binaryToDec(data[3:6])
        self.value = -1
        self.data = data[6:]
        self.subpackets = []

def getSubPacket(binaryData, lengthTypeID, nReadBits):
    currentPacket = packet(binaryData[nReadBits:]) # Skip data that has previously been read
    version = currentPacket.version
    typeID = currentPacket.typeID
    data = currentPacket.data
    packetLength = 6 # The header has size 6

    if typeID == 4:
        # Literal value
        literalValueBinary = []
        notLastGroup = 1

        i = 0
        while notLastGroup:
            notLastGroup = data[i*5]
            for y in range(4):
                literalValueBinary.append(data[i*5 + 1 + y])
            i = i + 1
            packetLength = packetLength + 5

        currentPacket.value = binaryToDec(literalValueBinary)
        #while (packetLength % 4 != 0): # The binary number should be a multiple of four bits. (Only applits to outermost packet?)
        #    packetLength = packetLength + 1

        if lengthTypeID == 0:
            nSubPacketsReadOrNBitsRead = packetLength
        else:
            nSubPacketsReadOrNBitsRead = 1
        return currentPacket, nSubPacketsReadOrNBitsRead, packetLength
        
    else:
       # operator
        currentLengthTypeID = data[0]
        packetLength = packetLength + 1
        subPacketsBitLength = -1
        numberOfSubPackets = -1
        subPacketsData = -1

        nBitsRead = 0

        if currentLengthTypeID == 0:
            subPacketsBitLength = binaryToDec(data[1:16])
            subPacketsData = data[16:]
            packetLength = packetLength + 15

            while nBitsRead < subPacketsBitLength:
                subpacket, nReadBits, nBitsReadCurrent = getSubPacket(subPacketsData, currentLengthTypeID, nBitsRead)
                currentPacket.subpackets.append(subpacket)
                nBitsRead = nBitsRead + nBitsReadCurrent
        else:
            numberOfSubPackets = binaryToDec(data[1:12])
            subPacketsData = data[12:]
            packetLength = packetLength + 11

            nSubPacketsRead = 0
            while nSubPacketsRead < numberOfSubPackets:
                subpacket, nSubPacketsReadCurrent, nBitsReadCurrent = getSubPacket(subPacketsData, currentLengthTypeID, nBitsRead)
                currentPacket.subpackets.append(subpacket)
                nSubPacketsRead = nSubPacketsRead + nSubPacketsReadCurrent
                nBitsRead = nBitsRead + nBitsReadCurrent

    if lengthTypeID == 0:
        nSubPacketsReadOrNBitsRead = nBitsRead + packetLength
    else:
        nSubPacketsReadOrNBitsRead = 1

    return currentPacket, nSubPacketsReadOrNBitsRead, nBitsRead + packetLength


initialPacket = packet(binary)
stringBinary = [str(x) for x in binary]
print("".join(stringBinary))
currentPacket = initialPacket 
typeID = currentPacket.typeID
data = currentPacket.data


if typeID == 4:
    # Literal value
    getSubPacket(binary, -1, 0, 0)
else:
    # operator
    lengthTypeID = data[0]
    subPacketsBitLength = -1
    numberOfSubPackets = -1
    subPacketsData = -1

    nBitsRead = 0

    if lengthTypeID == 0:
        subPacketsBitLength = binaryToDec(data[1:16])
        subPacketsData = data[16:]

        while nBitsRead < subPacketsBitLength:
            subpacket, nBitsReadCurrent, nBitsReadCurrent = getSubPacket(subPacketsData, lengthTypeID, nBitsRead)
            currentPacket.subpackets.append(subpacket)
            nBitsRead = nBitsRead + nBitsReadCurrent
    else:
        numberOfSubPackets = binaryToDec(data[1:12])
        subPacketsData = data[12:]

        nSubPacketsRead = 0
        while nSubPacketsRead < numberOfSubPackets:
            subpacket, nSubPacketsReadCurrent, nBitsReadCurrent = getSubPacket(subPacketsData, lengthTypeID, nBitsRead)
            currentPacket.subpackets.append(subpacket)
            nSubPacketsRead = nSubPacketsRead + nSubPacketsReadCurrent
            nBitsRead = nBitsRead + nBitsReadCurrent


sumVersionNumbers = 0
def printPackets(packet):
    global sumVersionNumbers
    print(packet.version)
    sumVersionNumbers = sumVersionNumbers + packet.version
    for i in range(len(packet.subpackets)):
        printPackets(packet.subpackets[i])

printPackets(initialPacket)

print("Answer problem 1:", sumVersionNumbers)

def getPacketValue(packet):
    if (packet.value != -1):
        return packet.value
    
    value = 0

    for i, subpacket in enumerate(packet.subpackets):
        if packet.typeID == 0:
            value = value + getPacketValue(subpacket)
        elif packet.typeID == 1:
            if i == 0:
                value = getPacketValue(subpacket)
            else:
                value = value*getPacketValue(subpacket)
        elif packet.typeID == 2:
            if i == 0:
                value = getPacketValue(subpacket)
            else:
                if getPacketValue(subpacket) < value:
                    value = getPacketValue(subpacket)
        elif packet.typeID == 3:
            if i == 0:
                value = getPacketValue(subpacket)
            else:
                if getPacketValue(subpacket) > value:
                    value = getPacketValue(subpacket)
        elif packet.typeID == 5:
            if getPacketValue(packet.subpackets[i]) > getPacketValue(packet.subpackets[i+1]):
                value = 1
            else:
                value = 0
            break
        elif packet.typeID == 6:
            if getPacketValue(packet.subpackets[i]) < getPacketValue(packet.subpackets[i+1]):
                value = 1
            else:
                value = 0
            break
        elif packet.typeID == 7:
            if getPacketValue(packet.subpackets[i]) == getPacketValue(packet.subpackets[i+1]):
                value = 1
            else:
                value = 0
            break
    packet.value = value
    return value
        
value = getPacketValue(initialPacket)

print("Answer problem 2:", value)

file.close()