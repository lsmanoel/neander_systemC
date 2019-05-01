// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef Ula_H
#define Ula_H

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

#endif