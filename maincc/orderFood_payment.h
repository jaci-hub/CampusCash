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

        //payment Method AVAILABLE AT SPECIFIED TIMES
        paymentMethod:
        cout << "* Select payment method\n";
        cout << "1- Meals\n";
        cout << "2- Coyote Cash\n";
        cout << "Please, enter an option: ";
        string metodoDePagamento;
        cin >> metodoDePagamento;
        if (metodoDePagamento == "1")
            myOrder.paymentMethod = "Meals";
        else if (metodoDePagamento == "2")
            myOrder.paymentMethod = "Coyote Cash";
        else goto paymentMethod;

        cout << "* Select an option\n";
        cout << "1- Place order\n";
        cout << "2- Cancel order\n";
        cout << "b- Back\n";
        cout << "Please, enter an option: ";
        string orderChoice;
        cin >> orderChoice;
        if (orderChoice == "1") {
            //add to orders table

            //display message
        }
        else if (orderChoice == "2")
            goto orderFood_paymentEnd;
        else if (orderChoice == "b")
            goto paymentMethod;
    }
    else puts("Connection to DataBase has failed");

orderFood_paymentEnd:
    cout << "";
}
//*******