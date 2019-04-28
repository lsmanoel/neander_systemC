// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

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
//Neander Programmser states
enum{
	STANDBY_PROG_STATE=STANDBY_STATE,
	TARGET_LOCK_STATE,
	TARGET_DROP_STATE,
	TARGET_READ_MEM_STATE,
	TARGET_WRITE_MEM_STATE,
	TARGET_HELLOWORD_STATE,
	TARGET_STANDBY_STATE
};

#define N_CYCLES_RUN 40

#define _DEFAULT 0xff

//=============================================================================
//NEANDER states
enum{
	STANDBY_NEA_STATE=STANDBY_STATE,
	PROG_READ_MEM_STATE,
	PROG_WRITE_MEM_STATE		
};

//=============================================================================
//Control Unit states
enum{
	STANDBY_UI_STATE=STANDBY_STATE,
	FETCH_OP_STATE,
	FETCH_OPERATING_STATE,
	LOAD_AC_STATE,
	NEA_READ_MEM_STATE,
	NEA_WRITE_MEM_STATE
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