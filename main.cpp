using namespace std;
#include <iostream>


#include "Headers/Application.h"

int main(int argc, char *argv[])
{
    Application* application = new Application();
    delete application;
    return 0;
}