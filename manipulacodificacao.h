#ifndef MANIPULACAOCODIFICACAO_H
#define MANIPULACAOCODIFICACAO_H

#include <string>
#include "arvore.h"
#include "estruturaordena.h"
#include <set>
#include <map>
#include <ctype.h>
#include "estruturacodificacao.h"

using namespace std;

//Faz toda a manipulação e codificacao do codigo de huffman
class ManipulaCodificacao{

private:

    set<EstruturaOrdena *> lista; //lista coms os cod {caracter, ou palavra} e suas frequencias
    Arvore *raiz;				  //aponta para a cabeça da arvore resultado da codficacao
	map<string, int> MapAux;	  //map para contar as frequencias.

	//funcao que verifica se existe na lista, o codigo informado como parametro
	bool auxVerificaExiste(string cod){
		set<EstruturaOrdena *>::iterator it; 
		for(it = lista.begin(); it != lista.end(); ++it){
			if((*it)->cod == cod) return true;
		}
		return false;
	}

	//conta a quantidade que o cod aparece, na string passado por primeiro parametro
	//caso passe como carcater sera tratado de uma forma diferente do que palavra
	int countCodString(string codAll, string cod, bool isCodCaracter){
		int count = 0;		//quantas vezes aparece a palavra
		int procura = 0;	//em qual lugar achou a palavra
		int pos = -1;		//pos que esta percorreendo a lista

		int auxPos = 0;     //auxiliar da posicao
		string auxCodAll = codAll;	//copia do codigo total
		while(true){

			pos = auxCodAll.find(cod); //acha a primeira ocorrencia da palavra
			if(pos != -1){

				//caso for carcater
				if(isCodCaracter == true){
					count++;
					auxCodAll = auxCodAll.substr(pos+cod.size(),codAll.size());
				}
				else{
					//₢aso for palavra com inicio na posicao 0
					if(pos == 0 && pos+cod.length() <= codAll.length()){

						int depois =  codAll.at(auxPos+pos+cod.size());
						//veifica se e uma palavra valida, ou nao uma aparicao de uma palavra dentro de outra
						if((depois >= 65 && depois <= 90) || (depois >= 97 && depois <= 122)){

						}
						else{
							count++;

						}

					}
					//caso a palavra esteja no final
					if((pos+cod.length()) >= codAll.length() && pos > 0){

						int antes =  codAll.at(auxPos+pos-1);
						//verifica se e uma palavra valida, verificando o comeco
						if((antes >= 65 && antes <= 90) || (antes >= 97 && antes <= 122)){

						}
						else{
							count++;

						}

					}
					//Caso a palavra esteja no meio do stringo total
					if(pos+cod.length() < codAll.length() && pos > 0){

						int antes = codAll.at(auxPos+pos-1);
						int depois =  codAll.at(auxPos+pos+cod.length());
						//verifica antes e depois
						if(((depois >= 65 && depois <= 90) || (depois >= 97 && depois <= 122)) || ((antes >= 65 && antes <= 90) || (antes >= 97 && antes <= 122))){

						}
						else{
							count++;

						}

					}
					auxPos += pos+cod.size();
					auxCodAll = auxCodAll.substr(pos+cod.size(),codAll.size());
				}
			}
			else{
				return count;
			}

		}
		return count;

	}

	//Pega o menor elemento da lista, e remove-o em seguida, retornando o mesmo
	EstruturaOrdena* getMenor(){
		set<EstruturaOrdena *>::iterator it; 
		set<EstruturaOrdena *>::iterator result;
		result = lista.begin();
		for(it = lista.begin(); it != lista.end(); ++it){
			if(((*it)->count) < (*result)->count){
				result = it;
			}
		}
		lista.erase(result);
		return *result;
	}

	//retorna o numero de itens ainda contidos na lista
	int auxCountLista(){
		int count = 0;
		set<EstruturaOrdena *>::iterator it; 
		for(it = lista.begin(); it != lista.end(); ++it){
			count++;
		}
		return count;
	}

	//Pega o resutlado contido na arvore de Huffman , e coloca no resultado em um vetor, com a Estrutura de Codificacao
	void auxMontaResultCodificao(string param, Arvore *no, map<string,string> *MapCodigos){
		EstruturaCodificao *auxEstruturaCodificao = new EstruturaCodificao();
		if(no != NULL){
			if((*no).getDireita() != NULL || (*no).getEsquerda() != NULL){
				this->auxMontaResultCodificao(param +"1", (*no).getDireita(), MapCodigos);
				this->auxMontaResultCodificao(param +"0", (*no).getEsquerda(), MapCodigos);
			}
			else{
				auxEstruturaCodificao->setCodificao(param);
				auxEstruturaCodificao->setValor((*no).getCod());
				(*MapCodigos)[(*no).getCod()]=param;
			}
		}
	}

	//pega a proxima palavra dentro de uma string
	string auxGetProxPalavra(string codAll, int positionApartir ){

		string result = "";
		char aux;
		int length = codAll.length();

		int i = positionApartir;

		aux = tolower(codAll.at(i));

		while(i < (length) && (aux >= 'a' && aux <= 'z')){
			result += codAll.at(i);
			i++;

			if(i < length) aux = tolower(codAll.at(i));
		}

		if(result.length() == 0){
			result += codAll.at(positionApartir);
		}

		return result;

	}

public:

	//construtor da classe
	ManipulaCodificacao(){

	}

	//retorna a raiz da arvore resultado de huffman
	Arvore* getRaiz(){
		return this->raiz;
	}

	//conta em um map, a ocorrencia de carracter ali dentro
	map<int,string> CountCodPorCaracter(string *codAll){

		lista.clear();

		map<int,string> tokens;

		int i = 0;
		int count_aux;
		EstruturaOrdena *a;

		while(i < (*codAll).length()){
			string aux = "";
			aux += (*codAll).at(i);

			MapAux[aux]++;

			tokens[i++] = (*codAll).at(i);
		}

		for(auto const &ent1 : MapAux){
			a = new EstruturaOrdena();
			a->cod = ent1.first;
			a->setCount(ent1.second);
			lista.insert(a);
		}

		return tokens;

	}

	//conta, por palavra, e coloca o resultado em um map de string
	map<int,string> CountCodPorPalavra(string *codAll){

		lista.clear();

		map<int,string> tokens;

		int i = 0;
		int position = 0;
		string auxPalavraProcura;
		EstruturaOrdena *a;
		while(position < (*codAll).length()){

			auxPalavraProcura = auxGetProxPalavra((*codAll), position);

			MapAux[auxPalavraProcura]++;

			tokens[i++] = auxPalavraProcura;

			position += auxPalavraProcura.length();
			cout << position << endl;
		}

		for(auto const &ent1 : MapAux){
			a = new EstruturaOrdena();
			a->cod = ent1.first;
			a->setCount(ent1.second);
			lista.insert(a);
		}

		return tokens;
	}

	//monta a arvore de Huffman apartir da lista gerada anteriormente, contando os carcaters.
	void montarArvore(){

		this->raiz = NULL; //raiz nula

		EstruturaOrdena *aux1Menor;			//pega o menor
		EstruturaOrdena *aux2Menor;			//pega outro menor, depois do menor
		EstruturaOrdena *novoItem;			//novo item de para a lista com os dois anteriores menores
		Arvore *Arvore_novo;


		while(this->auxCountLista() > 1){			//enquanto a lista conter mais que um elemento
			aux1Menor = this->getMenor();			//pega o menor
			aux2Menor = this->getMenor();			//pega o novo menor

			Arvore_novo = new Arvore("");
			if(aux1Menor->noArvore != NULL){						//caso , o primeiro menor, contenha um no de arvore
				Arvore_novo->setDireita(aux1Menor->noArvore);
			}
			else{													//se nao tem
				Arvore_novo->setDireita(new Arvore((*aux1Menor).cod));
			}

			if(aux2Menor->noArvore != NULL){						//caso, o segundo contenha um no de arvore
				Arvore_novo->setEsquerda(aux2Menor->noArvore);
			}														//se nao tem
			else{
				Arvore_novo->setEsquerda(new Arvore((*aux2Menor).cod));
			}

			//cria a novo estrutura
			novoItem = new EstruturaOrdena();
			novoItem->count = (*aux1Menor).count + (*aux2Menor).count ;
			novoItem->cod = "";
			novoItem->noArvore = Arvore_novo;

			//e adiciona na lista
			lista.insert(novoItem);

			//lembrando que na busca por item menor, ja é removido, os dois menores utilizados nessa operação
		}
		this->raiz = novoItem->noArvore;

	}

	//Mostra toda a lista
	void ShowLista(){

		set<EstruturaOrdena *>::iterator it; 
		for(it = lista.begin(); it != lista.end(); ++it){
			(*it)->show();

		}

	}

	//Mostra os valores da codificao diretamente da arvore, [mesma ideia da uniao dos restuldao em um vetor]
	void ShowArvore(string param, Arvore *no){
		if(no != NULL){
			if((*no).getDireita() != NULL || (*no).getEsquerda() != NULL){
				this->ShowArvore(param +"1", (*no).getDireita());
				this->ShowArvore(param +"0", (*no).getEsquerda());
			}
			else{
				cout << "codificacao[" << param << "]";
				(*no).show();
			}
		}
	}

	//retorna um map, com o resultado da codificao de huffman, com seu respctivo valor
	map<string,string> getResultCodificao(){
		map<string,string> MapCodigos;

		if((raiz) != NULL){
			this->auxMontaResultCodificao("", this->getRaiz(), &MapCodigos);
		}

		return MapCodigos;
	}


};



#endif 
