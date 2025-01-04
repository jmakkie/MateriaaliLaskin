#ifndef WORKERSCALCULATED_H
#define WORKERSCALCULATED_H

#import <QString>

class workersCalculated
{
public:
    workersCalculated(QString worker, double hours, double salary, double toPayment);

    // getters
    QString getWorker();
    double getHours();
    double getSalary();
    double getToPayment();

    // setters
    void setWorker(QString worker);
    void setHours(double hours);
    void setSalary(double salary);
    void setToPayment(double toPayment);

private:
    QString worker;
    double hours;
    double salary;
    double toPayment;
};

#endif // WORKERSCALCULATED_H
