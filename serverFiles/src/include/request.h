#include<string>
#include<vector>
#include <chrono>
#include <iostream>

using namespace std;

class request
{
private:

    std::chrono::time_point<std::chrono::system_clock> creationTime;
    string titlu;
    string descriere;
    string modAtribuire;
    string adresa;
    int idWorker;
    int idUser;
    string stareCerere;
    string stareWorker;
    
public:

    request();
    request(string titlu, string descriere, string modAtribuire, string adresa, int idUser);
    ~request();

    char* serializeRequest();
    char* serializeRequestForWorker(int id);
    void deserializeRequest(char* buffer);
    int  getMinutesSinceCreation() const;
    string getModAtribuire();
    string getAdresa();
    void setWorkerId(int id);
    int getWorkerId();

    friend std::istream& operator>>(std::istream& is, request& r);
    friend std::ostream& operator<<(std::ostream& os, const request& r);
};
