#include <iostream>
#include <string>

#include "cerere.h"

void adauga_in_farmacie(lista_de_medicamente& f,medicament m, int nr){
    f.push_back(m, nr);
}

template<typename T>
void adauga_in_cerere_dupa_ceva(lista_de_medicamente& c, stoc_farmacie& f, T id_sau_nume, int cant){
    if(typeid(T) == typeid(int) || typeid(T) == typeid(std::string))
        c.push_back(const_cast<medicament &>(f.get_by_ceva(id_sau_nume)), cant);
    else
        throw exceptie_med_fals("aiurea");
}

int main(){
    ///initializez niste date pentru stoc
    lista_de_medicamente *farm_1;
    farm_1 = lista_de_medicamente::Create("stoc");
    try {
        adauga_in_farmacie(*farm_1, medicament("Lactyferrin", 44.0, false, false), 5);
        adauga_in_farmacie(*farm_1, medicament("ImmunoMix", 47.0, false, false), 3);
        adauga_in_farmacie(*farm_1, medicament("Klearvol", 14.5, false, false), 8);
        adauga_in_farmacie(*farm_1, medicament("Nasirus", 22.0, false, false), 9);
        adauga_in_farmacie(*farm_1, medicament("Golamir", 26.0, false, false), 3);
        adauga_in_farmacie(*farm_1, medicament("Sintusin", 22.0, false, false), 5);
        adauga_in_farmacie(*farm_1, medicament("PropoGrip", 33.0, false, false), 2);
        adauga_in_farmacie(*farm_1, medicament("Suvezen", 69.59, true, false), 6);
        adauga_in_farmacie(*farm_1, medicament("Imigran", 11.82, true, false), 7);
        adauga_in_farmacie(*farm_1, medicament("Ferretab", 27.47, true, true), 9);
        adauga_in_farmacie(*farm_1, medicament("Nordimet", 262.2, true, true), 6);
    } catch(exceptie_adaugare_in_stoc &eroare) {
        std::cout << "\n" << eroare.what() << "\n";
    }
    std::cout << "\n\n" << *(stoc_farmacie*)farm_1 << "\n";

    ///initializez date pentru o cerere
    lista_de_medicamente *cerere_1;
    cerere_1 = lista_de_medicamente::Create("cerere");
    try {
        adauga_in_cerere_dupa_ceva<int>(*cerere_1, *(stoc_farmacie*)farm_1, 4, 1);
        adauga_in_cerere_dupa_ceva<std::string>(*cerere_1, *(stoc_farmacie*)farm_1, "Suvezen", 2);
        adauga_in_cerere_dupa_ceva<int>(*cerere_1, *(stoc_farmacie*)farm_1, 9, 3);
    } catch(exceptie_med_fals &eroare) {
        std::cout << "\n" << eroare.what() << "\n";
    }
    std::cout << "\n\n" << *(cerere*)cerere_1 << "\n";

    ///verific cererea cu functiile implementate
    if(((cerere*)cerere_1)->exista_in_stoc(*(stoc_farmacie*)farm_1)){
        std::cout << "\n\nMedicamentele cerute exista in stoc!\n";
    } else {
        std::cout << "\n\nMedicamentele cerute NU exista in stoc!\n";
    }
    std::cout << "\n";
    if(!((cerere*)cerere_1)->prescriptie_check()){
        std::cout << "Medicamentele nu pot fi eliberate fara prezentarea unei retete medicale!" << "\n\n";
    }
    double pret = cerere_1->valoare_totala();
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
