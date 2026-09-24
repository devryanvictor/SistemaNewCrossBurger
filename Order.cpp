#include "Order.hpp"

Order::Order() : number(0), customer(""), itemCount(0), total(0.0f) {}

Order::Order(int number, const string& customer) // construtor
    : number(number), customer(customer), itemCount(0), total(0.0f) {}

bool Order::addItem(const string& name, float price) {
    if (itemCount >= MAX_ITEMS) { // permite que não exceda o limite 
        return false;
    }
    items[itemCount] = name; // guarda o nome da primeira posição livre
    itemCount++; // vai incrementando conforme a quantidade de itens
    total = total + price; // soma o preço ao total
    return true; // avisa que deu certo
}

void Order::display() const {
    cout << "Pedido #" << number << " | Cliente: " << customer << " | Itens: ";
    if (itemCount == 0) { // se não tiver nenhum item, imprime (nenhum)
        cout << "(nenhum)";
    }
    for (int i = 0; i < itemCount; i++) {
        cout << items[i];
        if (i < itemCount - 1) { //imprime com virgula apenas se o item ainda não for o ultimo
            cout << ", ";
        }
    }
    cout << " | Total: R$ " << total << endl; // imprime o total
}