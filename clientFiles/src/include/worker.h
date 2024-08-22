#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class worker
{
private:
    string tip;
    string nume;
    string prenume;
    string telefon;
    string email;
    string parola;
    vector<pair<string, string>> experienta;
    vector<pair<string, string>> disponibilitate;
    string stare;

public:
    worker();
    worker(string tip, string nume, string prenume, string telefon, string email, string parola);

    void addExperienta(string denumire, string descriere);
    void addDisponibiliate(string oras, string timp);
    void changeState(string stare);
    char *serializeWorker();

    string getTip();
    string getNume();
    string getPrenume();
    string getTelefon();
    string getEmail();
    string getParola();

    void setTip(string tip);
    void setNume(string nume);
    void setPrenume(string prenume);
    void setTelefon(string telefon);
    void setEmail(string email);
    void setParola(string parola);

    ~worker();
};
