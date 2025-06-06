# Tradutor de Expressões Matemáticas

Este projeto implementa um tradutor que converte expressões matemáticas do formato **infixado** para o formato **pós-fixado** (notação polonesa reversa).

## 📋 Funcionalidades

- Lê arquivo de texto com expressões matemáticas infixas
- Converte cada expressão para notação pós-fixa
- Gera arquivo de saída com as expressões convertidas
- Suporta operadores: `+`, `-`, `*`, `/`, `^` e parênteses `()`
- Trata precedência de operadores corretamente

## 🚀 Como usar

### Pré-requisitos
- Python 3.6 ou superior
- VS Code (recomendado)

### Execução via linha de comando

```bash
python tradutor.py arquivo_entrada.txt arquivo_saida.txt
```

### Execução interativa

```bash
python tradutor.py
```
O programa solicitará os nomes dos arquivos de entrada e saída.

## 📁 Estrutura do Projeto

```
tradutor-expressoes-matematicas/
├── README.md
├── tradutor.py
├── exemplos/
│   ├── entrada.txt
│   └── saida.txt
└── requirements.txt
```

## 🔧 Exemplo de Uso

### Arquivo de entrada (`exemplos/entrada.txt`):
```
a+b*c
(a+b)*c
a+b*c-d
a^b+c*d
(a+b)*(c-d)
```

### Arquivo de saída gerado (`exemplos/saida.txt`):
```
abc*+
ab+c*
abc*+d-
ab^cd*+
ab+cd-*
```

## 🧮 Como funciona

O programa utiliza o **Algoritmo Shunting Yard** para converter expressões infixas em pós-fixas:

1. **Precedência de Operadores**:
   - `^` (potenciação): precedência 3
   - `*`, `/`: precedência 2  
   - `+`, `-`: precedência 1
   - `()`: precedência 0

2. **Processo de Conversão**:
   - Operandos vão diretamente para a saída
   - Operadores são empilhados respeitando precedência
   - Parênteses controlam a ordem de processamento

## 🎯 Algoritmo

O algoritmo segue estas regras:
1. Se o token é um operando → adiciona à saída
2. Se é `(` → empilha
3. Se é `)` → desempilha até encontrar `(`
4. Se é operador → desempilha operadores de maior/igual precedência, depois empilha
5. Ao final → desempilha todos os operadores restantes

## 📊 Exemplos de Conversão

| Expressão Infixa | Expressão Pós-fixa | Explicação |
|------------------|---------------------|------------|
| `a+b*c` | `abc*+` | Multiplicação tem precedência sobre adição |
| `(a+b)*c` | `ab+c*` | Parênteses alteram a precedência |
| `a^b+c*d` | `ab^cd*+` | Potenciação tem maior precedência |

## 🛠️ Desenvolvimento

Para contribuir com o projeto:

1. Clone o repositório
2. Faça suas modificações
3. Teste com diferentes expressões
4. Envie um pull request

## 📝 Licença

Este projeto foi desenvolvido como trabalho acadêmico.