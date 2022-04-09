import re

file = open("day21/input.txt", "r")

startingPosPlayer1 = None
startingPosPlayer2 = None

line = 'temp'
while line != '':
    line = file.readline()
    print(line)

    if line == '\n' or line == '':
        continue

    matches = re.findall(r'\d+', line)

    if startingPosPlayer1 is None:
        startingPosPlayer1 = int(matches[1])
    else:
        startingPosPlayer2 = int(matches[1])



nextDeterministicDieRoll = 1
nTimesDieRolled = 0
player1Score = 0
player2Score = 0
player1Pos = startingPosPlayer1
player2Pos = startingPosPlayer2
playerTurn = 1

while player1Score < 1000 and player2Score < 1000:

    dieRollSum = 0

    # Roll three times
    for i in range(3):
        dieRoll = nextDeterministicDieRoll
        dieRollSum = dieRollSum + dieRoll
        nextDeterministicDieRoll = nextDeterministicDieRoll % 100 + 1
        nTimesDieRolled = nTimesDieRolled + 1


    if playerTurn == 1:
        player1Pos = (player1Pos + dieRollSum - 1) % 10 + 1
        player1Score = player1Score + player1Pos
    else:
        player2Pos = (player2Pos + dieRollSum - 1) % 10 + 1
        player2Score = player2Score + player2Pos

    playerTurn = playerTurn % 2 + 1

if player1Score >= 1000:
    answer = player2Score*nTimesDieRolled
else:
    answer = player1Score*nTimesDieRolled

print("Answer problem 1:", answer)



stateSpaceCount = [[[[[0 for iPlayer2ScoreCount in range(21)] for iPlayer1ScoreCount in range(21)] for iPosPlayer2 in range(10)] for iPosPlayer1 in range(10)] for iTurn in range(2)]
stateSpaceCount[0][startingPosPlayer1-1][startingPosPlayer2-1][0][0] = 1

nPlayer1Wins = 0
nPlayer2Wins = 0
allGamesFinished = False
while not allGamesFinished:
    newStateSpaceCount = [[[[[0 for iPlayer2ScoreCount in range(21)] for iPlayer1ScoreCount in range(21)] for iPosPlayer2 in range(10)] for iPosPlayer1 in range(10)] for iTurn in range(2)]
    nGamesInPlay = 0

    allGamesFinished = True
    for iTurn in range(2):
        for iPosPlayer1 in range(1, 11):
            for iPosPlayer2 in range(1, 11):
                for iPlayer1ScoreCount in range(21):
                    for iPlayer2ScoreCount in range(21):
                        
                        count = stateSpaceCount[iTurn][iPosPlayer1-1][iPosPlayer2-1][iPlayer1ScoreCount][iPlayer2ScoreCount]
                        if count == 0:
                            continue
                        allGamesFinished = False
                        nGamesInPlay = nGamesInPlay + count
                        
                        if iTurn == 0:
                            for firstRoll in range(1, 4):
                                for secondRoll in range(1, 4):
                                    for thirdRoll in range(1, 4):
                                        dieRollSum = firstRoll + secondRoll + thirdRoll

                                        newIPosPlayer1 = (iPosPlayer1 + dieRollSum - 1) % 10 + 1
                                        if iPlayer1ScoreCount + newIPosPlayer1 < 21:
                                            newStateSpaceCount[1][newIPosPlayer1-1][iPosPlayer2-1][iPlayer1ScoreCount+newIPosPlayer1][iPlayer2ScoreCount] = \
                                                newStateSpaceCount[1][newIPosPlayer1-1][iPosPlayer2-1][iPlayer1ScoreCount+newIPosPlayer1][iPlayer2ScoreCount] + count
                                        else:
                                            nPlayer1Wins = nPlayer1Wins + count
                        else:
                            for firstRoll in range(1, 4):
                                for secondRoll in range(1, 4):
                                    for thirdRoll in range(1, 4):
                                        dieRollSum = firstRoll + secondRoll + thirdRoll

                                        newIPosPlayer2 = (iPosPlayer2 + dieRollSum - 1) % 10 + 1
                                        if iPlayer2ScoreCount + newIPosPlayer2 < 21:
                                            newStateSpaceCount[0][iPosPlayer1-1][newIPosPlayer2-1][iPlayer1ScoreCount][iPlayer2ScoreCount+newIPosPlayer2] = \
                                                newStateSpaceCount[0][iPosPlayer1-1][newIPosPlayer2-1][iPlayer1ScoreCount][iPlayer2ScoreCount+newIPosPlayer2] + count
                                        else:
                                            nPlayer2Wins = nPlayer2Wins + count
    
    stateSpaceCount = newStateSpaceCount
    print(nGamesInPlay)


if nPlayer1Wins > nPlayer2Wins:
    print("Answer problem 2:", nPlayer1Wins)
else:
    print("Answer problem 2:", nPlayer2Wins)

file.close()