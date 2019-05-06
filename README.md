# Neander - SystemC

* **to Clear:**
		$ rm -rf build

* **to Build:**
		$ mkdir build && cd build && cmake ../ && make && ./neander && cd ..
	
* **to ReBuild:**
		$ rm -rf build && mkdir build && cd build && cmake ../ && make && ./neander && cd ..


-----

# **Modelsim Script:** [**trace.do**](https://github.com/lsmanoel/neander_systemC/blob/master/trace.do)


- - -

# EXAMPLE

1. **LDA 10** - Load the accumulator register with value 10. **$Ac[10]=10$**
2. **ADD 11** - Add 11 with value (10) in accumulator reg. **$Ac[21]=Ac[10]+11$**
2. **ADD 1** - Add 1 with value (21) in accumulator reg. **$Ac[22]=Ac[21]+1$**
3. **STA 255** - Stores the value of the accumulator register at memory address 255. **$mem(255)=Ac(22)$**
5. **HLT** - Halt!


		sc_uint<8> memory_bank_1[256];

		sc_uint<8> _program_index = 0;

		memory_bank_1[_program_index++]=LDA_STATE;
		memory_bank_1[_program_index++]=10;
		memory_bank_1[_program_index++]=ADD_STATE;
		memory_bank_1[_program_index++]=11;
		memory_bank_1[_program_index++]=ADD_STATE;
		memory_bank_1[_program_index++]=1;
		memory_bank_1[_program_index++]=STA_STATE;
		memory_bank_1[_program_index++]=255;
		memory_bank_1[_program_index++]=HLT_STATE;
        
		while(_program_index<255){
			memory_bank_1[_program_index++]=0;
		}

![
](https://raw.githubusercontent.com/lsmanoel/neander_systemC/master/img/modelsim_1.png)