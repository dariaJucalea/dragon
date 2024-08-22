#include "include/worker.h"
#include <cstring>
#include <cstdlib>

worker::worker() : tip(), nume(), prenume(), telefon(), email(), parola(),stare("disponibil")
{
}
worker::worker(string tip, string nume, string prenume, string telefon, string email, string parola) : tip(tip), nume(nume), prenume(prenume), telefon(telefon), email(email), parola(parola),stare("disponibil")
{
}

void worker::addExperienta(string denumire, string descriere)
{
}

void worker::addDisponibiliate(string oras, string timp)
{
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

char *worker::serializeWorker()
{

    size_t totalSize = tip.length() + 1 + nume.length() + 1 + prenume.length() + 1 + telefon.length() + 1 + email.length() + 1 + parola.length() + 1+stare.length()+1;

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

    memcpy(buffer + offset, stare.c_str(), stare.length());
    offset += stare.length();
    buffer[offset] = '/';
    offset++;

    return buffer;
}

void worker::changeState(string stare)
{
    this->stare = stare;
}
