#include <systemc.h>
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