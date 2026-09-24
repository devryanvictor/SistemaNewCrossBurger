#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include "Order.hpp"

class ListNode {
public:
    Order data;
    ListNode* prev;
    ListNode* next;

    ListNode(const Order& order) : data(order), prev(nullptr), next(nullptr) {} // construtor
};

#endif