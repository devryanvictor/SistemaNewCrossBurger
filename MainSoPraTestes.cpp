#include "Order.hpp"
#include "OrderHistoryList.hpp"

int main() {
    OrderHistoryList history;

    Order o1(1, "Ana");
    o1.addItem("X-Burger", 25.00f);
    o1.addItem("Refrigerante", 6.00f);

    Order o2(2, "Bruno");
    o2.addItem("X-Bacon", 30.00f);

    Order o3(3, "Carla");
    o3.addItem("Batata Frita", 15.00f);

    Order o4(4, "Ana");
    o4.addItem("X-Salada", 22.00f);

    history.insertAtTail(o1);
    history.insertAtTail(o2);
    history.insertAtHead(o3);
    history.insertAtPosition(o4, 2);

    cout << "--- Para frente ---" << endl;
    history.traverseForward();

    cout << "\n--- Para tras ---" << endl;
    history.traverseBackward();

    cout << "\n--- Busca por numero (2) ---" << endl;
    Order* found = history.findByNumber(2);
    if (found != nullptr) {
        found->display();
    }

    cout << "\n--- Anterior e proximo a partir do #2 ---" << endl;
    history.goToPrevious()->display();
    history.goToNext()->display();
    if (history.goToNext() == nullptr) {
        cout << "Ja esta no ultimo pedido, nao ha proximo." << endl;
    }

    cout << "\n--- Busca por cliente (Ana) ---" << endl;
    int count = history.findByCustomer("Ana");
    cout << count << " pedido(s) encontrado(s)." << endl;

    cout << "\n--- Remocao do #4 (meio da lista) ---" << endl;
    if (history.removeByNumber(4)) {
        cout << "Removido." << endl;
    }
    if (!history.removeByNumber(99)) {
        cout << "Pedido 99 nao existe." << endl;
    }

    cout << "\n--- Relatorio do dia ---" << endl;
    history.dailyReport();

    return 0;
}