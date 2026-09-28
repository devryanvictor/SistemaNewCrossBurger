#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include "Pedido.hpp"

class ListNode {
public:
    Pedido dados;
    ListNode* ant;
    ListNode* prox;

    ListNode(const Pedido& pedido) : dados(pedido), ant(nullptr), prox(nullptr) {} // construtor
};

#endif