#ifndef ORDERHISTORYLIST_HPP
#define ORDERHISTORYLIST_HPP

// A OrderHistoryList é uma lista duplamente encadeada: uma sequência de nós (ListNode), 
// cada um guardando um pedido e dois ponteiros, um para o nó de trás e um para o da frente. 

#include <iostream>
#include <string>
#include "Order.hpp"
#include "ListNode.hpp"

using namespace std;

class OrderHistoryList {
private:
    ListNode* head;
    ListNode* tail;
    ListNode* current;
    int size;

    ListNode* findNode(int number) const;

public:
    OrderHistoryList();
    ~OrderHistoryList();

    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }

    void insertAtHead(const Order& order);
    void insertAtTail(const Order& order);
    bool insertAtPosition(const Order& order, int pos);

    bool removeByNumber(int number);

    Order* findByNumber(int number);
    int findByCustomer(const std::string& customer) const;

    void traverseForward() const;
    void traverseBackward() const;

    Order* goToHead();
    Order* goToNext();
    Order* goToPrevious();

    void dailyReport() const;
};

#endif