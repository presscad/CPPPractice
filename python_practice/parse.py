
# -*- coding: utf-8 -*-

cSpeedData = open("CSpeedData.txt","r")
parsedData = open("parsedData.txt","w")
for line in cSpeedData:
    lineStr = line.split(";")
    if len(lineStr) != 2:
        continue
    elif len(lineStr[0]) == 0 or len(lineStr[1]) == 0:
        continue
    elif lineStr[1] == "-1B/s\n" :
        continue
    else:
        pos = lineStr[1].find("B")
        speed = lineStr[1][:pos]
        speedValue = int(speed)
        if int(speedValue) > 1024:
            speedValue /= 1024
        speedStr = lineStr[0] + ";" + str(speedValue) + "KB/s\n"
        parsedData.write(speedStr)

cSpeedData.close()
parsedData.flush()
parsedData.close()

