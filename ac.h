// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef Ac_H
#define Ac_H

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

#endif