#include "exceptii.h"

exceptie_adaugare_in_stoc::exceptie_adaugare_in_stoc() : logic_error("Medicamentele trebuie adaugate in stoc in ordine") {}

exceptie_med_fals::exceptie_med_fals(const std::string &arg) : logic_error("Eroare: " + arg + " nu exista in stoc") {}

exceptie_med_fals::exceptie_med_fals(const int &arg) : logic_error("Eroare: medicamentul cu id " + std::to_string(arg) + " nu exista") {}
