#include "Pedido.hpp"

Cardapio::Cardapio() : valor(0), nome(""){}

Cardapio::Cardapio(const std::string nome, float valor)
  : nome(nome), valor(valor) {}

//-------------------------------------------------------------------------------------------------------------------


Pedido::Pedido() : numero(0), cliente(""), itemContador(0), total(0.0f) {}

Pedido::Pedido(int numero, const string& cliente) // construtor
    : numero(numero), cliente(cliente), itemContador(0), total(0.0f) {}

bool Pedido::adicionarItem(const string& nome, float preco) {
    if (itemContador >= MAX_ITEMS) { // permite que não exceda o limite 
        return false;
    }
    itens[itemContador] = nome; // guarda o nome da primeira posição livre
    itemContador++; // vai incrementando conforme a quantidade de itens
    total = total + preco; // soma o preço ao total
    return true; // avisa que deu certo
}

void Pedido::exibir() const {
    cout<< "Pedido #" << numero << " | Cliente: " << cliente << " | Itens: ";
    if (itemContador == 0) { // se não tiver nenhum item, imprime (nenhum)
        cout << "(nenhum)";
    }
    for (int i = 0; i < itemContador; i++) {
        cout << itens[i];
        if (i < itemContador - 1) { //imprime com virgula apenas se o item ainda não for o ultimo
            cout << ", ";
        }
    }
    cout << " | Total: R$ " << total << endl; // imprime o total
}