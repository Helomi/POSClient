//
// Created by helom on 26. 12. 2021.
//

#include "../Headers/Application.h"

Application::Application() {
    while (!vytvorSpojenie())
        sleep(2);
    uvod();
}

bool Application::vytvorSpojenie() {
    string ip = menu->zadajIP();
    string port = menu->zadajPort();
    server = gethostbyname(ip.c_str());
    if (server == NULL)
    {
        cout << "Chyba: Na zvolenej adrese nič nebeží!\n";
        cout << "Skús to znova\n";
        return false;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char*)server->h_addr,
            (char*)&serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(port.c_str()));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)

    {
        cout << "Chyba: Pri tvorení socketu došlo k chybe!\n";
        cout << "Skús to znova\n";
        return false;
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << "Chyba: Pri pokuse naviazať spojenie so serverom došlo k chybe!\n";
        cout << "Skús to znova\n";
        return false;
    }
    odosliSpravu(menu->zadajMeno());
    return true;
}

void Application::ukonciAplikaciu() {
    close(sockfd);
    exit(0);
}

bool Application::zalozHru() {
    odosliSpravu(menu->vytvorenieLobby());
    string pomocna = primiSpravu();
    if (pomocna.compare("OK") == 0)
    {
        cout << "Server bol úspešne vytvorený\n";
        return true;
    } else {
        cout << "Bol dosiahnutý maximálny počet serverov, server sa nepodarilo vytvoriť.\n";
        return false;
    }
}

bool Application::pripojenieDoHry() {
    list<string> zoznamLobby;
    Utilities utilities;
    string pomocna;
    odosliSpravu("DZL");
    primiSpravu();
    while (buffer) {
        pomocna = buffer;
        stringstream check1(pomocna);
        string pomocna2;
        while(getline(check1, pomocna2, '|'))
        {
            if (pomocna2.compare("END") == 0) {
                break;
            }
            zoznamLobby.push_back(pomocna2);
        }
        if (pomocna2.compare("END") == 0) {
            break;
        }
        primiSpravu();
    }


    system("clear");
    cout << "###################\n";
    cout << "#   VYPIS LOBBY   #\n";
    cout << "###################\n";
    if (zoznamLobby.size() == 0) {
        cout << "Nie je založená žiadna lobby!\n";
        sleep(1);
        return false;
    } else {
        list <string> :: iterator lobby;
        int i = 1;
        for (lobby = zoznamLobby.begin(); lobby != zoznamLobby.end(); lobby++)
        {
            if (lobby->find("#") != std::string::npos) {
                cout << i << ". " << *lobby << " | Status: Hra prebieha\n";
            } else {
                cout << i << ". " << *lobby << " | Status: Čakám na protihráča\n";
            }
            i++;
        }
        cout << "\n";
        cout << i << ". Návrat do hlavného menu\n";
    }
    cout << "Vyber si lobby kam sa chceš pripojiť.\n";
    int vyber = utilities.zadajCislo(1,zoznamLobby.size()+1);
    cout << "Vybral si: " << vyber << "\n";
    if (vyber == zoznamLobby.size()+1) {
        odosliSpravu("QUI");
        return false;
    }
    pomocna = "JOI|" + to_string(vyber);
    odosliSpravu(pomocna);
    return true;
}

void Application::uvod() {
    int vyber = menu->vypisMenu();
    switch (vyber) {
        case 1:
            if (zalozHru()) {
                cout << "Čakáš na pripojenie 2. hráča\n";
                zacniHru();
            } else {
                cout << "Server sa nepodarilo vytvoriť!\n";
                sleep(2);
                uvod();
            }
            break;
        case 2:
            if (!pripojenieDoHry()) {
                uvod();
            } else {
                zacniHru();
            }
            break;
        case 3:
            ukonciAplikaciu();
            break;
    }
}

void Application::odosliSpravu(string sprava) {
    bzero(buffer,256);
    strcpy(buffer, sprava.c_str());
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
    {
        perror("Error writing to socket");
    }
}

char* Application::primiSpravu() {
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
    }
    return buffer;
}

void Application::zacniHru() {
    string pomocna = primiSpravu();
    cout << pomocna << "\n";
    stringstream check1(pomocna);
    string pomocna2;
    getline(check1, pomocna2, '|');
    check1 >> velkostMapy;
    if (pomocna2.compare("STR") == 0) {
        cout << "Hra začína!\n";
        mapa = new char* [velkostMapy];
        for (int i = 0; i < velkostMapy; ++i) {
            mapa[i] = new char[velkostMapy];
            for (int j = 0; j < velkostMapy; ++j) {
                mapa[i][j] = ' ';
            }
        }
        do {
            vykresliPlochu();
        }
        while (urobTah());
    } else if (pomocna2.compare("NO") == 0) {
        cout << "Server ťa odmietnul pripojiť k tejto lobby\n";
        sleep(2);
        uvod();
    } else if (pomocna2.compare("OOT") == 0){ //OOT - Out of time
        cout << "Čas na pripojenie 2. hráča vypršal. Server sa uzavrel\n";
    } else {
        cout << "Dostal som nejakú neznámu správu???" << pomocna2 << "\n";
    }
}

void Application::vykresliPlochu() {
    system("clear");
    cout << "|   |   | X | --";
    for (int i = 0; i < velkostMapy-2; ++i) {
        cout << "----";
    }
    cout << ">\n|   |   |";
    for (int i = 0; i < velkostMapy; ++i) {
        cout << " " << i << " |";
    }
    cout << "\n";
    for (int i = 0; i < velkostMapy; ++i) {
        if (i == 0) {
            cout << "| Y | " << i << " ";
        } else if (i == velkostMapy-1) {
            cout << "| V | " << i << " ";
        } else {
            cout << "| | | " << i << " ";
        }
        cout << "|";
        for (int j = 0; j < velkostMapy; ++j) {
            cout << " " << mapa[i][j] << " |";
        }
        cout << "\n";
    }
}

bool Application::urobTah() {
    cout << "Čakám na správu od serveru..\n";
    string pomocna;
    int x;
    int y;
    Utilities utilities;
    pomocna = primiSpravu();
    stringstream check1(pomocna);
    string pomocna2;
    cout << "Dostal som správu " << pomocna << "\n";
    getline(check1, pomocna2, '|');
    if (pomocna2.compare("DTN") == 0) {
        tcflush(0,TCIFLUSH);
        while(true) {
            cout << "Zadaj X-ovú os:\n";
            x = utilities.zadajCislo(0, velkostMapy-1);
            cout << "Zadaj Y-ovú os:\n";
            y = utilities.zadajCislo(0, velkostMapy-1);
            if (kontrolaTahu(x, y)) {
                break;
            } else {
                cout << "Toto políčko už je obsadené skús to ešte raz.\n";
            }
        }
        odosliSpravu("UPD|" + to_string(x) + "|" + to_string(y));
        mapa[y][x] = 'O';
    } else if (pomocna2.compare("DTU") == 0)
    {
        tcflush(0,TCIFLUSH);
        getline(check1, pomocna2, '|');
        x = stoi(pomocna2);
        getline(check1, pomocna2, '|');
        y = stoi(pomocna2);
        mapa[y][x] = 'X';
        vykresliPlochu();
        cout << "Dostal som správu " << pomocna << "\n";
        while(true) {
            cout << "Zadaj X-ovú os:\n";
            x = utilities.zadajCislo(0, velkostMapy-1);
            cout << "Zadaj Y-ovú os:\n";
            y = utilities.zadajCislo(0, velkostMapy-1);
            if (kontrolaTahu(x, y)) {
                break;
            } else {
                cout << "Toto políčko už je obsadené skús to ešte raz.\n";
            }
        }
        mapa[y][x] = 'O';
        odosliSpravu("UPD|" + to_string(x) + "|" + to_string(y));
    } else if (pomocna2.compare("LOS") == 0) {
        getline(check1, pomocna2, '|');
        x = stoi(pomocna2);
        getline(check1, pomocna2, '|');
        y = stoi(pomocna2);
        mapa[y][x] = 'X';
        vykresliPlochu();
        cout << "Vypadá to že si prehral LOL!\n";
        return false;
    } else if (pomocna2.compare("WIN") == 0) {
        cout << "Vyhral si EZCLAP\n";
        return false;
    } else if (pomocna2.compare("DRW") == 0) {
        cout << "Remíza.. došli vám políčka borci :D\n";
        return false;
    } else if (pomocna2.compare("DRWU") == 0) {
        getline(check1, pomocna2, '|');
        x = stoi(pomocna2);
        getline(check1, pomocna2, '|');
        y = stoi(pomocna2);
        mapa[y][x] = 'X';
        vykresliPlochu();
        cout << "Remíza.. došli vám políčka borci :D\n";
        return false;
    } else if (pomocna2.compare("QUT") == 0) {
        cout << "Server stratil spojenie so súperom :/\nHra sa preto ukončí\n";
        return false;
    } else {
        cout << "Nastala neočakávaná chyba!\nHra sa ukončí\n";
        return false;
    }
    return true;
}

Application::~Application() {
    for (int i = 0; i < velkostMapy; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
    delete menu;
}

bool Application::kontrolaTahu(int x, int y) {
    if (mapa[y][x] == ' ') {
        return true;
    }
    return false;
}

