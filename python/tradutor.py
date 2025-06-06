import os

class TradutorExpressoes:
    def __init__(self):
        self.precedencia = {
            '+': 1,
            '-': 1,
            '*': 2,
            '/': 2,
            '^': 3,
            '(': 0
        }
    
    def eh_operador(self, caractere):
        return caractere in self.precedencia
    
    def eh_operando(self, caractere):
        return caractere.isalnum()
    
    def infixa_para_posfixa(self, expressao):
        expressao = expressao.replace(' ', '')
        pilha = []
        resultado = []
        
        for caractere in expressao:
            if self.eh_operando(caractere):
                resultado.append(caractere)
            elif caractere == '(':
                pilha.append(caractere)
            elif caractere == ')':
                while pilha and pilha[-1] != '(':
                    resultado.append(pilha.pop())
                if pilha:
                    pilha.pop()
            elif self.eh_operador(caractere):
                while (pilha and pilha[-1] != '(' and 
                       self.precedencia[pilha[-1]] >= self.precedencia[caractere]):
                    resultado.append(pilha.pop())
                pilha.append(caractere)
        
        while pilha:
            resultado.append(pilha.pop())
        
        return ''.join(resultado)
    
    def processar_arquivo(self, arquivo_entrada, arquivo_saida):
        try:
            with open(arquivo_entrada, 'r', encoding='utf-8') as arquivo:
                linhas = arquivo.readlines()
            
            resultados = []
            print(f"Processando {len(linhas)} expressão(ões)...")
            
            for numero_linha, linha in enumerate(linhas, 1):
                expressao = linha.strip()
                if expressao:
                    try:
                        expressao_posfixa = self.infixa_para_posfixa(expressao)
                        resultados.append(expressao_posfixa)
                        print(f"Linha {numero_linha}: {expressao} -> {expressao_posfixa}")
                    except Exception as erro:
                        mensagem_erro = f"ERRO: {expressao}"
                        print(f"Erro na linha {numero_linha} ({expressao}): {erro}")
                        resultados.append(mensagem_erro)
            
            with open(arquivo_saida, 'w', encoding='utf-8') as arquivo:
                for resultado in resultados:
                    arquivo.write(resultado + '\n')
            
            print(f"\nArquivo de saída gerado: {arquivo_saida}")
            
        except FileNotFoundError:
            print(f"Erro: Arquivo '{arquivo_entrada}' não encontrado!")
        except Exception as erro:
            print(f"Erro ao processar arquivos: {erro}")


def main():
    tradutor = TradutorExpressoes()
    
    print("=== TRADUTOR DE EXPRESSÕES MATEMÁTICAS ===")
    print("Converte expressões infixas para pós-fixas\n")
    
    arquivo_entrada = "../testes/entrada.txt"
    arquivo_saida = "../testes/saida.txt"
    
    if not os.path.exists(arquivo_entrada):
        print(f"Erro: Arquivo '{arquivo_entrada}' não encontrado!")
        return
    
    tradutor.processar_arquivo(arquivo_entrada, arquivo_saida)


if __name__ == "__main__":
    main()
