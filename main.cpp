#include "Stdafx.h"
#include "FileAccess.h"
#include "StoreSimulation.h"

int main(int argc, char *argv[]) {
	StoreSimulation Test(argc, argv);
	Test.PassI(argc, argv);
	system("pause");
	return 0;
}