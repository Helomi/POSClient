//
// Created by helom on 26. 12. 2021.
//

#include "../Headers/Application.h"


Application::Application() {
    vytvorSpojenie();
    zadajMeno();
    uvod();
}

void Application::vytvorSpojenie() {
    string ip = menu->ziskanieIP();
    string port = menu->ziskaniePort();
    server = gethostbyname(ip.c_str());
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host\n");
        exit(0);
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
        perror("Error creating socket");
        exit(0);
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error connecting to socket");
        exit(0);
    }
}

void Application::zadajMeno() {
    printf("Zadaj meno uživateľa: ");
    string meno;
    getline(cin, meno);
    odosliSpravu(meno);
    strcpy(buffer, primiSpravu());
    printf("%s\n",buffer);
}

void Application::ukonciAplikaciu() {
    delete menu;
    close(sockfd);
    exit(0);
}

void Application::zalozHru() {
    odosliSpravu(menu->vytvorenieLobby());
    strcpy(buffer, primiSpravu());
    cout << buffer << "\n";
}

bool Application::pripojenieDoHry() {
    list<string> zoznamLobby;
    bzero(buffer,256);
    Utilities utilities;
    string pomocna = "DZL"; //DZL = Daj zoznam lobby
    odosliSpravu(pomocna);
    strcpy(buffer, primiSpravu());
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
        string pomocna = "OK"; //DZL = Daj zoznam lobby
        odosliSpravu(pomocna);
        strcpy(buffer, primiSpravu());
    }


    system("clear");
    cout << "###################\n";
    cout << "#   VYPIS LOBBY   #\n";
    cout << "###################\n";
    if (zoznamLobby.size() == 0) {
        cout << "Nie je založená žiadna lobby";
        return false;
    } else {
        list <string> :: iterator lobby;
        int i = 1;
        for (lobby = zoznamLobby.begin(); lobby != zoznamLobby.end(); lobby++)
        {
            cout << i << ". " << *lobby << "\n";
            i++;
        }
        cout << i << ". Návrat do hlavného menu\n";
    }
    cout << "Vyber si lobby kam sa chceš pripojiť.\n";
    int vyber = utilities.zadajCislo(1,zoznamLobby.size()+1);
    if (vyber == zoznamLobby.size()+1) {
        pomocna = "JOI|" + to_string(0);
        odosliSpravu(pomocna);
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
            zalozHru();
            cout << "Čakáš na pripojenie 2. hráča\n";
            //TODO rozdroliť
            strcpy(buffer, primiSpravu());
            break;
        case 2:
            if (!pripojenieDoHry()) {
                uvod();
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
        exit(0);
    }
}

char* Application::primiSpravu() {
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
    {
        perror("Error reading from socket");
        exit(0);
    }
    return buffer;
}