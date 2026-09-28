#ifndef HISTORICOPEDIDOS_HPP
#define HISTORICOPEDIDOS_HPP

// A ListaHistoricoPedidos é uma lista duplamente encadeada: uma sequência de nós (ListNode), 
// cada um guardando um pedido e dois ponteiros, um para o nó de trás e um para o da frente. 

#include <iostream>
#include <string>
#include "Pedido.hpp"
#include "ListNode.hpp"

using namespace std;

class ListaHistoricoPedidos {
private:
    ListNode* head;
    ListNode* tail;
    ListNode* current;
    int tamanho;

    ListNode* encontrarNode(int numero) const;

public:
    ListaHistoricoPedidos();
    ~ListaHistoricoPedidos();

    bool isVazia() const { return head == nullptr; }
    int getTamanho() const { return tamanho; }

    void inserirHead(const Pedido& pedido);
    void inserirTail(const Pedido& pedido);
    bool inserirPosicao(const Pedido& pedido, int pos);

    bool removerPorNumero(int numero);

    Pedido* encontrarPorNumero(int numero);
    int encontrarPorCliente(const std::string& cliente) const;

    void percorreFrente() const;
    void percorreTras() const;

    Pedido* goToHead();
    Pedido* goToProx();
    Pedido* goToAnt();

    void reportDiario() const;
};

#endif