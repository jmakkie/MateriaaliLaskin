#ifndef WORKERS_H
#define WORKERS_H
#include <QString>

class workers
{
public:
    workers(QString worker, double hours);

    // getters
    QString getWorker();
    double getHours();
    // setters
    void setWorker(QString worker);
    void setHours(double hours);

private:
    QString worker;
    double hours;
};

#endif // WORKERS_H
