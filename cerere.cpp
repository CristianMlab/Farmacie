#include "cerere.h"

cerere::cerere() : prescriptie(false) {}

cerere::cerere(bool prescriptie) : prescriptie(prescriptie) {}

bool cerere::prescriptie_check() {
    bool medicamente_prescrise = false;
    for(auto & produse_cantitati_curr : produse_cantitati){
        if(produse_cantitati_curr.first.isPrescriptie())
            medicamente_prescrise = true;
    }
    if(medicamente_prescrise && !prescriptie){
        return false;
    }
    return true;
}

bool cerere::exista_in_stoc(const stoc_farmacie &farm) {
    std::vector<std::pair<medicament, int>> stoc = farm.getProduseCantitati();
    for(auto & produse_cantitati_cerere_curr : produse_cantitati){
        int id = produse_cantitati_cerere_curr.first.getMedId();
        if(id >= stoc.size())
            return false;
        if(stoc[id].first != produse_cantitati_cerere_curr.first)
            return false;
        if(stoc[id].second < produse_cantitati_cerere_curr.second)
            return false;
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const cerere &cerere) {
    os << "Cererea contine " << cerere.produse_cantitati.size() << " medicamente diferite:\n";
    for(const auto & produse_cantitati_curr : cerere.produse_cantitati)
        os << produse_cantitati_curr.first << " * " << produse_cantitati_curr.second << "\n";
    return os;
}
