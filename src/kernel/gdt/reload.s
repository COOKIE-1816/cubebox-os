reloadSegments:
   JMP   0x08:.reload_CS 
.reload_CS:
   MOV   AX, 0x10

   MOV   DS, AX
   MOV   ES, AX
   MOV   FS, AX
   MOV   GS, AX
   MOV   SS, AX

   RET
