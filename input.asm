# Data Test
.data
.word 375 4655 234436 34565
.half 3
.asciiz "Hello World"
.dword 893428942

# Text Test
.text 
add x5, x6, x7
label: andi x5, x6, 17
sd x5, 8(x21)
beq x0, x0, exit
lui x3, 65563
jal x0, label
exit:
