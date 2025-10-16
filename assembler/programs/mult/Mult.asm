// Mult.asm
// Multiplies two numbers in registers R0 and R1 and stores the result in R2.
// Assumes that R0 >= 0, R1 >= 0, and R0 * R1 < 2^16.
// Executes the multiplication in a single loop, doing R0 arithmetic plus operations.

@R2
M=0

(LOOP)
@R0
D=M
@END
D;JEQ
@R1
D=M
@R2
M=D+M
@R0
M=M-1
@LOOP
0;JMP

(END)
@END
0;JMP
