import re

def dictionary(file):
    dic = {}
    i = 0
    for line in file:
        string = re.sub(r'\s+', '', line)
        if(string.rsplit(';', 1)[0] != ''):
            dic[string.rsplit(';', 1)[0]] = i
            i += 1

    return dic

def reg(file):
    i = 0
    r = {}
    for line in file:
        string = re.sub(r'\s+', '', line)
        r[string] = i
        i += 1

    return r