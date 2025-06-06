# Implemente abaixo a funcao: compara_pilhas(pilha1, pilha2)
//Insira o código aqui


# ==========================
# Codigo auxiliar: nao altere as definicoes abaixo.
# Nao se preocupe com esse codigo. Ele serve apenas para testar sua atividade.
# ==========================

class Pilha:

	class NoPilha:
		def __init__(self, dado, prox):
			self.dado = dado
			self.prox = prox

	def __init__(self):
		self.__cabeca = None
		self.__tamanho = 0

	def is_empty(self):
		return self.__tamanho == 0

	def push(self, item):
		novo_no = self.NoPilha(item, self.__cabeca)
		self.__cabeca = novo_no
		self.__tamanho += 1

	def pop(self):
		if self.is_empty():
			raise Exception('Pilha vazia')
		dado = self.__cabeca.dado
		self.__cabeca = self.__cabeca.prox
		self.__tamanho -= 1
		return dado
	
	def top(self):
		if self.is_empty():
			raise Exception('Pilha vazia')
		return self.__cabeca.dado

	def __len__(self):
		return self.__tamanho

# Programa principal:
pilha1 = Pilha()
pilha2 = Pilha()
entrada = input()
while entrada != 'FIM':
	if entrada.startswith('empilha1 '):
		comando, dado = entrada.split(' ')
		pilha1.push(dado)
	elif entrada.startswith('empilha2 '):
		comando, dado = entrada.split(' ')
		pilha2.push(dado)
	entrada = input()
tam1, tam2 = len(pilha1), len(pilha2)
topo1, topo2 = pilha1.top(), pilha2.top()
resultado = compara_pilhas(pilha1, pilha2)
if (tam1 == len(pilha1)) and (tam2 == len(pilha2)) and (not pilha1.is_empty()) and (not pilha2.is_empty()) and (topo1 == pilha1.top()) and (topo2 == pilha2.top()):
	if resultado:
		print('As pilhas sao iguais!')
	else:
		print('As pilhas sao diferentes!')
