main:
	lui $r1 0
	lui $r1 0x82
	ori $r1 $r1 0x9f
	sw $r1 0($r0)
	
	lui $r0 0
	lui $r1 0
	lui $r2 0
	lui $r3 0
	jal OCTAL
	
self: 
	j self
	
OCTAL:
	lui $r0 0
	lw $r0 0($r0)
	sw $r3 1($r0)
	lui $r3 0
	
	lui $r1 0
	ori $r1 $r1 0x07
	and $r1 $r0 $r1
	or $r3 $r3 $r1
	
	lui $r1 0
	lui $r2 0
	ori $r1 $r1 0x38
	and $r1 $r0 $r1
	ori $r2 $r2 1
	sllv $r1 $r1 $r2
	or $r3 $r3 $r1
	
	lui $r1 1
	lui $r2 0
	ori $r1 $r1 0xc0
	and $r1 $r0 $r1
	ori $r2 $r2 2
	sllv $r1 $r1 $r2
	or $r3 $r3 $r1
	
	disp $r3 0
	lw $r3 1($r0)
	jr $r3
	