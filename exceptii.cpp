#include "exceptii.h"

std::string turnargstr(const std::string &arg) {
    std::string result;
    std::stringstream ss;
    ss << "Eroare: " << arg << " nu exista in stoc";
    ss >> result;
    return result;
}

std::string turnargint(const int &arg){
    std::string result;
    std::stringstream ss;
    ss << "Eroare: medicamentul cu id " << arg << " nu exista in stoc";
    ss >> result;
    return result;
}

exceptie_adaugare_in_stoc::exceptie_adaugare_in_stoc() : logic_error("Medicamentele trebuie adaugate in stoc in ordine") {}

exceptie_med_fals::exceptie_med_fals(const std::string &arg) : logic_error(turnargstr(arg)) {}

exceptie_med_fals::exceptie_med_fals(const int &arg) : logic_error(turnargint(arg)) {}
