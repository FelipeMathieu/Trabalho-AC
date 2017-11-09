import re

def getValueOfLabel(lista, value):
    for c in lista:
        if c[0] == value:
            return c[1]
    return 0

def codificador(file, dicionario, registradores):
    comandos = []
    auxComandos = []
    isMov = False
    auxMov = ""
    registrador_registrador = 0
    addr = 0
    immediate = 0
    auxCount = 0
    isRegAddres = False
    label = []
    linha = 0
    auxValueOfLabel = 0
    

    for line in file:
        string = re.sub(r'\n', '', line)
        string = string.replace(',', ' ')
        commands = string.split(" ")
        
        if "MOV" in commands:
            isMov = True
        else:
            isMov = False

        for c in commands:
            if not isMov:
                if c in dicionario:
                    comandos.append(dicionario[c])
                elif c in registradores:
                    comandos.append(int(registradores[c]))
                elif '[' in c:
                    comandos.append(int(c.strip("[]")))
                elif c != '':
                    if c.isdigit():
                        comandos.append(int(c))
                    else:
                        auxValueOfLabel = getValueOfLabel(label, c)
                        if auxValueOfLabel == 0:
                            label.append((c, linha + 5000))
                            comandos.append(linha + 5000)
                        else:
                            comandos.append(auxValueOfLabel)
            else:
                if c == "MOV":
                    auxComandos.append(c)
                elif c in registradores:
                    registrador_registrador += 1
                    auxComandos.append(int(registradores[c]))
                elif '[' in c:
                    addr += 1
                    auxComandos.append(int(c.strip("[]")))

                    if auxCount == 1:
                        isRegAddres = False
                    else:
                        isRegAddres = True
                else:
                    immediate += 1
                    auxComandos.append(int(c))
            
            auxCount += 1

        for co in auxComandos:
            if registrador_registrador == 2:
                if co == "MOV":
                    comandos.append(dicionario["MOV_RR"])
                else:
                    comandos.append(co)
            elif registrador_registrador == 1 and addr == 1:
                if co == "MOV":
                    if isRegAddres:
                        comandos.append(dicionario["MOV_RM"])
                    else:
                        comandos.append(dicionario["MOV_MR"])
                else:
                    comandos.append(co)
            elif registrador_registrador == 1 and immediate == 1:
                if co == "MOV":
                    comandos.append(dicionario["MOV_RI"])
                else:
                    comandos.append(co)
            elif addr == 1 and immediate == 1:
                if co == "MOV":
                    comandos.append(dicionario["MOV_MI"])
                else:
                    comandos.append(co)
            
        registrador_registrador = 0
        addr = 0
        immediate = 0    
        auxCount = 0
        auxComandos.clear()
        linha += 1

    return comandos