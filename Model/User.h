#pragma once

#include <iostream>

struct User {

public:
    char Email[255];
    char FirstName[255];
    char LastName[255];
    char Password[255];
    char Gender[255];
    int Age;

    User() = default;

    User(char *email, char *firstName, char *lastName, char *password, char *gender, int age) {
        strcpy(Email, email);
        strcpy(FirstName, firstName);
        strcpy(LastName, lastName);
        strcpy(Password, password);
        strcpy(Gender, gender);
        Age = age;
    }

    ~User() = default;
};