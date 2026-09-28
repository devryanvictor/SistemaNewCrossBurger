#include "HistoricoPedidos.cpp"
#include "HistoricoPedidos.hpp"
#include "Pedido.cpp"
#include <iostream>

using namespace std;


int main (void){
ListaHistoricoPedidos historico;
Pedido pedido;

int opcao;
int numPedido = 1; 




//std::string nome = "hamburguer";
//int preco = 20;

//for (int i = 0; i < 2; i++){
  //  pedido.adicionarItem(nome, preco);
  //  nome = "refri";
  //  preco = 5;
//}

do{
    cout << "\n----------NewCrossBurger Pedidos!----------\n\n";
    cout << "1 - registrar um pedido\n";
    cout << "2 - Exibir todos os pedidos\n";
    cout << "3 - encontrar um pedido\n";
    cout << "4 - registrar um pedido\n";
    cout << "5 - ver registro de vendas Diario\n";
    cout << "6 - remover pedido \n";
    cout << "0 - fechar aplicacao\n\n";
    cin >> opcao;


    if (opcao == 1){
        std::string cliente;
        string nomepedido;
        int preco;

        cout << "\n---------- REGISTRAR PEDIDOS ----------\n";

        cout << "Informe seu nome:\n";
        cin >> cliente;
        Pedido pedido(numPedido, cliente);
        cout << "Informe seu pedido:\n";
        do{
            cout << "1 - Hamburguer\n";
            cout << "2 - Refrigerante\n";
            cout << "0 - finalizar pedido\n";
            cin >> opcao;
            if (opcao == 1){
                nomepedido = "Hamburguer";
                preco = 20.0;
            }else if(opcao == 2){
                nomepedido = "Refrigerante";
                preco = 7.0;
            }else{
                cout << "Nao temos essa opcao";
            }
            
            pedido.adicionarItem(nomepedido, preco);
            pedido.exibir();

        }while(opcao !=0);
        opcao = -1;

        

        historico.inserirTail(pedido);

        cout << "\nPedido registrado!\n";

        numPedido++;
    }

    else if (opcao == 2) {

        cout << "\n---------- SEUS PEDIDOS ----------\n";

        historico.percorreFrente();
    }

    else if (opcao == 3){
        int numero;

        cout << "Informe o numero do pedido:\n";
        cin >> numero;

        Pedido* encontrado = historico.encontrarPorNumero(numero);

        if (encontrado != nullptr) {
            cout << "Pedido encontrado!.\n";
            encontrado->exibir();
        } else {
            cout << "Pedido nao encontrado.\n";
        }
    }

    
}while(opcao != 0);

    return 0;
}