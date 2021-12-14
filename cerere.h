#ifndef FARMACIE_LEGIT_CERERE_H
#define FARMACIE_LEGIT_CERERE_H

#include "stoc_farmacie.h"

class cerere : public lista_de_medicamente{
private:
    bool prescriptie;
public:
    cerere();

    explicit cerere(bool prescriptie);

    bool prescriptie_check();

    bool exista_in_stoc( const stoc_farmacie& farm );

    friend std::ostream &operator<<(std::ostream &os, const cerere &cerere);
};

std::ostream &operator<<(std::ostream &os, const cerere &cerere);

#endif //FARMACIE_LEGIT_CERERE_H
