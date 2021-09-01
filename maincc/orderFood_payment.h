#pragma once
#include <iostream>
#include <string>
#include "criar_sender.h"
#include "file_com_pragmaonce_mysql.h"
#include "orderPaymentFee.h"
#include "getCurrentDateTime.h"
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
        cout << "2- Cash\n";
        cout << "Please, enter an option: ";
        string metodoDePagamento, thePaymentMethod;
        cin >> metodoDePagamento;
        if (metodoDePagamento == "1")
            thePaymentMethod = "studentMeals";
        else if (metodoDePagamento == "2")
            thePaymentMethod = "studentBalance";
        else goto paymentMethod;

        //show the student line number IF the order is placed
        int lineNumber;
        string querySelectOrderID = "SELECT orderID FROM " + myOrder.get_selectedBuilding() + "OrdersTable";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateFoodPayment = mysql_query(conn, qSelectOrderID);
        if (!qstateFoodPayment) {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res)) {
                lineNumber = stoi(row[0]);
            }
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        cout << "** You will be #" << lineNumber + 1 << " in line! **\n";

        cout << "* Select an option\n";
        cout << "1- Place order\n";
        cout << "2- Cancel order\n";
        cout << "b- Back\n";
        cout << "Please, enter an option: ";
        string orderChoice;
        cin >> orderChoice;
        if (orderChoice == "1") {
            //payment
            string queryEmail1 = "SELECT " + thePaymentMethod + " FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qEmail1 = queryEmail1.c_str();
            qstateFoodPayment = mysql_query(conn, qEmail1);
            if (!qstateFoodPayment) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                string oldValue = row[0];
                double newValue = stod(oldValue);

                //Cash
                if (thePaymentMethod == "studentBalance") {
                    newValue -= myOrder.get_foodOrderTotal() + orderPaymentFee();

                    //Update senders balance in the classSender
                    student1.balance = newValue;
                }
                //Meals
                else if (thePaymentMethod == "studentMeals") {
                    newValue -= 1;

                    //Update senders balance in the classSender
                    student1.mealPlanBalance = newValue;
                }

                //Update senders balance in the DB
                string newValueString = to_string(newValue);
                string querynewValue = "UPDATE studentdatatable SET " + thePaymentMethod + " = '" + newValueString + "' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qnewValue = querynewValue.c_str();
                qstateFoodPayment = mysql_query(conn, qnewValue);
                if (qstateFoodPayment)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //add order to FoodBuildingsOrdersTable
            string queryAddOrder = "INSERT INTO " + myOrder.get_selectedBuilding() + "OrdersTable(orderID, studentEmail, diet, meal, sideOne, sideTwo, sideThree, onOffCampus, dorm, roomNumber, subTotal, deliveryFee, paymentMethod, orderDateTime) VALUES(" + to_string(lineNumber + 1) + ", '" + student1.get_email() + "', " + "'" + myOrder.get_selectedDiet() + "', " + "'" + myOrder.get_selectedMeal() + "', " + "'" + myOrder.get_selectedSideOne() + "', " + "'" + myOrder.get_selectedSideTwo() + "', " + "'" + myOrder.get_selectedSideThree() + "', " + "'" + myOrder.get_selectedOnOffCampus() + "', " + "'" + myOrder.get_selectedDorm() + "', " + "'" + myOrder.get_selectedRoom() + "', " + to_string(myOrder.get_foodOrderTotal()) + ", " + to_string(orderPaymentFee()) + ", '" + thePaymentMethod + "', '" + getCurrentDateTime() + "')";
            const char* qAddOrder = queryAddOrder.c_str();
            qstateFoodPayment = mysql_query(conn, qAddOrder);
            if (qstateFoodPayment)
                cout << "Query failed: " << mysql_error(conn) << "\n";

            //add FoodBuilding to studentdatatable->buildingOrderedFrom
            string queryAddFoodBuilding = "UPDATE studentDataTable SET buildingOrderedFrom = '" + myOrder.get_selectedBuilding() + "' WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qAddFoodBuilding = queryAddFoodBuilding.c_str();
            qstateFoodPayment = mysql_query(conn, qAddFoodBuilding);
            if (qstateFoodPayment)
                cout << "Query failed: " << mysql_error(conn) << "\n";

            //display message
            if (lineNumber + 1 == 1) {
                cout << "*** Campus Cash (CC) ***" << "\n";
                cout << "* Your order is being prepared right now!\n";
            }
            else if (lineNumber + 1 > 1) {
                cout << "*** Campus Cash (CC) ***" << "\n";
                cout << "* Line#: " << lineNumber + 1 << "\n";
            }
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