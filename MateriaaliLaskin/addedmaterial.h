#ifndef ADDEDMATERIAL_H
#define ADDEDMATERIAL_H

#include <QString>

class addedmaterial
{
public:
    addedmaterial(QString name, QString length, double price, double amount, QString lisaName, double lisaValue);

    // getters
    QString getName();
    QString getLength();
    double getPrice();
    double getAmount();
    QString getLisaName();
    double getLisaValue();
    // setters
    void setName(QString name);
    void setLength(QString length);
    void setPrice(double price);
    void setAmount(double amount);
    void setLisaName(QString lisaName);
    void setLisaValue(double lisaValue);

private:
    QString name;
    QString length;
    double price;
    double amount;
    QString lisaName;
    double lisaValue;
};

#endif // ADDEDMATERIAL_H
