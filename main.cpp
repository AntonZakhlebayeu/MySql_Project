#include <iostream>
#include "Database/Database.h"
#include "SHA256/sha256.h"
#include "Controller/Header/Controller.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

int main() {
    Database database;
    database.OpenDatabaseConnection();

    database.WelcomePage();

    return 0;
}
