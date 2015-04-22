# -*- coding: utf-8 -*-

cSpeedData = open("CSpeedData.txt","r")
parsedData = open("parsedData.txt","w")
speedPairs = {}
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
        else:
            temp = speedValue
            speedValue /= 1024
            bValue = temp % 1024
            speedStr = lineStr[0] + ";" + str(bValue) + "KB/s\n"
        #parsedData.write(speedStr)
        speedPairs[lineStr[0]] = int(speed)

print "Before...\n"
print speedPairs
sorted(speedPairs.iteritems(), key=lambda t:t[1])
print "After...\n"
print speedPairs

for k in speedPairs:
    parsedData.write(k)
    parsedData.write(";")
    parsedData.write(str(speedPairs[k]))
    parsedData.write("KB/s\n")

cSpeedData.close()
parsedData.flush()
parsedData.close()

