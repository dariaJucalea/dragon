#include "include/user.h"
#include <cstring>
#include <cstdlib>


user::user(std::string tip, std::string nume, std::string prenume, std::string telefon, std::string email, std::string parola)
    : tip(tip), nume(nume), prenume(prenume), telefon(telefon), email(email), parola(parola) {}


user::~user() {}


char* user::serializeUser() {
    
    size_t totalSize = tip.length() + 1 + nume.length() + 1 + prenume.length() + 1 + telefon.length() + 1 + email.length() + 1 + parola.length() + 1;

    
    char* buffer = (char*)malloc(totalSize);
    if (!buffer) {
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




std::ostream& operator<<(std::ostream& os, const user& u) {
    os << "Tip: " << u.tip << "\n"
       << "Nume: " << u.nume << "\n"
       << "Prenume: " << u.prenume << "\n"
       << "Telefon: " << u.telefon << "\n"
       << "Email: " << u.email << "\n"
       << "Parola: " << u.parola << "\n";
    return os;
}
