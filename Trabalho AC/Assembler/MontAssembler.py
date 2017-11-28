from Dictionary import *
from Encoder import *

if __name__ == "__main__":
    with open("OPCODES.esym") as codFile:
       cod = codFile.readlines()
    codFile.close()
    d = dictionary(cod)

    with open("REGCODES.esym") as regFile:
        registrador = regFile.readlines()
    regFile.close()
    r = reg(registrador)

    print(d)
    print(r)

    with open("Assembly3.txt") as assemblyFlie:
        aux = assemblyFlie.readlines()
    c = codificador(aux, d, r)

    print(c)

    fileObject = open("Codificacao3.txt", "w")
    i = 0
    for v in c:
        string = str(v)
        if i < len(c) - 1:
            fileObject.write(string + "\n")
        else:
            fileObject.write(string)
        i += 1
    fileObject.close()