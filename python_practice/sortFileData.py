# -*- coding: utf-8 -*-

cSpeedData = open("CSpeedData.txt","r")
parsedData = open("parsedData.txt","w")
speedPairs = {}
for line in cSpeedData:
    lineStr = line.split(";")
    print lineStr
    if len(lineStr) != 3:
        continue
    elif len(lineStr[0]) == 0 or len(lineStr[1]) == 0:
        continue
    elif lineStr[2] == "-1B/s\n" :
        continue
    else:
        pos = lineStr[2].find("B")
        speed = lineStr[2][:pos]
        speedPairs[lineStr[0]+";"+lineStr[1]] = int(speed)

from operator import itemgetter
sortedPairs = sorted(speedPairs.items(), key=itemgetter(1))

for k in sortedPairs:
    parsedData.write(k[0])
    parsedData.write(";")
    value = k[1]
    speed = ""
    if value > (1024*1024):
        value /= (1024*1024)
        speed = str(value) + "MB/s\n"
    elif value > 1024:
        value /= 1024
        speed = str(value) + "KB/s\n"
    else:
        value %= 1024
        speed = str(value) + "B/s\n"

    parsedData.write(speed)
cSpeedData.close()
parsedData.flush()
parsedData.close()

