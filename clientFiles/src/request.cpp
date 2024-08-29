#include "include/request.h"
#include <cstdlib>
#include <cstring>

request::request()
{
    this->stareCerere = "Noua";
    this->stareWorker = "Indisponibil";
    this->idWorker = -1;
}

request::request(string titlu, string descriere, string modAtribuire, string adresa, int idUser, int idWorker) : titlu(titlu), descriere(descriere), modAtribuire(modAtribuire), adresa(adresa), idUser(idUser),idWorker(idWorker)
{
    this->stareCerere = "Noua";
    this->stareWorker = "Indisponibil";
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
