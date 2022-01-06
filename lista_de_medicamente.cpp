#include "lista_de_medicamente.h"


lista_de_medicamente::lista_de_medicamente() = default;

void lista_de_medicamente::push_back(medicament& first, int second){
    produse_cantitati.emplace_back(first, second);
}

const std::vector<std::pair<medicament, int>> &lista_de_medicamente::getProduseCantitati() const {
    return produse_cantitati;
}

lista_de_medicamente::lista_de_medicamente(const std::vector<std::pair<medicament, int>> &produseCantitati) {
    for(int i = 0; i<produseCantitati.size(); i++)
        if(produseCantitati[i].first.getMedId() != i){
            throw exceptie_adaugare_in_stoc();
        }
    this -> produse_cantitati = produseCantitati;
}

double lista_de_medicamente::valoare_totala() {
    float total = 0;
    for(auto & produse_cantitati_curr : produse_cantitati)
        if(produse_cantitati_curr.first.isCompensat()) {
            std::cout << "Se aplica reducere de 90% pentru medicamentul compensat " << produse_cantitati_curr.first << "\n";
            total += produse_cantitati_curr.first.getPret() * produse_cantitati_curr.second * 0.1;
        } else {
            total += produse_cantitati_curr.first.getPret() * produse_cantitati_curr.second;
        }
    return total;
}
