import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class Tradutor {

    private static int obterPrecedencia(char op) {
        switch (op) {
            case '^':
                return 3;
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
        }
        return 0;
    }

    public static String infixaParaPosfixa(String infixa) throws IllegalArgumentException {
        StringBuilder posfixa = new StringBuilder();
        Stack<Character> pilha = new Stack<>();

        for (char token : infixa.toCharArray()) {
            if (Character.isLetterOrDigit(token)) {
                posfixa.append(token);
            } else if (token == '(') {
                pilha.push(token);
            } else if (token == ')') {
                while (!pilha.isEmpty() && pilha.peek() != '(') {
                    posfixa.append(pilha.pop());
                }
                if (!pilha.isEmpty() && pilha.peek() == '(') {
                    pilha.pop();
                } else {
                    throw new IllegalArgumentException("Erro: Parênteses desbalanceados na expressão: " + infixa);
                }
            } else {
                while (!pilha.isEmpty() && obterPrecedencia(pilha.peek()) >= obterPrecedencia(token)) {
                    posfixa.append(pilha.pop());
                }
                pilha.push(token);
            }
        }

        while (!pilha.isEmpty()) {
            if (pilha.peek() == '(') {
                 throw new IllegalArgumentException("Erro: Parênteses desbalanceados na expressão: " + infixa);
            }
            posfixa.append(pilha.pop());
        }

        return posfixa.toString();
    }

    public static void main(String[] args) {
        String arquivoEntradaNome;
        String arquivoSaidaNome;
        BufferedReader consoleReader = new BufferedReader(new InputStreamReader(System.in));

        try {
            if (args.length == 2) {
                arquivoEntradaNome = args[0];
                arquivoSaidaNome = args[1];
            } else if (args.length == 0) {
                System.out.print("Digite o nome do arquivo de entrada: ");
                arquivoEntradaNome = consoleReader.readLine();
                System.out.print("Digite o nome do arquivo de saida: ");
                arquivoSaidaNome = consoleReader.readLine();
            } else {
                System.err.println("Uso: java Tradutor <arquivo_entrada> <arquivo_saida>");
                System.err.println("Ou execute sem argumentos para modo interativo.");
                return;
            }

            try (BufferedReader leitor = new BufferedReader(new FileReader(arquivoEntradaNome));
                 BufferedWriter escritor = new BufferedWriter(new FileWriter(arquivoSaidaNome))) {

                String linha;
                while ((linha = leitor.readLine()) != null) {
                    if (linha.trim().isEmpty()) continue;
                    try {
                        String posfixa = infixaParaPosfixa(linha.trim());
                        escritor.write(posfixa);
                        escritor.newLine();
                    } catch (IllegalArgumentException e) {
                        System.err.println("Erro ao processar a expressao '" + linha + "': " + e.getMessage());
                        escritor.write("Erro: " + e.getMessage() + " na expressao: " + linha);
                        escritor.newLine();
                    }
                }
                System.out.println("Tradução concluida. Resultados em: " + arquivoSaidaNome);

            } catch (IOException e) {
                System.err.println("Erro de E/S: " + e.getMessage());
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler entrada do console: " + e.getMessage());
        }
    }
}
