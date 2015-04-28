# -*- coding: utf-8 -*-

cSpeedData = open("CSpeedData.txt","r")
parsedData = open("parsedData.txt","w")
speedPairs = {}
for line in cSpeedData:
    lineStr = line.split(";")
    if len(lineStr) == 3:
        pos = lineStr[2].find("B")
        speed = lineStr[2][:pos]
        speedPairs[lineStr[1]] = int(speed)
    elif len(lineStr) == 2:
        pos = lineStr[1].find("B")
        speed = lineStr[1][:pos]
        speedPairs[lineStr[0]] = int(speed)
    else:
		continue

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
    elif value == -1:
        speed = str(value) + "B/s\n"
    else:
        value %= 1024
        speed = str(value) + "B/s\n"

    parsedData.write(speed)
cSpeedData.close()
parsedData.flush()
parsedData.close()

