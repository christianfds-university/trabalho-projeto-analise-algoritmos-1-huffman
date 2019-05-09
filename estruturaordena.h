#ifndef ESTRUTURAORDENA_H
#define ESTRUTURAORDENA_H

using namespace std;
#include <iostream>
#include <string>
#include "arvore.h"

//Classe auxiliar na ordenacao, e na manipulacao para a lista dos valores
class EstruturaOrdena{

public:
	Arvore *noArvore;
	string cod;
	int count;

	//construtor da classe
	EstruturaOrdena(){
		this->noArvore = NULL;
		this->count = 0;
	}

	//setter de count
	void setCount(int count){
		this->count = count;
	}

	//vizualizador do valor contido
	//caso possua arvore, ele nao tem codigo, e vice versa.
	void show(){
		if(this->noArvore != NULL){
			cout << "[POSSUI NO";
			printf("] = %d\n", count);
		}else{
			printf("COD[");
			cout << cod;
			printf("] = %d\n", count);
		}
	}

	//Destrutor da classe
	~EstruturaOrdena(){
		this->noArvore = NULL;
		this->count = 0;
	}
};


#endif // ESTRUTURAORDENA_H
