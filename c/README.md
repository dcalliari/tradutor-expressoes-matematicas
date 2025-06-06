# Tradutor de Expressões Matemáticas (C)

Este projeto implementa um tradutor que converte expressões matemáticas do formato **infixado** para o formato **pós-fixado** (notação polonesa reversa) utilizando a linguagem C.

## 📋 Funcionalidades

- Lê arquivo de texto com expressões matemáticas infixas.
- Converte cada expressão para notação pós-fixa.
- Gera arquivo de saída com as expressões convertidas.
- Suporta operadores: `+`, `-`, `*`, `/`, `^` e parênteses `()`.
- Trata precedência de operadores corretamente.
- Informa erros de parênteses desbalanceados e problemas na pilha (cheia/vazia).

## 🚀 Como usar

### Pré-requisitos

- Compilador C (GCC, Clang, MinGW para Windows, etc.)
- VS Code (recomendado) ou outro editor de texto.

### Compilação

Navegue até o diretório `c` e compile o código. Exemplo usando GCC:

```bash
gcc tradutor.c -o tradutor_c -Wall
```

No Windows (com MinGW, por exemplo):

```bash
gcc tradutor.c -o tradutor_c.exe -Wall
```

O `-Wall` ativa avisos comuns do compilador, o que é uma boa prática.

### Execução via linha de comando

Após a compilação, execute o programa fornecendo os nomes dos arquivos de entrada e saída:

```bash
./tradutor_c ../testes/entrada.txt ../testes/saida_c.txt 
```

No Windows, o executável pode ser chamado diretamente:

```bash
tradutor_c.exe ..\testes\entrada.txt ..\testes\saida_c.txt
```

(Assumindo que os arquivos de teste estão em um diretório `testes` no nível acima do diretório `c`)

### Execução interativa

Execute o programa sem argumentos para que ele solicite os nomes dos arquivos:

```bash
./tradutor_c
```

Ou no Windows:

```bash
tradutor_c.exe
```

O programa solicitará os nomes dos arquivos de entrada e saída.

## 📁 Estrutura do Projeto (sugerida)

```
tradutor-expressoes-matematicas/
├── c/
│   ├── tradutor.c
│   └── README.md (este arquivo)
├── cpp/
│   ├── tradutor.cpp
│   ├── tradutor_cpp.exe
│   └── README.md
├── python/
│   ├── tradutor.py
│   └── README.md
├── testes/
│   ├── entrada.txt
│   └── saida.txt
└── requirements.txt (para a versão Python)
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
a+b)
```

### Arquivo de saída gerado (`testes/saida_c.txt` após execução com C):

```
abc*+
ab+c*
abc*+d-
ab^cd*+
ab+cd-*
```
(Nota: As linhas `((a+b)` e `a+b)` causarão um erro e não serão traduzidas ou resultarão em saída vazia/incorreta, com uma mensagem de erro impressa no console.)

## 🧮 Como funciona

O programa utiliza o **Algoritmo Shunting Yard** para converter expressões infixas em pós-fixas, implementado em C:

1.  **Pilha**: Uma pilha simples é implementada para armazenar operadores e parênteses.
2.  **Precedência de Operadores**:
    *   `^` (potenciação): precedência 3
    *   `*`, `/`: precedência 2
    *   `+`, `-`: precedência 1
    *   `()`: precedência 0 (usado para controle de fluxo)

3.  **Processo de Conversão**:
    *   Operandos (letras ou números) são adicionados diretamente à string de saída pós-fixa.
    *   Operadores são gerenciados usando a pilha, respeitando suas precedências.
    *   Parênteses `(` são empilhados.
    *   Parênteses `)` fazem com que operadores sejam desempilhados da pilha para a saída até que um `(` seja encontrado.
    *   Ao final da expressão, quaisquer operadores restantes na pilha são movidos para a saída.
    *   A função de conversão retorna um status de sucesso ou falha, e mensagens de erro são impressas em `stderr`.

## 🎯 Algoritmo (Detalhado em C)

A função `infixaParaPosfixa` processa cada caractere da expressão infixa:

1.  Ignora espaços em branco.
2.  Se o caractere é um operando (letra ou número, verificado por `isalnum`), adiciona-o à string de saída `posfixa`.
3.  Se o caractere é um parêntese de abertura `(`, empilha-o usando a `Stack`.
4.  Se o caractere é um parêntese de fechamento `)`:
    *   Desempilha operadores da `Stack` e adiciona-os à `posfixa` até que um `(` seja encontrado no topo da `Stack`.
    *   Remove o `(` da `Stack`.
    *   Se a `Stack` ficar vazia antes de encontrar um `(`, ou se não houver `(` no topo, reporta um erro de parênteses desbalanceados e a função retorna falha.
5.  Se o caractere é um operador:
    *   Enquanto a `Stack` não estiver vazia, o topo da `Stack` não for `(`, e o operador no topo da `Stack` tiver precedência maior ou igual à do caractere atual, desempilha o operador do topo e adiciona-o à `posfixa`.
    *   Empilha o caractere (operador atual).
6.  Após processar todos os caracteres da expressão infixa, desempilha quaisquer operadores restantes na `Stack` e adiciona-os à `posfixa`. Se um `(` for encontrado na `Stack` neste estágio, reporta um erro de parênteses desbalanceados e a função retorna falha.
7.  Termina a string `posfixa` com um caractere nulo `\0`.

## 🛠️ Desenvolvimento

Para contribuir com o projeto:

1.  Clone o repositório.
2.  Navegue até o diretório `c`.
3.  Faça suas modificações no arquivo `tradutor.c`.
4.  Compile (e.g., `gcc tradutor.c -o tradutor_c -Wall`) e teste com diferentes expressões, incluindo casos de erro.
5.  Envie um pull request com suas melhorias.

## 📝 Licença

Este projeto foi desenvolvido como um exemplo e pode ser usado livremente.
