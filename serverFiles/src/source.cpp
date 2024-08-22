#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <mutex>
#include "include/user.h"
#include "include/worker.h"
#include <signal.h>
#include "include/user.h"
#include "include/request.h"

#define PORT 44000

using namespace std;

vector<user> users;
vector<worker> workers;

void initializeUsers()
{
    ifstream infile("src/data/users.txt");

    if (!infile)
    {
        cerr << "Eroare la deschiderea fisierului de useri" << std::endl;
        exit(1);
    }

    int size;

    infile >> size;
    infile.ignore();

    for (int i = 0; i < size; i++)
    {
        user u;
        infile >> u;
        users.push_back(u);
    }

    infile.close();
}

void initializeWorkers()
{
    ifstream infile("src/data/workers.txt");

    if (!infile)
    {
        cout << "Eroare la deschiderea fisierului de workeri" << std::endl;
    }

    int size;

    infile >> size;
    infile.ignore();

    for (int i = 0; i < size; i++)
    {

        worker w;
        infile >> w;
        workers.push_back(w);
    }

    infile.close();
}

void saveUsers()
{
    ofstream outfile("src/data/users.txt");

    if (!outfile)
    {
        cerr << "Eroare la deschiderea fisierului de useri" << std::endl;
        exit(1);
    }

    outfile << users.size();

    outfile << endl;

    for (int i = 0; i < users.size(); i++)
    {
        outfile << users[i];
    }
    outfile.close();
}

void saveWorkers()
{
    ofstream outfile("src/data/workers.txt");

    if (!outfile)
    {
        cerr << "Eroare la deschiderea fisierului de useri" << std::endl;
        exit(1);
    }

    outfile << workers.size();

    outfile << endl;

    for (int i = 0; i < workers.size(); i++)
    {
        outfile << workers[i];
    }
    outfile.close();
}

void signalHandler(int signum)
{
    cout << "\nInterrupt signal (" << signum << ") received. Saving users and shutting down...\n";

    saveUsers();

    exit(signum);
}

void register_user(int socket)
{
    char *buffer;

    int size;

    recv(socket, &size, sizeof(int), 0);

    buffer = (char *)malloc(size * sizeof(char));

    int valread = recv(socket, buffer, size, 0);

    printf("Received from client: %s\n", buffer);

    user *utilizator = new user();

    utilizator->deserializeUser(buffer);

    bool exists = false;

    for (user &u : users)
    {
        if (u.compareUsers(*utilizator) == true)
        {
            exists = true;
        }
    }

    for (worker &w : workers)
    {
        if (w.getEmail() == utilizator->getEmail())
        {
            exists = true;
        }
    }

    int status;

    if (exists == false)
    {
        users.push_back(*utilizator);

        saveUsers();

        status = 1;

        send(socket, &status, sizeof(int), 0);
    }

    status = 2;

    send(socket, &status, sizeof(int), 0);
}

void register_worker(int socket)
{
    char *buffer;

    int size;

    recv(socket, &size, sizeof(int), 0);

    buffer = (char *)malloc(size * sizeof(char));

    int valread = recv(socket, buffer, size, 0);

    printf("Received from client: %s\n", buffer);

    worker *work = new worker();

    work->deserializeWorker(buffer);

    bool exists = false;

    for (worker &w : workers)
    {
        if (w.compareWorkers(*work) == true)
        {
            exists = true;
        }
    }

    for (user &u : users)
    {
        if (u.getEmail() == work->getEmail())
        {
            exists = true;
        }
    }

    int status;

    if (exists == false)
    {
        workers.push_back(*work);

        saveWorkers();

        status = 1;

        send(socket, &status, sizeof(int), 0);
    }

    status = 2;

    send(socket, &status, sizeof(int), 0);
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

    cout<<buffer<<endl;

    return buffer;
}

void handle_user_menu(int socket)
{

    while(1)
    {
        int optiune;

        recv(socket,&optiune,sizeof(int),0);

        switch(optiune)
        {
            case 12:
            {
                int size;

                recv(socket,&size, sizeof(int),0);

                char* buffer;

                buffer=(char*)malloc(size*sizeof(char));

                recv(socket,buffer,size,0);

                printf("%s\n",buffer);

                request* req=new request();

                req->deserializeRequest(buffer);

                std::cout<<*req;

            }

            case 13:
            {
                int size;

                recv(socket,&size,sizeof(int),0);
    
            }
        }

       
    }
}

void handle_worker_menu(int socket)
{

    while(1)
    {

    int optiune;

    recv(socket, &optiune, sizeof(int), 0);

    switch (optiune)
    {
    case 10:
    {
        int id;

        recv(socket, &id, sizeof(int), 0);

        int size = workers[id].getDisponibilitate().size();

        send(socket, &size, sizeof(int), 0);

        for (int i = 0; i < size; i++)
        {
            char *buffer = serializeDisponibilitate(workers[id].getDisponibilitate()[i].first, workers[id].getDisponibilitate()[i].second);

            int length = strlen(buffer);

            send(socket, &length, sizeof(int), 0);

            send(socket, buffer, length, 0);
        }

        break;
    }

    case 11:
    {
        int id;

        recv(socket,&id,sizeof(int),0);

        int length;

        recv(socket, &length, sizeof(int), 0);

        char *buffer = (char *)malloc(length * sizeof(char));

        recv(socket, buffer, length, 0);

        char* token;

        token = strtok(buffer, "/");

        string oras,timp;

        if (token != nullptr)
        {
            oras= std::string(token);
        }

        token = strtok(nullptr, "/");
        if (token != nullptr)
        {
            timp = std::string(token);
        }

        workers[id].addDisponibiliate(oras,timp);

        saveWorkers();

    }
    }
    }
}

void authenticate(int socket)
{
    int size;

    char *buffer;

    string email, parola;

    recv(socket, &size, sizeof(int), 0);

    buffer = (char *)malloc(size * sizeof(char));

    recv(socket, buffer, size, 0);

    char *token;
    char *mutableBuffer = strdup(buffer);

    token = strtok(mutableBuffer, "/");
    if (token != nullptr)
    {
        email = std::string(token);
    }

    token = strtok(nullptr, "/");
    if (token != nullptr)
    {
        parola = std::string(token);
    }

    bool exists = false;
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i].getParola() == parola && users[i].getEmail() == email)
        {

            int response = 1;
            exists = true;

            cout << users[i].getEmail() << " " << users[i].getParola() << endl;

            send(socket, &response, sizeof(int), 0);

            int position = i;

            send(socket, &position, sizeof(int), 0);

            handle_user_menu(socket);
            break;
        }
    }

    for (size_t i = 0; i < workers.size(); ++i)
    {
        if (workers[i].getParola() == parola && workers[i].getEmail() == email)
        {
            int response = 2;
            exists = true;

            send(socket, &response, sizeof(int), 0);

            int position = i;

            send(socket, &position, sizeof(int), 0);

            handle_worker_menu(socket);

            break;
        }
    }
    if (exists == false)
    {
        int response = -1;

        send(socket, &response, sizeof(int), 0);
    }
}

void make_request(int socket)
{
}

void get_request(int socket)
{
}

void handle_client(int client_socket)
{

    while (true)
    {

        int option;

        int valread = recv(client_socket, &option, sizeof(int), 0);

        switch (option)
        {
        case 1:
        {
            register_user(client_socket);
            break;
        }
        case 2:
        {
            register_worker(client_socket);
            break;
        }
        case 3:
        {
            authenticate(client_socket);
            break;
        }
        case 4:
        {
            make_request(client_socket);
            break;
        }
        case 5:
        {
            get_request(client_socket);
            break;
        }
        }
    }

    close(client_socket);
}

int main()
{
    signal(SIGINT, signalHandler);

    initializeUsers();
    initializeWorkers();

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    vector<thread> threads;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    cout << "Server listening on port " << PORT << endl;

    while (true)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        threads.push_back(thread(handle_client, new_socket));
    }

    for (auto &th : threads)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    saveUsers();

    close(server_fd);

    return 0;
}
