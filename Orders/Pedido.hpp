#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>

using namespace std;
#include <string> //traz o tipo string utilizado em costumer(clientes) e items(itens)

const int MAX_ITEMS = 20;

class Pedido {
    public:
        Pedido();
        Pedido(int numero, const std::string& cliente);
    
        bool adicionarItem(const std::string& nome, float preco);
        void exibir() const;
    
        int getNumero() const { return numero; }
        std::string getCliente() const { return cliente; }
        float getTotal() const { return total; }
    private:
        int numero;
        std::string cliente;
        std::string itens[MAX_ITEMS];
        int itemContador;
        float total;

};


#endif

#ifndef CARDAPIO_HPP
#define CARDAPIO_HPP

class Cardapio {
public:
    Cardapio();
    Cardapio(const std::string nome, float valor);

    std::string getNome() const;
    float getValor() const;

private:
    int valor;
    std::string nome;
};
#endif