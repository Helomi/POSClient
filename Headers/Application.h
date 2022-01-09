//
// Created by helom on 26. 12. 2021.
//

#ifndef SEMESTRALKACLIENT_APPLICATION_H
#define SEMESTRALKACLIENT_APPLICATION_H

#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <termios.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <list>
#include <bits/stdc++.h>


#include "../Headers/Vypisy.h"


using namespace std;



class Application {
private:
    Vypisy* menu = new Vypisy();
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[256];
    int velkostMapy;
    char** mapa;

    bool zalozHru();
    void ukonciAplikaciu();
    bool vytvorSpojenie();
    bool pripojenieDoHry();
    void uvod();
    void odosliSpravu(string sprava);
    char* primiSpravu();
    void zacniHru();
    void vykresliPlochu();
    bool urobTah();
    bool kontrolaTahu(int x, int y);
public:
    Application();
    ~Application();
};


#endif //SEMESTRALKACLIENT_APPLICATION_H
