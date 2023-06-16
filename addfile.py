# +-----------------------------------------------+
# |                 /addfile.py                   |
# | A tool to add file to build.sh automatically  |
# +-----------------------------------------------+

#required pkgs: dialog (system)

import sys
import os

print("+---------------------------------------------+")
print("| Script: /addfile.py                         |")
print("| Usage:  Adds file to build.sh automatically |")
print("+---------------------------------------------+")
print(f"Args: {sys.argv}")

s = ""
dialog_flags = "--backtitle \"CubeBox OS: Build Environment tools: Add file to build.sh\""

ext_NASM     = ".asm"
ext_i686_ASM = ".s"
ext_i686_GCC = ".c"
ext_OBJ      = ".o"

com_ASSEMBLY = "#[addfile.py: assembly]"
com_C        = "#[addfile.py: c]"
com_OBJECT   = "#[addfile.py: obj]"

def getArg(__argIndex):
    return sys.argv[__argIndex + 1]

def prompt(text):
    os.system(f"dialog {dialog_flags} --inputbox \"{text}\" 8 {len(text) + 3} 2> ./addfile.tmp");
    
    TMPf = os.open("./addfile.tmp", os.O_RDONLY)
    input_ = os.read(TMPf, 1024)

    os.close(TMPf)
    os.system("rm ./addfile.tmp")

    return input_

def buildSh_replace(__target, __replacement):
    buildShR = open("build.sh", "r")
    buildSh_buff = os.read(buildShR)

    buildSh_buff = buildSh_buff.replace(__target, __replacement)

    buildShW = open("build.sh", "w")
    buildShW.write((buildSh_buff))

def addNasm(__file):
    buildSh_replace(com_ASSEMBLY, f"{__file}\n{com_ASSEMBLY}")
    addObj(f"{__file}{com_OBJECT}")

def addI686Gcc(__file):
    buildSh_replace(com_C, f"{__file}\n{com_C}")
    addObj(f"{__file}{com_OBJECT}")

def addI686Asm(__file):
    buildSh_replace(com_ASSEMBLY, f"{__file}\n{com_ASSEMBLY}")
    addObj(f"{__file}{com_OBJECT}")

def addObj(__file):
    buildSh_replace(com_OBJECT, f"{__file}\n{com_OBJECT}")

def addSingleFile(__file):
    ext = __file.split(b".")
    ext = ext[len(ext)]

    if ext == ext_NASM:
        addNasm(__file)
    elif ext == ext_i686_ASM:
        addI686Asm(__file)
    elif ext == ext_i686_GCC:
        addI686Gcc(__file)
    elif ext == ext_OBJ:
        addObj(__file)
    else:
        print("Incompatible file!")

def addFiles(__files):
    for i in __files:
        addSingleFile(str( __files[i]))

def getFiles():
    fileList = []

    if len(sys.argv) > 1:
        l = len(sys.argv) - 1
        s = "args"

        for i in range(l):
            fileList[i] = getArg(i)
    else:
        userInput = prompt("Input file names (split by comma \",\")")
        fileList = userInput.split(b",")

    print(f"Files: {fileList}")
    return fileList

addFiles(getFiles())
