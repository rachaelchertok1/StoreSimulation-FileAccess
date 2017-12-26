#include "Stdafx.h"
#include "FileAccess.h"

/**/
/*
FileAccess::FileAccess() FileAccess::FileAccess()

NAME

FileAccess::FileAccess - Opens Inventory file, Sales file, Summary file, and UpdatedInventory file

SYNOPSIS

FileAccess::FileAccess(int argc, char* argv[]);
a_argc             --> the count of the number of command line arguments.
a_argv[]   		   --> the array of command line arguments.

DESCRIPTION

This function checks if the correct number of files are included 
as command line arguemnts. The function also opens the Inventory file,
Sales file, Summary file, and UpdatedInventory file.

RETURNS

Returns the FileAccess object (this function is the 
FileAccess constructor).

AUTHOR

Rachael Chertok

DATE

9:30pm 12/18/2017

*/
/**/
FileAccess::FileAccess(int argc, char* argv[]){
	//If four files are not included in command line arguments
	if (argc != 5) {
		cerr << "Invalid number of files" << endl;
		exit(-1);
	}

	//Opening files
	m_invFile.open(argv[1], ios::in);
	m_salesFile.open(argv[2], ios::in);
	m_updatedInvFile.open(argv[3], ios::out);
	m_summaryFile.open(argv[4], ios::out);
	
	if (!m_invFile || !m_salesFile || !m_updatedInvFile || !m_summaryFile) {
		cerr << "One or multiple files could not be opened. Program terminated. " << endl;
		system("pause");
		exit(1);
	}

}


FileAccess::~FileAccess(){
	m_invFile.close();
	m_salesFile.close();
	m_updatedInvFile.close();
	m_summaryFile.close();
}

/**/
/*
FileAccess::GetNextLineInv() FileAccess::GetNextLineInv()

NAME

FileAccess::GetNextLineInv - reads in next line of Inventory file

SYNOPSIS

bool FileAccess::GetNextLineInv(string &a_invbuf);

a_invbuf           --> a buffer that stores on line at a time from the Inventory file.

DESCRIPTION

This function reads in the next line of the Inventory file.

RETURNS

Returns true if a line was read successfully from the file and
returns false if there was nothing else to read from the file. 
One of these two cases will always occur.

AUTHOR

Rachael Chertok

DATE

10:30pm 12/18/2017

*/
/**/
bool
FileAccess::GetNextLineInv(string &a_invbuf) {
	//If there is no more data in InvFile, return false
	if (m_invFile.eof()) {
		return false;
	}
	getline(m_invFile, a_invbuf);

	//Return true indicating success
	return true;
}

/**/
/*
FileAccess::GetNextLineSales() FileAccess::GetNextLineSales()

NAME

FileAccess::GetNextLineSales - reads in next line of Sales file

SYNOPSIS

bool FileAccess::GetNextLineSales(string &a_salesbuf);

a_salesbuf          --> a buffer that stores one line at a time from the Sales file.

DESCRIPTION

This function reads in the next line of the Sales file.

RETURNS

Returns true if a line was read successfully from the file and
returns false if there was nothing else to read from the file.
One of these two cases will always occur.

AUTHOR

Rachael Chertok

DATE

12:00pm 12/19/2017

*/
/**/
bool
FileAccess::GetNextLineSales(string &a_salesbuf) {
	//If there is no more data in salesFile, return false
	if (m_salesFile.eof()) {
		return false;
	}
	getline(m_salesFile, a_salesbuf);

	//Return true indicating success
	return true;
}

/**/
/*
FileAccess::ReadInvFile() FileAccess::ReadInvFile()

NAME

FileAccess::ReadInvFile - processes next line of Inventory file

SYNOPSIS

bool FileAccess::ReadInvFile(string &a_buff)

 a_buff         --> a buffer that stores one line at a time from the Inventory file.

DESCRIPTION

This function processes the data read from the next line of the inventory
file. This includes parsing the line into the merchandise name, price, and
initial quantity of the item. The price is then converted to a double
and the initial quantity is converted to an int. If the item of merchandise
already exists in the products list, the quantity of the product in the list
is updated. If the item of merchandise does not already exist in the products
list, a new merchandise item is created and added to the products list with the
merchandise name, price of the item, quantity of the item, and a boolean value set
to true to indicate that it was added as a merchandise item, and will not be a missing
item if sold.

RETURNS

Returns true if a line was read successfully from the file and
returns false if there was nothing else to read from the file.
One of these two cases will always occur.

AUTHOR

Rachael Chertok

DATE

1:37pm 12/19/2017

*/
/**/
bool
FileAccess::ReadInvFile(string &a_buff) {
	//If there is not a line to read in invFile, return false
	if (GetNextLineInv(a_buff) == false) {
		return false;
	}
	
	//Parsing a line of invFile
	istringstream ins(a_buff);
	string merchandiseName, price, initQuantity;
	ins >> merchandiseName >> price >> initQuantity;
	m_invFile >> merchandiseName >> price >> initQuantity;

	//Converting price from a string to a double
	double priceDoub = stod(price);

	//Converting initial quantity from a string to an int
	int initQuantityInt = stoi(initQuantity);

	bool itemFound = false;
	//If item already exists, adds to quantity of that object
	for (unsigned int i = 0; i < productsList.size(); i++) {
		if (merchandiseName == productsList[i].GetM_MerchandiseName()) {
			productsList[i].AddingToQuantity(initQuantityInt);
			itemFound = true;
			break;
		}
	}
	if (itemFound == false) {
		//Creating a new product and adding it to the productsList vector
		productsList.push_back(Product(merchandiseName, priceDoub, initQuantityInt, false));
	}
	
	//Return true to indicate line was read and handled properly
	return true;
}

/**/
/*
FileAccess::ReadSalesFile() FileAccess::ReadSalesFile()

NAME

FileAccess::ReadSalesFile - processes next line of Sales file

SYNOPSIS

bool FileAccess::ReadSalesFile(string &a_buff)

a_buff         --> a buffer that stores one line at a time from the Sales file.

DESCRIPTION

This function processes the data read from the next line of the Sales
file. This includes parsing the line into the merchandise name and
quantity sold of the item. The quantity sold is then converted to an int.
If the item of merchandise already exists in the products list, the quantity 
sold of the product in the list is updated. If the item of merchandise
does not already exist in the products list, a new merchandise item is 
created and added to the products list with the merchandise name
and a boolean value set to false to indicate that it if sold, the item 
would be considered missing because the item was not initially in the
inventory before being sold.

RETURNS

Returns true if a line was read successfully from the file and
returns false if there was nothing else to read from the file.
One of these two cases will always occur.

AUTHOR

Rachael Chertok

DATE

4:07pm 12/19/2017

*/
/**/
bool
FileAccess::ReadSalesFile(string &a_buff) {
	//If there is not a line to read in salesFile, return false
	if (GetNextLineSales(a_buff) == false) {
		return false;
	}

	//Parsing a line of salesFile
	istringstream ins(a_buff);
	string merchandiseNameSales, quantitySoldString;
	ins >> merchandiseNameSales >> quantitySoldString;

	//Converting after sale quantity from a string to an int
	int quantitySoldInt = stoi(quantitySoldString);

	//Looking for item in vector and finding index if it exists
	bool itemFound = false;
	for (unsigned int i = 0; i < productsList.size(); i++) {
		//If the product already exists, update its quantity sold
		if (merchandiseNameSales == productsList[i].GetM_MerchandiseName()) {
			productsList[i].SetM_QuantitySold(quantitySoldInt);
			itemFound = true;
			break;
		}
	}
	//If item not found, create a new item and set missing=true
	if (itemFound == false) {
		productsList.push_back(Product(merchandiseNameSales, quantitySoldInt, true));
	}

	//Return true to indicate line was read and handled properly
	return true;
}

/**/
/*
FileAccess::WriteToSummaryFile() FileAccess::WriteToSummaryFile()

NAME

FileAccess::WriteToSummaryFile - writes product information to Summary file

SYNOPSIS

void FileAccess::WriteToSummaryFile();

DESCRIPTION

This function writes information to the Summary file about the merchandise
sold, in descending alphabetical order. If the item was stored in the
inventory before being sold, the merchandise name, quantity sold,
and total money taken in are written to the Summary file. If the item
was not stored in the inventory before it was sold, only the merchandise
name and quantity sold are written to the Summary file.

RETURNS

Return type is void.

AUTHOR

Rachael Chertok

DATE

10:03pm 12/19/2017

*/
/**/
void
FileAccess::WriteToSummaryFile() {
	//Sorting products in descending alphabetical order before writing to summary file
	sort(productsList.begin(), productsList.end());
	
	//Writing the merchandise name, quantity sold, and money taken in
	//(ONLY for items that were sold)
	for (unsigned int i = 0; i < productsList.size(); i++) {
		if (productsList[i].GetM_QuantitySold() > 0){
			m_summaryFile << left << setw(20) << productsList[i].GetM_MerchandiseName() << setw(10)
				<< productsList[i].GetM_QuantitySold();
			if (productsList[i].GetM_Missing() == false) {
				m_summaryFile << setw(20) << productsList[i].CalculateTotalMoneyTakenIn() << endl;
			}
			else {
				m_summaryFile << endl;
			}		
		}
	}
}

/**/
/*
FileAccess::WriteToUpdatedInventoryFile() FileAccess::WriteToUpdatedInventoryFile()

NAME

FileAccess::WriteToUpdatedInventoryFile - writes product information to UpdatedInventory file

SYNOPSIS

FileAccess::WriteToUpdatedInventoryFile();

DESCRIPTION

This function writes information to the UpdatedInventory file about
all of the merchandise (both sold and not sold). The merchandise name,
price, and updated quantity are written to the file. If the item
is missing (meaning that it was sold, but was not already included
in the inventory list), the message "WARNING:MISSING ITEM" is written
to the file, to be displayed on the offending line. If there is a 
negative inventory (meaning that a larger quantity of the item was
sold than there was in the initial quantity), the message 
"WARNING:NEGATIVE INVENTORY" is written to the file, to be displayed
on the offending line.

RETURNS

Return type is void.

AUTHOR

Rachael Chertok

DATE

2:30pm 12/23/2017

*/
/**/
void
FileAccess::WriteToUpdatedInventoryFile() {
	//Writing the merchandise name, price, and updated quantity
	//to the updated inventory file
	for (unsigned int i = 0; i < productsList.size(); i++) {
		m_updatedInvFile << left << setw(20) << productsList[i].GetM_MerchandiseName() << setw(20)
			<< productsList[i].GetM_Price() << setw(20)
			<< productsList[i].CalculateQuantityAfterSold();
		
		//If an error occurs
		if (productsList[i].GetM_Missing() == true || productsList[i].CalculateQuantityAfterSold() < 0){
			//If product is a missing item in the inventory (sold but not originally in inventory)
			//Issue a missing item warning at end of offending line
			if (productsList[i].GetM_Missing() == true) {
				m_updatedInvFile << setw(20) << "WARNING:MISSING ITEM     ";
				if (productsList[i].CalculateQuantityAfterSold() < 0) {
					m_updatedInvFile << setw(20) <<"WARNING:NEGATIVE INVENTORY" << endl;
				}
				else {
					m_updatedInvFile << endl;
				}
			}

			//If negative inventory (a larger quantity of the item was sold than there was in original inventory)
			//Issue a negative inventory warning at the end of the offeending line
			else if (productsList[i].CalculateQuantityAfterSold() < 0) {
				m_updatedInvFile << setw(20) << "    NEGATIVE INVENTORY" << endl;
			}
		}
		else {
			m_updatedInvFile << endl;
		}
	}
}
