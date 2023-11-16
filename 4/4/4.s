	 
	EXPORT SystemInit
    EXPORT __main


	AREA MYPROG,CODE,READONLY 

SystemInit FUNCTION
	; initialization code
 ENDFUNC


; main logic of code
__main FUNCTION
       ENTRY
		LDR R0,=0X7 ; N
		MOV R2,#1
FACT
		CMP R0, #1
		BLE loop
		MUL R2, R0, R2 ; CALCULATING DOUBLE FACTORIEL
		SUB R0, R0, #2 ; DECREASING BY 2
		B FACT
		
loop
	b loop
 ENDFUNC	
 END





