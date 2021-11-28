#include <iostream>
#include <string>
#include <vector>

class medicament{
private:
    std::string nume;
    float pret;
    bool prescriptie; /// True pentru medicamentele care necesita prescriptie medicala, False pentru medicamentele "Over the counter"
    bool compensat; /// True pentru compensate, False pentru necompensate (se aplica 90% reducere la pret)
    int med_id; /// este unic si coincide cu pozitia medicamentului in vectorul din stocul farmaciei
public:
    medicament() = default;

    medicament(const std::string &nume, float pret, bool prescriptie, bool compensat, int medId) :
    nume(nume),pret(pret),prescriptie(prescriptie),compensat(compensat),med_id(medId) {}

    float getPret() const {
        return pret;
    }

    bool isPrescriptie() const {
        return prescriptie;
    }

    bool isCompensat() const {
        return compensat;
    }

    int getMedId() const {
        return med_id;
    }

    void setMedId(int medId) {
        med_id = medId;
    }

    const std::string &getNume() const {
        return nume;
    }

    friend std::ostream &operator<<(std::ostream &os, const medicament &medicament) {
        os << medicament.nume << "(id=" << medicament.med_id << ")";
        return os;
    }

    medicament(const medicament& copie) {
        this->nume = copie.nume;
        this->pret = copie.pret;
        this->prescriptie = copie.prescriptie;
        this->compensat = copie.compensat;
        this->med_id = copie.med_id;
    }

    medicament& operator=(const medicament& copie) {
        this->nume = copie.nume;
        this->pret = copie.pret;
        this->prescriptie = copie.prescriptie;
        this->compensat = copie.compensat;
        this->med_id = copie.med_id;
        std::cout << "op= med\n";
        return *this;
    }

    bool operator==(const medicament &rhs) const {
        return med_id == rhs.med_id;
    }

    bool operator!=(const medicament &rhs) const {
        return !(rhs == *this);
    }

    ///destructorul este apelat foarte des deoarece vectorul isi realoca spatiul dinamic la fiecare push_back
    ~medicament() {
        std::cout << "destr " << *this << ", ";
    }
};

class stoc_farmacie{
private:
    std::vector<std::pair<medicament, int>> produse_cantitati;
public:
    stoc_farmacie() = default;

    /*
    explicit stoc_farmacie(const std::vector<std::pair<medicament, int>> &produseCantitati) {
        for(int i = 0; i<produseCantitati.size(); i++)
            if(produseCantitati[i].first.getMedId() != i){
                std::cout << "\n\nEroare: ID gresit";
                exit(1);
            }
        this -> produse_cantitati = produseCantitati;
    }
    */

    int get_next_id(){
        return produse_cantitati.size();
    }

    /// daca nu este corespunzator idul programul se opreste
    void push_back(const medicament& first, int second){
        if(first.getMedId() == get_next_id())
            produse_cantitati.emplace_back(first, second);
        else {
            std::cout << "\n\nEroare: ID gresit, medicamentul nu a fost adaugat in stocul farmaciei";
        }
    }

    const medicament &get_by_id(int id){
        return produse_cantitati[id].first;
    }

    int get_by_nume(const std::string& nume){
        for(const auto & produse_cantitati_curr : produse_cantitati){
            if(produse_cantitati_curr.first.getNume() == nume)
                return produse_cantitati_curr.first.getMedId();
        }
        std::cout << "Nu exista medicament cu numele " << nume << "\n";
        return -1;
    }

    const std::vector<std::pair<medicament, int>> &getProduseCantitati() const {
        return produse_cantitati;
    }

    friend std::ostream &operator<<(std::ostream &os, const stoc_farmacie &farmacie) {
        os << "Stocul farmaciei contine " << farmacie.produse_cantitati.size() << " medicamente diferite:\n";
        for(const auto & produse_cantitati_curr : farmacie.produse_cantitati)
            os << produse_cantitati_curr.first << " * " << produse_cantitati_curr.second << "\n";
        return os;
    }
};

class cerere{
private:
    std::vector<std::pair<medicament, int>> produse_cantitati;
    bool prescriptie;
public:
    cerere() : prescriptie(false) {}

    /*
    cerere(const std::vector<std::pair<medicament, int>> &produseCantitati, bool prescriptie) :
    produse_cantitati(produseCantitati), prescriptie(prescriptie) {}
    */

    void push_back(const medicament& first, int second){
        produse_cantitati.emplace_back(first, second);
    }

    float pret_total(){
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

    bool prescriptie_check(){
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

    bool exista_in_stoc( const stoc_farmacie& farm ){
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

    friend std::ostream &operator<<(std::ostream &os, const cerere &cerere) {
        os << "Cererea contine " << cerere.produse_cantitati.size() << " medicamente diferite:\n";
        for(const auto & produse_cantitati_curr : cerere.produse_cantitati)
            os << produse_cantitati_curr.first << " * " << produse_cantitati_curr.second << "\n";
        return os;
    }
};

int main(){
    ///initializez niste date pentru stoc
    stoc_farmacie farm_1;
    farm_1.push_back(medicament("Lactyferrin", 44.0, false, false, farm_1.get_next_id()), 5);
    farm_1.push_back(medicament("ImmunoMix", 47.0, false, false, farm_1.get_next_id()), 3);
    farm_1.push_back(medicament("Klearvol", 14.5, false, false, farm_1.get_next_id()), 8);
    farm_1.push_back(medicament("Nasirus", 22.0, false, false, farm_1.get_next_id()), 9);
    farm_1.push_back(medicament("Golamir", 26.0, false, false, farm_1.get_next_id()), 3);
    farm_1.push_back(medicament("Sintusin", 22.0, false, false, farm_1.get_next_id()), 5);
    farm_1.push_back(medicament("PropoGrip", 33.0, false, false, farm_1.get_next_id()), 2);
    farm_1.push_back(medicament("Suvezen", 69.59, true, false, farm_1.get_next_id()), 6);
    farm_1.push_back(medicament("Imigran", 11.82, true, false, farm_1.get_next_id()), 7);
    farm_1.push_back(medicament("Ferretab", 27.47, true, true, farm_1.get_next_id()), 9);
    farm_1.push_back(medicament("Nordimet", 262.2, true, true, farm_1.get_next_id()), 6);
    std::cout << "\n\n" << farm_1 << "\n";

    ///initializez date pentru o cerere
    cerere cerere_1;
    cerere_1.push_back(farm_1.get_by_id(4), 1);
    cerere_1.push_back(farm_1.get_by_id(farm_1.get_by_nume("Suvezen")), 2);
    cerere_1.push_back(farm_1.get_by_id(9), 3);
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
    float pret = cerere_1.pret_total();
    std::cout << "Pretul total este de " << pret << "\n\n";

    ///verific operator= si cc la medicament
    medicament test_1("ImmunoMix", 47.0, false, false, 1);
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

