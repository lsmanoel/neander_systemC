//---------------------

#include "machine_state.h"

using namespace std;

// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

//=============================================================================
//*****************************************************************************
//Basic Machine State Template:
SC_MODULE(programmer){
	sc_in<bool>				clock;

	sc_out<bool>		prog_mode;
	sc_out<uint8_t>		prog_output;

	sc_uint<8>	main_state;

	sc_uint<8> program_counter;
	sc_uint<8>* program;

	void process()
	{
		state_process();
	}

	SC_CTOR(programmer)
	{
		main_state = START_STATE;

		SC_CTHREAD(process, clock.pos())	
	}

	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void reset(){
		// RESET
		program_counter=0;
	}

	void set_program(sc_uint<8>* program_input){
		program = program_input;
	}

	//=========================================================================
	// Machine State:

	void exit_state_process()
	{

	}

	void reset_state_process()
	{
		reset();
	}

	void start_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "START" << endl;
		cout << "===================================" << endl;		
	}

	void standby_state_process()
	{
		
	}

	void halt_state_process()
	{
		cout << "===================================" << endl;
		cout << "HALT!" << endl;
		cout << "===================================" << endl;
		cout << "+++++++++++++++++++++++++++++++++++" << endl;
		while(1){wait();};
	}

	void helloword_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: HelloWord" << endl;
		cout << "===================================" << endl;
	}

	void target_lock_state_process()
	{
		prog_mode.write(true);
	
		cout << "______________________________________" << endl;
		cout << endl;
		cout << "!!!!!!!!!!! PROG STATE !!!!!!!!!!!!!!!" << endl;
	}

	void target_drop_state_process()
	{
		prog_output.write(EXIT_STATE);
		prog_mode.write(false);

		cout << "!!!!!!!!!!!! DROP TARGET !!!!!!!!!!!!!" << endl;
		cout << "______________________________________" << endl;
		cout << endl;	
	}

	void target_helloword_state_process()
	{
		prog_output.write(HELLOWORD_STATE);
	}

	void target_read_memory_state_process()
	{
		prog_output.write(PROG_READ_MEM_STATE);
	}

	void target_write_memory_state_process()
	{
		prog_output.write(PROG_WRITE_MEM_STATE);
	}

	void target_standby_state_process()
	{
		prog_output.write(STANDBY_STATE);
	}

	void state_process()
	{
		while(main_state){
			// cout << (char)(program_counter+48) << endl;
			main_state=program[program_counter];
			switch(main_state){
				case EXIT_STATE:		
					exit_state_process(); 
					break;
				case NOP_STATE:
					program_counter++;
					break;
				case START_STATE:	
					start_state_process(); 
					program_counter++;
					break;
				case RESET_STATE:					 	
					reset_state_process();
					program_counter++; 
					break;			
				case HALT_STATE: 		
					halt_state_process(); 
					break;
				case HELLOWORD_STATE:
					helloword_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_LOCK_STATE:
					target_lock_state_process(); 
					program_counter++;	 	
					break;
				case TARGET_DROP_STATE:
					target_drop_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_READ_MEM_STATE:
					cout << "--read" << endl;
					target_read_memory_state_process(); 
					program_counter++;	 	
					break;
				case TARGET_WRITE_MEM_STATE:
					cout << "--write" << endl;
					target_write_memory_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_HELLOWORD_STATE:
					target_helloword_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_STANDBY_STATE:
					target_standby_state_process();
					program_counter++;	 	
					break;

				default: standby_state_process(); 
			};
			wait();
		}	
	}
};

//=============================================================================
//*****************************************************************************
//Mux:
SC_MODULE(mux)
{
	sc_in<bool> 		sel;

	sc_in<uint8_t> 		input_a;
	sc_in<uint8_t> 		input_b;
	sc_out<uint8_t> 	output;

	void process()
	{
		if(sel) output.write(input_b);
		else output.write(input_a);
	}

	SC_CTOR(mux)
	{
		SC_METHOD(process);
		sensitive << input_a << input_b << sel;
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//=============================================================================
//*****************************************************************************
//Arithmetic Logic Unit (ULA):
SC_MODULE(ula){
	sc_out<bool> 		flagN;
	sc_out<bool> 		flagZ;

	sc_in<uint8_t> 		op;
	sc_in<uint8_t> 		input_a;
	sc_in<uint8_t> 		input_b;
	sc_out<uint8_t>		result;

	sc_signal<uint8_t>	_add_result;
	sc_signal<uint8_t>	_or_result;
	sc_signal<uint8_t>	_and_result;
	sc_signal<uint8_t>	_not_result;


	void process()
	{
		
		_add_result = input_a + input_b;
		_or_result  = input_a | input_b;
		_and_result = input_a & input_b;
		_not_result = ~input_a;
		switch(op){
			case ULA_ADD: result.write(_add_result); break;
			case ULA_OR:  result.write(_or_result);  break;
			case ULA_AND: result.write(_and_result); break;
			case ULA_NOT: result.write(_not_result); break;
			default: 	  result.write(input_a);
		}

	}

	SC_CTOR(ula)
	{
		SC_METHOD(process);
		sensitive << input_a << input_b << op; 
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//=============================================================================
//*****************************************************************************
//Acumulator:
SC_MODULE(ac){
	sc_in<bool>				load;
	sc_in<uint8_t> 			input_a;
	sc_out<uint8_t> 		data_out;

	void process()
	{
		if(load) data_out.write(input_a);
	}

	SC_CTOR(ac)
	{
		SC_METHOD(process);
		sensitive << load.pos();
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

};

//=============================================================================
//*****************************************************************************
SC_MODULE(pc)
{
	sc_in<bool> 		inc;
	sc_in<bool> 		load;

	sc_out<uint8_t> 	data_out;
	sc_in<uint8_t> 		input_a;
	sc_uint<8> 			_counter;

	void process()
	{		
		if(load) _counter = input_a.read();
		if(inc) _counter++;
		data_out.write(_counter);
	}

	SC_CTOR(pc)
	{
		SC_METHOD(process)
		sensitive << inc << load;
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}	
};

//=============================================================================
//*****************************************************************************
//Memory:
SC_MODULE(mem){
	sc_in<bool> 			rd;
	sc_in<bool> 			wr;
	sc_in<bool> 			zr;

	const sc_uint<8> 		zero=0;

	sc_in<uint8_t> 			addr_in;
	sc_in<uint8_t> 			data_in;
	sc_out<uint8_t> 		data_out;

	sc_signal<uint8_t> memory_bank[256];

	SC_CTOR(mem)
	{
		SC_METHOD(process);
		sensitive << rd << wr << zr;
	}

	void process()
	{
		if(rd) mem_rd_process();
		if(wr) mem_wr_process();
		if(zr) data_out.write(zero);
		else data_out.write(data_in.read());
	}

	void mem_rd_process()
	{
		data_out.write(memory_bank[addr_in.read()].read()); 
	}

	void mem_wr_process()
	{
		memory_bank[addr_in.read()].write(data_in.read());
	}

	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//=============================================================================
//*****************************************************************************
//Control Unit
SC_MODULE(uc){
	sc_uint<8> uc_counter_cycle;

	sc_in<bool>			clock;
	
	sc_in<bool>			prog_mode;

	sc_in<bool> 		ula_flagN;
	sc_in<bool> 		ula_flagZ;

	sc_in<bool>			rd;
	sc_in<bool>			wr;

	sc_out<uint8_t>		ula_op;

	sc_out<bool>		pc_load;
	sc_out<bool>		pc_inc;

	sc_out<bool>		mem_addr_sel;
	sc_out<bool>		mem_rd;
	sc_out<bool>		mem_wr;
	sc_out<bool>		mem_zr;

	sc_out<bool>		ac_load;
	sc_out<bool>		ac_input_sel;

	sc_in<uint8_t>		instruction_decoder;

	sc_signal<uint8_t> 	main_state;
	sc_signal<bool>		_operating;

	void process(){
		while(main_state){
			mem_rd_wr_daemon();
			state_process();
			wait();
		}
	}

	void mem_rd_wr_daemon(){
		if(rd.read()==true)
			main_state.write(NEA_READ_MEM_STATE);

		if(wr.read()==true)
			main_state.write(NEA_WRITE_MEM_STATE);
	}

	SC_CTOR(uc)
	{
		main_state.write(RESET_STATE);

		uc_counter_cycle=0;

		SC_CTHREAD(process, clock.pos())	
	}

	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void rst()
	{
		mem_wr.write(false);
		mem_rd.write(false);	
	}

	//=========================================================================
	// Machine State:
	void exit_state_process()
	{

	}

	void reset_state_process()
	{
		rst();
	}

	void start_state_process()
	{

	}

	void standby_state_process()
	{
	
	}

	void halt_state_process()
	{
		cout << "===================================" << endl;
		cout << "HALT!" << endl;
		cout << "===================================" << endl;
		cout << "+++++++++++++++++++++++++++++++++++" << endl;
		while(1){};
	}

	void helloword_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "HelloWord" << endl;
		cout << "===================================" << endl;
	}

	//=========================================================================
	// instruction_decoder:	

	void nop_op_process()
	{
		_operating.write(false);
		cout << "|" << endl;
	}

	void sta_op_process()
	{
		mem_rd.write(true);
		mem_addr_sel.write(true);
		mem_wr.write(true);

		_operating.write(true);
	}

	void lda_op_process()
	{
		mem_rd.write(true);
		mem_addr_sel.write(true);
		ula_op.write(ULA_BYPASS);
		ac_load.write(true);

		_operating = true;
	}

	void add_op_process()
	{
		mem_rd.write(true);
		mem_addr_sel.write(true);
		ula_op.write(ULA_ADD);
		ac_load.write(true);

		_operating.write(true);
	}

	void or_op_process()
	{
		mem_rd.write(true);
		mem_addr_sel.write(true);
		ula_op.write(ULA_OR);
		ac_load.write(true);

		_operating.write(true);
	}

	void and_op_process()
	{
		mem_rd.write(true);
		mem_addr_sel.write(true);
		ula_op.write(ULA_AND);
		ac_load.write(true);

		_operating.write(true);
	}

	void not_op_process()
	{
		ula_op.write(ULA_NOT);
		ac_load.write(true);

		_operating.write(false);
	}

	void jmp_op_process()
	{
		mem_rd.write(true);
		pc_load.write(true);

		_operating.write(true);
	}

	void jn_op_process()
	{
		if(ula_flagN){
			mem_rd.write(true);
			pc_load.write(true);
		}

		_operating.write(true);
	}

	void jz_op_process()
	{
		if(ula_flagZ){
			mem_rd.write(true);
			pc_load.write(true);
		}

		_operating.write(true);
	}

	void fetch_op_state_process()
	{
		cout << "-----------------------------------" << endl;
		cout << "-> FETCH_OP";
		mem_rd.write(true);
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
	}

	void fetch_operating_state_process()
	{
		cout << " -> FETCH_OPERATING";
		mem_rd.write(true);
		mem_addr_sel.write(true);		
	}

	void load_ac_state_process()
	{
		cout << " -> LOAD_AC|" << endl;
	}

	void nea_read_mem_state_process()
	{
		cout << "nea_read_mem_state_process" << endl;
	}

	void nea_write_mem_state_process()
	{
		cout << "nea_write_mem_state_process..." << endl;
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
				if(prog_mode.read()) 
					main_state.write(STANDBY_STATE);
				else
					main_state.write(FETCH_OP_STATE); 

				//-----------------------------
				start_state_process(); 
				break;

			case RESET_STATE:
				main_state.write(STANDBY_STATE); 

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
				if(prog_mode.read())
					main_state.write(STANDBY_STATE);
				else
					if(_operating.read())
						main_state.write(FETCH_OPERATING_STATE);
					else
						main_state.write(LOAD_AC_STATE);
				
				//-----------------------------
				fetch_op_state_process();
				break;

			case FETCH_OPERATING_STATE:
				if(prog_mode.read())
					main_state.write(STANDBY_STATE);
				else
					main_state.write(LOAD_AC_STATE);

				//-----------------------------
				fetch_operating_state_process();
				break;

			case LOAD_AC_STATE:
				if(prog_mode.read())
					main_state.write(STANDBY_STATE);
				else
					main_state.write(FETCH_OP_STATE);

				//-----------------------------
				load_ac_state_process();
				break;

			case NEA_READ_MEM_STATE:
				main_state.write(STANDBY_STATE);

				//-----------------------------
				nea_read_mem_state_process();
				break;

			case NEA_WRITE_MEM_STATE:
				main_state.write(STANDBY_STATE);

				//-----------------------------
				nea_write_mem_state_process();
				break;

			default: standby_state_process(); 
		}
	};
};


//=============================================================================
//*****************************************************************************
//Neander:
SC_MODULE(neander){
	sc_in<bool>			clock;
	uc*					uc_1;
	pc*					pc_1;
	mux*				mux_1;
	mux*				mux_2;
	mem*				mem_1;
	ula*				ula_1;
	ac* 				ac_1;

	sc_signal<bool>		wr;
	sc_signal<bool>		rd;
	sc_signal<bool>		mode;

	sc_in<bool>			prog_mode;
	sc_in<uint8_t>		prog_input;

	sc_uint<8> 			program_counter;
	sc_uint<8>* 		program;
	sc_uint<8> 			main_state;	

	//----------------------------------------------
	sc_signal<bool> 	ula_flagN;
	sc_signal<bool> 	ula_flagZ;
	sc_signal<uint8_t>	ula_op;
	sc_signal<uint8_t>	ula_result;

	sc_signal<bool>		pc_load;
	sc_signal<bool>		pc_inc;
	sc_signal<uint8_t>	pc_data_out;

	sc_signal<bool>		mem_addr_sel;
	sc_signal<bool>		mem_wr;
	sc_signal<bool>		mem_rd;
	sc_signal<bool>		mem_zr;

	sc_signal<uint8_t>	mem_data_in;
	sc_signal<uint8_t>	mem_data_out;
	sc_signal<uint8_t>	mem_addr_in;
	
	sc_signal<bool>		ac_load;
	sc_signal<uint8_t>	ac_input;
	sc_signal<bool>		ac_input_sel;
	sc_signal<uint8_t> 	ac_data_out;

	void process()
	{
		while(1)
		{
			state_process();
			wait();
		}
	}

	SC_CTOR(neander)
	{
		uc_1 = new uc("UC");
		pc_1 = new pc("PC");
		mux_1 = new mux("MUX1");
		mux_2 = new mux("MUX2");
		mem_1 = new mem("MEM");
		ula_1 = new ula("ULA");
		ac_1 = new ac("AC");

		//------------------------------------------
		main_state = RESET_STATE;

		//------------------------------------------
		uc_1->clock(clock);

		uc_1->ula_flagN(ula_flagN);
		uc_1->ula_flagZ(ula_flagZ);
		uc_1->ula_op(ula_op);

		uc_1->pc_load(pc_load);
		uc_1->pc_inc(pc_inc);

		uc_1->mem_addr_sel(mem_addr_sel);
		uc_1->mem_rd(mem_rd);
		uc_1->mem_wr(mem_wr);
		uc_1->mem_zr(mem_zr);

		uc_1->rd(rd);
		uc_1->wr(wr);

		uc_1->instruction_decoder(mem_data_out);

		uc_1->ac_load(ac_load);
		uc_1->ac_input_sel(ac_input_sel);

		uc_1->prog_mode(prog_mode);
		//------------------------------------------
		pc_1->inc(pc_inc);
		pc_1->load(pc_load);
		pc_1->data_out(pc_data_out);

		pc_1->input_a(mem_data_out);

		//------------------------------------------
		mux_1->input_a(pc_data_out);

		mux_1->sel(mem_addr_sel);
		mux_1->input_b(mem_data_out);
		mux_1->output(mem_addr_in);

		mux_2->sel(ac_input_sel);
		mux_2->output(ac_input);

		mux_2->input_a(ula_result);

		mux_2->input_b(prog_input);

		//------------------------------------------
		mem_1->rd(mem_rd);
		mem_1->wr(mem_wr);
		mem_1->zr(mem_zr);
		mem_1->data_in(mem_data_in);
		mem_1->data_out(mem_data_out);
		mem_1->addr_in(mem_addr_in);

		//------------------------------------------
		ula_1->flagN(ula_flagN);
		ula_1->flagZ(ula_flagZ);
		ula_1->op(ula_op);
		ula_1->result(ula_result);

		ula_1->input_a(mem_data_out);
		ula_1->input_b(ac_data_out);

		//------------------------------------------
		ac_1->load(ac_load);
		ac_1->input_a(ac_input);
		ac_1->data_out(ac_data_out);

		//------------------------------------------
		SC_CTHREAD(process, clock.pos())
	}


	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void rst(){
		// RESET
		program_counter=0;
	}

	void set_pgrm(sc_uint<8>* program_input){
		program = program_input;
	} 

	//=========================================================================
	// Machine State:
	void exit_state_process()
	{
		main_state = HALT_STATE;

		rd.write(false);
		wr.write(false);
	}

	void reset_state_process()
	{
		main_state = START_STATE;

		rst();

		rd.write(false);
		wr.write(false);
	}

	void start_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "START" << endl;
		cout << "===================================" << endl;
		rd.write(false);
		wr.write(false);
	}

	void standby_state_process()
	{
		rd.write(false);
		wr.write(false);
	}

	void halt_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() << "HALT!" << endl;
		cout << "===================================" << endl;
		cout << "+++++++++++++++++++++++++++++++++++" << endl;
		rd.write(false);
		wr.write(false);
		while(1){wait();};
	}

	void helloword_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: " << "HelloWord" << endl;
		cout << "===================================" << endl;
		rd.write(false);
		wr.write(false);
	}

	void prog_read_mem_state_process()
	{
		rd.write(true);
		wr.write(false);	
	}

	void prog_write_mem_state_process()
	{
		rd.write(false);
		wr.write(true);
	}

	void state_process()
	{
		if(prog_mode.read()) 	
		{	
			main_state = prog_input.read();
		}
		else
		{ 					
			main_state = program[program_counter];
		}	

		switch(main_state){
			case EXIT_STATE: 		
				exit_state_process(); 
				break;
			case NOP_STATE:
				program_counter++;
				break;
			case START_STATE:	
				start_state_process();
				program_counter++;
				break;
			case RESET_STATE: 	
				reset_state_process();
				program_counter++;
				break;			
			case HALT_STATE: 		
				halt_state_process();
				break;
			case HELLOWORD_STATE: 	
				helloword_state_process();
				program_counter++;
				break;

			case PROG_READ_MEM_STATE:
				prog_read_mem_state_process();
				break;
			case PROG_WRITE_MEM_STATE:
				prog_write_mem_state_process();
				break;

			default: standby_state_process();
		};


	}

		//-------------------------------------------------------------------------
	// Testbench:
	static int testbench(const char * trace_file)
	{
		cout << endl;
		cout << "***********************************" << endl;
		cout << "*                                 *" << endl;
		cout << "*         start testbench         *" << endl;
		cout << "*                                 *" << endl;
		cout << "***********************************" << endl;
		cout << endl;
		
		sc_uint<8> program_prog[]={
			//RESET_STATE,
			//START_STATE,
			//HELLOWORD_STATE,
			TARGET_LOCK_STATE,
			//TARGET_HELLOWORD_STATE,
			//TARGET_WRITE_MEM_STATE,
			TARGET_READ_MEM_STATE,
			TARGET_WRITE_MEM_STATE,
			TARGET_DROP_STATE,
			STANDBY_STATE
		};

		sc_uint<8> bootloader_neander[]={
			//RESET_STATE,
			//START_STATE,
			//HELLOWORD_STATE,
			//HELLOWORD_STATE,
			//HELLOWORD_STATE,
			STANDBY_STATE
		};


		sc_clock _clock("clk", 1, SC_NS);

		sc_signal<bool>			prog_mode;
		sc_signal<uint8_t>		prog_input;

		neander* _nea = new neander("Nea");
		programmer* _prog = new programmer("Prog");

		_prog->clock(_clock);		
		_nea->clock(_clock);

		_prog->set_program(program_prog);
		_nea->set_pgrm(bootloader_neander);

		_prog->prog_mode(prog_mode);
		_nea->prog_mode(prog_mode);

		_prog->prog_output(prog_input);
		_nea->prog_input(prog_input);

		
		//---------------------------------------------------------------------
		sc_trace_file *t_file = sc_create_vcd_trace_file(trace_file);
		sc_trace(t_file, _clock, "nea.clock");
		sc_trace(t_file, _nea->uc_1->clock, "nea.cu.clock");

		sc_trace(t_file, _nea->uc_1->main_state, "nea.cu.main_state");

		sc_trace(t_file, _nea->pc_load, "nea.pc_load");
		sc_trace(t_file, _nea->pc_inc, "nea.pc_inc");
		sc_trace(t_file, _nea->mem_addr_sel, "nea.mem_addr_sel");
		sc_trace(t_file, _nea->mem_rd, "nea.mem_rd");
		sc_trace(t_file, _nea->mem_wr, "nea.mem_wr");
		sc_trace(t_file, _nea->ac_load, "nea.ac_load");
		sc_trace(t_file, _nea->prog_input, "nea.prog_state");

		sc_trace(t_file, _nea->main_state, "nea.main_state");

		sc_trace(t_file, prog_mode, "prog_mode");
		sc_trace(t_file, prog_input, "prog_state");
		sc_trace(t_file, _nea->prog_mode, "nea.prog_mode");
		sc_trace(t_file, _nea->prog_input, "nea.prog_state");

		//---------------------------------------------------------------------
		sc_start(20, SC_NS);
		sc_stop();

		sc_close_vcd_trace_file(t_file);

		cout << endl;
		cout << "***********************************" << endl;
		cout << "*                                 *" << endl;
		cout << "*          end testbench          *" << endl;
		cout << "*                                 *" << endl;
		cout << "***********************************" << endl;
		cout << endl;
	  	
	  	return 0;
	}
};