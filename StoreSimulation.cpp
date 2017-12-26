#include "StoreSimulation.h"


StoreSimulation::StoreSimulation(int argc, char* argv[]){
	store = new FileAccess(argc, argv);
}


StoreSimulation::~StoreSimulation()
{
}

/**/
/*
StoreSimulation::PassI() StoreSimulation::PassI()

NAME

StoreSimulation::PassI - runs the new file access class

SYNOPSIS

void StoreSimulation::PassI(int a_argc, char* a_argv[]);
a_argc             --> the count of the number of command line arguments.
a_argv[]   		   --> the array of command line arguments.

DESCRIPTION

This function maintains the flow of the program by calling 
the necessary functions in the correct order from 
the file access class. This includes reading and properly storing
the information from  both the Inventory and Sales files 
and then writing the necessary information to the Summary 
and Updated Inventory files.

RETURNS

Return type is void.

AUTHOR

Rachael Chertok

DATE

4:27pm 12/19/2017

*/
/**/
void
StoreSimulation::PassI(int a_argc, char* a_argv[]) {
	string m_buff;
	while (store->ReadInvFile(m_buff) == true) {
		//We want to continue reading while there are lines left to read
	}
	while (store->ReadSalesFile(m_buff) == true) {
		//We want to continue reading while there are lines left to read
	}

	store->WriteToSummaryFile();
	store->WriteToUpdatedInventoryFile();

	return;
}
