	 
	EXPORT SystemInit
    EXPORT __main


	AREA MYPROG,CODE,READONLY 

SystemInit FUNCTION
	; initialization code
 ENDFUNC


; main logic of code
__main FUNCTION
       ENTRY
		LDR R2,=0X1
		STR R2,[SP]
		MOV R5,#0; NUM OF SHIFTS

		LDR R4,[SP]
SET		LSR R4,R4,#1  ; FINDING OUT NUM OF BIT IN THE NUMBER
		ADD R5,R5,#1
		CMP R4,#0
		BNE SET
		EOR R0,R0,R0
		EOR R1,R1,R1
COUNT 
		LSRS R2,#1  ; RIGHT SHIFT AND SETTING FLAGS
		ADDCS R1,#1  ; INC NUM OF ONE IF C=1
		ADDCC R0,#1 ; INC NUM IF ZEROS IF C=0
		SUB R5,#1
		CMP R5,#0
		BEQ loop
		B COUNT
loop
	b loop
 ENDFUNC	
 END


