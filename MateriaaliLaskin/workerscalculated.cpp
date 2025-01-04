#include "workerscalculated.h"

workersCalculated::workersCalculated(QString worker, double hours, double salary, double toPayment)
    : worker(worker), hours(hours), salary(salary), toPayment(toPayment)
{}


// getters
QString workersCalculated::getWorker() {return worker;}
double workersCalculated::getHours() {return hours;}
double workersCalculated::getSalary() {return salary;}
double workersCalculated::getToPayment() {return toPayment;}

// setters
void workersCalculated::setWorker(QString worker) {this -> worker = worker;}
void workersCalculated::setHours(double hours) {this -> hours = hours;}
void workersCalculated::setSalary(double salary) {this -> salary = salary;}
void workersCalculated::setToPayment(double toPayment) {this -> toPayment = toPayment;}
