#!/usr/bin/python
#
# Converts a command log exported from WTViewer
# to a comma-separated value table
#

log = open("capture commands.log","r")
csv = open("capture commands.csv", "w")

# Read first line
line = log.readline()
previous_type = ""
while line:
    if line[:10].find("Send") == 0:
        s = line.split(",")
        cmd = s[1][:20].strip()
        if previous_type == "Send":
            csv.write("\n")
        csv.write(cmd+";")
        previous_type = "Send"
    elif line[:10].find("Receive") == 0:
        s = line.split(",")
        cmd = s[1][:20].strip()
        if previous_type == "":
            csv.write(";")
        csv.write(cmd+";\n")
        previous_type = "Receive"
    
    # Read next line
    line = log.readline()

log.close()
csv.close()
