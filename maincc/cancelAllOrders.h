#pragma once
#include <iostream>
#include <string>
#include "classSender.h"
#include "classOrderFood.h"
#include "formatName.h"

using namespace std;

int qstateCancelAllOrders;

//***cancelAllOrders function***
void cancelAllOrders() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        int maxOrderID;
        string studentEmail, paymentMethod;
        //get the max orderID (to set the for-loop)
        string querySelectOrderID = "SELECT MAX(orderID) AS maxOrderID FROM " + allinOne_class.get_buildingName() + "OrdersTable";
        const char* qSelectOrderID = querySelectOrderID.c_str();
        qstateCancelAllOrders = mysql_query(conn, qSelectOrderID);
        if (!qstateCancelAllOrders) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            maxOrderID = stoi(row[0]);
        }
        else cout << "Query failed: " << mysql_error(conn) << "\n";
        
        for(int i = maxOrderID; i > 0; i--) {
            //get studentEmail and paymentMethod
            string querySelectEmailAndPaymentMethod = "SELECT studentEmail, paymentMethod FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE orderID = " + to_string(i);
            const char* qSelectEmailAndPaymentMethod = querySelectEmailAndPaymentMethod.c_str();
            qstateCancelAllOrders = mysql_query(conn, qSelectEmailAndPaymentMethod);
            if (!qstateCancelAllOrders) {
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
            qstateCancelAllOrders = mysql_query(conn, qSelectSubtotalDelFee);
            if (!qstateCancelAllOrders) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                totalCharged = stod(row[0]) + stod(row[1]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //set buildingorderedfrom = 'none'
            string queryUpdatebuildingorderedfrom = "UPDATE studentdatatable SET buildingOrderedFrom = 'none' WHERE studentEmail = '" + studentEmail + "'";
            const char* qUpdatebuildingorderedfrom = queryUpdatebuildingorderedfrom.c_str();
            qstateCancelAllOrders = mysql_query(conn, qUpdatebuildingorderedfrom);
            if (qstateCancelAllOrders)
                cout << "Query failed: " << mysql_error(conn) << "\n";
        
            //refund
            string queryEmail1 = "SELECT " + paymentMethod + " FROM studentdatatable WHERE studentEmail = '" + studentEmail + "'";
            const char* qEmail1 = queryEmail1.c_str();
            qstateCancelAllOrders = mysql_query(conn, qEmail1);
            if (!qstateCancelAllOrders) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);

                string oldValue = row[0];
                double newValue = stod(oldValue);

                //Cash
                if (paymentMethod == "studentBalance")
                    newValue += totalCharged;
                //Meals
                else if (paymentMethod == "studentMeals")
                    newValue += 1;

                //Update senders balance in the DB
                string newValueString = to_string(newValue);
                string querynewValue = "UPDATE studentdatatable SET " + paymentMethod + " = '" + newValueString + "' WHERE studentEmail = '" + studentEmail + "'";
                const char* qnewValue = querynewValue.c_str();
                qstateCancelAllOrders = mysql_query(conn, qnewValue);
                if (qstateCancelAllOrders)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";
        }

        //remove ALL orderID > 0 
        string queryRemAll = "DELETE FROM " + allinOne_class.get_buildingName() + "OrdersTable WHERE orderID > 0";
        const char* qRemAll = queryRemAll.c_str();
        qstateCancelAllOrders = mysql_query(conn, qRemAll);
        if (qstateCancelAllOrders)
            cout << "Query failed: " << mysql_error(conn) << "\n";
    }
    else puts("Connection to DataBase has failed");
}