#pragma once

#include <regex>
#include <iostream>

using std::regex;

bool EmailValidation(const char Email[255]) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(Email, pattern);
}

bool PasswordValidation(const char Password[255]) {
    int i = 0, length = 0;
    while(Password[i] != '\0') {
        length++;
        i++;
    }

    return length>=8;
}

bool PasswordComparison(const char Password[255], const char ConfirmPassword[255]) {
    return strcmp(Password, ConfirmPassword) == 0;
}
