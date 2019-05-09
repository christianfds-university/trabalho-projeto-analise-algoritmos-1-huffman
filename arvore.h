#ifndef ARVORE_H
#define ARVORE_H

using namespace std;
#include <string>
#include <iostream>

//Arvore de Huffman contendo os valores, e as sequencias das codificacoes
class Arvore{

private:
    //codigo  = palavra ou caracterer
    string cod;
    //direita = 1 e esquerda = 0 da arvore
    Arvore *direita, *esquerda;

public:
    //Construtor da classe arvor
    Arvore(string cod){
        this->setPalavra(cod);
        this->direita = this->esquerda = NULL;
    }

    //------------ Getters e Setters da Classe ------------------
    void setPalavra(string palavra){
        this->cod = palavra;
    }

    string getCod(){
        return this->cod;
    }

    void setDireita(Arvore *direita){
        this->direita = direita;
    }

    void setEsquerda(Arvore *esquerda){
        this->esquerda = esquerda;
    }

    Arvore * getEsquerda(){
        return this->esquerda;
    }
    Arvore * getDireita(){
        return this->direita;
    }

    //------------------------------------------------------------
    //Printar na tela o conteudo deste no
    void show(){
        cout << " [ITEM] == [" << cod << "]"<<endl;
    }

    ~Arvore(){

    }
};



#endif // ARVORE_H
