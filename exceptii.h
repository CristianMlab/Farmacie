#ifndef FARMACIE_LEGIT_EXCEPTII_H
#define FARMACIE_LEGIT_EXCEPTII_H

#include <stdexcept>

class exceptie_adaugare_in_stoc : public std::logic_error {
public:
    explicit exceptie_adaugare_in_stoc();
};

class exceptie_med_fals : public std::logic_error {
public:
    explicit exceptie_med_fals(const std::string &arg);
    explicit exceptie_med_fals(const int &arg);
};


#endif //FARMACIE_LEGIT_EXCEPTII_H
