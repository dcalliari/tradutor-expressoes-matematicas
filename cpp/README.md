# Tradutor de Expressões Matemáticas (C++)

Este projeto implementa um tradutor que converte expressões matemáticas do formato **infixado** para o formato **pós-fixado** (notação polonesa reversa) utilizando C++.

## 📋 Funcionalidades

- Lê arquivo de texto com expressões matemáticas infixas.
- Converte cada expressão para notação pós-fixa.
- Gera arquivo de saída com as expressões convertidas.
- Suporta operadores: `+`, `-`, `*`, `/`, `^` e parênteses `()`.
- Trata precedência de operadores corretamente.
- Informa erros de parênteses desbalanceados.

## 🚀 Como usar

### Pré-requisitos

- Compilador C++ (g++, Clang, MSVC, etc.)
- VS Code (recomendado) ou outro editor de texto/IDE.

### Compilação

Navegue até o diretório `cpp` e compile o código. Exemplo usando g++:

```bash
g++ tradutor.cpp -o tradutor_cpp -std=c++11
```

### Execução via linha de comando

Após a compilação, execute o programa fornecendo os nomes dos arquivos de entrada e saída:

```bash
./tradutor_cpp arquivo_entrada.txt arquivo_saida.txt
```

No Windows, o executável pode ser chamado diretamente:

```bash
tradutor_cpp.exe arquivo_entrada.txt arquivo_saida.txt
```

### Execução interativa

Execute o programa sem argumentos para que ele solicite os nomes dos arquivos:

```bash
./tradutor_cpp
```

Ou no Windows:

```bash
tradutor_cpp.exe
```

O programa solicitará os nomes dos arquivos de entrada e saída.

## 📁 Estrutura do Projeto (sugerida)

```
tradutor-expressoes-matematicas/
├── cpp/
│   ├── tradutor.cpp
│   └── README.md (este arquivo)
├── python/
│   ├── tradutor.py
│   └── README.md
├── testes/
│   ├── entrada.txt
│   └── saida.txt
```

## 🔧 Exemplo de Uso

### Arquivo de entrada (`testes/entrada.txt`):

```
a+b*c
(a+b)*c
a+b*c-d
a^b+c*d
(a+b)*(c-d)
((a+b)
```

### Arquivo de saída gerado (`testes/saida.txt` após execução com C++):

```
abc*+
ab+c*
abc*+d-
ab^cd*+
ab+cd-*
```
(Nota: A linha `((a+b)` causará um erro e não será traduzida, com uma mensagem impressa no console.)

## 🧮 Como funciona

O programa utiliza o **Algoritmo Shunting Yard** para converter expressões infixas em pós-fixas:

1.  **Precedência de Operadores**:
    *   `^` (potenciação): precedência 3
    *   `*`, `/`: precedência 2
    *   `+`, `-`: precedência 1
    *   `()`: precedência 0 (usado para controle de fluxo)

2.  **Processo de Conversão**:
    *   Operandos (letras ou números) são adicionados diretamente à string de saída pós-fixa.
    *   Operadores são gerenciados usando uma pilha, respeitando suas precedências.
    *   Parênteses `(` são empilhados.
    *   Parênteses `)` fazem com que operadores sejam desempilhados da pilha para a saída até que um `(` seja encontrado.
    *   Ao final da expressão, quaisquer operadores restantes na pilha são movidos para a saída.

## 🎯 Algoritmo (Detalhado)

O algoritmo processa cada token (caractere) da expressão infixa:

1.  Se o token é um operando (letra ou número), adiciona-o à string de saída pós-fixa.
2.  Se o token é um parêntese de abertura `(`, empilha-o.
3.  Se o token é um parêntese de fechamento `)`, desempilha operadores da pilha e adiciona-os à saída até que um parêntese de abertura `(` seja encontrado no topo da pilha. Remove o `(` da pilha. Se a pilha ficar vazia antes de encontrar um `(`, há um erro de parênteses desbalanceados.
4.  Se o token é um operador:
    *   Enquanto a pilha não estiver vazia, o topo da pilha não for `(`, e o operador no topo da pilha tiver precedência maior ou igual à do token atual, desempilha o operador do topo e adiciona-o à saída.
    *   Empilha o token (operador atual).
5.  Após processar todos os tokens da expressão infixa, desempilha quaisquer operadores restantes na pilha e adiciona-os à saída. Se um `(` for encontrado na pilha neste estágio, há um erro de parênteses desbalanceados.

## 🛠️ Desenvolvimento

Para contribuir com o projeto:

1.  Clone o repositório.
2.  Navegue até o diretório `cpp`.
3.  Faça suas modificações no arquivo `tradutor.cpp`.
4.  Compile e teste com diferentes expressões, incluindo casos de erro.
5.  Envie um pull request com suas melhorias.

## 📝 Licença

Este projeto foi desenvolvido como um exemplo e pode ser usado livremente.
