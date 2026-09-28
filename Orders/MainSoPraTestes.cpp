#include "Pedido.hpp"
#include "HistoricoPedidos.hpp"

int main() {
    ListaHistoricoPedidos history;

    Pedido o1(1, "Ana");
    o1.adicionarItem("X-Burger", 25.00f);
    o1.adicionarItem("Refrigerante", 6.00f);

    Pedido o2(2, "Bruno");
    o2.adicionarItem("X-Bacon", 30.00f);

    Pedido o3(3, "Carla");
    o3.adicionarItem("Batata Frita", 15.00f);

    Pedido o4(4, "Ana");
    o4.adicionarItem("X-Salada", 22.00f);

    history.inserirTail(o1);
    history.inserirTail(o2);
    history.inserirHead(o3);
    history.inserirPosicao(o4, 2);

    cout << "--- Para frente ---" << endl;
    history.percorreFrente();

    cout << "\n--- Para tras ---" << endl;
    history.percorreTras();

    cout << "\n--- Busca por numero (2) ---" << endl;
    Pedido* encontrado = history.encontrarPorNumero(2);
    if (encontrado != nullptr) {
        encontrado->exibir();
    }

    cout << "\n--- Anterior e proximo a partir do #2 ---" << endl;
    history.goToAnt()->exibir();
    history.goToProx()->exibir();
    if (history.goToProx() == nullptr) {
        cout << "Ja esta no ultimo pedido, nao ha proximo." << endl;
    }

    cout << "\n--- Busca por cliente (Ana) ---" << endl;
    int count = history.encontrarPorCliente("Ana");
    cout << count << " pedido(s) encontrado(s)." << endl;

    cout << "\n--- Remocao do #4 (meio da lista) ---" << endl;
    if (history.removerPorNumero(4)) {
        cout << "Removido." << endl;
    }
    if (!history.removerPorNumero(99)) {
        cout << "Pedido 99 nao existe." << endl;
    }

    cout << "\n--- Relatorio do dia ---" << endl;
    history.reportDiario();

    return 0;
}