main:
	lui $r0 0xff
	ori $r0 $r0 0xfe
	lui $r1 0x7f
	ori $r1 $r1 0xff
	sub $r2 $r0 $r1