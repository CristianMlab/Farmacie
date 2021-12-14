#ifndef FARMACIE_LEGIT_MEDICAMENT_H
#define FARMACIE_LEGIT_MEDICAMENT_H

#include <string>
#include <iostream>

class medicament {
private:
    std::string nume;
    float pret;
    bool prescriptie; /// True pentru medicamentele care necesita prescriptie medicala, False pentru medicamentele "Over the counter"
    bool compensat; /// True pentru compensate, False pentru necompensate (se aplica 90% reducere la pret)
    int med_id; /// este unic si coincide cu pozitia medicamentului in vectorul din stocul farmaciei
public:
    static int nr_medicamente;

    medicament();

    medicament(const std::string &nume, float pret, bool prescriptie, bool compensat);

    float getPret() const;

    bool isPrescriptie() const;

    bool isCompensat() const;

    int getMedId() const;

    void setMedId(int medId);

    const std::string &getNume() const;

    friend std::ostream &operator<<(std::ostream &os, const medicament &medicament);

    medicament(const medicament& copie);

    medicament& operator=(const medicament& copie);

    bool operator==(const medicament &rhs) const;

    bool operator!=(const medicament &rhs) const;

    ///destructorul este apelat foarte des deoarece vectorul isi realoca spatiul dinamic la fiecare push_back
    ~medicament();
};

std::ostream &operator<<(std::ostream &os, const medicament &medicament);


#endif //FARMACIE_LEGIT_MEDICAMENT_H
