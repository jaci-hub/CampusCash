#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "classOrderFood.h"
#include "formatName.h"

using namespace std;

int qstateCancelOrder;

//***cancelOrder function***
void cancelOrder() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        //get buildingOrderedFrom
        string buildingOrderedFrom;
        string querySelectbuildingOrderedFrom = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectbuildingOrderedFrom = querySelectbuildingOrderedFrom.c_str();
        qstateCancelOrder = mysql_query(conn, qSelectbuildingOrderedFrom);
        if (!qstateCancelOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            buildingOrderedFrom = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        buildingOrderedFrom = formatName(buildingOrderedFrom);

        //get orderID
        string orderID;
        string querySelectOrderID = "SELECT orderID FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateCancelOrder = mysql_query(conn, qSelectOrderID);
        if (!qstateCancelOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            orderID = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //get paymentMethod
        string thePaymentMethod;
        string querySelectpaymentMethod = "SELECT paymentMethod FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectpaymentMethod = querySelectpaymentMethod.c_str();
        qstateCancelOrder = mysql_query(conn, qSelectpaymentMethod);
        if (!qstateCancelOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            thePaymentMethod = row[0];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //get subtotal and delivery fee
        double totalCharged;
        string querySelectSubtotalDelFee = "SELECT subTotal, deliveryFee FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qSelectSubtotalDelFee = querySelectSubtotalDelFee.c_str();
        qstateCancelOrder = mysql_query(conn, qSelectSubtotalDelFee);
        if (!qstateCancelOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            totalCharged = stod(row[0]) + stod(row[1]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //remove student from orderstable
        string queryRem = "DELETE FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qRem = queryRem.c_str();
        qstateCancelOrder = mysql_query(conn, qRem);
        if (qstateCancelOrder)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //decrement the orderID of all IF it is greater than the canceled one
        string queryUpdateOrderID = "UPDATE " + buildingOrderedFrom + "OrdersTable SET orderID = orderID - 1 WHERE orderID > " + orderID;
        const char* qUpdateOrderID = queryUpdateOrderID.c_str();
        qstateCancelOrder = mysql_query(conn, qUpdateOrderID);
        if (qstateCancelOrder)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //setting buildingOrderedFrom to 'none'
        string queryUpdatebuildingOrderedFrom = "UPDATE studentdatatable SET buildingOrderedFrom = 'none' WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qUpdatebuildingOrderedFrom = queryUpdatebuildingOrderedFrom.c_str();
        qstateCancelOrder = mysql_query(conn, qUpdatebuildingOrderedFrom);
        if (qstateCancelOrder)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //refund student
        string queryEmail1 = "SELECT " + thePaymentMethod + " FROM studentdatatable WHERE studentEmail = '" + student1.get_email() + "'";
        const char* qEmail1 = queryEmail1.c_str();
        qstateCancelOrder = mysql_query(conn, qEmail1);
        if (!qstateCancelOrder) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            string oldValue = row[0];
            double newValue = stod(oldValue);

            //Cash
            if (thePaymentMethod == "studentBalance") {
                newValue += totalCharged;

                //Update senders balance in the classSender
                student1.balance = newValue;
            }
            //Meals
            else if (thePaymentMethod == "studentMeals") {
                newValue += 1;

                //Update senders balance in the classSender
                student1.mealPlanBalance = newValue;
            }

            //Update senders balance in the DB
            string newValueString = to_string(newValue);
            string querynewValue = "UPDATE studentdatatable SET " + thePaymentMethod + " = '" + newValueString + "' WHERE studentEmail = '" + student1.get_email() + "'";
            const char* qnewValue = querynewValue.c_str();
            qstateCancelOrder = mysql_query(conn, qnewValue);
            if (qstateCancelOrder)
                cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}