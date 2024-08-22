#include "include/menu.h"
#include "include/user.h"
#include "include/worker.h"
#include "include/request.h"
#include <unistd.h>
#include <iostream>

menu::menu()
{
}

menu::~menu()
{
}

char *serializeDisponibilitate(string oras, string timp)
{
    int size = oras.length() + 1 + timp.length() + 1;

    char *buffer = (char *)malloc(size * sizeof(char));

    size_t offset = 0;

    memcpy(buffer + offset, oras.c_str(), oras.length());
    offset += oras.length();
    buffer[offset] = '/';
    offset++;

    memcpy(buffer + offset, timp.c_str(), timp.length());
    offset += timp.length();
    buffer[offset] = '/';
    offset++;

    return buffer;
}

void adaugaDisponibilitate(int id, int sock, string oras, string program)
{
    int opt = 11;

    send(sock, &opt, sizeof(int), 0);

    send(sock, &id, sizeof(int), 0);

    char *buffer = serializeDisponibilitate(oras, program);

    int length = strlen(buffer);

    cout << length << endl;

    send(sock, &length, sizeof(int), 0);

    send(sock, buffer, length, 0);
}

void stergeDisponibilitate(int sock, int id, int nr)
{
}

void menu::getProgram(int id, int sock)
{
    system("clear");
    cout << "Program:\n";

    int opt = 10;

    send(sock, &opt, sizeof(int), 0);

    send(sock, &id, sizeof(int), 0);

    int size;

    recv(sock, &size, sizeof(int), 0);

    for (int i = 0; i < size; i++)
    {
        int length;

        recv(sock, &length, sizeof(int), 0);

        char *buffer = (char *)malloc(length * sizeof(char));

        recv(sock, buffer, length, 0);

        char *token = strtok(buffer, "/");

        printf("%d.%s-", i, token);

        token = strtok(NULL, "/");

        printf("%s\n", token);
    }
}

void menu::modificaProgramul(int id, int sock)
{
    system("clear");
    cout << "1.Adauga disponibilitate\n";
    cout << "2.Sterge disponibilitate\n";
    cout << "3.Inapoi\n";
    cout << "Introduceti optiunea: ";
    int optiune;
    cin >> optiune;

    switch (optiune)
    {
    case 1:
    {
        cout << "Introduceti oras: ";
        string oras;
        cin >> oras;

        cout << "Introduceti varianta corecta de timp pentru disponibilitate:\n";
        cout << "1.Full time\n";
        cout << "2.In cursul saptamanii\n";
        cout << "3.In weekend\n";
        cout << "4.Doar la ocazii speciale\n";

        int val;
        cout << "Introduceti varianta: ";
        cin >> val;

        string program;

        if (val == 1)
            program = "Full time";
        else if (val == 2)
            program = "Weekdays";
        else if (val == 3)
            program = "Weekend days";
        else
            program = "Special";

        adaugaDisponibilitate(id, sock, oras, program);

        this->modificaProgramul(id, sock);
        break;
    }
    case 2:
    {
        this->getProgram(id, sock);

        cout << "Ce disponibilitate vreti sa stergeti?\n";

        int nr;

        cout << "Introduceti numarul (numerotarea incepe de la 0): ";

        cin >> nr;

        stergeDisponibilitate(sock, id, nr);
        break;
    }
    case 3:
    {
        system("clear");

        this->WorkerMenu(id, sock);
        break;
    }
    default:
        cout << "Optiune invalida. Va rugam incercati din nou.\n";
        this->modificaProgramul(id, sock);
        break;
    }
}

void getSolicitariPrimite(int id, int sock)
{
}

void getSolicitariFinalizate(int id, int sock)
{
}

void modificaSolicitareInCurs(int id, int sock)
{
}

void menu::WorkerMenu(int id, int sock)
{
    system("clear");
    cout << "1.Modifica programul\n";
    cout << "2.Solicitari primite\n";
    cout << "3.Solicitari finalizate\n";
    cout << "4.Programul meu\n";
    cout << "5.Modifica stare solicitare\n";
    int optiune;
    cout << "Introduceti optiunea: ";
    cin >> optiune;

    switch (optiune)
    {
    case 1:
    {
        this->modificaProgramul(id, sock);
        break;
    }
    case 2:
    {
        getSolicitariPrimite(id, sock);
        break;
    }
    case 3:
    {
        getSolicitariFinalizate(id, sock);
        break;
    }
    case 4:
    {
        this->getProgram(id, sock);

        cout << "Pentru a va intoarce apasati 1: ";

        int tasta;

        cin >> tasta;

        if (tasta == 1)
            this->WorkerMenu(id, sock);

        break;
    }
    case 5:
    {
        modificaSolicitareInCurs(id, sock);
        break;
    }
    default:
        cout << "Optiune invalida. Va rugam incercati din nou.\n";
        this->WorkerMenu(id, sock);
        break;
    }
}

void menu::plaseazaCerere(int id, int sock)
{
    system("clear");
    std::string titlu;
    std::string descriere;
    std::string modeAtribuire;
    std::string adresa;
    int mode;

    std::cout << "Introduceti titlul solicitarii: ";
    std::getline(std::cin >> std::ws, titlu);

    std::cout << "Introduceti descrierea solicitarii: ";
    std::getline(std::cin, descriere);

    std::cout << "Introduceti adresa in format oras, strada, numar, apartament, etc.: ";
    std::getline(std::cin >> std::ws, adresa);

    std::cout << "Alegeti modul de atribuire al solicitarii:\n";
    std::cout << "1. Manual (aleg eu electricianul din lista data de aplicatie)\n";
    std::cout << "2. Automat (aplicatia imi atribuie automat un electrician)\n";

    std::cout << "Introduceti varianta: ";
    std::cin >> mode;

    if (mode == 1)
    {
        modeAtribuire = "manual";

        int opt = 13;

        send(sock, &opt, sizeof(int), 0);

        int size;

        size=adresa.length();

        send(sock,&size, sizeof(int),0);

        send(sock,adresa.c_str(),size,0);

    }
    else
    {
        modeAtribuire = "automat";
    }

    request *req = new request(titlu, descriere, modeAtribuire, adresa, id);

    char *buffer = req->serializeRequest();
    printf("%s\n", buffer);

    int optiune = 12;
    send(sock, &optiune, sizeof(int), 0);

    int size = strlen(buffer);

    send(sock, &size, sizeof(int), 0);

    send(sock, buffer, size, 0);

    sleep(300000000);
}

void menu::UserMenu(int id, int sock)
{
    system("clear");
    cout << "1.Solicitari plasate\n";
    cout << "2.Solicitari finalizate\n";
    cout << "3.Plaseaza o solicitare\n";
    int optiune;
    cout << "Introduceti optiunea: ";
    cin >> optiune;

    switch (optiune)
    {
    case 1:
    {
        this->plaseazaCerere(id, sock);
        break;
    }
    case 2:
    {
        break;
    }
    case 3:
    {
        break;
    }
    default:
        cout << "Optiune invalida. Va rugam incercati din nou.\n";
        this->UserMenu(id, sock);
        break;
    }
}

user *buildUser()
{
    system("clear");
    int optiune;
    string tip;
    string nume;
    string prenume;
    string email;
    string telefon;
    string parola;

    cout << "Tip:\n";
    cout << "1.Persoana fizica\n";
    cout << "2.Persoana juridica(companie)\n";
    cout << "3.Persoana juridica(HoReCa)\n";
    cout << "Introduceti optiunea:";
    cin >> optiune;
    if (optiune == 1)
        tip = "fizica";
    else if (optiune == 2)
        tip = "companie";
    else if (optiune == 3)
        tip = "horeca";

    cout << "Nume:";
    cin >> nume;

    cout << "Prenume:";
    cin >> prenume;

    cout << "Telefon:";
    cin >> telefon;

    cout << "Email:";
    cin >> email;

    cout << "Parola:";
    cin >> parola;

    user *utilizator = new user(tip, nume, prenume, telefon, email, parola);
    return utilizator;
}

worker *buildWorker()
{
    system("clear");
    int optiune;
    string tip;
    string nume;
    string prenume;
    string email;
    string telefon;
    string parola;

    cout << "Tip:\n";
    cout << "1.Persoana fizica\n";
    cout << "2.Persoana juridica(companie)\n";
    cout << "3.Persoana juridica(HoReCa)\n";
    cout << "Introduceti optiunea:";
    cin >> optiune;
    if (optiune == 1)
        tip = "fizica";
    else if (optiune == 2)
        tip = "companie";
    else if (optiune == 3)
        tip = "horeca";

    cout << "Nume:";
    cin >> nume;

    cout << "Prenume:";
    cin >> prenume;

    cout << "Telefon:";
    cin >> telefon;

    cout << "Email:";
    cin >> email;

    cout << "Parola:";
    cin >> parola;

    worker *work = new worker(tip, nume, prenume, telefon, email, parola);
    return work;
}

void menu::print(int sock)
{
    cout << "Bine ati venit in aplicatia Dragon!\n";
    cout << "1. Autentificate\n";
    cout << "2. Creati cont\n";
    cout << "3. Exit\n";
    cout << "Introduceti optiunea: ";
    this->handleOption(sock);
}

bool menu::handleOption(int sock)
{
    int optiune;

    cin >> optiune;

    if (optiune == 1)
    {
        int opt = 3;
        send(sock, &opt, sizeof(int), 0);

        string email, parola;
        system("clear");
        cout << "Introduceti emailul: ";
        cin >> email;
        cout << "Introduceti parola: ";
        cin >> parola;

        size_t totalSize = email.length() + 1 + parola.length() + 1;
        char *buffer = (char *)malloc(totalSize);
        if (!buffer)
        {
            std::cerr << "Memory allocation failed!" << std::endl;
            exit(1);
        }

        size_t offset = 0;

        memcpy(buffer + offset, email.c_str(), email.length());
        offset += email.length();
        buffer[offset] = '/';
        offset++;

        memcpy(buffer + offset, parola.c_str(), parola.length());
        offset += parola.length();
        buffer[offset] = '\0';
        offset++;

        int size = strlen(buffer);
        send(sock, &size, sizeof(int), 0);

        send(sock, buffer, size, 0);

        int response;

        recv(sock, &response, sizeof(int), 0);

        cout << response << endl;

        if (response == 1)
        {
            int id;

            recv(sock, &id, sizeof(int), 0);

            cout << id << endl;

            this->role = 1;

            this->UserMenu(id, sock);
        }
        else if (response == 2)
        {
            int id;

            recv(sock, &id, sizeof(int), 0);

            this->role = 2;

            this->WorkerMenu(id, sock);
        }

        system("clear");
        return true;
    }
    else if (optiune == 2)
    {
        system("clear");
        cout << "Creati cont de:\n";
        cout << "1.Utilizator\n";
        cout << "2.Specialist\n";
        cout << "3.Inapoi\n";
        cout << "Introduceti optiunea: ";
        cin >> optiune;
        switch (optiune)
        {
        case 1:
        {
            int opt = 1;

            send(sock, &opt, sizeof(int), 0);

            user *utilizator = buildUser();

            char *buffer;

            buffer = utilizator->serializeUser();

            int size = strlen(buffer) + 1;

            send(sock, &size, sizeof(int), 0);

            send(sock, buffer, size, 0);

            int status;

            recv(sock, &status, sizeof(int), 0);

            system("clear");

            if (status == 1)
            {
                cout << "Utilizator creat cu succes!\n";
            }
            else if (status == 2)
            {
                cout << "Utilizator deja existent!\n";
            }

            this->print(sock);
            break;
        }
        case 2:
        {
            int opt = 2;

            send(sock, &opt, sizeof(int), 0);

            worker *work = buildWorker();

            char *buffer;

            buffer = work->serializeWorker();

            int size = strlen(buffer) + 1;

            send(sock, &size, sizeof(int), 0);

            send(sock, buffer, size, 0);

            int status;

            recv(sock, &status, sizeof(int), 0);

            system("clear");

            if (status == 1)
            {
                cout << "Specialist creat cu succes!\n";
            }
            else if (status == 2)
            {
                cout << "Specialist deja existent!\n";
            }

            this->print(sock);
            break;
        }
        case 3:
        {
            system("clear");
            this->print(sock);
            break;
        }
        }
        return true;
    }
    else if (optiune == 3)
    {
        return true;
    }
    else
    {
        cout << "Optiunea invalida. Va rugam incercati din nou." << std::endl;
        return false;
    }
}
