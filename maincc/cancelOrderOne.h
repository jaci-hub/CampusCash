#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "classOrderFood.h"
#include "formatName.h"

using namespace std;

int qstateCancelOrderOne;

//***cancelOrderOne function***
void cancelOrderOne() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        string studentEmail, paymentMethod;
        //get studentEmail and paymentMethod
        string querySelectEmailAndPaymentMethod = "SELECT studentEmail, paymentMethod FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE orderID = 1";
        const char* qSelectEmailAndPaymentMethod = querySelectEmailAndPaymentMethod.c_str();
        qstateCancelOrderOne = mysql_query(conn, qSelectEmailAndPaymentMethod);
        if (!qstateCancelOrderOne) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            studentEmail = row[0];
            paymentMethod = row[1];
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //get subtotal and delivery fee
        double totalCharged;
        string querySelectSubtotalDelFee = "SELECT subTotal, deliveryFee FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE studentEmail = '" + studentEmail + "'";
        const char* qSelectSubtotalDelFee = querySelectSubtotalDelFee.c_str();
        qstateCancelOrderOne = mysql_query(conn, qSelectSubtotalDelFee);
        if (!qstateCancelOrderOne) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            totalCharged = stod(row[0]) + stod(row[1]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //remove student from orderstable
        string queryRem = "DELETE FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE orderID = 1";
        const char* qRem = queryRem.c_str();
        qstateCancelOrderOne = mysql_query(conn, qRem);
        if (qstateCancelOrderOne)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //decrement all orderID > 1
        string queryUpdateOrderID = "UPDATE " + allinOne_class.get_buildingName() + "OrdersTable SET orderID = orderID - 1 WHERE orderID > 0";
        const char* qUpdateOrderID = queryUpdateOrderID.c_str();
        qstateCancelOrderOne = mysql_query(conn, qUpdateOrderID);
        if (qstateCancelOrderOne)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //set buildingorderedfrom = 'none'
        string queryUpdatebuildingorderedfrom = "UPDATE studentdatatable SET buildingOrderedFrom = 'none' WHERE studentEmail = '" + studentEmail + "'";
        const char* qUpdatebuildingorderedfrom = queryUpdatebuildingorderedfrom.c_str();
        qstateCancelOrderOne = mysql_query(conn, qUpdatebuildingorderedfrom);
        if (qstateCancelOrderOne)
            cout << "Query failed: " << mysql_error(conn) << "\n";

        //refund
        string queryEmail1 = "SELECT " + paymentMethod + " FROM studentdatatable WHERE studentEmail = '" + studentEmail + "'";
        const char* qEmail1 = queryEmail1.c_str();
        qstateCancelOrderOne = mysql_query(conn, qEmail1);
        if (!qstateCancelOrderOne) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);

            string oldValue = row[0];
            double newValue = stod(oldValue);

            //Cash
            if (paymentMethod == "Cash")
                newValue += totalCharged;
            //Meals
            else if (paymentMethod == "Meals")
                newValue += 1;

            //Update student balance in the DB
            string newValueString = to_string(newValue);
            string querynewValue = "UPDATE studentdatatable SET " + paymentMethod + " = '" + newValueString + "' WHERE studentEmail = '" + studentEmail + "'";
            const char* qnewValue = querynewValue.c_str();
            qstateCancelOrderOne = mysql_query(conn, qnewValue);
            if (qstateCancelOrderOne)
                cout << "Query failed: " << mysql_error(conn) << "\n";
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";

        //set canceledOrderMessage = '1'
        string querycanceledOrderMessage = "UPDATE studentdatatable SET canceledOrderMessage = '1' WHERE studentEmail = '" + studentEmail + "'";
        const char* qcanceledOrderMessage = querycanceledOrderMessage.c_str();
        qstateCancelOrderOne = mysql_query(conn, qcanceledOrderMessage);
        if (qstateCancelOrderOne)
            cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}