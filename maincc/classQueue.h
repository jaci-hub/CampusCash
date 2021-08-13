#pragma once
#include <iostream>
#include <string>
using namespace std;

class Queue
{
private:
    int front;
    int rear;
    int arr[100000];

public:
    Queue() {
        rear = -1;
        front = -1;
        for (int i = 0; i < 100000; i++) {
            arr[i] = 0;
        }
    }
    bool isEmpty() {
        if (front == -1 && rear == -1)
            return true;
        else
            return false;
    }
    bool isFull() {
        if (rear == 99999)
            return true;
        else
            return false;
    }
    void enqueue(int val) {
        if (isFull())
            cout << "Queue is full!\n";
        else {
            front = 0;
            rear++;
            arr[rear] = val;
        }
    }
    void dequeue() {
        if (isEmpty())
            cout << "Queue is Empty!\n";
        else {
            for (int i = 0; i < rear; i++)
                arr[i] = arr[i + 1];
            arr[rear] = 0;
            rear--;
        }
    }
    void count() {
        if (rear + 1 == 0)
            cout << "There is no one in line\n";
        else if (rear + 1 == 1)
            cout << "There is one person in line\n";
        else
        {
            cout << "There are " << rear + 1 << " people in line\n";
        }
    }
    void display() {
        for (int i = 0; i < 10; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};