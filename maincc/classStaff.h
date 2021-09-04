#pragma once
#include <iostream>
#include <string>
using namespace std;

//***class Staff***
class Staff {
private:
    string name, email, id, type, foodBuilding, staffStatus; //left id as string and not int cuz it can have leading zeros

public:
    Staff() {
        type = this->type;
        name = this->name;
        email = this->email;
        id = this->id;
        foodBuilding = this->foodBuilding;
        staffStatus = this->staffStatus;
    }

    string get_name() {
        return name;
    }

    string get_email() {
        return email;
    }

    string get_id() {
        return id;
    }

    string get_type() {
        return type;
    }

    string get_foodBuilding() {
        return foodBuilding;
    }

    string get_staffStatus() {
        return staffStatus;
    }

    friend void criarStaff();
};

Staff staff; //criacao do staff type Staff
//*******