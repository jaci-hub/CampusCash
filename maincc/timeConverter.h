#pragma once
#include <iostream>
#include <string>
using namespace std;

string timeConverter(string atime) {
    string resultTime, horaString;
    int k = 0;
    while (atime[k] != ':') {
        horaString += atime[k];
        k++;
    }
    //to militar time
    if (atime[atime.size() - 1] == 'M') {
        //AM
        if (atime[atime.size() - 2] == 'A') {
            int i = 0;
            while (atime[i] != 'A') {
                resultTime += atime[i];
                i++;
            }
        }
        //PM
        else if (atime[atime.size() - 2] == 'P') {
            int hora = stoi(horaString) + 12;
            //12PM
            if (hora == 24) {
                int i = 0;
                while (atime[i] != 'P') {
                    resultTime += atime[i];
                    i++;
                }
            }
            //1PM+
            else {
                resultTime = to_string(hora);
                int i = atime.find(':');
                while (atime[i] != 'P') {
                    resultTime += atime[i];
                    i++;
                }
            }
        }
    }
    //to non-militar time
    else {
        if (stoi(horaString) <= 11) {
            resultTime = horaString;
            int i = atime.find(':');
            while (atime[i]) {
                resultTime += atime[i];
                i++;
            }
            resultTime += " AM";
        }
        else {
            int hora = stoi(horaString) - 12;
            //12PM
            if (hora == 0) {
                int i = 0;
                while (atime[i]) {
                    resultTime += atime[i];
                    i++;
                }
                resultTime += " PM";
            }
            //1PM+
            else {
                resultTime = to_string(hora);
                int i = atime.find(':');
                while (atime[i]) {
                    resultTime += atime[i];
                    i++;
                }
                resultTime += " PM";
            }
        }
    }

    return resultTime;
}