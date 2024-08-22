#include "include/request.h"
#include <cstdlib>
#include <cstring>

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

std::istream &operator>>(std::istream &is, request &r)
{

    return is;
}

std::ostream &operator<<(std::ostream &os, const request &r)
{
    os << "Titlu: " << r.titlu << "\n"
       << "Descriere: " << r.descriere << "\n"
       << "Mod atribuire: " << r.modAtribuire << "\n"
       << "Adresa: " << r.adresa << "\n";

    return os;
}

char *request::serializeRequest()
{

    std::string creationTimeStr = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(creationTime.time_since_epoch()).count());
    std::string idWorkerStr = std::to_string(idWorker);
    std::string idUserStr = std::to_string(idUser);

    std::string serializedData = creationTimeStr + "/" +
                                 idWorkerStr + "/" +
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

void request::deserializeRequest(char *buffer)
{

    char *token = strtok(buffer, "/");

    if (token != nullptr)
    {

        auto creationTimeSec = std::stoll(token);
        creationTime = std::chrono::system_clock::from_time_t(creationTimeSec);
        token = strtok(nullptr, "/");
    }

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
