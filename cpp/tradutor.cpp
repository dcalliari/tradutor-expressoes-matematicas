#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <stdexcept>

int obterPrecedencia(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

std::string infixaParaPosfixa(const std::string& infixa) {
    std::stack<char> pilha;
    std::string posfixa = "";

    for (char token : infixa) {
        if (isalnum(token)) {
            posfixa += token;
        } else if (token == '(') {
            pilha.push(token);
        } else if (token == ')') {
            while (!pilha.empty() && pilha.top() != '(') {
                posfixa += pilha.top();
                pilha.pop();
            }
            if (!pilha.empty() && pilha.top() == '(') {
                pilha.pop();
            } else {
                throw std::runtime_error("Erro: Parênteses desbalanceados na expressão.");
            }
        } else {
            while (!pilha.empty() && obterPrecedencia(pilha.top()) >= obterPrecedencia(token)) {
                posfixa += pilha.top();
                pilha.pop();
            }
            pilha.push(token);
        }
    }

    while (!pilha.empty()) {
        if (pilha.top() == '(') {
             throw std::runtime_error("Erro: Parênteses desbalanceados na expressão.");
        }
        posfixa += pilha.top();
        pilha.pop();
    }

    return posfixa;
}

int main(int argc, char* argv[]) {
    std::string arquivoEntradaNome;
    std::string arquivoSaidaNome;

    if (argc == 3) {
        arquivoEntradaNome = argv[1];
        arquivoSaidaNome = argv[2];
    } else if (argc == 1) {
        std::cout << "Digite o nome do arquivo de entrada: ";
        std::cin >> arquivoEntradaNome;
        std::cout << "Digite o nome do arquivo de saida: ";
        std::cin >> arquivoSaidaNome;
    } else {
        std::cerr << "Uso: tradutor_cpp <arquivo_entrada> <arquivo_saida>" << std::endl;
        std::cerr << "Ou execute sem argumentos para modo interativo." << std::endl;
        return 1;
    }

    std::ifstream arquivoEntrada(arquivoEntradaNome);
    std::ofstream arquivoSaida(arquivoSaidaNome);

    if (!arquivoEntrada.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada: " << arquivoEntradaNome << std::endl;
        return 1;
    }

    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro ao criar o arquivo de saida: " << arquivoSaidaNome << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivoEntrada, linha)) {
        if (linha.empty()) continue;
        try {
            std::string posfixa = infixaParaPosfixa(linha);
            arquivoSaida << posfixa << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Erro ao processar a expressao '" << linha << "': " << e.what() << std::endl;
        }
    }

    std::cout << "Tradução concluida. Resultados em: " << arquivoSaidaNome << std::endl;

    arquivoEntrada.close();
    arquivoSaida.close();

    return 0;
}
