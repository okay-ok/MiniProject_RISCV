.data
.word 20 40 50 60 70 
.word 30
.word 10
.word 15

.text
addi x30, x0, 1
slli x30, x30, 28
lw x11, 0(x30)
lw x12, 20(x30)
lw x13, 24(x30)
lw x14, 28(x30)
lw x15, 8(x30)
addi x5, x0, 80
addi x6, x0, 85
addi x20, x0, 100
jal x1, func1
exit: #fall-thru code
mul x10, x10, x15
jal x0, final_exit
func1:
addi x2, x2, -4
sw x5, 0(x2)
addi x2, x2, -4
sw x6, 0(x2)
addi x2, x2, -4
sw x20, 0(x2)
add x5, x11, x12
add x6, x13, x14
sub x20, x5, x6
addi x10, x20, 0
lw x20, 0(x2)
addi x2, x2, 4
lw x6, 0(x2)
addi x2, x2, 4
lw x5, 0(x2)
addi x2, x2, 4
jalr x0, x1, 0
final_exit: # all good
addi x25, x0, 250
