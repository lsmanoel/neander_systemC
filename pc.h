// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef PC_H
#define PC_H

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
		if(load.read()==true) _counter = input_a.read();

		data_out.write(_counter);
		_counter++;
	}

	SC_CTOR(pc)
	{
		SC_METHOD(process)
		sensitive << inc.pos();
	}

	void helloword()
	{
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}	
};

#endif