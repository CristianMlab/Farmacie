#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class medicament{
private:
    std::string nume;
    float pret;
    bool prescriptie; /// True pentru medicamentele care necesita prescriptie medicala, False pentru medicamentele "Over the counter"
    bool compensat; /// True pentru compensate, False pentru necompensate (se aplica 90% reducere la pret)
public:
    medicament() = default;

    medicament(const std::string &nume, float pret, bool prescriptie, bool compensat) : nume(nume), pret(pret),
                                                                                        prescriptie(prescriptie),
                                                                                        compensat(compensat) {}

    float getPret() const {
        return pret;
    }

    bool isPrescriptie() const {
        return prescriptie;
    }

    bool isCompensat() const {
        return compensat;
    }

    void setNume(const std::string &nume) {
        medicament::nume = nume;
    }

    void setPret(float pret) {
        medicament::pret = pret;
    }

    void setPrescriptie(bool prescriptie) {
        medicament::prescriptie = prescriptie;
    }

    void setCompensat(bool compensat) {
        medicament::compensat = compensat;
    }

    friend std::ostream &operator<<(std::ostream &os, const medicament &medicament) {
        os << medicament.nume;
        return os;
    }

    bool operator==(const medicament &rhs) const {
        return nume == rhs.nume &&
               pret == rhs.pret &&
               prescriptie == rhs.prescriptie &&
               compensat == rhs.compensat;
    }

    bool operator!=(const medicament &rhs) const {
        return !(rhs == *this);
    }
};

class stoc_farmacie{
private:
    std::vector<medicament> produse;
    std::vector<int> cantitati;
public:
    stoc_farmacie() = default;

    stoc_farmacie(const std::vector<medicament> &produse, const std::vector<int> &cantitati) : produse(produse), cantitati(cantitati) {}

    const std::vector<medicament> &getProduse() const {
        return produse;
    }

    const std::vector<int> &getCantitati() const {
        return cantitati;
    }

    void setProduse(const std::vector<medicament> &produse) {
        stoc_farmacie::produse = produse;
    }

    void setCantitati(const std::vector<int> &cantitati) {
        stoc_farmacie::cantitati = cantitati;
    }

    friend std::ostream &operator<<(std::ostream &os, const stoc_farmacie &farmacie) {
        os << "Farmacia are " << farmacie.produse.size() << " medicamente diferite:\n";
        for(int i=0; i<farmacie.produse.size(); i++)
            os << farmacie.produse[i] << " * " << farmacie.cantitati[i] << "\n";
        return os;
    }
};

class cerere{
private:
    std::vector<medicament> produse;
    std::vector<int> cantitati;
    bool prescriptie;

public:
    cerere(const std::vector<medicament> &produse, const std::vector<int> &cantitati, bool prescriptie) :
    produse(produse), cantitati(cantitati), prescriptie(prescriptie) {}

    const std::vector<medicament> &getProduse() const {
        return produse;
    }

    void setProduse(const std::vector<medicament> &produse) {
        cerere::produse = produse;
    }

    const std::vector<int> &getCantitati() const {
        return cantitati;
    }

    void setCantitati(const std::vector<int> &cantitati) {
        cerere::cantitati = cantitati;
    }

    bool isPrescriptie() const {
        return prescriptie;
    }

    void setPrescriptie(bool prescriptie) {
        cerere::prescriptie = prescriptie;
    }

    float pret_total(){
        float total = 0;
        for(int i=0; i<produse.size(); i++)
            if(produse[i].isCompensat()) {
                std::cout << "Se aplica reducere de 90% pentru medicamentul compensat " << produse[i] << "\n";
                total += produse[i].getPret() * cantitati[i] * 0.1;
            } else {
                total += produse[i].getPret() * cantitati[i];
            }
        return total;
    }

    bool prescriptie_check(){
        bool medicamente_prescrise = false;
        for(int i=0; i<produse.size(); i++){
            if(produse[i].isPrescriptie())
                medicamente_prescrise = true;
        }
        if(medicamente_prescrise && !prescriptie){
            return false;
        }
        return true;
    }

    bool exista_in_stoc( stoc_farmacie farm ){
        std::vector<medicament> stoc_m = farm.getProduse();
        std::vector<int> stoc_c = farm.getCantitati();
        for(int i=0; i<produse.size(); i++){
            int nr = 0;
            auto it = stoc_m.begin();
            for (; it != stoc_m.end(); it++) {
                if(*it == produse[i])
                    break;
                nr++;
            }
            if( it == stoc_m.end() ){
                return 0;
            }
            if(stoc_c[nr] < cantitati[i]){
                return 0;
            }
        }
        return 1;
    }

    friend std::ostream &operator<<(std::ostream &os, const cerere &cerere) {
        os << "Cererea are " << cerere.produse.size() << " medicamente diferite:\n";
        for(int i=0; i<cerere.produse.size(); i++)
            os << cerere.produse[i] << " * " << cerere.cantitati[i] << "\n";
        return os;
    }
};

int main(){
    ///initializez niste date pentru stoc
    std::vector<medicament> medicamente_farmacie;
    medicamente_farmacie.push_back(medicament("Lactyferrin", 44.0, 0, 0));
    medicamente_farmacie.push_back(medicament("ImmunoMix", 47.0, 0, 0));
    medicamente_farmacie.push_back(medicament("Klearvol", 14.5, 0, 0));
    medicamente_farmacie.push_back(medicament("Nasirus", 22.0, 0, 0));
    medicamente_farmacie.push_back(medicament("Golamir", 26.0, 0, 0));
    medicamente_farmacie.push_back(medicament("Sintusin", 22.0, 0, 0));
    medicamente_farmacie.push_back(medicament("PropoGrip", 33.0, 0, 0));
    medicamente_farmacie.push_back(medicament("Suvezen", 69.59, 1, 0));
    medicamente_farmacie.push_back(medicament("Imigran", 11.82, 1, 0));
    medicamente_farmacie.push_back(medicament("Ferretab", 27.47, 1, 1));
    medicamente_farmacie.push_back(medicament("Nordimet", 262.2, 1, 1));
    std::vector<int> cant_farmacie = {5, 3, 8, 9, 3, 5, 2, 6, 7, 9, 6};
    stoc_farmacie farm_1(medicamente_farmacie, cant_farmacie);
    std::cout << farm_1 << "\n";

    ///initializez date pentru o cerere
    std::vector<medicament> medicamente_cerere;
    medicamente_cerere.push_back(medicamente_farmacie[4]);
    medicamente_cerere.push_back(medicamente_farmacie[7]);
    medicamente_cerere.push_back(medicamente_farmacie[9]);
    std::vector<int> cant_cerere = {1, 2, 3};
    cerere cerere_1(medicamente_cerere, cant_cerere, 0);
    std::cout << cerere_1 << "\n";

    ///verific cererea cu functiile implementate
    if(cerere_1.exista_in_stoc(farm_1)){
        std::cout << "Medicamentele cerute exista in stoc!\n";
    } else {
        std::cout << "Medicamentele cerute NU exista in stoc!\n";
    }
    std::cout << "\n";
    if(!cerere_1.prescriptie_check()){
        std::cout << "Medicamentele nu pot fi eliberate fara prezentarea unei retete medicale!" << "\n\n";
    }
    float pret = cerere_1.pret_total();
    std::cout << "Pretul total este de " << pret << "\n";
}

