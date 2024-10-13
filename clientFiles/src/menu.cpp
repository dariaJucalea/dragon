#include "include/menu.h"
#include "include/user.h"
#include "include/worker.h"
#include "include/request.h"
#include <unistd.h>
#include <iostream>

using namespace std;

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

    std::cout << length << endl;

    send(sock, &length, sizeof(int), 0);

    send(sock, buffer, length, 0);
}

void stergeDisponibilitate(int sock, int id, int nr)
{
}

void menu::getProgram(int id, int sock)
{
    system("clear");
    std::cout << "Program:\n";

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
    std::cout << "1.Adauga disponibilitate\n";
    std::cout << "2.Sterge disponibilitate\n";
    std::cout << "3.Inapoi\n";
    std::cout << "Introduceti optiunea: ";
    int optiune;
    std::cin >> optiune;

    switch (optiune)
    {
    case 1:
    {
        std::cout << "Introduceti oras: ";
        string oras;
        std::cin >> oras;

        std::cout << "Introduceti varianta corecta de timp pentru disponibilitate:\n";
        std::cout << "1.Full time\n";
        std::cout << "2.In cursul saptamanii\n";
        std::cout << "3.In weekend\n";
        std::cout << "4.Doar la ocazii speciale\n";

        int val;
        std::cout << "Introduceti varianta: ";
        std::cin >> val;

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

        std::cout << "Ce disponibilitate vreti sa stergeti?\n";

        int nr;

        std::cout << "Introduceti numarul (numerotarea incepe de la 0): ";

        std::cin >> nr;

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
        std::cout << "Optiune invalida. Va rugam incercati din nou.\n";
        this->modificaProgramul(id, sock);
        break;
    }
}

void printRequest(char *buffer)
{
    std::cout << "--------\n";
    char *token;

    token = strtok(buffer, "/");

    std::cout << "Nr crt: " << token << endl;

    token = strtok(NULL, "/");

    std::cout << "Titlu: " << token << endl;

    token = strtok(NULL, "/");

    std::cout << "Descriere: " << token << endl;

    token = strtok(NULL, "/");

    token = strtok(NULL, "/");

    std::cout << "Adresa: " << token << endl;
    std::cout << "--------\n";
}

void preiaCerere(int sock, int id, int nr)
{
    int optiune = 13;

    send(sock, &optiune, sizeof(int), 0);

    send(sock, &id, sizeof(int), 0);

    send(sock, &nr, sizeof(int), 0);

    int response;

    recv(sock, &response, sizeof(int), 0);
}

void getSolicitariPrimite(int id, int sock)
{
    system("clear");
    int optiune = 12;

    send(sock, &optiune, sizeof(int), 0);

    send(sock, &id, sizeof(int), 0);

    int count;

    recv(sock, &count, sizeof(int), 0);

    if (count != 0)
    {

        for (int i = 0; i < count; i++)
        {
            int length;

            char *buffer;

            recv(sock, &length, sizeof(int), 0);

            buffer = (char *)malloc(length * sizeof(char));

            recv(sock, buffer, length, 0);

            printRequest(buffer);
        }

        std::cout << "Doriti sa preluati vreo cerere?\n1.Da\n2.Nu\n";

        int opt;

        std::cin >> opt;

        if (opt == 1)
        {
            std::cout << "Introduceti numarul cererii pe care doriti sa o preluati: ";

            int nr;

            std::cin >> nr;

            preiaCerere(sock, id, nr);
        }
    }
    else
    {
        std::cout << "Nu ati primit nicio cerere\n";
    }
}

void getSolicitariFinalizate(int id, int sock)
{
}

void modificaSolicitareInCurs(int id, int sock)
{
}

void menu::getCereriPlasate(int id, int sock)
{
    int opt = 14;

    send(sock, &opt, sizeof(int), 0);

    send(sock, &id, sizeof(int), 0);

    std::cout << "Ce cereri doriti sa vizualizati?\n";
    std::cout << "1.Noi\n";
    std::cout << "2.In desfasurare\n";
    std::cout << "3.Suspendate\n";
    std::cout << "4.Anulate\n";
    std::cout << "5.Nepreluate\n";
    std::cout << " 6.In lucru in momentul de fata\n";

    std::cout << "Introduceti un numar de la 1 la 6 si 7 pentru a reveni la meniul initial: \n";

    int type;

    std::cin >> type;

    while (type < 1 && type > 7)
    {
        std::cout << "Nu ati introdus o valoare valida\n";
        std::cout << "Introduceti un numar de la 1 la 5 si 6 pentru a reveni la meniul initial: \n";

        std::cin >> type;
    }

    if (type == 7)
    {
        this->UserMenu(id, sock);
    }
    else
    {
        send(sock, &type, sizeof(type), 0);

        switch (type)
        {
        case 1:
        {
            printf("SOLICITARI NOI:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);
            break;
        }
        case 2:
        {
            printf("SOLICITARI IN DESFASURARE:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);
            break;
        }
        case 3:
        {
            printf("SOLICITARILE SUSPENDATE:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);
            break;
        }
        case 4:
        {
            printf("SOLICITARI ANULATE:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);
            break;
        }
        case 5:
        {
            printf("SOLICITARI NEPRELUATE:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);

            break;
        }
        case 6:
        {
            printf("SOLICITARI IN DESFASURARE LA MOMENTUL ACTUAL:\n");

            int nr;

            recv(sock, &nr, sizeof(nr), 0);

            system("clear");

            for (int i = 0; i < nr; i++)
            {
                int length;

                recv(sock, &length, sizeof(length), 0);

                char *buffer;

                buffer = (char *)malloc(length * sizeof(char));

                recv(sock, buffer, length, 0);

                request req;

                req.deserializeRequest(buffer);

                printf("--------------\n");

                std::cout << req;

                printf("--------------\n");
            }

            std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
            int iesire;
            cin >> iesire;

            while (iesire != 1)
            {
                std::cout << "Doriti sa iesiti din acest meniu?\nApasati 1 pentru a iesi:";
                cin >> iesire;
            }

            this->UserMenu(id, sock);

            break;
        }
        }
    }
}

void menu::getCereriFinalizateUser(int id, int sock)
{

    int value=15;

    send(sock,&value,sizeof(int),0);

    std::cout << "CERERI FINAZATE:\n";

    system("clear");

    send(sock, &id, sizeof(int), 0);

    int count;

    recv(sock, &count, sizeof(count), 0);

    for (int i = 0; i < count; i++)
    {
        int len;
        recv(sock, &len, sizeof(int), 0);

        char *buffer = (char *)malloc(len * sizeof(char));

        recv(sock, buffer, len, 0);

        request req;

        req.deserializeRequest(buffer);

        std::cout << "-------------------\n";

        std::cout << req;

        std::cout << "-------------------\n";
    }

    std::cout << "Doriti sa va intoarceti la meniul principal? Introduceti 1: ";

    int opt;

    std::cin >> opt;

    while (opt != 1)
    {
        std::cout << "Doriti sa va intoarceti la meniul principal? Introduceti 1: ";
        std::cin >> opt;
    }

    this->UserMenu(id, sock);
}

void parseWorker(char *buffer)
{
    char *token;

    std::cout << "-------------------\n";

    token = strtok(buffer, "/");

    printf("Nr. crt.: %d\n", atoi(token));

    token = strtok(NULL, "/");

    printf("Nume: %s\n", token);

    token = strtok(NULL, "/");

    printf("Prenume: %s\n", token);
}

int menu::chooseWorker(int count, int *workersId, int id, int sock)
{
    std::cout << "Introduceti un numar de worker valabil: ";

    int idW;

    std::cin >> idW;

    if (idW != -1)
    {

        bool ok = false;

        for (int i = 0; i < count; i++)
        {
            if (workersId[i] == idW)
            {
                ok = true;
            }
        }

        if (ok == true)
        {
            return idW;
        }
    }
    else
    {
        this->UserMenu(id, sock);
    }
    return -1;
}

void menu::WorkerMenu(int id, int sock)
{
    system("clear");
    std::cout << "1.Modifica programul\n";
    std::cout << "2.Solicitari primite\n";
    std::cout << "3.Solicitari finalizate\n";
    std::cout << "4.Programul meu\n";
    std::cout << "5.Modifica stare solicitare\n";
    int optiune;
    std::cout << "Introduceti optiunea: ";
    std::cin >> optiune;

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

        std::cout << "Pentru a va intoarce apasati 1: ";

        int tasta;

        std::cin >> tasta;

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
        std::cout << "Optiune invalida. Va rugam incercati din nou.\n";
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

        size = adresa.length();

        send(sock, &size, sizeof(int), 0);

        send(sock, adresa.c_str(), size, 0);

        int count;

        recv(sock, &count, sizeof(int), 0);

        int workersId[count];

        for (int i = 0; i < count; i++)
        {
            char *buffer;

            int length;

            recv(sock, &length, sizeof(int), 0);

            buffer = (char *)malloc(length * sizeof(char));

            recv(sock, buffer, length, 0);

            parseWorker(buffer);

            char *token;

            token = strtok(buffer, "/");

            int id;

            id = atoi(token);

            workersId[i] = id;
        }

        int value = chooseWorker(count, workersId, id, sock);

        while (1)
        {
            if (value != -1)
            {
                request *req = new request(titlu, descriere, modeAtribuire, adresa, id, value);

                char *buffer = req->serializeRequest();
                // printf("%s\n", buffer);

                int optiune = 12;
                send(sock, &optiune, sizeof(int), 0);

                int sizee = strlen(buffer);

                send(sock, &sizee, sizeof(int), 0);

                send(sock, buffer, sizee, 0);

                system("clear");

                printf("Ati introdus un id de worker valid. Solicitarea a fost plasata cu succes!\n");
                sleep(5);

                this->UserMenu(id, sock);
            }
            else
            {
                printf("Ati introdus un id de worker invalid, va rugam sa introduceti unul valid.\n");
                printf("Daca doriti sa va intoarceti introduceti -1.\n");
                value = chooseWorker(count, workersId, id, sock);
            }
        }
    }
    else
    {
        modeAtribuire = "automat";

        request *req = new request(titlu, descriere, modeAtribuire, adresa, id, -1);

        char *buffer = req->serializeRequest();
        printf("%s\n", buffer);

        int optiune = 12;
        send(sock, &optiune, sizeof(int), 0);

        int size = strlen(buffer);

        send(sock, &size, sizeof(int), 0);

        send(sock, buffer, size, 0);
    }

    sleep(300000000);
}

void menu::UserMenu(int id, int sock)
{
    system("clear");
    std::cout << "1.Solicitari plasate\n";
    std::cout << "2.Solicitari finalizate\n";
    std::cout << "3.Plaseaza o solicitare\n";
    int optiune;
    std::cout << "Introduceti optiunea: ";
    std::cin >> optiune;

    switch (optiune)
    {
    case 1:
    {
        this->getCereriPlasate(id, sock);
        break;
    }
    case 2:
    {
        this->getCereriFinalizateUser(id, sock);
        break;
    }
    case 3:
    {
        this->plaseazaCerere(id, sock);
        break;
    }
    default:
        std::cout << "Optiune invalida. Va rugam incercati din nou.\n";
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

    std::cout << "Tip:\n";
    std::cout << "1.Persoana fizica\n";
    std::cout << "2.Persoana juridica(companie)\n";
    std::cout << "3.Persoana juridica(HoReCa)\n";
    std::cout << "Introduceti optiunea:";
    std::cin >> optiune;
    if (optiune == 1)
        tip = "fizica";
    else if (optiune == 2)
        tip = "companie";
    else if (optiune == 3)
        tip = "horeca";

    std::cout << "Nume:";
    std::cin >> nume;

    std::cout << "Prenume:";
    std::cin >> prenume;

    std::cout << "Telefon:";
    std::cin >> telefon;

    std::cout << "Email:";
    std::cin >> email;

    std::cout << "Parola:";
    std::cin >> parola;

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

    std::cout << "Tip:\n";
    std::cout << "1.Persoana fizica\n";
    std::cout << "2.Persoana juridica(companie)\n";
    std::cout << "3.Persoana juridica(HoReCa)\n";
    std::cout << "Introduceti optiunea:";
    std::cin >> optiune;
    if (optiune == 1)
        tip = "fizica";
    else if (optiune == 2)
        tip = "companie";
    else if (optiune == 3)
        tip = "horeca";

    std::cout << "Nume:";
    std::cin >> nume;

    std::cout << "Prenume:";
    std::cin >> prenume;

    std::cout << "Telefon:";
    std::cin >> telefon;

    std::cout << "Email:";
    std::cin >> email;

    std::cout << "Parola:";
    std::cin >> parola;

    worker *work = new worker(tip, nume, prenume, telefon, email, parola);
    return work;
}

void menu::print(int sock)
{
    std::cout << "Bine ati venit in aplicatia Dragon!\n";
    std::cout << "1. Autentificate\n";
    std::cout << "2. Creati cont\n";
    std::cout << "3. Exit\n";
    std::cout << "Introduceti optiunea: ";
    this->handleOption(sock);
}

bool menu::handleOption(int sock)
{
    int optiune;

    std::cin >> optiune;

    if (optiune == 1)
    {
        int opt = 3;
        send(sock, &opt, sizeof(int), 0);

        string email, parola;
        system("clear");
        std::cout << "Introduceti emailul: ";
        std::cin >> email;
        std::cout << "Introduceti parola: ";
        std::cin >> parola;

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

        std::cout << response << endl;

        if (response == 1)
        {
            int id;

            recv(sock, &id, sizeof(int), 0);

            std::cout << id << endl;

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
        std::cout << "Creati cont de:\n";
        std::cout << "1.Utilizator\n";
        std::cout << "2.Specialist\n";
        std::cout << "3.Inapoi\n";
        std::cout << "Introduceti optiunea: ";
        std::cin >> optiune;
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
                std::cout << "Utilizator creat cu succes!\n";
            }
            else if (status == 2)
            {
                std::cout << "Utilizator deja existent!\n";
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
                std::cout << "Specialist creat cu succes!\n";
            }
            else if (status == 2)
            {
                std::cout << "Specialist deja existent!\n";
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
        std::cout << "Optiunea invalida. Va rugam incercati din nou." << std::endl;
        return false;
    }
}
