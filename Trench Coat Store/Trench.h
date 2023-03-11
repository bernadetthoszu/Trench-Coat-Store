#pragma once

#include "Exceptions.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class TrenchCoat
{
private:
	int ID;
	std::string size;
	std::string colour;
	int quantity;
	int price;
	std::string photograph;
public:
	//default constructor
	TrenchCoat() : ID{ 0 }, size{ "" }, colour{ "" }, quantity{ 0 }, price{ 0 }, photograph{ "" } {}
	//constructor with parameters
	TrenchCoat(const int ID, const std::string& size, const std::string& colour, const int price, const int quantity, const std::string& photograph);
	//copy constructor
	TrenchCoat(const TrenchCoat& other);

	//inline methods

	/*
	Get the ID of the coat. */
	int getID() const { return this->ID; }

	/*
	Get the size of the coat. */
	std::string getSize() const { return this->size; }

	/*
	Get the colour of the coat. */
	std::string getColour() const { return this->colour; }

	/*
	Get the quantity of the coat. */
	int getQuantity() const { return this->quantity; }

	/*
	Get the price of the coat. */
	int getPrice() const { return this->price; }

	/*
	Get the link to the coat's photograph. */
	std::string getPhotograph() const { return this->photograph; }

	/*
	Set the size of the coat. Size must be a value of type string. */
	void setSize(const std::string& new_size) { this->size = new_size; }

	/*
	Set the colour of the coat. Colour must be a value of type string. */
	void setColour(const std::string& new_colour) { this->colour = new_colour; }

	/*
	Set the quantity of the coat. Quantity must be a positive int. */
	void setQuantity(const int quantity) { this->quantity = quantity; }

	/*
	Set the price of the coat. Price must be a positive, non-zero, int. */
	void setPrice(const int price) { this->price = price; }

	/*
	Set the link to the photograph of the coat. The link must be a value of type string. */
	void setPhotograph(const std::string& new_photograph) { this->photograph = new_photograph; }

	TrenchCoat& operator=(const TrenchCoat& other);
	bool operator==(const TrenchCoat& other);

	/*
	Get printable version of an object of type TrenchCoat. */
	std::string toSring() const;

	friend std::istream& operator>>(std::istream& is, TrenchCoat& t);
	friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& t);
};

std::vector<std::string> tokenize(std::string str, char delimiter);
