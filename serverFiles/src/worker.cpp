#include "include/worker.h"
#include <cstring>
#include <cstdlib>
#include <regex>

using namespace std;

worker::worker() : tip(), nume(), prenume(), telefon(), email(), parola()
{
}
worker::worker(string tip, string nume, string prenume, string telefon, string email, string parola) : tip(tip), nume(nume), prenume(prenume), telefon(telefon), email(email), parola(parola)
{
}

void worker::addExperienta(string denumire, string descriere)
{
}

void worker::addDisponibiliate(string oras, string timp)
{
    disponibilitate.push_back(make_pair(oras,timp));
}
worker::~worker()
{
}

string worker::getTip()
{
    return this->tip;
}

string worker::getNume()
{
    return this->nume;
}

string worker::getPrenume()
{
    return this->prenume;
}

string worker::getTelefon()
{
    return this->telefon;
}

string worker::getEmail()
{
    return this->email;
}

string worker::getParola()
{
    return this->parola;
}

void worker::setTip(string tip)
{
    this->tip = tip;
}

void worker::setNume(string nume)
{
    this->nume = nume;
}

void worker::setPrenume(string prenume)
{
    this->prenume = prenume;
}

void worker::setTelefon(string telefon)
{
    this->telefon = telefon;
}

void worker::setEmail(string email)
{
    this->email = email;
}

void worker::setParola(string parola)
{
    this->parola = parola;
}

void worker::setStare(std::string stare)
{
    this->stare=stare;
}

 std::vector<std::pair<std::string,std::string>> worker::getDisponibilitate()
 {
    return this->disponibilitate;
 }

char *worker::serializeWorker()
{

    size_t totalSize = tip.length() + 1 + nume.length() + 1 + prenume.length() + 1 + telefon.length() + 1 + email.length() + 1 + parola.length() + 1;

    char *buffer = (char *)malloc(totalSize);
    if (!buffer)
    {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr;
    }

    size_t offset = 0;

    memcpy(buffer + offset, tip.c_str(), tip.length());
    offset += tip.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, nume.c_str(), nume.length());
    offset += nume.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, prenume.c_str(), prenume.length());
    offset += prenume.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, telefon.c_str(), telefon.length());
    offset += telefon.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, email.c_str(), email.length());
    offset += email.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, parola.c_str(), parola.length());
    offset += parola.length();
    buffer[offset] = '/';
    offset++;

    return buffer;
}

void worker::deserializeWorker(char *buffer)
{
    char *token;
    char *mutableBuffer = strdup(buffer);

    token = strtok(mutableBuffer, "/");
    if (token != nullptr)
    {
        tip = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        nume = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        prenume = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        telefon = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        email = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        parola = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        stare = std::string(token);
    }

    free(mutableBuffer);
}

std::ostream &operator<<(std::ostream &os, const worker &u)
{
    os << "Tip: " << u.tip << "\n"
       << "Nume: " << u.nume << "\n"
       << "Prenume: " << u.prenume << "\n"
       << "Telefon: " << u.telefon << "\n"
       << "Email: " << u.email << "\n"
       << "Parola: " << u.parola << "\n"
       << "Stare: "<<u.stare<<"\n";

    os << u.experienta.size() << "\n";
    for (int i = 0; i < u.experienta.size(); i++)
    {
        os << u.experienta[i].first << "\n";
        os << u.experienta[i].second << "\n";
    }

    os << u.disponibilitate.size() << "\n";
    for (int i = 0; i < u.disponibilitate.size(); i++)
    {
        os << u.disponibilitate[i].first << "\n";
        os << u.disponibilitate[i].second << "\n";
    }

    return os;
}

std::istream &operator>>(std::istream &is, worker &u)
{
    std::string line;
    char buffer[1024];
    char *p;

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setTip(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setNume(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setPrenume(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setTelefon(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setEmail(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setParola(p ? p : "");

    is.getline(buffer, sizeof(buffer));
    p = strtok(buffer, ": ");
    p = strtok(NULL, ": ");
    u.setStare(p ? p : "");

    int size;

    is >> size;

    is.ignore();

    char buffer1[1024];
    char buffer2[1024];

    for (int i = 0; i < size; i++)
    {
        is.getline(buffer1, sizeof(buffer1));
        is.getline(buffer2, sizeof(buffer2));
        u.addExperienta(buffer1, buffer2);
    }

    is >> size;
    is.ignore();

    for (int i = 0; i < size; i++)
    {
        is.getline(buffer1, sizeof(buffer1));
        is.getline(buffer2, sizeof(buffer2));
        u.addDisponibiliate(buffer1, buffer2);
    }

    return is;
}

bool worker::compareWorkers(worker u)
{
    if (this->email == u.getEmail())
        return true;
    return false;
}

void worker::changeState(string stare)
{
    this->stare = stare;
}
