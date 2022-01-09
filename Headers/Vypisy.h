//
// Created by helom on 26. 12. 2021.

//

#ifndef SEMESTRALKACLIENT_VYPISY_H
#define SEMESTRALKACLIENT_VYPISY_H

#include <iostream>
#include "Utilities.h"
#include <unistd.h>


using namespace std;

class Vypisy {
private:
public:
    Vypisy();
    int vypisMenu();
    string vytvorenieLobby();
    string zadajIP();
    string zadajPort();
    string zadajMeno();
};


#endif //SEMESTRALKACLIENT_VYPISY_H
