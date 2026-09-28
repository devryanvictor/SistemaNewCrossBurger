#include "HistoricoPedidos.hpp" // traz a declaração da classe (e, junto, Order e ListNode)

ListaHistoricoPedidos::ListaHistoricoPedidos() : head(nullptr), tail(nullptr), current(nullptr), tamanho(0) {} // construtor: a lista nasce vazia (sem nós, sem cursor, tamanho 0)

ListaHistoricoPedidos::~ListaHistoricoPedidos() { // destrutor: roda sozinho quando a lista é destruída e libera todos os nós
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // repete até passar do último nó
        ListNode* proxNode = curr->prox; // guarda o próximo ANTES de apagar (depois do delete não dá mais para ler curr->next)
        delete curr; // libera a memória do nó atual
        curr = proxNode; // avança usando o endereço guardado
    }
}

ListNode* ListaHistoricoPedidos::encontrarNode(int numero) const { // método privado: devolve o NÓ que tem esse número (ou nullptr). const = não altera a lista
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // repete enquanto não passou do último
        if (curr->dados.getNumero() == numero) { // curr->data é o pedido do nó, e .getNumber() lê o número dele. Se for o procurado, devolve o nó.
            return curr;
        }
        curr = curr->prox; // senão, vai para o próximo.
    }
    return nullptr; // se saiu do laço, percorreu tudo e não achou, então devolve nullptr. Com lista vazia, head é nullptr, o laço nem começa e devolve nullptr direto.
}

// ---------- inserções ----------
void ListaHistoricoPedidos::inserirHead(const Pedido& pedido) { // insere no início. Recebe o pedido por referência constante (não copia na chamada)
    ListNode* newNode = new ListNode(pedido); // cria o nó, com uma cópia do pedido, e prev e next já em nullptr.
    if (isVazia()) { // se a lista estava vazia, o nó novo é ao mesmo tempo o primeiro e o último.
        head = newNode; // o novo é o primeiro
        tail = newNode; // e também o último
    } else { // se já havia nós, são três passos, nesta ordem:
        newNode->prox = head; // 1) o novo aponta para o antigo primeiro
        head->ant = newNode; // 2) o antigo primeiro aponta de volta para o novo (é isso que faz a lista ser dupla)
        head = newNode; // 3) o novo passa a ser o primeiro (tem que ser por último, senão perde o acesso ao antigo head)
    }
    tamanho++; // um nó a mais na lista (o tail não muda, o último continua o mesmo)
}

void ListaHistoricoPedidos::inserirTail(const Pedido& pedido) { // insere no fim: espelho do insertAtHead
    ListNode* newNode = new ListNode(pedido); // cria o nó com uma cópia do pedido
    if (isVazia()) { // lista vazia: o novo é o primeiro e o último
        head = newNode; // o novo é o primeiro
        tail = newNode; // e também o último
    } else { // já havia nós: três passos, nesta ordem
        newNode->ant = tail; // 1) o novo aponta para trás, para o antigo último
        tail->prox = newNode; // 2) o antigo último aponta para frente, para o novo
        tail = newNode; // 3) o novo passa a ser o último. Não percorre nada: o tail já aponta para o fim, então é O(1)
    }
    tamanho++; // um nó a mais
}

bool ListaHistoricoPedidos::inserirPosicao(const Pedido& Pedido, int pos) { // insere na posição pos (começa em 0). Devolve false se a posição for inválida
    if (pos < 0 || pos > tamanho) { // posição negativa ou maior que o tamanho é inválida (pos == size é válida: significa "no fim")
        return false; // avisa quem chamou que não inseriu
    }
    if (pos == 0) { // posição 0 = início
        inserirHead(Pedido); // reaproveita o método que já existe, sem repetir código
        return true; // deu certo
    }
    if (pos == tamanho) { // posição igual ao tamanho = fim
        inserirTail(Pedido); // reaproveita o insertAtTail
        return true; // deu certo
    }
    ListNode* curr = head; // daqui em diante só restam posições do MEIO (o nó da posição tem vizinho dos dois lados)
    for (int i = 0; i < pos; i++) { // anda pos passos a partir do início
        curr = curr->prox; // avança um nó
    }
    // ao sair do for, curr é o nó que hoje ocupa a posição pos; o novo entrará ANTES dele
    ListNode* newNode = new ListNode(Pedido); // cria o nó com uma cópia do pedido
    newNode->ant = curr->ant; // o novo aponta para trás, para o vizinho de trás de curr
    newNode->prox = curr; // o novo aponta para frente, para o próprio curr
    curr->ant->prox = newNode; // o vizinho de trás passa a apontar para frente, para o novo (usa curr->prev antes de ele mudar)
    curr->ant = newNode; // curr passa a apontar para trás, para o novo (tem que ser por último)
    tamanho++; // um nó a mais
    return true; // deu certo
}

// ---------- remoções ----------
bool ListaHistoricoPedidos::removerPorNumero(int numero) { // remove o pedido com esse número, esteja onde estiver. Devolve false se não existir
    ListNode* alvo = encontrarNode(numero); // localiza o nó a remover
    if (alvo == nullptr) { // não existe pedido com esse número
        return false; // caso extremo: remoção de nó inexistente, não mexe em nada
    }
    if (alvo->ant != nullptr) { // o alvo tem vizinho de trás?
        alvo->ant->prox = alvo->prox; // sim: o vizinho de trás "pula" o alvo e aponta direto para o seguinte
    } else { // não: o alvo era o primeiro
        head = alvo->prox; // então o head avança para o seguinte
    }
    if (alvo->prox != nullptr) { // o alvo tem vizinho da frente?
        alvo->prox->ant = alvo->ant; // sim: o vizinho da frente "pula" o alvo e aponta direto para o anterior
    } else { // não: o alvo era o último
        tail = alvo->ant; // então o tail recua para o anterior
    }
    if (current == alvo) { // o cursor estava justamente no nó que vai ser apagado?
        current = (alvo->prox != nullptr) ? alvo->prox : alvo->ant; // então move para o vizinho da frente; se não houver, o de trás (se era o único, vira nullptr)
    }
    delete alvo; // libera a memória do nó (só agora, depois de terminar de usar o target)
    tamanho--; // um nó a menos
    return true; // deu certo
}

// ---------- buscas ----------
Pedido* ListaHistoricoPedidos::encontrarPorNumero(int numero) { // busca por número. Devolve o endereço do pedido (ou nullptr). Não é const porque move o cursor
    ListNode* node = encontrarNode(numero); // reaproveita o findNode
    if (node == nullptr) { // não achou
        return nullptr; // busca sem resultado
    }
    current = node; // posiciona o cursor no nó achado (permite buscar e depois navegar para o anterior/próximo)
    return &node->dados; // devolve o endereço do pedido DENTRO do nó (não uma cópia). O -> é lido antes do &
}

int ListaHistoricoPedidos::encontrarPorCliente(const string& cliente) const { // busca por cliente: imprime os pedidos dele e devolve quantos achou
    int encontrado = 0; // contador de pedidos encontrados
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // percorre a lista toda (não para no primeiro, porque o cliente pode ter vários pedidos)
        if (curr->dados.getCliente() == cliente) { // o cliente do pedido é o procurado?
            curr->dados.exibir(); // imprime o pedido
            encontrado++; // conta mais um
        }
        curr = curr->prox; // vai para o próximo nó
    }
    return encontrado; // 0 significa que nenhum foi encontrado
}

// ---------- percursos ----------
void ListaHistoricoPedidos::percorreFrente() const { // imprime do início ao fim
    if (isVazia()) { // lista vazia?
        cout << "Historico vazio." << endl; // avisa em vez de não mostrar nada
        return; // sai do método
    }
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // até passar do último
        curr->dados.exibir(); // imprime o pedido do nó
        curr = curr->prox; // segue para frente
    }
}

void ListaHistoricoPedidos::percorreTras() const { // imprime do fim ao início (só é possível porque a lista é dupla)
    if (isVazia()) { // lista vazia?
        cout << "Historico vazio." << endl; // avisa
        return; // sai do método
    }
    ListNode* curr = tail; // começa no ÚLTIMO nó
    while (curr != nullptr) { // até passar do primeiro
        curr->dados.exibir(); // imprime o pedido do nó
        curr = curr->ant; // segue para trás
    }
}

// ---------- navegação com cursor (RF08) ----------
Pedido* ListaHistoricoPedidos::goToHead() { // coloca o cursor no primeiro nó
    current = head; // o cursor vai para o início
    return (current != nullptr) ? &current->dados : nullptr; // se a lista tem nós, devolve o pedido; se está vazia, devolve nullptr (evita acessar ->data de nullptr)
}

Pedido* ListaHistoricoPedidos::goToProx() { // avança o cursor um nó
    if (current == nullptr || current->prox == nullptr) { // cursor sem posição, ou já no último nó?
        return nullptr; // não há para onde ir; o cursor NÃO se move. A ordem do || importa: se current for nullptr, para ali e não lê current->next
    }
    current = current->prox; // avança o cursor
    return &current->dados; // devolve o pedido do novo nó
}

Pedido* ListaHistoricoPedidos::goToAnt() { // recua o cursor um nó: espelho do goToNext
    if (current == nullptr || current->ant == nullptr) { // cursor sem posição, ou já no primeiro nó?
        return nullptr; // não há para onde ir; o cursor NÃO se move
    }
    current = current->ant; // recua o cursor
    return &current->dados; // devolve o pedido do novo nó
}

// ---------- relatório do dia (RF11) ----------
void ListaHistoricoPedidos::reportDiario() const { // imprime todos os pedidos, a quantidade e o total vendido
    if (isVazia()) { // lista vazia?
        cout << "Nenhum pedido no historico." << endl; // avisa
        return; // sai do método
    }
    float totalVendido = 0.0f; // acumulador do total vendido (começa em zero, senão teria valor lixo)
    ListNode* curr = head; // começa no primeiro nó
    while (curr != nullptr) { // percorre do início ao fim
        curr->dados.exibir(); // imprime o pedido
        totalVendido += curr->dados.getTotal(); // soma o total do pedido ao acumulador
        curr = curr->prox; // vai para o próximo nó
    }
    cout << "Quantidade de pedidos: " << tamanho << endl; // size já é a quantidade de nós, não precisa contar de novo
    cout << "Total vendido: R$ " << totalVendido << endl; // imprime a soma
}