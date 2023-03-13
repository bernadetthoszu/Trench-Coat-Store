#include "TrenchCoat.h"
#include <string>
#include <format>

TrenchCoat::TrenchCoat(const int ID, const std::string& size, const std::string& colour, const int price, const int quantity, const std::string& photograph) : ID{ ID }, size{ size }, colour{ colour }, price{ price }, quantity{ quantity }, photograph{ photograph } {}

TrenchCoat::TrenchCoat(const TrenchCoat& other)
{
    //(*) 
    this->ID = other.ID;
    this->size = other.size;
    this->colour = other.colour;
    this->price = other.price;
    this->quantity = other.quantity;
    this->photograph = other.photograph;
}

TrenchCoat& TrenchCoat::operator=(const TrenchCoat& v)
{
    if (this == &v)
        return *this;

    this->ID = v.ID;
    this->size = v.size;
    this->colour = v.colour;
    this->price = v.price;
    this->quantity = v.quantity;
    this->photograph = v.photograph;

    return *this;
}

bool TrenchCoat::operator==(const TrenchCoat& v)
{
    return this->ID == v.ID && this->size == v.size && this->colour == v.colour && this->price == v.price && this->quantity == v.quantity && this->photograph == v.photograph;
}

std::string TrenchCoat::toSring() const
{
    //std::string strTrench = std::format("ID: {0}, Size: {1}, Colour: {2}, Quantity: {3}, Price: {4}, \n Photograph: {5}", this->ID, this->size, this->colour, this->quantity, this->price, this->photograph);
    std::string strTrench = "";
    strTrench += "ID: ";
    strTrench += std::to_string(this->ID);
    strTrench += ", Size: ";
    strTrench += this->size;
    strTrench += ", Colour: ";
    strTrench += this->colour;
    strTrench += ", Quantity: ";
    strTrench += std::to_string(this->quantity);
    strTrench += ", Price: ";
    strTrench += std::to_string(this->price);
    strTrench += ",\n Photograph: ";
    strTrench += this->photograph;
    //strTrench += "\n";

    return strTrench;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& is, TrenchCoat& t)
{
    if (!is.good())
        throw StreamError("Error opening file!\n");

    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 6)  //check whether data for trench coat is complete
        return is;
    t.ID = std::stoi(tokens[0]); //convert string representing an integer to int
    t.size = tokens[1];
    t.colour = tokens[2];
    t.quantity = std::stoi(tokens[3]);
    t.price = std::stoi(tokens[4]);
    t.photograph = tokens[5];

    return is;
}

std::ostream& operator<<(std::ostream& os, const TrenchCoat& t)
{
    if (!os.good())
        throw StreamError("Error opening file!\n");

    os << t.ID << "," << t.size << "," << t.colour << "," << t.quantity << "," << t.price << "," << t.photograph << "\n";
    return os;
}
