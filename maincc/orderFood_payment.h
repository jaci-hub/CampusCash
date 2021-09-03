#pragma once
#include <iostream>
#include <string>
#include "criar_sender.h"
#include "file_com_pragmaonce_mysql.h"
#include "getFee.h"
#include "getCurrentDateTime.h"
#include "orderFood.h"
#include "setLineNumber.h"
#include "getLineNumber.h"
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
        cout << "* Delivery Fee: $" << myOrder.get_foodOrderTotal() * getFee(myOrder.get_selectedOnOffCampus() + " Delivery Fee") / 100.00 << "\n";
        cout << "** TOTAL: $" << myOrder.get_foodOrderTotal() * (1.00 + getFee(myOrder.get_selectedOnOffCampus() + " Delivery Fee") / 100.00) << "\n";

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

        
        cout << "** You will be #" << setLineNumber() << " in line! **\n";

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
                    newValue -= myOrder.get_foodOrderTotal() * (1.00 + getFee(myOrder.get_selectedOnOffCampus() + " Delivery Fee") / 100.00);

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
            string queryAddOrder = "INSERT INTO " + myOrder.get_selectedBuilding() + "OrdersTable(orderID, studentEmail, diet, meal, sideOne, sideTwo, sideThree, onOffCampus, dorm, roomNumber, subTotal, deliveryFee, paymentMethod, orderDateTime) VALUES(" + to_string(setLineNumber()) + ", '" + student1.get_email() + "', " + "'" + myOrder.get_selectedDiet() + "', " + "'" + myOrder.get_selectedMeal() + "', " + "'" + myOrder.get_selectedSideOne() + "', " + "'" + myOrder.get_selectedSideTwo() + "', " + "'" + myOrder.get_selectedSideThree() + "', " + "'" + myOrder.get_selectedOnOffCampus() + "', " + "'" + myOrder.get_selectedDorm() + "', " + "'" + myOrder.get_selectedRoom() + "', " + to_string(myOrder.get_foodOrderTotal()) + ", " + to_string(myOrder.get_foodOrderTotal() * getFee(myOrder.get_selectedOnOffCampus() + " Delivery Fee") / 100.00) + ", '" + thePaymentMethod + "', '" + getCurrentDateTime() + "')";
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
            if (getLineNumber() == 1) {
                cout << "*** Campus Cash (CC) ***" << "\n";
                cout << "* Your order is being prepared right now!\n";
            }
            else if (getLineNumber() > 1) {
                cout << "*** Campus Cash (CC) ***" << "\n";
                cout << "* Line#: " << getLineNumber() << "\n";
            }

            //set canceledOrderMessage = '0' first
            string querycanceledOrderMessage0 = "UPDATE studentdatatable SET canceledOrderMessage = '0' WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qcanceledOrderMessage0 = querycanceledOrderMessage0.c_str();
            qstateFoodPayment = mysql_query(conn, qcanceledOrderMessage0);
            if (qstateFoodPayment)
                cout << "Query failed: " << mysql_error(conn) << "\n";
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