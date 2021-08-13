#pragma once
#include <iostream>
#include <string>
using namespace std;

string formatName(string name) {
    //getting all spaces out of the name first
    for (int i = 0; i < name.length(); i++)
        if (name[i] == ' ') name.erase(name.find(' '), 1);

    //name in all lower-case
    for (int i = 0; i < name.size(); i++)
        name[i] = tolower(name[i]);

    return name;
}