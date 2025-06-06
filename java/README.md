# Tradutor de Expressões Matemáticas (Java)

Este projeto implementa um tradutor que converte expressões matemáticas do formato **infixado** para o formato **pós-fixado** (notação polonesa reversa) utilizando Java.

## 📋 Funcionalidades

- Lê arquivo de texto com expressões matemáticas infixas.
- Converte cada expressão para notação pós-fixa.
- Gera arquivo de saída com as expressões convertidas.
- Suporta operadores: `+`, `-`, `*`, `/`, `^` e parênteses `()`.
- Trata precedência de operadores corretamente.
- Informa erros de parênteses desbalanceados através de exceções.

## 🚀 Como usar

### Pré-requisitos

- JDK (Java Development Kit) 8 ou superior.
- VS Code (recomendado, com o "Extension Pack for Java") ou outra IDE Java.

### Compilação

Navegue até o diretório `java` (onde o arquivo `Tradutor.java` está localizado) e compile o código:

```bash
javac Tradutor.java
```

Isso irá gerar o arquivo `Tradutor.class`.

### Execução via linha de comando

Após a compilação, execute o programa a partir do diretório que contém o diretório `java` (ou seja, o diretório raiz do projeto `tradutor-expressoes-matematicas`), ou certifique-se de que o classpath está configurado corretamente. Forneça os nomes dos arquivos de entrada e saída como argumentos.

Se você está no diretório `tradutor-expressoes-matematicas`:

```powershell
java -cp ./java Tradutor ./testes/entrada.txt ./testes/saida_java.txt
```

Ou, se você navegou para dentro do diretório `java`:

```powershell
java Tradutor ../testes/entrada.txt ../testes/saida_java.txt
```

### Execução interativa

Execute o programa sem argumentos para que ele solicite os nomes dos arquivos:

Se você está no diretório `tradutor-expressoes-matematicas`:

```powershell
java -cp ./java Tradutor
```

Ou, se você navegou para dentro do diretório `java`:

```powershell
java Tradutor
```

O programa solicitará os nomes dos arquivos de entrada e saída no console.

## 📁 Estrutura do Projeto (sugerida)

```
tradutor-expressoes-matematicas/
├── c/
│   ├── tradutor.c
│   ├── tradutor_c.exe
│   └── README.md
├── cpp/
│   ├── tradutor.cpp
│   ├── tradutor_cpp.exe
│   └── README.md
├── java/
│   ├── Tradutor.java
│   ├── Tradutor.class  (gerado após compilação)
│   └── README.md (este arquivo)
├── python/
│   ├── tradutor.py
│   └── README.md
├── testes/
│   ├── entrada.txt
│   ├── saida.txt
│   ├── saida_c.txt
│   └── saida_java.txt (será gerado)
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

### Arquivo de saída gerado (`testes/saida_java.txt` após execução com Java):

```
abc*+
ab+c*
abc*+d-
ab^cd*+
ab+cd-*
```
(Nota: As linhas `((a+b)` e `a+b)` causarão um erro `IllegalArgumentException` e não serão traduzidas, com uma mensagem de erro impressa no console.)

## 🧮 Como funciona

O programa utiliza o **Algoritmo Shunting Yard** para converter expressões infixas em pós-fixas:

1.  **Precedência de Operadores**: Definida no método `obterPrecedencia`.
    *   `^` (potenciação): precedência 3
    *   `*`, `/`: precedência 2
    *   `+`, `-`: precedência 1
    *   `()`: precedência 0 (implicitamente, para controle)

2.  **Processo de Conversão** (método `infixaParaPosfixa`):
    *   Utiliza a classe `java.util.Stack<Character>` para a pilha de operadores.
    *   Operandos (letras ou números) são adicionados diretamente a um `StringBuilder` que formará a expressão pós-fixa.
    *   Operadores são gerenciados na pilha respeitando suas precedências.
    *   Parênteses `(` são empilhados.
    *   Parênteses `)` fazem com que operadores sejam desempilhados para a saída até que um `(` seja encontrado.
    *   Erros de parênteses desbalanceados lançam uma `IllegalArgumentException`.
    *   Ao final, quaisquer operadores restantes na pilha são movidos para a saída.

## 🎯 Algoritmo (Detalhado em Java)

A classe `Tradutor` com seu método estático `infixaParaPosfixa` realiza a conversão:

1.  Itera sobre cada caractere (`token`) da string `infixa`.
2.  Se `token` é uma letra ou dígito (`Character.isLetterOrDigit`), anexa-o ao `StringBuilder` da `posfixa`.
3.  Se `token` é `(`, empilha-o na `Stack`.
4.  Se `token` é `)`:
    *   Enquanto a `Stack` não estiver vazia e o topo (`peek()`) não for `(`, desempilha (`pop()`) da `Stack` e anexa à `posfixa`.
    *   Se a `Stack` não estiver vazia e o topo for `(`, desempilha-o (removendo o parêntese de abertura).
    *   Caso contrário (pilha vazia ou `(` não encontrado), lança `IllegalArgumentException` por parênteses desbalanceados.
5.  Se `token` é um operador:
    *   Enquanto a `Stack` não estiver vazia e a precedência do operador no topo da `Stack` for maior ou igual à precedência do `token` atual, desempilha da `Stack` e anexa à `posfixa`.
    *   Empilha o `token` (operador atual).
6.  Após o loop, enquanto a `Stack` não estiver vazia:
    *   Se o topo da `Stack` for `(`, lança `IllegalArgumentException` (parênteses desbalanceados).
    *   Desempilha da `Stack` e anexa à `posfixa`.
7.  Retorna a string construída pelo `StringBuilder`.

O método `main` lida com a leitura dos nomes dos arquivos (via argumentos de linha de comando ou entrada interativa) e processa cada linha do arquivo de entrada, escrevendo o resultado ou uma mensagem de erro no arquivo de saída e no console.

## 🛠️ Desenvolvimento

Para contribuir com o projeto:

1.  Clone o repositório.
2.  Navegue até o diretório `java`.
3.  Faça suas modificações no arquivo `Tradutor.java`.
4.  Compile (`javac Tradutor.java`) e teste com diferentes expressões, incluindo casos de erro.
5.  Envie um pull request com suas melhorias.

## 📝 Licença

Este projeto foi desenvolvido como um exemplo e pode ser usado livremente.
