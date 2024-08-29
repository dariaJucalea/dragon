#include "include/request.h"
#include <cstdlib>
#include <cstring>
#include <iomanip> 

request::request()
{
    this->stareCerere = "Noua";
    creationTime = std::chrono::system_clock::now();
    this->stareWorker = "Indisponibil";
    this->idWorker = -1;
}

request::request(string titlu, string descriere, string modAtribuire, string adresa, int idUser) : titlu(titlu), descriere(descriere), modAtribuire(modAtribuire), adresa(adresa), idUser(idUser)
{
    this->stareCerere = "Noua";
    creationTime = std::chrono::system_clock::now();
    this->stareWorker = "Indisponibil";
    this->idWorker = -1;
}

int request::getMinutesSinceCreation() const
{
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - creationTime);
    return duration.count();
}

request::~request()
{
}

int request::getWorkerId()
{
    return this->idWorker;
}

std::istream &operator>>(std::istream &is, request &r)
{
    std::string line;
    std::string dateTimeStr;

   
    std::getline(is, line);
    std::istringstream creationTimeStream(line.substr(line.find(": ") + 2));
    std::tm tm = {};
    creationTimeStream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    r.creationTime = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    std::getline(is, line);
    r.titlu = line.substr(line.find(": ") + 2);

    std::getline(is, line);
    r.descriere = line.substr(line.find(": ") + 2);

    std::getline(is, line);
    r.modAtribuire = line.substr(line.find(": ") + 2);

    std::getline(is, line);
    r.adresa = line.substr(line.find(": ") + 2);

    std::getline(is, line);
    r.idUser = std::stoi(line.substr(line.find(": ") + 2));

    std::getline(is, line);
    r.idWorker = std::stoi(line.substr(line.find(": ") + 2));

    std::getline(is, line);
    r.stareCerere = line.substr(line.find(": ") + 2);

    std::getline(is, line);
    r.stareWorker = line.substr(line.find(": ") + 2);

    return is;
}

string request::getModAtribuire()
{
    return this->modAtribuire;
}

string request::getAdresa()
{
    return this->adresa;
}

void request::setWorkerId(int id)
{
    this->idWorker=id;
}

std::ostream &operator<<(std::ostream &os, const request &r)
{

    std::time_t creationTime = std::chrono::system_clock::to_time_t(r.creationTime);

    os << "Creation time: " << std::put_time(std::localtime(&creationTime), "%Y-%m-%d %H:%M:%S") << "\n"
       << "Titlu: " << r.titlu << "\n"
       << "Descriere: " << r.descriere << "\n"
       << "Mod atribuire: " << r.modAtribuire << "\n"
       << "Adresa: " << r.adresa << "\n"
       << "Id user: " << r.idUser << "\n"
       << "Id worker: " << r.idWorker << "\n"
       << "Stare cerere: " << r.stareCerere << "\n"
       << "Stare worker: " << r.stareWorker << "\n";

    return os;
}

char *request::serializeRequest()
{

    std::string idWorkerStr = std::to_string(idWorker);
    std::string idUserStr = std::to_string(idUser);

    std::string serializedData = idWorkerStr + "/" +
                                 idUserStr + "/" +
                                 titlu + "/" +
                                 descriere + "/" +
                                 modAtribuire + "/" +
                                 adresa + "/" +
                                 stareCerere + "/" +
                                 stareWorker + "/";

    size_t totalSize = serializedData.length() + 1;
    char *buffer = (char *)malloc(totalSize);
    if (!buffer)
    {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr;
    }

    memcpy(buffer, serializedData.c_str(), totalSize);

    return buffer;
}

char *request::serializeRequestForWorker(int id)
{
    
    std::string idStr = std::to_string(id);

  
    std::string serializedData = idStr + "/" +
                                 titlu + "/" +
                                 descriere + "/" +
                                 modAtribuire + "/" +
                                 adresa + "/";

   
    size_t totalSize = serializedData.length() + 1;
    char *buffer = (char *)malloc(totalSize);
    if (!buffer)
    {
        std::cerr << "Memory allocation failed!" << std::endl;
        return nullptr;
    }

   
    memcpy(buffer, serializedData.c_str(), totalSize);

    return buffer;
}

void request::deserializeRequest(char *buffer)
{


    
    char *token = strtok(buffer, "/");


    if (token != nullptr)
    {

        idWorker = std::stoi(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        idUser = std::stoi(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        titlu = std::string(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        descriere = std::string(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        modAtribuire = std::string(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        adresa = std::string(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        stareCerere = std::string(token);
        token = strtok(nullptr, "/");
    }

    if (token != nullptr)
    {

        stareWorker = std::string(token);
    }
}
