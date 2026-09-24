#ifndef ORDER_HPP
#define ORDER_HPP
#include <iostream>

using namespace std;
#include <string> //traz o tipo string utilizado em costumer(clientes) e items(itens)

const int MAX_ITEMS = 20;

class Order {
    public:
        Order();
        Order(int number, const std::string& customer);
    
        bool addItem(const std::string& name, float price);
        void display() const;
    
        int getNumber() const { return number; }
        std::string getCustomer() const { return customer; }
        float getTotal() const { return total; }
    private:
        int number;
        std::string customer;
        std::string items[MAX_ITEMS];
        int itemCount;
        float total;

};

#endif