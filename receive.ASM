RS    	  BIT P3.5 ;?3??????????,???????????
RW    	  BIT P3.6
E     	  BIT P3.7
A_BIT 	  EQU 20h ;???????????
B_BIT 	  EQU 21h ;???????????
C_BIT 	  EQU 22H ;????
D_BIT 	  EQU 23H ;????
E_BIT     EQU 24H ;????
F_BIT     EQU 25H ;????	
V_1		  EQU 31H ;???
V_2 	  EQU 32H ;??
V_3 	  EQU 33H ;??
K1        EQU P2.0
K2        EQU P2.1
T_DF      EQU 34H ;FORMAT??????(decimal fraction),????????(?????)
T_INTEGER EQU 35H ;FORMAT??????(integer),??????????1??

	
		    ORG 0000H
            LJMP MAIN
		    ORG	30H
	
MAIN:      MOV P1, #0C0H		
		   LCALL LCDINI
           MOV A, #00H
           LCALL   WENABEL
           MOV   DPTR, #TEMP
           LCALL   WCHAR
		  
		   MOV	V_1,#00H
		   MOV	V_2,#00H
           MOV A, #0C0H
           LCALL   WENABEL
           MOV   DPTR, #VOLTAGE
           LCALL   WCHAR
		   
		   
MAIN1:	   ACALL ACCEPT
		   ACALL KEY1
		   SJMP MAIN1
;--------------??----------------------
ACCEPT:    MOV R7, #05H
           ACALL UART
		   MOV T_INTEGER, 40H
		   MOV T_DF, 41H
		   MOV V_3, 42H
		   MOV V_2, 43H
		   MOV V_1, 44H
		   MOV A, V_2
		   JZ AA1
		   DEC V_2
		   AJMP AA2
		   
AA1:       MOV A, V_3
		   JZ AA2
		   MOV V_2, #09H
		   DEC V_3
AA2:
		   RET


;--------------????-------------------
KEY1:     SETB K1
          JB K1, KEY2
		  ACALL TEM
		  RET

KEY2:     SETB K2
          JB K2, MAIN1
		  ACALL ADCV
		  RET
;--------------TEM/ADCV-------------------
TEM:      MOV P1, #00H  
		  ACALL SHOWSPACE2
		  ACALL DISPLAY
		  ACALL ACCEPT
		  SETB K2
          JB K2, TEM
		  ACALL ADCV
		  RET

ADCV:     MOV P1, #0FFH    
		  ACALL SHOWSPACE1
		  MOV DPTR, #TABLE2
		  ACALL LCDDISP
		  ACALL ACCEPT
		  SETB K1
          JB K1, ADCV
		  ACALL TEM
		  RET
/************ ?????? ************/
UART:    CLR EA
		 MOV TMOD, #22H
		 MOV TH1, #0F4H
		 MOV TL1, #0F4H
		 MOV PCON, #00H
		 SETB TR1
		 MOV SCON, #50H
		 
BLOOP1:  JNB RI, $
	     CLR RI
		 MOV A, SBUF
		 XRL A, #0E1H
		 JNZ BLOOP1
		 MOV SBUF, #0E2H
		 JNB TI, $
		 CLR TI
		 MOV R0, #40H
		 ;MOV R7, #01H
		 MOV R1, #00H ; ???
		 
BLOOP2:  JNB RI, $
		 CLR RI
		 MOV A, SBUF
		 MOV @R0, A
		 INC R0
		 ADD A, R1
		 MOV R1, A
		 DJNZ R7, BLOOP2
		 JNB RI, $
		 CLR RI
		 MOV A, SBUF
		 XRL A, R1 ; ?????????
		 JZ END1
		 MOV SBUF, #0FFH
		 JNB TI, $
		 CLR TI
		 SJMP BLOOP1
		
END1:     MOV SBUF, #00H
	     RET		   
;-------????---------------------------------------
		   
DISPLAY:             MOV a, T_INTEGER
                     MOV b,#10
                     div ab
                     MOV A_BIT,a ;????A_BIT
					 MOV B_BIT,b ;????B_BIT
                     MOV A, T_DF
                     MOV R0, #C_BIT
                    MOV R2, #4
               	D0: MOV B, #10
                     MUL AB
                     MOV B, #16
                     DIV AB
                     MOV @R0, A     
                     INC R0
                     MOV A, B
                     DJNZ R2, D0
                     ;-------------------------------------
					 MOV	DPTR,#TABLE2
                     MOV A, #85H
                     LCALL   WENABEL
                     MOV A, A_BIT
					 MOVC A,@A+DPTR
					 ACALL WDATA
                     MOV A, B_BIT
					 MOVC A,@A+DPTR
					 ACALL WDATA
                     MOV A, #2EH
                     LCALL   WDATA
                     MOV A, C_BIT
					 MOVC A,@A+DPTR
                     LCALL   WDATA
                     MOV A, D_BIT
					 MOVC A,@A+DPTR
                     LCALL   WDATA
                     MOV A, E_BIT
					 MOVC A,@A+DPTR
                     LCALL   WDATA
                     MOV A, F_BIT
					 MOVC A,@A+DPTR
                     LCALL   WDATA
                     MOV A, #0DFH        
                     LCALL   WDATA
                     MOV A, #43H
                     LCALL   WDATA
                     RET		   
					 
					 
SHOWSPACE1:          MOV A, #85H
					 ACALL WENABEL
					 MOV DPTR, #SPACE
					 MOV R7, #00H
L2:				     MOV A, R7
					 MOVC A, @A+DPTR
					 ACALL WDATA
					 INC R7
					 CJNE R7, #0BH, L2
					 RET
SHOWSPACE2:          MOV A, #0C8H
					 ACALL WENABEL
					 MOV DPTR, #SPACE
					 MOV R7, #00H
L22:				 MOV A, R7
					 MOVC A, @A+DPTR
					 ACALL WDATA
					 INC R7
					 CJNE R7, #08H, L22
					 RET
		
LCDDISP:		    MOV A,#0C8H
					ACALL WENABEL
					MOV A,V_3
					MOVC A,@A+DPTR
					ACALL WDATA
					MOV A,#2EH
					ACALL WDATA
					MOV A,V_2
					MOVC A,@A+DPTR
					ACALL WDATA
					MOV A,V_1
					MOVC A,@A+DPTR
					ACALl WDATA
					
					MOV A,#56H
					ACALL WDATA
					RET
		   
		   
		   
;---??????,???????-------------------------------------------------
LCDINI:            MOV   A, #01H
				   LCALL WENABEL
				   MOV   A, #38H
				   LCALL WENABEL
				   MOV   A, #38H
				   LCALL WENABEL
				   MOV   A, #0FH
				   LCALL WENABEL
				   MOV   A, #06H
				   LCALL WENABEL
				   RET
;----???------------------------------------------
WENABEL:           MOV P0, A
				   CLR RS ;??????
				   CLR RW
				   CLR E
				   LCALL DELAY
				   SETB E
				   RET
;----???---------------------------------------------
WDATA:        MOV P0, A
			  SETB RS ;????
			  CLR RW
			  CLR E
			  LCALL DELAY 
			  SETB E
			  RET
;-----????????---------------------------------------------------------------
WCHAR:     CLR    A
		   MOVC   A, @A+DPTR
		   JZ     END_PR
		   LCALL  WDATA
		   INC    DPTR
		   LJMP   WCHAR
END_PR:    RET
;----??---------------------------------------------------------
DELAY:    MOV R3, #20
D1:       MOV R4, #25
          DJNZ R4, $
		  DJNZ R3, D1 
          RET
DELAY1:   MOV R3, #20H
		  DJNZ R3, $
          RET
DELAY3:
          MOV R5,#19
DEL1:
          MOV R4,#25
DEL2:
          DJNZ R4,$
          DJNZ R5,DEL1
          RET

D1mS:     MOV R7,#250
LOOP0:    NOP
          NOP
          DJNZ R7,LOOP0
          RET

D1S:       MOV R6,#4
LOOOP2:    MOV R5,#250
LOOOP1:    LCALL D1mS
           DJNZ R5,LOOOP1
           DJNZ R6,LOOOP2
           RET
			  
;--------------------------------------------------------------------------------------
TEMP:    DB  'TEMP:',00H
VOLTAGE: DB  'VOLTAGE:',00H
TABLE2:  DB  30H,31H,32H,33H,34H
	     DB  35H,36H,37H,38H,39H
SPACE:   DB  20H,20H,20H,20H,20H
	     DB  20H,20H,20H,20H,20H, 20H, 20H, 20H
END
