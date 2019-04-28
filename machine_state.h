// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************
#include <iostream>
#include <systemc.h>

#define N_CYCLES_RUN 40
#define _DEFAULT 0xff

//=============================================================================
//*****************************************************************************
//Comum States:
enum{
	EXIT_STATE=0,
	NOP_STATE,
	HALT_STATE,
	RESET_STATE,
	START_STATE,
	STOP_STATE,
	HELLOWORD_STATE,
	STANDBY_STATE
};

//=============================================================================
//NEANDER states
enum{
	STANDBY_NEA_STATE=STANDBY_STATE,	
};

//=============================================================================
//Control Unit states
enum{
	STANDBY_UI_STATE=STANDBY_STATE,
	FETCH_OP_STATE,
	FETCH_OPERATING_STATE,
	LOAD_AC_STATE
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Control Unit ops
#define STA_STATE 	0b00010000
#define LDA_STATE 	0b00100000
#define ADD_STATE 	0b00110000	
#define OR_STATE 	0b01000000 
#define AND_STATE 	0b01010000 
#define NOT_STATE 	0b01100000 
#define JMP_STATE 	0b10000000 
#define JN_STATE 	0b10010000 
#define JZ_STATE 	0b10100000 
#define HLT_STATE 	0b11110000	

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Mux ops
enum{
	ULA_BYPASS=0,
	ULA_ADD, 
	ULA_OR, 
	ULA_AND, 
	ULA_NOT 
};