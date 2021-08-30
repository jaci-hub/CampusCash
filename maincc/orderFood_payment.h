#pragma once
#include <iostream>
#include <string>
#include "criar_sender.h"
#include "file_com_pragmaonce_mysql.h"
#include "orderPaymentFee.h"
#include "orderFood.h"
using namespace std;

int qstateFoodPayment;

//****send_cash function***
void orderFood_payment() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "* Subtotal: $" << myOrder.get_foodOrderTotal() << "\n";
        cout << "* Delivery Fee: $" << orderPaymentFee() << "\n";
        cout << "** TOTAL: $" << myOrder.get_foodOrderTotal() + orderPaymentFee() << "\n";

        //paymentMethod(); ???
    }
    else puts("Connection to DataBase has failed");
}
//*******