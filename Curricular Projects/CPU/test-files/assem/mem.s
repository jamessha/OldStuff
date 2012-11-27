ori $r3 $r3, 0
label1: lui $r2 2
beq $r3 $r2 exit
addi $r3 $r3 1
j label1
exit: lui $r0 0xFF
