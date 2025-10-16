// Fill.asm
// Paints the screen black when any key is pressed. Paints the screen white when no key is pressed. 
// Run in an infinite loop.

(SET_COLOR)
@color
M=0
@KBD
D=M
@FILL_INIT
D;JEQ
@color
M=-1

(FILL_INIT)
@n
M=0
@KBD
D=A
@SCREEN
D=D-A
@screen_width
M=D

(FILL_LOOP)
@screen_width
D=M
@n
D=D-M
@SET_COLOR
D;JLE
@SCREEN
D=A
@n
D=D+M
@location
M=D
@color
D=M
@location
A=M
M=D
@n
M=M+1
@FILL_LOOP
0;JMP
