//
// Created by helom on 26. 12. 2021.
//

#ifndef SEMESTRALKACLIENT_UTILITIES_H
#define SEMESTRALKACLIENT_UTILITIES_H

#include <iostream>
#include <string>
using namespace std;

class Utilities {
private:
public:
    int zadajCislo(int min, int max)
    {
        cout << "Zadaj cislo od " << min << " do " << max << "\n";
        int i = 0;
        cin >> i;
        while (true)
        {
            if (!cin) {
                cin.clear();
                cin.ignore(INTMAX_MAX, '\n');
            }
            else if (i >= min && i <= max){
                return i;
            }
            cout << "Zadali ste chybne cislo\n";
            cin >> i;
        }
    }
};

#endif //SEMESTRALKACLIENT_UTILITIES_H
