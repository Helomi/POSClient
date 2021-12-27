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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    void zalozHru();
    void ukonciAplikaciu();
    void zadajMeno();
    void vytvorSpojenie();
    bool pripojenieDoHry();
    void uvod();
public:
    Application();
};


#endif //SEMESTRALKACLIENT_APPLICATION_H
