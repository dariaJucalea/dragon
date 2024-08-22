#include "include/user.h"
#include <cstring>
#include <cstdlib>
#include <regex>

user::user()
    : tip(), nume(), prenume(), telefon(), email(), parola() {}

user::user(std::string tip, std::string nume, std::string prenume, std::string telefon, std::string email, std::string parola)
    : tip(tip), nume(nume), prenume(prenume), telefon(telefon), email(email), parola(parola) {}

user::~user() {}

char *user::serializeUser()
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

void user::deserializeUser(char *buffer)
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

    free(mutableBuffer);
}

string user::getTip()
{
    return this->tip;
}

string user::getNume()
{
    return this->nume;
}
string user::getPrenume()
{
    return this->prenume;
}

string user::getTelefon()
{
    return this->telefon;
}

string user::getEmail()
{
    return this->email;
}

string user::getParola()
{
    return this->parola;
}

void user::setTip(string tip)
{
    this->tip = tip;
}

void user::setNume(string nume)
{
    this->nume = nume;
}

void user::setPrenume(string prenume)
{
    this->prenume = prenume;
}

void user::setTelefon(string telefon)
{
    this->telefon = telefon;
}

void user::setEmail(string email)
{
    this->email = email;
}

void user::setParola(string parola)
{
    this->parola = parola;
}

std::ostream &operator<<(std::ostream &os, const user &u)
{
    os << "Tip: " << u.tip << "\n"
       << "Nume: " << u.nume << "\n"
       << "Prenume: " << u.prenume << "\n"
       << "Telefon: " << u.telefon << "\n"
       << "Email: " << u.email << "\n"
       << "Parola: " << u.parola << "\n";

    return os;
}

std::istream &operator>>(std::istream &is, user &u)
{
    std::string line;
    char buffer[256];
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

    return is;
}

bool user::compareUsers(user u)
{
    if (this->email == u.getEmail())
        return true;
    return false;
}



