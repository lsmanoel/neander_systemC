// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#ifndef Mem_H
#define Mem_H

//=============================================================================
//*****************************************************************************
//Memory:
SC_MODULE(mem){
	sc_in<bool> 			rd;
	sc_in<bool> 			wr;

	const sc_uint<8> 		zero=0;

	sc_in<uint8_t> 			addr_in;
	sc_in<uint8_t> 			data_in;
	sc_out<uint8_t> 		data_out;

	sc_uint<8>* memory_bank;

	void memory_load(sc_uint<8>* memory_bank_addrs){
		memory_bank = memory_bank_addrs;
		cout << this->name() <<" memory_bank[0]=" << memory_bank[0] << endl;
	}

	SC_CTOR(mem)
	{
		SC_METHOD(process);
		sensitive << rd << wr;
	}

	void process()
	{
		if(rd.read()==false) mem_rd_process();
		else if(wr.read()==true) mem_wr_process();
		else data_out.write(data_in.read());
	}

	void mem_rd_process()
	{
		
		cout << endl;
		cout << "---------------)))))---------------" << endl;
		cout << this->name() <<" memory_bank[addr_in.read()]=" << memory_bank[addr_in.read()] << endl;
		//data_out.write(36);
		data_out.write(memory_bank[addr_in.read()]);
		//data_out = memory_bank[addr_in.read()];
		cout << "---------------(((((---------------" << endl; 
	}

	void mem_wr_process()
	{
		memory_bank[addr_in.read()] = data_in.read();
	}

	void helloword(){
		cout << "-----------------------------------" << endl;
		cout << this->name() <<" says: HelloWord" << endl;
		cout << "-----------------------------------" << endl;
	}
};

#endif