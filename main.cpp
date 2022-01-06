#include <iostream>
#include <string>

#include "cerere.h"

void adauga_in_farmacie(lista_de_medicamente& f,medicament m, int nr){
    f.push_back(m, nr);
}

void adauga_in_cerere_dupa_id(cerere& c, stoc_farmacie& f, int id, int cant){
    c.push_back(const_cast<medicament &>(f.get_by_id(id)), cant);
}

void adauga_in_cerere_dupa_nume(cerere& c, stoc_farmacie& f, const std::string &nume, int cant){
    c.push_back(const_cast<medicament &>(f.get_by_nume(nume)), cant);
}

int main(){
    ///initializez niste date pentru stoc
    stoc_farmacie farm_1;
    try {
        adauga_in_farmacie(farm_1, medicament("Lactyferrin", 44.0, false, false), 5);
        adauga_in_farmacie(farm_1, medicament("ImmunoMix", 47.0, false, false), 3);
        adauga_in_farmacie(farm_1, medicament("Klearvol", 14.5, false, false), 8);
        adauga_in_farmacie(farm_1, medicament("Nasirus", 22.0, false, false), 9);
        adauga_in_farmacie(farm_1, medicament("Golamir", 26.0, false, false), 3);
        adauga_in_farmacie(farm_1, medicament("Sintusin", 22.0, false, false), 5);
        adauga_in_farmacie(farm_1, medicament("PropoGrip", 33.0, false, false), 2);
        adauga_in_farmacie(farm_1, medicament("Suvezen", 69.59, true, false), 6);
        adauga_in_farmacie(farm_1, medicament("Imigran", 11.82, true, false), 7);
        adauga_in_farmacie(farm_1, medicament("Ferretab", 27.47, true, true), 9);
        adauga_in_farmacie(farm_1, medicament("Nordimet", 262.2, true, true), 6);
    } catch(exceptie_adaugare_in_stoc &eroare) {
        std::cout << "\n" << eroare.what() << "\n";
    }
    std::cout << "\n\n" << farm_1 << "\n";

    ///initializez date pentru o cerere
    cerere cerere_1(false);
    try {
        adauga_in_cerere_dupa_id(cerere_1, farm_1, 4, 1);
        adauga_in_cerere_dupa_nume(cerere_1, farm_1, "Suvezen", 2);
        adauga_in_cerere_dupa_id(cerere_1, farm_1, 9, 3);
    } catch(exceptie_med_fals &eroare) {
        std::cout << "\n" << eroare.what() << "\n";
    }
    std::cout << "\n\n" << cerere_1 << "\n";

    ///verific cererea cu functiile implementate
    if(cerere_1.exista_in_stoc(farm_1)){
        std::cout << "\n\nMedicamentele cerute exista in stoc!\n";
    } else {
        std::cout << "\n\nMedicamentele cerute NU exista in stoc!\n";
    }
    std::cout << "\n";
    if(!cerere_1.prescriptie_check()){
        std::cout << "Medicamentele nu pot fi eliberate fara prezentarea unei retete medicale!" << "\n\n";
    }
    double pret = cerere_1.valoare_totala();
    std::cout << "Pretul total este de " << pret << "\n\n";

    ///verific operator= si cc la medicament
    medicament test_1("ImmunoMix", 47.0, false, false);
    medicament test_2;
    test_2 = test_1; //operator= apelat aici
    if(test_2 != test_1) std::cout << "operator= nu functioneaza\n\n";
    test_2.setMedId(-1);
    if(test_2 == test_1) std::cout << "operator= nu functioneaza\n\n";

    medicament test_3 = test_1; // cc apelat aici
    if(test_3 != test_1) std::cout << "cc nu functioneaza\n\n";
    test_3.setMedId(-2);
    if(test_3 == test_1) std::cout << "cc nu functioneaza\n\n";
}
