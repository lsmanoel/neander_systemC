// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef Mux_H
#define Mux_H

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

#endif