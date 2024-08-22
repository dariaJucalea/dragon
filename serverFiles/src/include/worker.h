#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class worker
{
private:
    std::string tip;
    std::string nume;
    std::string prenume;
    std::string telefon;
    std::string email;
    std::string parola;
    std::string stare;
    std::vector<std::pair<std::string, std::string>> experienta;
    std::vector<std::pair<std::string, std::string>> disponibilitate;

public:
    worker();
    worker(std::string tip, std::string nume, std::string prenume, std::string telefon, std::string email, std::string parola);

    void addExperienta(std::string denumire, std::string descriere);
    void addDisponibiliate(std::string oras, std::string timp);
    char *serializeWorker();
    void deserializeWorker(char *buffer);
    bool compareWorkers(worker u);
    void changeState(std::string stare);

    std::string getTip();
    std::string getNume();
    std::string getPrenume();
    std::string getTelefon();
    std::string getEmail();
    std::string getParola();
    std::vector<std::pair<std::string,std::string>> getDisponibilitate();

    void setTip(std::string tip);
    void setNume(std::string nume);
    void setPrenume(std::string prenume);
    void setTelefon(std::string telefon);
    void setEmail(std::string email);
    void setParola(std::string parola);
    void setStare(std::string stare);

    friend std::ostream &operator<<(std::ostream &os, const worker &u);
    friend std::istream &operator>>(std::istream &is, worker &u);

    ~worker();
};

#endif // WORKER_H
