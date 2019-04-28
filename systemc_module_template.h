#include <systemc.h>
#include <iostream>

//*****************************************************************************
//Basic Template - Method:
SC_MODULE(_name)
{
	sc_in<bool>			clock;

	void process()
	{		
		//<<<
	}

	SC_CTOR(_name)
	{
		helloword();

		SC_METHOD(process)
		sensitive << clock.pos();
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//*****************************************************************************
//Basic Template - Thread:
SC_MODULE(_name)
{
	sc_in<bool>			clock;

	void process()
	{		
		while(1)
		{
			//<<<
			wait();
		}
	}

	SC_CTOR(_name)
	{
		helloword();

		SC_THREAD(process)
		sensitive_pos << clock;
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//*****************************************************************************
//Basic Template - CThread:
SC_MODULE(_name)
{
	sc_in<bool>			clock;

	void process()
	{		
		while(1)
		{
			//<<<
			wait();
		}
	}

	SC_CTOR(_name)
	{
		helloword();

		SC_CTHREAD(process, clock.pos())
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

//*****************************************************************************
//Basic Machine State Template:
SC_MODULE(_name){
	sc_in<bool>				clock;

	void process()
	{
		while(main_state)
		{
			state_process();
			wait();
		}
	}

	SC_CTOR(_name)
	{
		main_state = START_STATE;

		helloword();

		SC_CTHREAD(process, clock.pos())	
	}

	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}

	void reset(){
		mem_data_out.write(0);
	}

	//=========================================================================
	sc_signal<uint8_t> 	main_state;	

	void exit_state_process()
	{
		main_state = HALT_STATE;
	}

	void reset_state_process()
	{
		main_state = START_STATE;

		reset();
	}

	void start_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: HelloWord" << endl;
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
		while(1){};
	}

	void helloword_state_process()
	{
		cout << "===================================" << endl;
		cout << this->name() <<" THREAD says: HelloWord" << endl;
		cout << "===================================" << endl;
	}

	void state_process()
	{
		switch(main_state)
		{
			case EXIT_STATE:
				main_state = HALT_STATE; 		
				exit_state_process(); 
				break;
			case START_STATE:
				main_state = HELLOWORD_STATE; 	
				start_state_process(); 
				break;
			case RESET_STATE: 	
				main_state = START_STATE;
				reset_state_process(); 
				break;			
			case HALT_STATE: 		
				halt_state_process(); 
				break;
			case HELLOWORD_STATE: 	
				main_state = STANDBY_STATE;
				helloword_state_process(); 
				break;
			default:
				standby_state_process(); 
		}
	};
	//=========================================================================	
};