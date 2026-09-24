# New Cross Burger — Estruturas Encadeadas

Trabalho 01 de **Estrutura de Dados Lineares** (EDL – TADS4M), IFRN Campus Nova Cruz.

O sistema controla os pedidos de uma hamburgueria usando três estruturas de dados
**implementadas à mão** (é proibido usar `vector`, `list`, `stack`, `queue` etc. nas
estruturas centrais):

| Tópico |            Estrutura           |                Para que serve                 | Situação |
|--------|---------------=----------------|-----------------------------------------------|----------|
|  3.1   |    Lista duplamente encadeada  |          Histórico de pedidos do dia          |  Pronto  |
|  3.2   |     Fila encadeada simples     |       Fila de preparo da cozinha (FIFO)       | A fazer  |
|   3.3  |    Pilha encadeada simples     | Desfazer ações / pilha de retirada| A fazer   |
|    —   | Menu interativo (`main` final) | Juntar tudo, com dados digitados pelo usuário | A fazer  |

---

## 1. Como rodar no terminal (passo a passo)

Rodar um programa em C++ tem duas etapas: **compilar** (transformar o código em um
programa executável) e **executar** esse programa.

### 1.1 Pré-requisito: ter o compilador `g++`

Confira se já está instalado:

```
g++ --version
```

Se aparecer a versão, pode pular para o passo 1.2. Se der "comando não encontrado":

- **Ubuntu/Debian:** `sudo apt install g++`
- **macOS:** `xcode-select --install`
- **Windows:** instale o [MSYS2](https://www.msys2.org/) e, no terminal dele, rode
  `pacman -S mingw-w64-ucrt-x86_64-gcc`. Depois adicione a pasta `bin` do MinGW ao
  `PATH` do Windows. Outra opção é usar o **WSL** (Ubuntu dentro do Windows) e seguir
  as instruções de Linux.

### 1.2 Abrir o terminal na pasta certa

O terminal precisa estar **dentro da pasta onde estão os arquivos** `.cpp` e `.hpp`.

```
exemplo: cd caminho/para/OrderHistoryList
```

No Windows, dá para abrir a pasta no Explorer, clicar na barra de endereço, digitar
`cmd` e apertar Enter: o terminal já abre no lugar certo.

Confira se está no lugar certo listando os arquivos (`ls` no Linux/macOS, `dir` no
Windows). Deve aparecer `Order.cpp`, `OrderHistoryList.cpp`, `MainSpPraTestes.cpp` etc.

### 1.3 Compilar (tópico 3.1)

```
g++ -std=c++17 -Wall -Wextra -o history MainSoPraTestes.cpp Order.cpp OrderHistoryList.cpp
```

siga o mesmo exemplo de cima para os outros

O que cada parte significa:

| Parte | Significado |
|---|---|
| `g++` | O compilador de C++ |
| `-std=c++17` | Usa o padrão C++17 (necessário para `nullptr` em compiladores antigos) |
| `-Wall -Wextra` | Liga os avisos do compilador, que ajudam a achar erros |
| `-o history` | Nome do programa que será gerado |
| `MainSpPraTestes.cpp Order.cpp OrderHistoryList.cpp` | Os arquivos `.cpp` que formam o programa |

Se **nenhuma mensagem** aparecer, a compilação deu certo e um arquivo `history`
(`history.exe` no Windows) foi criado.

> Os arquivos `.hpp` **não** entram no comando. Eles são puxados automaticamente
> pelos `#include` dentro dos `.cpp`.

### 1.4 Executar

- **Linux / macOS:** `./history`
- **Windows (cmd):** `history.exe`
- **Windows (PowerShell):** `.\history.exe`

### 1.5 Saída esperada (tópico 3.1)

```
--- Para frente ---
Pedido #3 | Cliente: Carla | Itens: Batata Frita | Total: R$ 15
Pedido #1 | Cliente: Ana | Itens: X-Burger, Refrigerante | Total: R$ 31
Pedido #4 | Cliente: Ana | Itens: X-Salada | Total: R$ 22
Pedido #2 | Cliente: Bruno | Itens: X-Bacon | Total: R$ 30

--- Para tras ---
Pedido #2 | Cliente: Bruno | Itens: X-Bacon | Total: R$ 30
Pedido #4 | Cliente: Ana | Itens: X-Salada | Total: R$ 22
Pedido #1 | Cliente: Ana | Itens: X-Burger, Refrigerante | Total: R$ 31
Pedido #3 | Cliente: Carla | Itens: Batata Frita | Total: R$ 15

--- Busca por numero (2) ---
Pedido #2 | Cliente: Bruno | Itens: X-Bacon | Total: R$ 30

--- Anterior e proximo a partir do #2 ---
Pedido #4 | Cliente: Ana | Itens: X-Salada | Total: R$ 22
Pedido #2 | Cliente: Bruno | Itens: X-Bacon | Total: R$ 30
Ja esta no ultimo pedido, nao ha proximo.

--- Busca por cliente (Ana) ---
Pedido #1 | Cliente: Ana | Itens: X-Burger, Refrigerante | Total: R$ 31
Pedido #4 | Cliente: Ana | Itens: X-Salada | Total: R$ 22
2 pedido(s) encontrado(s).

--- Remocao do #4 (meio da lista) ---
Removido.
Pedido 99 nao existe.

--- Relatorio do dia ---
Pedido #3 | Cliente: Carla | Itens: Batata Frita | Total: R$ 15
Pedido #1 | Cliente: Ana | Itens: X-Burger, Refrigerante | Total: R$ 31
Pedido #2 | Cliente: Bruno | Itens: X-Bacon | Total: R$ 30
Quantidade de pedidos: 3
Total vendido: R$ 76
```

Se a sua saída for igual a essa, o tópico 3.1 está funcionando.

### 1.6 Erros comuns

| Mensagem | Causa provável | Solução |
|---|---|---|
| `g++: command not found` / "não é reconhecido" | Compilador não instalado ou fora do `PATH` | Ver o passo 1.1 |
| `No such file or directory` | O terminal está na pasta errada | Ver o passo 1.2 |
| `undefined reference to 'Order::...'` | Esqueceu algum `.cpp` no comando | Incluir **todos** os `.cpp` do tópico |
| `multiple definition of 'main'` | Há dois arquivos com `main` no mesmo comando | Compilar **só um** arquivo de teste por vez (ver seção 3) |
| `fatal error: Order.hpp: No such file` | Arquivos em pastas diferentes | Deixar `.cpp` e `.hpp` na **mesma pasta** |
| `'nullptr' was not declared` | Compilador antigo, sem C++11 | Usar `-std=c++17` no comando |
| `Permission denied` ao executar | Programa sem permissão de execução | Linux/macOS: `chmod +x history` |

> **Importante:** toda vez que alterar qualquer `.cpp` ou `.hpp`, é preciso
> **compilar de novo** antes de executar. O programa antigo não se atualiza sozinho.

---

## 2. Como o código está organizado

```
order_history/
├── Order.hpp / Order.cpp                  -> classe Order (o pedido)
├── ListNode.hpp                           -> classe ListNode (o nó da lista)
├── OrderHistoryList.hpp / .cpp            -> classe OrderHistoryList (a lista)
├── MainSpPraTestes.cpp                    -> main de teste do tópico 3.1
└── README.md
```

### 2.1 Convenções do projeto

- **`.hpp`** guarda a **declaração** da classe (quais atributos e métodos existem).
  **`.cpp`** guarda a **implementação** (o código dos métodos).
- Todo `.hpp` tem *include guard* (`#ifndef` / `#define` / `#endif`), para não ser
  incluído duas vezes e causar erro de "classe definida duas vezes".
- Em `.hpp` **não** se usa `using namespace std;`, e sim `std::string`, `std::` etc.
- **Nomes de classes, atributos, métodos e variáveis em inglês.** Mensagens
  impressas no console e dados de teste ficam em português.
- Atributos são `private`. O acesso de fora é feito por métodos (getters).
- Valores em dinheiro usam `float`, impressos do jeito padrão do `cout`
  (por exemplo, `25.5` e não `25.50`).

### 2.2 Classe `Order` (o pedido)

Guarda os dados de um pedido.

| Atributo | Tipo | O que guarda |
|---|---|---|
| `number` | `int` | Número do pedido (identificador) |
| `customer` | `std::string` | Nome do cliente |
| `items[MAX_ITEMS]` | array de `std::string` | Nomes dos itens (`MAX_ITEMS = 20`) |
| `itemCount` | `int` | Quantos itens já foram adicionados |
| `total` | `float` | Valor total do pedido |

| Método | O que faz |
|---|---|
| `Order()` | Cria um pedido vazio |
| `Order(number, customer)` | Cria um pedido com número e cliente, sem itens e com total 0 |
| `addItem(name, price)` | Adiciona um item e soma o preço ao total. Retorna `false` se o pedido já está com 20 itens |
| `display()` | Imprime o pedido em uma linha |
| `getNumber()`, `getCustomer()`, `getTotal()` | Leitura dos atributos privados |

### 2.3 Classe `ListNode` (o nó)

É uma "caixinha" da lista. Guarda um `Order` e dois ponteiros:

| Atributo | O que guarda |
|---|---|
| `data` | O pedido (uma cópia) |
| `prev` | Ponteiro para o nó **anterior** (`nullptr` no primeiro nó) |
| `next` | Ponteiro para o nó **seguinte** (`nullptr` no último nó) |

Os atributos são `public` de propósito: o nó é só uma peça interna da lista, e a
lista mexe direto nos ponteiros.

```
nullptr <- [prev|Pedido 3|next] <-> [prev|Pedido 1|next] <-> [prev|Pedido 2|next] -> nullptr
             ^                                                                    ^
            head                                                                tail
```

### 2.4 Classe `OrderHistoryList` (lista duplamente encadeada, tópico 3.1)

Atributos privados: `head` (primeiro nó), `tail` (último nó), `current` (cursor de
navegação) e `size` (quantidade de nós).

| Método | O que faz | Requisito |
|---|---|---|
| `insertAtHead(order)` | Insere no início | Op. mínima 3.1 |
| `insertAtTail(order)` | Insere no fim | RF04 |
| `insertAtPosition(order, pos)` | Insere na posição `pos` (começa em 0). Retorna `false` se a posição é inválida | Op. mínima 3.1 |
| `removeByNumber(number)` | Remove o pedido com esse número, em qualquer posição. Retorna `false` se não existe | RF10 |
| `findByNumber(number)` | Devolve o pedido (ou `nullptr`) e move o cursor até ele | RF09 |
| `findByCustomer(customer)` | Imprime todos os pedidos do cliente e retorna quantos achou | RF09 |
| `traverseForward()` | Imprime do início ao fim | Op. mínima 3.1 |
| `traverseBackward()` | Imprime do fim ao início | Op. mínima 3.1 |
| `goToHead()`, `goToNext()`, `goToPrevious()` | Movem o cursor e devolvem o pedido (ou `nullptr` se não há para onde ir) | RF08 |
| `dailyReport()` | Imprime todos os pedidos, a quantidade e o total vendido | RF11 |
| `isEmpty()`, `getSize()` | Lista vazia? / quantos pedidos | Auxiliares |

**Casos extremos já tratados:** lista vazia (mensagem em vez de erro), busca sem
resultado (`nullptr` ou contagem 0), remoção de pedido inexistente (`false`),
posição de inserção inválida (`false`), pedido cheio de itens (`false`), cursor
sem próximo/anterior (`nullptr`).

O destrutor da lista libera todos os nós com `delete`, então não há vazamento de memória.

---

## 3. Sobre os arquivos `MainSpPraTestes`

O `main` final do trabalho será um **menu interativo**, com dados digitados pelo
usuário. Enquanto ele não existe, cada tópico tem um arquivo de teste com o `main`
fixo, que cria pedidos de exemplo e chama os métodos da estrutura para mostrar que
ela funciona.

Regras para não dar erro de compilação:

1. **Só pode haver um `main` por programa.** Ao compilar, use **um** arquivo de
   teste por vez. Se colocar dois no mesmo comando, aparece `multiple definition of 'main'`.
2. O arquivo de teste inclui apenas os `.hpp` de que precisa.
3. Cada tópico deve ter pelo menos um arquivo de teste, e o comando de compilação
   do tópico deve ser registrado na tabela abaixo.

| Tópico | Arquivo de teste | Comando de compilação |
|---|---|---|
| 3.1 Lista | `MainSpPraTestes.cpp` | `g++ -std=c++17 -Wall -Wextra -o history MainSpPraTestes.cpp Order.cpp OrderHistoryList.cpp` |
| 3.2 Fila | *(a definir)* | *(a definir)* |
| 3.3 Pilha | *(a definir)* | *(a definir)* |

---

## 4. Como criar o próximo tópico (padrão a seguir)

Para manter tudo igual, cada estrutura nova segue o mesmo molde do 3.1:

1. Criar o nó (por exemplo `QueueNode.hpp`) com o dado e os ponteiros necessários.
   Fila e pilha são **simplesmente** encadeadas, então só têm o ponteiro `next`.
2. Criar a classe da estrutura em `.hpp` (declaração) e `.cpp` (implementação),
   com include guard e `std::` no `.hpp`.
3. Implementar as operações mínimas do enunciado (fila: enfileirar, desenfileirar,
   vazia?, peek; pilha: empilhar, desempilhar, vazia?, peek).
4. Tratar os casos extremos: estrutura vazia, busca sem resultado, remoção de nó inexistente.
5. Escrever um arquivo de teste com `main` e registrar o comando na tabela da seção 3.
6. Compilar com `-Wall -Wextra` e corrigir **todos** os avisos.
7. Destruidor liberando os nós com `delete`.

A classe `Order` é reaproveitada por todas as estruturas: não precisa ser reescrita.

---

## 5. Requisitos do trabalho (resumo)

- **RF01** Cadastrar pedido (cliente, itens, valor total)
- **RF02** Adicionar/remover item de um pedido em construção, registrando na pilha de desfazer
- **RF03** Desfazer a última ação do pedido em construção
- **RF04** Fechar o pedido: inserir na fila de preparo e no fim do histórico
- **RF05** Chamar a cozinha: desenfileirar o próximo pedido
- **RF06** Marcar pedido como pronto: empilhar na pilha de retirada
- **RF07** Retirar pedido pronto: desempilhar o topo
- **RF08** Consultar histórico para frente e para trás
- **RF09** Buscar pedido no histórico por número/cliente
- **RF10** Cancelar/remover pedido do histórico (remoção no meio da lista)
- **RF11** Relatório do dia (percorrer do início ao fim, total vendido, quantidade)

Requisitos não funcionais: nós implementados manualmente, tratamento de casos
extremos, menu textual interativo e linguagem C++.

## 6 Como o main funciona agora (versão de teste)

O arquivo `MainSpPraTestes.cpp` **não é o programa final**. É um teste automático do
tópico 3.1: ele não pergunta nada ao usuário, roda uma vez de cima para baixo e termina.
Serve para provar que a lista duplamente encadeada funciona antes de construirmos o menu.

### O que ele faz, na ordem

1. **Cria a lista** de histórico (`OrderHistoryList history;`), vazia.
2. **Cria 4 pedidos fixos no código** (não são digitados):

   | Pedido | Cliente | Itens | Total |
   |---|---|---|---|
   | 1 | Ana | X-Burger, Refrigerante | 31 |
   | 2 | Bruno | X-Bacon | 30 |
   | 3 | Carla | Batata Frita | 15 |
   | 4 | Ana | X-Salada | 22 |

3. **Insere os pedidos**, testando os três tipos de inserção:

   | Ação | Estado da lista |
   |---|---|
   | `insertAtTail(o1)` | `[1]` |
   | `insertAtTail(o2)` | `[1, 2]` |
   | `insertAtHead(o3)` | `[3, 1, 2]` |
   | `insertAtPosition(o4, 2)` | `[3, 1, 4, 2]` |

4. **Percorre** a lista para frente (3, 1, 4, 2) e para trás (2, 4, 1, 3).
5. **Busca por número** (pedido 2). Isso também posiciona o cursor nesse pedido.
6. **Navega com o cursor**: vai para o anterior (4), volta para o próximo (2) e tenta
   avançar mais uma vez, o que falha porque o 2 é o último (caso extremo).
7. **Busca por cliente** ("Ana"): acha 2 pedidos (1 e 4).
8. **Remove** o pedido 4 (no meio da lista) e tenta remover o pedido 99, que não existe
   (caso extremo).
9. **Imprime o relatório do dia**: sobram 3 pedidos e o total vendido é 76 (15 + 31 + 30).
   O pedido 4 não entra na conta, o que confirma que a remoção funcionou.

### Como saber se está tudo certo

Compare a saída do seu terminal com a da seção "Saída esperada". Se for igual, o tópico 3.1
está funcionando.

### Limitações da versão de teste

- Os dados são fixos: para testar outro cenário é preciso editar o código e compilar de novo.
- Nas linhas de navegação, o teste chama `goToPrevious()->display()` sem conferir se o
  retorno é `nullptr`. Isso só é seguro porque sabemos que existe pedido anterior naquele
  ponto. **No menu final, o retorno deve sempre ser conferido antes de usar.**
- Ainda não cobre: `goToHead()`, `isEmpty()`, `getSize()`, inserção em posição inválida
  e métodos chamados com a lista vazia.

---

## O que vamos fazer (próximos passos)

### Roteiro

- [x] **3.1** Lista duplamente encadeada (`Order`, `ListNode`, `OrderHistoryList`) e teste
- [ ] Completar o teste do 3.1 com os casos extremos que faltam (lista vazia, posição
      inválida, `goToHead`)
- [ ] **3.2** Fila encadeada simples (preparo da cozinha): enfileirar, desenfileirar,
      verificar se está vazia, consultar o primeiro (`peek`) + arquivo de teste próprio
- [ ] **3.3** Pilha encadeada simples: empilhar, desempilhar, verificar se está vazia,
      consultar o topo (`peek`) + arquivo de teste próprio. O grupo precisa decidir se
      faz a pilha de desfazer, a de retirada ou as duas
- [ ] Expandir a classe `Order` para permitir **remover item** (RF02), o que exige guardar
      o preço de cada item, e não só o total
- [ ] **Main final com menu interativo**, unindo as três estruturas

### Como o main final será diferente

| | Main de teste (agora) | Main final (objetivo) |
|---|---|---|
| Dados | Fixos no código | Digitados pelo usuário |
| Execução | Uma vez, de cima para baixo | Repete o menu até o usuário escolher "Sair" |
| Estruturas | Só a lista (3.1) | Lista, fila e pilha juntas |
| Objetivo | Provar que a estrutura funciona | Cumprir os requisitos RF01 a RF11 |

Os arquivos `MainSpPraTestes` continuam existindo depois disso: servem para testar cada
estrutura isolada, sem passar pelo menu.

### Proposta de menu (a confirmar com o grupo)

| Opção | Requisito | O que usa |
|---|---|---|
| Novo pedido | RF01 | `Order` |
| Adicionar / remover item | RF02 | `Order` + pilha de desfazer |
| Desfazer última ação | RF03 | Pilha de desfazer |
| Fechar pedido | RF04 | Fila de preparo + `insertAtTail` do histórico |
| Chamar cozinha | RF05 | Desenfileirar |
| Marcar pedido como pronto | RF06 | Pilha de retirada (empilhar) |
| Retirar pedido pronto | RF07 | Pilha de retirada (desempilhar) |
| Consultar histórico (próximo/anterior) | RF08 | `goToNext`, `goToPrevious` |
| Buscar pedido | RF09 | `findByNumber`, `findByCustomer` |
| Cancelar pedido do histórico | RF10 | `removeByNumber` |
| Relatório do dia | RF11 | `dailyReport` |
| Sair | — | — |

### Cuidados para o menu

- **Sempre conferir** se um método retornou `nullptr` ou `false` antes de usar o resultado.
- **Entrada de texto:** misturar `cin >>` com `getline` causa um erro clássico, em que o
  `getline` lê uma linha vazia. Depois de um `cin >>`, é preciso limpar o resto da linha
  (`cin.ignore()`).
- **Validar a opção do menu:** o usuário pode digitar letras ou números fora da lista.
- Fechar um pedido (RF04) coloca o mesmo pedido na fila e no histórico. Como cada nó guarda
  uma **cópia**, as duas estruturas ficam independentes.