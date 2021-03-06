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



string Vypisy::zadajIP() {
    system("clear");
    string ip;
    cout << "Zadaj IP: ";
    getline(cin, ip);
    return ip;
}

string Vypisy::zadajPort() {
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
    int vyber;
    switch (utilities.zadajCislo(1,3)) {
        case 1:
            vyber = 3;
            break;
        case 2:
            vyber = 5;
            break;
        case 3:
            vyber = 7;
            break;
    }
    return "CRT|" + navrat + "|" + to_string(vyber);
}

string Vypisy::zadajMeno() {
    printf("Zadaj meno uživateľa: ");
    string meno;
    while (meno.size() < 5 || meno.size() > 50) {
        getline(cin, meno);
        if (meno.size() < 5) {
            system("clear");
            printf("Tvoje meno je moc krátke, minimálne 5 znakov!\n");
            printf("Zadaj meno uživateľa: ");
        }
        if (meno.size() > 50) {
            system("clear");
            printf("Tvoje meno je moc dlhé, maximálne 50 znakov!\n");
            printf("Zadaj meno uživateľa: ");
        }
    }
    return meno;
}
