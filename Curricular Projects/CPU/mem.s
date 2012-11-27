ori $r3 $r3, 0
jal label1
lui $r1 4
addi $r0 $r0 -1
sw $r1 0($r0)
j label2

label1: 
ori $r0 $r0 0xFF
addi $r0 $r0 -1
lui $r1 10
sw $r1 0($r0)
jr $r3

label2:
lw $r1 0($r0)
addi $r0 $r0 1
lw $r2 0($r0)
addi $r0 $r0 1
disp $r1 0
disp $r2 1
