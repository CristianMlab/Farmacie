#ifndef FARMACIE_LEGIT_STOC_FARMACIE_H
#define FARMACIE_LEGIT_STOC_FARMACIE_H

#include "lista_de_medicamente.h"

class stoc_farmacie : public lista_de_medicamente{

public:
    void push_back(const medicament& first, int second) override;

    const medicament &get_by_id(int id);

    const medicament &get_by_nume(const std::string& nume);

    friend std::ostream &operator<<(std::ostream &os, const stoc_farmacie &farmacie);
};

std::ostream &operator<<(std::ostream &os, const stoc_farmacie &farmacie);

#endif //FARMACIE_LEGIT_STOC_FARMACIE_H
