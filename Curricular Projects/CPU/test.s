lui $r3 0xFF
ori $r3 $r3 0x00
lui $r2 0
ori $r2 $r2 0x04
srlv $r1 $r3 $r2
disp $r1 0
self: j self
