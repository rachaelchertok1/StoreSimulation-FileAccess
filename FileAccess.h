#include "Stdafx.h"
#include "Product.h"
#ifndef FILEACCESS_H
#define FILEACCESS_H

class FileAccess
{
public:
	//Default constructor
	FileAccess() {
		cout << "Default file constructor running :)" << endl;
	}

	//Opens the files
	FileAccess(int argc, char* argv[]);

	//Closes the files
	~FileAccess();

	//Gets next line from file 
	/*ADD IN FURTHER EXPLANATINO ACCORDING TO CODING STANDARD*/
	bool GetNextLineInv(string &a_invbuf);

	bool GetNextLineSales(string &a_salesbuf);

	bool ReadInvFile(string &a_buff);

	bool ReadSalesFile(string &a_buff);

	void WriteToUpdatedInventoryFile();

	void WriteToSummaryFile();

private:
	ifstream m_invFile;  //inventoryfile
	ifstream m_salesFile;  //sales file
	ofstream m_updatedInvFile;  //updated inventory file
	ofstream m_summaryFile;  //summary file

	vector<Product> productsList;
};

#endif