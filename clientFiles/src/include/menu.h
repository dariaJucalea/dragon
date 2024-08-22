#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

class menu
{
private:
  int role;

public:
  menu();
  void print(int sock);
  bool handleOption(int sock);
  void UserMenu(int id, int sock);
  void WorkerMenu(int id, int sock);
  void getProgram(int id, int sock);
  void modificaProgramul(int id, int sock);
  void plaseazaCerere(int id, int sock);

  ~menu();
};
