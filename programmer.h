// #include "machine_state.h"

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
					target_read_memory_state_process(); 
					program_counter++;	 	
					break;
				case TARGET_WRITE_MEM_STATE:
					target_write_memory_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_HELLOWORD_STATE:
					target_helloword_state_process(); 
					program_counter++;	 	
					break;

				case TARGET_STANDBY_STATE:
					target_standby_state_process();

				default: standby_state_process(); 
			};
			wait();
		}	
	}
};