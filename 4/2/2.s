	 
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
	MOV R3,#0
	
LUCAS
	ADD R0,R0,R1
	ADD R3,R3,#3
	
LUCAS_CON ; FINDING BIGGEST LUCAS NUMBER WHICH IS LESS THAN 0XFFFFFFFF
	CMP R0,R1
	ADDSLS R0,R0,R1
	ADDSHI R1,R0,R1
	ADD R3,#1
	BCS FINAL ; IF CARRY FLAG SET => 33BIT
	B LUCAS_CON
FINAL 
	CMP R0,R1 ; BIGGER NUMBER IN THE REGISTERS
	PUSHHI {R0}  
	PUSHLS {R1}
	SUB R3,#1
	PUSH {R3}
loop
	b loop
 ENDFUNC	
 END

