#include "medicament.h"
#include <iostream>
#include <string>

medicament::medicament(){
    nr_medicamente++;
}

medicament::medicament(const std::string &nume, float pret, bool prescriptie, bool compensat) : nume(nume),pret(pret),prescriptie(prescriptie),compensat(compensat) {
    nr_medicamente++;
}

float medicament::getPret() const { return pret; }

bool medicament::isPrescriptie() const { return prescriptie; }

bool medicament::isCompensat() const { return compensat; }

int medicament::getMedId() const { return med_id; }

void medicament::setMedId(int medId) { med_id = medId; }

const std::string &medicament::getNume() const { return nume; }

std::ostream &operator<<(std::ostream &os, const medicament &medicament) {
    os << medicament.nume << "(id=" << medicament.med_id << ")";
    return os;
}

medicament::medicament(const medicament& copie) {
    this->nume = copie.nume;
    this->pret = copie.pret;
    this->prescriptie = copie.prescriptie;
    this->compensat = copie.compensat;
    this->med_id = copie.med_id;
}

medicament& medicament::operator=(const medicament& copie) {
    this->nume = copie.nume;
    this->pret = copie.pret;
    this->prescriptie = copie.prescriptie;
    this->compensat = copie.compensat;
    this->med_id = copie.med_id;
    std::cout << "op= med\n";
    return *this;
}

bool medicament::operator==(const medicament &rhs) const {
    return med_id == rhs.med_id;
}

bool medicament::operator!=(const medicament &rhs) const {
    return !(rhs == *this);
}

medicament::~medicament() {
    std::cout << "destr " << *this << ", ";
}

int medicament::nr_medicamente = 0;