#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class user {
private:
    std::string tip;
    std::string nume;
    std::string prenume;
    std::string telefon;
    std::string email;
    std::string parola;

public:
    user(std::string tip, std::string nume, std::string prenume, std::string telefon, std::string email, std::string parola);
    ~user();

    char* serializeUser();


    friend std::ostream& operator<<(std::ostream& os, const user& u);
};

#endif // USER_H
