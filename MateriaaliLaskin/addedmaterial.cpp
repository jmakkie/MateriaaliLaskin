#include "addedmaterial.h"

addedmaterial::addedmaterial(QString name, QString length, double price, double amount, QString lisaName, double lisaValue)
    : name(name), length(length), price(price), amount(amount), lisaName(lisaName), lisaValue(lisaValue)
{

}

// getters
QString addedmaterial::getName() {return name;}
QString addedmaterial::getLength() {return length;}
double addedmaterial::getPrice() {return price;}
double addedmaterial::getAmount() {return amount;}
QString addedmaterial::getLisaName() {return lisaName;}
double addedmaterial::getLisaValue() {return lisaValue;}

// setters
void addedmaterial::setName(QString name) {this -> name = name;}
void addedmaterial::setLength(QString length) {this -> length = length;}
void addedmaterial::setPrice(double price) {this -> price = price;}
void addedmaterial::setAmount(double amount) {this -> amount = amount;}
void addedmaterial::setLisaName(QString lisaName) {this -> lisaName = lisaName;}
void addedmaterial::setLisaValue(double lisaValue)  {this -> lisaValue = lisaValue;}
