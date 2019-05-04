// *****************************************************************************
// lucas on 29/03/19.
// *****************************************************************************

#include <systemc.h>
#include "machine_state.h"
#include "pc.h"
#include "ac.h"
#include "ula.h"
#include "mux.h"
#include "mem.h"
#include "uc.h"
#include "neander.h"


int sc_main( int argc, char *argv[] )  {
	cout << "\n" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$                               $$" << endl; 	
	cout << "$$        Start Simulation       $$"<< endl;
	cout << "$$                               $$" << endl; 
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "\n" << endl;
	
	neander::testbench("trace");

	cout << "\n" << endl;
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$                               $$" << endl; 
	cout << "$$       Ending Simulation!      $$" << endl;
	cout << "$$                               $$" << endl; 
	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "\n" << endl;
	return 0;
};
