// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef UC_H
#define UC_H

//=============================================================================
//*****************************************************************************
//Control Unit
SC_MODULE(uc){
	sc_uint<8> uc_counter_cycle;

	sc_in<bool>			clock;

	sc_in<bool> 		ula_flagN;
	sc_in<bool> 		ula_flagZ;
	sc_out<bool>		ula_op_now;
	sc_out<uint8_t>		ula_op;


	sc_out<bool>		pc_load;
	sc_out<bool>		pc_inc;

	sc_out<bool>		mem_addr_sel;
	sc_out<bool>		mem_rd;
	sc_out<bool>		mem_wr;

	sc_out<bool>		ac_load;

	sc_in<uint8_t>		instruction_decoder;

	sc_signal<uint8_t> 	main_state;
	
	sc_signal<bool>		_operating;
	sc_signal<bool>		_accumulating;

	void process(){
		while(main_state){
			if(clock.read()){
				state_process();
			}
			else{
				reset_pulse();
			}

			wait();
		}
	}


	SC_CTOR(uc)
	{
		main_state.write(START_STATE);

		uc_counter_cycle=0;

		_operating.write(false);
		_accumulating.write(false);

		SC_THREAD(process)	
		sensitive << clock;
	}

	void helloword(){
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void reset_machine()
	{

	}

	void start_machine()
	{

	}

	void stop_machine()
	{

	}

	//=========================================================================
	// Machine State:
	void exit_state_process()
	{

	}

	void halt_state_process()
	{
		main_state.write(STANDBY_STATE); 

		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "HALT!" << endl;
		cout << "===================================" << endl;
		cout << "+++++++++++++++++++++++++++++++++++" << endl;
	}

	void reset_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "RESET" << endl;
		cout << "===================================" << endl;
	}

	void start_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "START" << endl;
		cout << "===================================" << endl;
	}

	void stop_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "STOP" << endl;
		cout << "===================================" << endl;
	}

	void helloword_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "HelloWord" << endl;
		cout << "===================================" << endl;
	}

	void standby_state_process()
	{
	
	}

	void state_process()
	{
		switch(main_state){
			case EXIT_STATE:
				main_state.write(HALT_STATE);  
				//-----------------------------
				exit_state_process(); 
				break;

			case START_STATE:
				main_state.write(FETCH_OP_STATE); 
				//-----------------------------
				start_state_process(); 
				break;

			case STOP_STATE:
				main_state.write(STANDBY_STATE); 
				//-----------------------------
				stop_state_process(); 
				break;

			case RESET_STATE:
				main_state.write(START_STATE); 
				//-----------------------------
				reset_state_process(); 
				break;	

			case HALT_STATE:
				//----------------------------- 		
				halt_state_process(); 
				break;

			case HELLOWORD_STATE:
				main_state.write(STANDBY_STATE); 	
				//-----------------------------
				helloword_state_process(); 
				break;

			case FETCH_OP_STATE:
				main_state.write(DECODE_OP_STATE);
				//-----------------------------
				fetch_op_state_process();
				break;

			case DECODE_OP_STATE:
				main_state.write(FETCH_OPERATING_STATE);
				//-----------------------------
				decode_op_state_process();
				break;

			case FETCH_OPERATING_STATE:
				main_state.write(ULA_OPERATION_STATE);
				//-----------------------------
				fetch_operating_state_process();
				break;

			case ULA_OPERATION_STATE:
				main_state.write(LOAD_AC_STATE);
				//-----------------------------
				ula_operation_state_process();
				break;

			case LOAD_AC_STATE:
				main_state.write(FETCH_OP_STATE);
				//-----------------------------
				load_ac_state_process();
				break;

			default: standby_state_process(); 
		}
	};

	//=========================================================================
	// instruction_decoder:	
	void nop_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_BYPASS);

		_operating.write(false);
		_accumulating.write(false);

		cout << " nop|" << endl;
	}

	void sta_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_BYPASS);

		_operating.write(false);
		_accumulating.write(false);

		cout << " sta|" << endl;
	}

	void lda_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_BYPASS);

		_operating.write(true);
		_accumulating.write(true);

		cout << " lda";
	}

	void add_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_ADD);

		_operating.write(true);
		_accumulating.write(true);

		cout << " add";
	}

	void or_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_OR);

		_operating.write(true);
		_accumulating.write(true);

		cout << " or";
	}

	void and_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_AND);

		_operating.write(true);
		_accumulating.write(true);

		cout << " and";
	}

	void not_op_process()
	{
		//-----------------------------------
		ula_op.write(ULA_NOT);

		_operating.write(false);
		_accumulating.write(true);

		cout << " not";
	}

	void jmp_op_process()
	{
		mem_rd.write(true);

		//-----------------------------------
		_operating.write(true);
		_accumulating.write(false);

		cout << " jmp";
	}

	void jn_op_process()
	{

		//-----------------------------------
		_operating.write(true);
		_accumulating.write(false);

		cout << " jn";
	}

	void jz_op_process()
	{
		if(ula_flagZ){
			pc_load.write(true);
			mem_rd.write(true);
		}

		//-----------------------------------	
		_operating.write(true);
		_accumulating.write(false);

		cout << " jz";
	}

	void fetch_op_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << "-> FETCH_OP ";

		mem_rd.write(true);

		//-----------------------------------
		mem_addr_sel.write(false);

		_operating.write(false);
		_accumulating.write(false);
	}

	void decode_op_state_process()
	{
		cout << "-> DECODE_OP ";
		switch(instruction_decoder)
		{
			case STA_STATE: sta_op_process(); 		break;
			case LDA_STATE: lda_op_process(); 		break;
			case ADD_STATE: add_op_process(); 		break;	
			case OR_STATE: 	or_op_process(); 		break; 
			case AND_STATE: and_op_process(); 		break; 
			case NOT_STATE: not_op_process(); 		break; 
			case JMP_STATE: jmp_op_process(); 		break; 
			case JN_STATE: 	jn_op_process(); 		break; 
			case JZ_STATE: 	jz_op_process(); 		break; 
			case HLT_STATE: halt_state_process(); 	break;

			default: nop_op_process(); break;
		};

		mem_rd.write(true);
		pc_inc.write(true);

		//-----------------------------------
		mem_addr_sel.write(false);
	}

	void fetch_operating_state_process()
	{
		if(_operating.read()==true){
			cout << "-> FETCH_OPERATING ";
		}

		mem_rd.write(true);

		//-----------------------------------
		mem_addr_sel.write(true);
	}

	void ula_operation_state_process()
	{
		cout << "-> ULA_OPERATION  ";

		ula_op_now.write(true);
		
		//-----------------------------------
		mem_addr_sel.write(true);
	}

	void load_ac_state_process()
	{
		cout << "-> LOAD_AC " << endl;

		if(_accumulating.read()==true){
			ac_load.write(true);
		}

		mem_rd.write(true);
		pc_inc.write(true);

		//-----------------------------------
		mem_addr_sel.write(false);
	}

	void reset_pulse()
	{
		ac_load.write(false);
		pc_load.write(false);
		pc_inc.write(false);
		mem_rd.write(false);
		mem_wr.write(false);
		ula_op_now.write(false);
	}
};

#endif