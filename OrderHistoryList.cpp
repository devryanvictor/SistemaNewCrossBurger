#include "OrderHistoryList.hpp" // traz a declaração da classe (e, junto, Order e ListNode)

OrderHistoryList::OrderHistoryList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {} // construtor: a lista nasce vazia (sem nós, sem cursor, tamanho 0)

OrderHistoryList::~OrderHistoryList() { // destrutor: roda sozinho quando a lista é destruída e libera todos os nós
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // repete até passar do último nó
        ListNode* nextNode = curr->next; // guarda o próximo ANTES de apagar (depois do delete não dá mais para ler curr->next)
        delete curr; // libera a memória do nó atual
        curr = nextNode; // avança usando o endereço guardado
    }
}

ListNode* OrderHistoryList::findNode(int number) const { // método privado: devolve o NÓ que tem esse número (ou nullptr). const = não altera a lista
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // repete enquanto não passou do último
        if (curr->data.getNumber() == number) { // curr->data é o pedido do nó, e .getNumber() lê o número dele. Se for o procurado, devolve o nó.
            return curr;
        }
        curr = curr->next; // senão, vai para o próximo.
    }
    return nullptr; // se saiu do laço, percorreu tudo e não achou, então devolve nullptr. Com lista vazia, head é nullptr, o laço nem começa e devolve nullptr direto.
}

// ---------- inserções ----------
void OrderHistoryList::insertAtHead(const Order& order) { // insere no início. Recebe o pedido por referência constante (não copia na chamada)
    ListNode* newNode = new ListNode(order); // cria o nó, com uma cópia do pedido, e prev e next já em nullptr.
    if (isEmpty()) { // se a lista estava vazia, o nó novo é ao mesmo tempo o primeiro e o último.
        head = newNode; // o novo é o primeiro
        tail = newNode; // e também o último
    } else { // se já havia nós, são três passos, nesta ordem:
        newNode->next = head; // 1) o novo aponta para o antigo primeiro
        head->prev = newNode; // 2) o antigo primeiro aponta de volta para o novo (é isso que faz a lista ser dupla)
        head = newNode; // 3) o novo passa a ser o primeiro (tem que ser por último, senão perde o acesso ao antigo head)
    }
    size++; // um nó a mais na lista (o tail não muda, o último continua o mesmo)
}

void OrderHistoryList::insertAtTail(const Order& order) { // insere no fim: espelho do insertAtHead
    ListNode* newNode = new ListNode(order); // cria o nó com uma cópia do pedido
    if (isEmpty()) { // lista vazia: o novo é o primeiro e o último
        head = newNode; // o novo é o primeiro
        tail = newNode; // e também o último
    } else { // já havia nós: três passos, nesta ordem
        newNode->prev = tail; // 1) o novo aponta para trás, para o antigo último
        tail->next = newNode; // 2) o antigo último aponta para frente, para o novo
        tail = newNode; // 3) o novo passa a ser o último. Não percorre nada: o tail já aponta para o fim, então é O(1)
    }
    size++; // um nó a mais
}

bool OrderHistoryList::insertAtPosition(const Order& order, int pos) { // insere na posição pos (começa em 0). Devolve false se a posição for inválida
    if (pos < 0 || pos > size) { // posição negativa ou maior que o tamanho é inválida (pos == size é válida: significa "no fim")
        return false; // avisa quem chamou que não inseriu
    }
    if (pos == 0) { // posição 0 = início
        insertAtHead(order); // reaproveita o método que já existe, sem repetir código
        return true; // deu certo
    }
    if (pos == size) { // posição igual ao tamanho = fim
        insertAtTail(order); // reaproveita o insertAtTail
        return true; // deu certo
    }
    ListNode* curr = head; // daqui em diante só restam posições do MEIO (o nó da posição tem vizinho dos dois lados)
    for (int i = 0; i < pos; i++) { // anda pos passos a partir do início
        curr = curr->next; // avança um nó
    }
    // ao sair do for, curr é o nó que hoje ocupa a posição pos; o novo entrará ANTES dele
    ListNode* newNode = new ListNode(order); // cria o nó com uma cópia do pedido
    newNode->prev = curr->prev; // o novo aponta para trás, para o vizinho de trás de curr
    newNode->next = curr; // o novo aponta para frente, para o próprio curr
    curr->prev->next = newNode; // o vizinho de trás passa a apontar para frente, para o novo (usa curr->prev antes de ele mudar)
    curr->prev = newNode; // curr passa a apontar para trás, para o novo (tem que ser por último)
    size++; // um nó a mais
    return true; // deu certo
}

// ---------- remoções ----------
bool OrderHistoryList::removeByNumber(int number) { // remove o pedido com esse número, esteja onde estiver. Devolve false se não existir
    ListNode* target = findNode(number); // localiza o nó a remover
    if (target == nullptr) { // não existe pedido com esse número
        return false; // caso extremo: remoção de nó inexistente, não mexe em nada
    }
    if (target->prev != nullptr) { // o alvo tem vizinho de trás?
        target->prev->next = target->next; // sim: o vizinho de trás "pula" o alvo e aponta direto para o seguinte
    } else { // não: o alvo era o primeiro
        head = target->next; // então o head avança para o seguinte
    }
    if (target->next != nullptr) { // o alvo tem vizinho da frente?
        target->next->prev = target->prev; // sim: o vizinho da frente "pula" o alvo e aponta direto para o anterior
    } else { // não: o alvo era o último
        tail = target->prev; // então o tail recua para o anterior
    }
    if (current == target) { // o cursor estava justamente no nó que vai ser apagado?
        current = (target->next != nullptr) ? target->next : target->prev; // então move para o vizinho da frente; se não houver, o de trás (se era o único, vira nullptr)
    }
    delete target; // libera a memória do nó (só agora, depois de terminar de usar o target)
    size--; // um nó a menos
    return true; // deu certo
}

// ---------- buscas ----------
Order* OrderHistoryList::findByNumber(int number) { // busca por número. Devolve o endereço do pedido (ou nullptr). Não é const porque move o cursor
    ListNode* node = findNode(number); // reaproveita o findNode
    if (node == nullptr) { // não achou
        return nullptr; // busca sem resultado
    }
    current = node; // posiciona o cursor no nó achado (permite buscar e depois navegar para o anterior/próximo)
    return &node->data; // devolve o endereço do pedido DENTRO do nó (não uma cópia). O -> é lido antes do &
}

int OrderHistoryList::findByCustomer(const string& customer) const { // busca por cliente: imprime os pedidos dele e devolve quantos achou
    int found = 0; // contador de pedidos encontrados
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // percorre a lista toda (não para no primeiro, porque o cliente pode ter vários pedidos)
        if (curr->data.getCustomer() == customer) { // o cliente do pedido é o procurado?
            curr->data.display(); // imprime o pedido
            found++; // conta mais um
        }
        curr = curr->next; // vai para o próximo nó
    }
    return found; // 0 significa que nenhum foi encontrado
}

// ---------- percursos ----------
void OrderHistoryList::traverseForward() const { // imprime do início ao fim
    if (isEmpty()) { // lista vazia?
        cout << "Historico vazio." << endl; // avisa em vez de não mostrar nada
        return; // sai do método
    }
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // até passar do último
        curr->data.display(); // imprime o pedido do nó
        curr = curr->next; // segue para frente
    }
}

void OrderHistoryList::traverseBackward() const { // imprime do fim ao início (só é possível porque a lista é dupla)
    if (isEmpty()) { // lista vazia?
        cout << "Historico vazio." << endl; // avisa
        return; // sai do método
    }
    ListNode* curr = tail; // começa no ÚLTIMO nó
    while (curr != nullptr) { // até passar do primeiro
        curr->data.display(); // imprime o pedido do nó
        curr = curr->prev; // segue para trás
    }
}

// ---------- navegação com cursor (RF08) ----------
Order* OrderHistoryList::goToHead() { // coloca o cursor no primeiro nó
    current = head; // o cursor vai para o início
    return (current != nullptr) ? &current->data : nullptr; // se a lista tem nós, devolve o pedido; se está vazia, devolve nullptr (evita acessar ->data de nullptr)
}

Order* OrderHistoryList::goToNext() { // avança o cursor um nó
    if (current == nullptr || current->next == nullptr) { // cursor sem posição, ou já no último nó?
        return nullptr; // não há para onde ir; o cursor NÃO se move. A ordem do || importa: se current for nullptr, para ali e não lê current->next
    }
    current = current->next; // avança o cursor
    return &current->data; // devolve o pedido do novo nó
}

Order* OrderHistoryList::goToPrevious() { // recua o cursor um nó: espelho do goToNext
    if (current == nullptr || current->prev == nullptr) { // cursor sem posição, ou já no primeiro nó?
        return nullptr; // não há para onde ir; o cursor NÃO se move
    }
    current = current->prev; // recua o cursor
    return &current->data; // devolve o pedido do novo nó
}

// ---------- relatório do dia (RF11) ----------
void OrderHistoryList::dailyReport() const { // imprime todos os pedidos, a quantidade e o total vendido
    if (isEmpty()) { // lista vazia?
        cout << "Nenhum pedido no historico." << endl; // avisa
        return; // sai do método
    }
    float totalSold = 0.0f; // acumulador do total vendido (começa em zero, senão teria valor lixo)
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // percorre do início ao fim
        curr->data.display(); // imprime o pedido
        totalSold += curr->data.getTotal(); // soma o total do pedido ao acumulador
        curr = curr->next; // vai para o próximo nó
    }
    cout << "Quantidade de pedidos: " << size << endl; // size já é a quantidade de nós, não precisa contar de novo
    cout << "Total vendido: R$ " << totalSold << endl; // imprime a soma
}