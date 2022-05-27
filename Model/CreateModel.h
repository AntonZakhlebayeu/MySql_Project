#pragma once
#include "User.h"
#include "../SHA256/sha256.h"
#include "Validators.h"

using std::cout;
using std::cin;
using std::endl;

User CreateUser() {
    char Email[255];
    char FirstName[255];
    char LastName[255];
    char Gender[255];
    char Password[255];
    char ConfirmPassword[255];

    cout << "Enter the Email: " << endl;
    cin >> Email;
    while(!EmailValidation(Email)) {
        cout << "Invalid email!\nEmail template: example@example.com" << endl;
        cin >> Email;
    }

    cout << "Enter the FirstName: " << endl;
    cin >> FirstName;

    cout << "Enter the LastName: " << endl;
    cin >> LastName;

    cout << "Enter the password: " << endl;
    cin >> Password;
    while(!PasswordValidation(Password)) {
        cout << "Password must be more than 8 characters" << endl;
        cin >> Password;
    }

    cout << "Enter the password: " << endl;
    cin >> ConfirmPassword;
    while(!PasswordValidation(ConfirmPassword)) {
        cout << "Password must be more than 8 characters" << endl;
        cin >> ConfirmPassword;
    }

    while(!PasswordComparison(Password, ConfirmPassword)) {
        cout << "Passwords must be equal" << endl;
        cin >> ConfirmPassword;
    }

    SHA256 sha;
    sha.update(Password);
    uint8_t *digest = sha.digest();
    strcpy(Password, SHA256::toString(digest).c_str());
    delete[] digest;

    cout << "Is male?\n"
            "1 - male\n"
            "2 - female\n";
    int choice;
    cin >> choice;
    choice == 1 ? strcpy(Gender, "male") : strcpy(Gender, "female");

    int Age;
    cout << "Enter the age:\n";
    cin >> Age;

    return *new User(Email, FirstName, LastName, Password, Gender, Age);
}

