#pragma once
#include "Stdafx.h"
#ifndef PRODUCT_H
#define PRODUCT_H

class Product
{
public:
	Product(string a_merchandiseName, double a_price, int a_quantity, bool a_missing);
	Product(string a_merchandiseName, int a_quantitySold, bool a_missing);
	~Product();

	int AddingToQuantity(int a_newQuantity);
	int CalculateQuantityAfterSold();
	double CalculateTotalMoneyTakenIn();

	string GetM_MerchandiseName() {
		return m_merchandiseName;
	}
	double GetM_Price() {
		return m_price;
	}
	int GetM_Quantity() {
		return m_quantity;
	}
	int GetM_QuantitySold() {
		return m_quantitySold;
	}
	bool GetM_Missing() {
		return m_missing;
	}
	void SetM_QuantitySold(int a_quantitySold) {
		m_quantitySold = a_quantitySold;
	}

	//Overloading operators to use when sorting
	bool operator <(Product comparisonProduct);
	bool operator >(Product comparisonProduct);

private:
	string m_merchandiseName;
	double m_price;
	int m_quantity;
	int m_quantitySold;
	bool m_missing; //True if a merchandise item in the sales file is not in the inventory
};

#endif