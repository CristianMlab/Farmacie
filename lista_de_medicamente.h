
#ifndef FARMACIE_LEGIT_LISTA_DE_MEDICAMENTE_H
#define FARMACIE_LEGIT_LISTA_DE_MEDICAMENTE_H

#include <vector>
#include "medicament.h"
#include "exceptii.h"

class lista_de_medicamente {
protected:
    std::vector<std::pair<medicament, int>> produse_cantitati;
public:
    lista_de_medicamente();

    explicit lista_de_medicamente(const std::vector<std::pair<medicament, int>> &produseCantitati);

    virtual void push_back(medicament& first, int second);

    const std::vector<std::pair<medicament, int>> &getProduseCantitati() const;

    double valoare_totala();
};


#endif //FARMACIE_LEGIT_LISTA_DE_MEDICAMENTE_H
