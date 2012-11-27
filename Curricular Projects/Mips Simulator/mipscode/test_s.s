.text

# _start is the entry point into any program.
.global _start
.ent    _start 
_start:

#
#  The header ends here, and code goes below
#

# print a string.  (note the %lo syntax only works if the string is
# in the lower 32KB of memory, which it always will be for us)
label1:
        jal string1
label2:
        j exit
string1:
        li $sp, 0x5000
        li $t1, 0x1114
        sw $t1, 0($sp)
        lw $t0, 0($sp)
        jr $t0

# exit the simulation (v0 = 10, syscall)
exit:
	ori   $v0, $zero, 10
	syscall

.end _start

.data
str1: .asciiz "String number 1\n"
str2: .asciiz "String number 2\n"
str3: .asciiz "Back to the beginning!\n"
strtest: .asciiz "testtesttest!\n"
x:  .word 20
