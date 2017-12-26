#include "Product.h"

Product::Product(string a_merchandiseName, double a_price, int a_quantity, bool a_missing)
{
	m_merchandiseName = a_merchandiseName;
	m_price = a_price;
	m_quantity = a_quantity;
	m_missing = a_missing;
	m_quantitySold = 0;;
}
Product::Product(string a_merchandiseName, int a_quantityAfterSales, bool a_missing) {
	m_merchandiseName = a_merchandiseName;
	m_quantitySold = a_quantityAfterSales;
	m_missing = a_missing;
	m_price = 0;
	m_quantity = 0;
}

Product::~Product()
{
}

//Adds to the quantity of the merchandise item
int Product::AddingToQuantity(int a_newQuantity) {
	return m_quantity += a_newQuantity;
}

//Calculates the quantity of the merchandise item after an amount was sold
int Product::CalculateQuantityAfterSold() {
	return m_quantity - m_quantitySold;
}

//Calculates total money taken in from selling the item
double Product::CalculateTotalMoneyTakenIn() {
	return m_price * m_quantitySold;
}

//Overloads < operator to use when sorting the products list
//To output in alphabetical order into the Summary file
bool Product::operator <(Product comparisonProduct) {
	return this->m_merchandiseName < comparisonProduct.m_merchandiseName;
}

//Overloads > operator to use when sorting the products list
//To output in alphabetical order into the Summary file
bool Product::operator >(Product comparisonProduct) {
	return this->m_merchandiseName > comparisonProduct.m_merchandiseName;
}

