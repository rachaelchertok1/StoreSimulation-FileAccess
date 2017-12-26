#pragma once
#include "Stdafx.h"
#include "FileAccess.h"
#include "Product.h"
#ifndef STORESIMULATION_H
#define STORESIMULATION_H

class StoreSimulation
{
public:
	StoreSimulation(int argc, char* argv[]);
	~StoreSimulation();
	void PassI(int a_argc, char* a_argv[]);

private:
	string m_buff;
	FileAccess* store;
};

#endif