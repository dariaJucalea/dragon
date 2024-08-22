#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;
class user
{
private:
    string tip;
    string nume;
    string prenume;
    string telefon;
    string email;
    string parola;

public:
    user();
    user(std::string tip, std::string nume, std::string prenume, std::string telefon, std::string email, std::string parola);
    ~user();

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

    char *serializeUser();
    void deserializeUser(char *data);
    bool compareUsers(user u);

    friend std::ostream &operator<<(std::ostream &os, const user &u);
    friend std::istream &operator>>(std::istream &os, user &u);
};

#endif // USER_H
