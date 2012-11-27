main:
	lui $r1 0xFF
	ori $r1 $r1 0xFF
	sw $r1 0($r0)
	sw $r1 1($r0)
	sw $r1 2($r0)
	sw $r1 3($r0)
	lui $r1 0
	ori $r1 $r1 0xFF
	sw $r1 4($r0)
	
	jal StringLen
	
self: 
	j self
	
StringLen:
	lui $r0 0
	lui $r1 0
	lui $r2 0

loop:
	lw $r2 0($r1)
	sw $r3 0($r1)
	lui $r3 0
	beq $r2 $r3 exit
	zb $r2 $r2
	bne $r2 $r3 hasZero
	addi $r0 $r0 2
	lw $r3 0($r1)
	addi $r1 $r1 1
	j loop
	
hasZero:
	addi $r0 $r0 1
	j exit
	
exit:
	disp $r0 0
	lw $r3 0($r1)
	jr $r3