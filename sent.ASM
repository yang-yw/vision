TEMPER_L  EQU 29H;????????????
TEMPER_H  EQU 28H;????????????
T_DF      EQU 27H ;FORMAT??????(decimal fraction)
T_INTEGER EQU 26H ;FORMAT??????(integer)
FLAG1     BIT 50H

A_BIT EQU 20h ;???????????
B_BIT EQU 21h ;???????????
C_BIT EQU 22H ;????
D_BIT EQU 23H ;????
E_BIT EQU 24H ;????
F_BIT EQU 25H ;????
V_0   EQU 30H				;???
V_1   EQU 31H				;???
V_2   EQU 32H				;??
V_3   EQU 33H				;??
ADC	  EQU 35H

    
CLOCK BIT P0.2			
ST	  BIT P0.1
EOC	  BIT P0.0
OE	  BIT P0.3
QD    BIT P0.7

            ORG 0000H
            LJMP MAIN
		    ORG	000BH
		    LJMP INT_T0
		    ORG	30H
	
MAIN:       
		   ACALL DS18B20
		   ACALL ADCV
		   CLR EA
		   ACALL TRANS
           LJMP MAIN
		   
;--------------??-------------------
TRANS:     MOV R0, #40H
		   MOV @R0, T_INTEGER
		   INC R0
		   MOV @R0, T_DF
		   INC R0
		   MOV @R0, V_3
		   INC R0
		   MOV @R0, V_2
		   INC R0
		   MOV @R0, V_1
		   MOV R7, #05H
		  ACALL UART
		   RET

;--------------??-------------------
UART:    ;CLR EA
		 MOV TMOD, #22H ; T1????2 ???
		 MOV TH1, #0F4H ; ?? T1????2 SMOD=0 ?????11.050M
		 MOV TL1, #0F4H ; Bode????2.4k ??????F4H
		 MOV PCON, #00H ; SMOD=0 bode????
		 SETB TR1       ; ???1????? ??   TCON
		 MOV SCON, #50H ; ??????1 ????
		 
ALOOP1:  MOV SBUF, #0E1H
		 JNB TI, $
		 CLR TI
		 JNB RI, $
		 CLR RI
		 MOV A, SBUF
		 XRL A, #0E2H
		 JNZ ALOOP1
		 
ALOOP2:  MOV R0, #40H
		 ;MOV R7, #01H  ; ????? 
		 MOV R1, #00H  ; ???

ALOOP3:  MOV SBUF, @R0
		 MOV A, R1
		 ADD A, @R0
		 MOV R1, A
		 INC R0
		 JNB TI, $
		 CLR TI
		 DJNZ R7, ALOOP3
		 MOV SBUF, R1
		 JNB TI, $
		 CLR TI
		 JNB RI, $
		 CLR RI
		 MOV A, SBUF
		 XRL A, #00H
		 JNZ ALOOP3
		 RET
		 
;--------------ADC????-------------------
ADCV:     
		  MOV	V_0,#00H
		  MOV	V_1,#00H
		  MOV	V_2,#00H		
		  MOV	TMOD,#22H				;???????2
		  MOV	TH0,#0FFH				
		  MOV	TL0,#00H
		  MOV	IE,#82H					;?T0??
		  SETB TR0					    ;T0????
		  ACALL STARTADC
		  
		  
STARTADC:		
		CLR	ST
		SETB ST						;?????SAR(SAR???A/D????????????)
		CLR	ST						;?????ADC??
		JNB	EOC,$					;??????
		SETB OE						;ADC??
		MOV	ADC,P2					;??AD????
		CLR	OE 		
		MOV	A,ADC					
		MOV	R7,A					;R7??AD??????				
		MOV	V_3,#00H				;????
		MOV	V_2,#00H				;????
		MOV	A,#00H					
LOOP1:	ADD	A,#20H					;????????100mV
		DA	A						;?????BCD?
		JNC	LOOP2					;Cy?0??,Cy?1????
		MOV	R4,A					;R4?????????
		INC	V_2					    ;???1
		MOV	A,V_2
		CJNE A,#0AH,LOOP4			;????10??,?10????
		MOV	V_2,#00H				;???0
		INC	V_3					    ;???1
LOOP4:	MOV	A,R4
LOOP2:	DJNZ R7,LOOP1				;R7?1??0??,?0????
		ACALL BTOD1
		RET

		ORG	0200H
BTOD1:	MOV	R6,A					;R6??R7?0??A??
		ANL	A,#0F0H					;R6?11110000B???A
		MOV	R5,#4
LOOP3:	RR	A
		DJNZ R5,LOOP3				
		MOV	V_1,A					;A??4???????	
		MOV	A,R6
		ANL	A,#0FH					
		MOV	V_0,A					;R6?00001111B??????
		RET	
		
INT_T0:	CPL	CLOCK					;??????
		RETI

;--------------DS18B20??-------------------
DS18B20:   MOV	IE,#02H   
WA2:	   
		   LCALL TIEMCONV          ;????????
           LCALL T_FORMAT              ;????2???????
           LCALL DELAY3
		   RET
;--------------DS18B20????????-------------------
TIEMCONV:            LCALL INIT_1820      ;???DS18B20
                     JB FLAG1,T_C0
                     RET                  ; ??DS1820????  ?DS18B20??????

T_C0:                MOV A,#0CCH          ; ??ROM??
                     LCALL WRITE_1820
                     MOV A,#44H           ; ????????
                     LCALL WRITE_1820
                     LCALL D1S            ;????AD????,12??????750m?
                     LCALL INIT_1820      ;?????????
                     MOV A,#0CCH          ; ??ROM??
                     LCALL WRITE_1820
                     MOV A,#0BEH          ; ???????
                     LCALL WRITE_1820
                     LCALL READ_1820      ; ???????????28H(TEMPER_H)?29H(TEMPER_L)?
                     RET

;------DS18B20???????-----------------------------------------
INIT_1820:         SETB  QD
                   NOP
                   CLR QD
                   MOV R0,#1              ;??????500????????
INIT0:             MOV R1,#250
                   DJNZ R1,$
                   DJNZ R0,INIT0

                   SETB QD                ;???????
                   NOP

                   MOV R0, #15
INIT1:             JNB QD, INIT3          ;??60us??DS18B20??
                   DJNZ R0, INIT1
                   LJMP INIT4             ; ???????
INIT3:             SETB FLAG1             ; ????,??DS1820??
                   LJMP INIT5
INIT4:             CLR FLAG1              ; ????,??DS1820???
                   LJMP INIT6
INIT5:             MOV R0, #120
                   DJNZ R0, $             ; ??240us
INIT6:             SETB QD
                   RET

;---------?DS18B20????-------------------------------------
WRITE_1820:       MOV R2,#8     ;??8???
WR0:              CLR QD
				  MOV R3,#6
				  DJNZ R3,$
				  RRC A
				  MOV QD,C
				  MOV R3,#20
				  DJNZ R3,$
				  SETB QD
				  NOP
				  NOP
				  DJNZ R2,WR0
				  SETB QD
				  RET

;------?DS18B20???,?DS18B20????????????--------------------------
READ_1820:         MOV R4,#2                   ; ?????????DS18B20???
                   MOV R1,#TEMPER_L               ; ????29H(TEMPER_L)
RE0:               MOV R2,#8
RE1:               SETB QD
                   NOP
                   NOP
                   CLR QD
                   NOP
                   NOP
                   SETB QD
                   MOV R3,#5
                   DJNZ R3, $
                   MOV C,QD
                   MOV R3,#20
                   DJNZ R3, $
                   RRC A
                   DJNZ R2,RE1
                   MOV @R1,A
                   DEC R1            ; ????28H(TEMPER_H)
                   DJNZ R4,RE0
                   RET

;-----??????????----------
T_FORMAT:         MOV A, #0FH
                  ANL A, TEMPER_L
                  MOV T_DF, A           ;??????(4?)

                  MOV A, TEMPER_L
                  SWAP A
                  MOV TEMPER_L, A

                  MOV A, TEMPER_H
                  SWAP A
                  MOV R0, #TEMPER_L
                  XCHD A, @R0

                  MOV T_INTEGER, A       ;??????(1??)
                  RET

;----??---------------------------------------------------------
DELAY:      MOV R3, #20
D1:         MOV R4, #250
			DJNZ R4, $
			DJNZ R3, D1 
			RET
DELAY1:     MOV R3, #20H
		    DJNZ R3, $
            RET
DELAY3:
            MOV R5,#190
DEL1:
            MOV R4,#250
DEL2:
            DJNZ R4,$
            DJNZ R5,DEL1
            RET

D1mS:       MOV R7,#250
LOOP0:      NOP
		    NOP
		    DJNZ R7,LOOP0
		    RET

D1S:          MOV R6,#4
LOOOP2:       MOV R5,#250
LOOOP1:       LCALL D1mS
              DJNZ R5,LOOOP1
              DJNZ R6,LOOOP2
              RET
