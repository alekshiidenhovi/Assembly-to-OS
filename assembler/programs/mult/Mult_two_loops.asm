// Mult_two_loops.asm
// Multiplies two numbers in registers R0 and R1 and stores the result in R2.
// Assumes that R0 >= 0, R1 >= 0, and R0 * R1 < 2^16.
// Executes the multiplication in two nested loops, doing R0 * R1 arithmetic plus operations.

@R2
M=0

(OUTER)
@R0
D=M
@END
D;JEQ
@R1
D=M
@x
M=D

(INNER)
@x
D=M
@CLEANUP
D;JEQ
@R2
M=M+1
@x
M=M-1
@INNER
0;JMP

(CLEANUP)
@R0
M=M-1
@OUTER
0;JMP

(END)
@END
0;JMP
