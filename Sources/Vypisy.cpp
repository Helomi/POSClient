//
// Created by helom on 26. 12. 2021.
//

#include "../Headers/Vypisy.h"


Vypisy::Vypisy() {

}

int Vypisy::vypisMenu() {
    Utilities utilities;
    system("clear");
    cout << "############\n";
    cout << "# Menu #\n";
    cout << "############\n";
    cout << "1. Založiť hru\n";
    cout << "2. Pripojiť sa k hre\n";
    cout << "3. Zatvoriť aplikáciu\n";
    return utilities.zadajCislo(1,3);
}


string Vypisy::ziskanieIP() {
    system("clear");
    string ip;
    cout << "Zadaj IP: ";
    getline(cin, ip);
    return ip;
}

string Vypisy::ziskaniePort() {
    string port;
    cout << "Zadaj Port: ";
    getline(cin, port);
    return port;
}

string Vypisy::vytvorenieLobby() {
    Utilities utilities;
    string navrat;
    system("clear");
    cout << "Zadaj názov lobby: ";
    //TODO Obmedziť veľkosť názvu na napr. 50 char.
    cin >> navrat;
    cout << "################\n";
    cout << "# Veľkosť mapy #\n";
    cout << "################\n";
    cout << "1. 3x3\n";
    cout << "2. 5x5\n";
    cout << "3. 7x7\n";
    return "CRT|" + navrat + "|" + to_string(utilities.zadajCislo(1,3));
}
