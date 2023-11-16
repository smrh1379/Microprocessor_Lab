	 
	EXPORT SystemInit
    EXPORT __main


	AREA MYPROG,CODE,READONLY 

SystemInit FUNCTION
	; initialization code
 ENDFUNC


; main logic of code
__main FUNCTION
       ENTRY
START
	MOV R0,#2 ; fitst element of lucas
	MOV R1,#1 ; second element of lucas
	MOV R2,#15  ; N
	PUSH {R2}
	MOV R3,#0
	MOV	R2,#0
LUCAS
	POP {R2}
	PUSH {R0} ; pushing first
	ADD R3,R3,#1
	CMP R3,R2
	BEQ loop
	PUSH {R1} ; pushing second 
	ADD R3,R3,#1
	CMP R3,R2
	BEQ loop
	ADD R0,R0,R1
	PUSH {R0} ; pushing third
	ADD R3,R3,#1
	CMP R3,R2
	BEQ loop
LUCAS_CON ; computing lucas for n>=4
	CMP R0,R1
	ADDLT R0,R0,R1
	ADDGT R1,R0,R1
	PUSHLT {R0}
	PUSHGT {R1}
	ADD R3,#1
	CMP R3,R2
	BEQ loop
	B LUCAS_CON
loop
	b loop
 ENDFUNC	
 END


