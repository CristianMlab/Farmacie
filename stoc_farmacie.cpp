#include "stoc_farmacie.h"

void stoc_farmacie::push_back(medicament &first, int second) {
    first.setMedId(produse_cantitati.size());
    produse_cantitati.emplace_back(first, second);
}

const medicament &stoc_farmacie::get_by_id(int id) {
    if(id < produse_cantitati.size())
        return produse_cantitati[id].first;
    throw exceptie_med_fals(id);
}

const medicament &stoc_farmacie::get_by_nume(const std::string &nume) {
    for(const auto & produse_cantitati_curr : produse_cantitati){
        if(produse_cantitati_curr.first.getNume() == nume)
            return produse_cantitati_curr.first;
    }
    throw exceptie_med_fals(nume);
}

template<> const medicament &stoc_farmacie::get_by_ceva<int>(int id_sau_nume){
    return get_by_id(id_sau_nume);
};

template<> const medicament &stoc_farmacie::get_by_ceva<std::string>(std::string id_sau_nume){
    return get_by_nume(id_sau_nume);
};


std::ostream &operator<<(std::ostream &os, const stoc_farmacie &farmacie) {
    os << "Stocul farmaciei contine " << farmacie.produse_cantitati.size() << " medicamente diferite:\n";
    for(const auto & produse_cantitati_curr : farmacie.produse_cantitati)
        os << produse_cantitati_curr.first << " * " << produse_cantitati_curr.second << "\n";
    return os;
}
