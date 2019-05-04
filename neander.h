// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef Neander_H
#define Neander_H

using namespace std;

//=============================================================================
//*****************************************************************************
//Neander:
SC_MODULE(neander){
	sc_in<bool>			clock;
	// sc_signal<bool>		clock_out;
	// sc_signal<bool>		clock_en;
	
	//----------------------------------------------
	uc*					uc_1;
	pc*					pc_1;
	mux*				mux_1;
	mem*				mem_1;
	ula*				ula_1;
	ac* 				ac_1;

	//----------------------------------------------
	sc_uint<8> 			program_counter;
	sc_uint<8>* 		program;
	sc_uint<8> 			main_state;	

	//----------------------------------------------
	sc_signal<bool>		pc_load;
	sc_signal<bool>		pc_inc;
	sc_signal<uint8_t>	pc_data_out;

	sc_signal<bool>		mem_addr_sel;
	sc_signal<bool>		mem_wr;
	sc_signal<bool>		mem_rd;

	sc_signal<uint8_t>	mem_data_in;
	sc_signal<uint8_t>	mem_data_out;
	sc_signal<uint8_t>	mem_addr_in;

	sc_signal<bool> 	ula_flagN;
	sc_signal<bool> 	ula_flagZ;
	sc_signal<bool>		ula_op_now;
	sc_signal<uint8_t>	ula_op;
	sc_signal<uint8_t>	ula_result;
	
	sc_signal<bool>		ac_load;
	sc_signal<uint8_t> 	ac_data_out;

	void process()
	{
		while(1)
		{	
			state_process();
			wait();
		}
	}

	// void method_clock_en()
	// {
	// 	if(clock_en.read()==true){
	// 		clock_out.write(clock.read());
	// 	}
	// 	else{
	// 		clock_out.write(false);
	// 	}
	// }

	SC_CTOR(neander)
	{
		uc_1 = new uc("UC");
		pc_1 = new pc("PC");
		mux_1 = new mux("MUX");
		mem_1 = new mem("MEM");
		ula_1 = new ula("ULA");
		ac_1 = new ac("AC");

		cout << '1';
		//------------------------------------------
		main_state = RESET_STATE;

		//------------------------------------------
		uc_1->clock(clock);
		// clock_en.write(true);

		uc_1->ula_flagN(ula_flagN);
		uc_1->ula_flagZ(ula_flagZ);
		uc_1->ula_op_now(ula_op_now);
		uc_1->ula_op(ula_op);

		uc_1->pc_load(pc_load);
		uc_1->pc_inc(pc_inc);

		uc_1->mem_addr_sel(mem_addr_sel);
		uc_1->mem_rd(mem_rd);
		uc_1->mem_wr(mem_wr);

		uc_1->instruction_decoder(mem_data_out);

		uc_1->ac_load(ac_load);

		//------------------------------------------
		pc_1->inc(pc_inc);
		pc_1->load(pc_load);
		pc_1->data_out(pc_data_out);

		pc_1->input_a(mem_data_out);

		//------------------------------------------
		mux_1->sel(mem_addr_sel);
		mux_1->input_a(pc_data_out);
		mux_1->input_b(mem_data_out);
		mux_1->output(mem_addr_in);

		//------------------------------------------
		mem_1->rd(mem_rd);
		mem_1->wr(mem_wr);
		mem_1->data_in(mem_data_in);
		mem_1->data_out(mem_data_out);
		mem_1->addr_in(mem_addr_in);

		//------------------------------------------
		ula_1->flagN(ula_flagN);
		ula_1->flagZ(ula_flagZ);
		ula_1->op_now(ula_op_now);
		ula_1->op(ula_op);
		ula_1->result(ula_result);

		ula_1->input_a(mem_data_out);
		ula_1->input_b(ac_data_out);

		//------------------------------------------
		ac_1->load(ac_load);
		ac_1->input_a(ula_result);
		ac_1->data_out(ac_data_out);



		//------------------------------------------
		SC_CTHREAD(process, clock.pos())

		// SC_METHOD(method_clock_en)
		// sensitive << clock << clock_en;
	}


	void helloword(){
		cout << endl;
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void reset_machine()
	{
		main_state = RESET_STATE;
	}

	void start_machine()
	{
		main_state = START_STATE;
	}

	void stop_machine()
	{
		main_state = STOP_STATE;
	}

	void set_program(sc_uint<8>* program_input){
		program = program_input;
	} 

	//=========================================================================
	// Machine State:
	void exit_state_process()
	{
		main_state = HALT_STATE;

	}

	void halt_state_process()
	{
		cout << endl;
		cout << "===================================" << endl;
		cout << this->name() << " says: HALT!" << endl;
		cout << "===================================" << endl;
		cout << "+++++++++++++++++++++++++++++++++++" << endl;
		
		// clock_en.write(false);
		
		// while(1){wait();};
	}

	void reset_state_process()
	{
		// RESET
		program_counter=0;
	}

	void start_state_process()
	{
		// cout << "===================================" << endl;
		// cout << this->name() <<" THREAD says: " << "START" << endl;
		// cout << "===================================" << endl;

		uc_1->start_machine();
	}

	void stop_state_process()
	{
		// cout << "===================================" << endl;
		// cout << this->name() <<" THREAD says: " << "STOP" << endl;
		// cout << "===================================" << endl;
		// clock_en.write(false);
	}

	void helloword_state_process()
	{
		// cout << "===================================" << endl;
		// cout << this->name() <<" THREAD says: " << "HelloWord" << endl;
		// cout << "===================================" << endl;
	}

	void standby_state_process()
	{

	}

	void state_process()
	{
					
		main_state = program[program_counter];	

		switch(main_state){
			case EXIT_STATE: 		
				exit_state_process(); 
				break;
			case NOP_STATE:
				program_counter++;
				break;
			case HALT_STATE: 		
				halt_state_process();
				break;
			case RESET_STATE: 	
				reset_state_process();
				program_counter++;
				break;			
			case START_STATE:	
				start_state_process();
				program_counter++;
				break;
			case STOP_STATE:	
				stop_state_process();
				program_counter++;
				break;
			case HELLOWORD_STATE: 	
				helloword_state_process();
				program_counter++;
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

		sc_uint<8> bootloader_neander[]={
			RESET_STATE,
			START_STATE,
			// HELLOWORD_STATE,
			STANDBY_STATE,
		};


		sc_clock _clock("clk", 1, SC_NS);

		neander* _nea = new neander("Nea");
	
		_nea->clock(_clock);

		_nea->set_program(bootloader_neander);

		sc_uint<8> memory_bank_1[256];

		sc_uint<8> _program_index = 0;

		//memory_bank_1[_program_index++]=NOP_STATE;
		memory_bank_1[_program_index++]=LDA_STATE;
		memory_bank_1[_program_index++]=10;
		memory_bank_1[_program_index++]=ADD_STATE;
		memory_bank_1[_program_index++]=11;
		memory_bank_1[_program_index++]=STA_STATE;
		memory_bank_1[_program_index++]=255;
		memory_bank_1[_program_index++]=HLT_STATE;
		while(_program_index<255){
			memory_bank_1[_program_index++]=0;
		}



		_nea->mem_1->memory_load(memory_bank_1);
		
		//---------------------------------------------------------------------
		sc_trace_file *t_file = sc_create_vcd_trace_file(trace_file);
		sc_trace(t_file, _clock, "nea.clock");
		// sc_trace(t_file, _nea->clock_out, "nea.clock");
		sc_trace(t_file, _nea->uc_1->clock, "nea.cu.clock");

		sc_trace(t_file, _nea->uc_1->main_state, "nea.cu.main_state");
		sc_trace(t_file, _nea->uc_1->instruction_decoder, "nea.cu.instruction_decoder");

		sc_trace(t_file, _nea->pc_load, "nea.pc_load");
		sc_trace(t_file, _nea->pc_inc, "nea.pc_inc");
		sc_trace(t_file, _nea->mem_addr_sel, "nea.mem_addr_sel");
		sc_trace(t_file, _nea->mem_addr_in, "nea.mem_addr_in");
		sc_trace(t_file, _nea->mem_data_out, "nea.mem_data_out");
		sc_trace(t_file, _nea->mem_data_in, "nea.mem_data_out");
		sc_trace(t_file, _nea->mem_rd, "nea.mem_rd");
		sc_trace(t_file, _nea->mem_wr, "nea.mem_wr");
		sc_trace(t_file, _nea->ac_load, "nea.ac_load");
		sc_trace(t_file, _nea->ula_op, "nea.ula_op");
		sc_trace(t_file, _nea->ula_op_now, "nea.ula_op_now");

		sc_trace(t_file, _nea->main_state, "nea.main_state");
		sc_trace(t_file, _nea->pc_data_out, "nea.pc_data_out");
		sc_trace(t_file, _nea->pc_1->data_out, "nea.pc.data_out");


		sc_trace(t_file, _nea->mem_1->rd, "nea.mem.rd");
		sc_trace(t_file, _nea->mem_1->data_out, "nea.mem.data_out");
		sc_trace(t_file, _nea->mem_1->data_out, "nea.mem.data_out");

		sc_trace(t_file, _nea->ac_1->data_out, "nea.ac.data_out");
		sc_trace(t_file, _nea->ac_data_out, "nea.ac_data_out");
		sc_trace(t_file, _nea->ula_result, "nea.ula_result");
		sc_trace(t_file, _nea->ula_1->input_a, "nea.ula.input_a");
		sc_trace(t_file, _nea->ula_1->input_b, "nea.ula.input_b");

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

#endif