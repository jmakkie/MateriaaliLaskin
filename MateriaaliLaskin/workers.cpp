#include "workers.h"

workers::workers(QString worker, double hours)
        : worker(worker), hours(hours)
{}

// getters
QString workers::getWorker() {return worker;}
double workers::getHours() {return hours;}


// setters
void workers::setWorker(QString worker) {this -> worker = worker;}
void workers::setHours(double hours) {this -> hours = hours;}
