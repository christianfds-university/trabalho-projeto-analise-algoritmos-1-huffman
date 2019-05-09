#ifndef ESTRUTURACODIFICACAO_H
#define ESTRUTURACODIFICACAO_H

#include <iostream>
using namespace std;
#include <string>

//Utilizada para retornar de formar correta a ser utlizada em outros lugares
class EstruturaCodificao{

private:
    string codificacao; //codificacao de uffman de 0 e 1s
    string valor;       //o que a codificao significa

public:
    //Construtor da classe
    EstruturaCodificao(){
        codificacao = "";
        valor = "";
    }

    //---------- Getters e Setters -------------------
    void setCodificao(string codificacao){
        this->codificacao = codificacao;
    }

    void setValor(string valor){
        this->valor = valor;
    }

    string getCodificao(){
        return this->codificacao;
    }

    string getValor(){
        return this->getValor();
    }

    //------------------------------------------------
    //visualizar os valores contidos nas variaveis
    void show(){
        cout << "cod[" << this->codificacao << "] valor[" << this->valor <<"]"<< endl;
    }

    ~EstruturaCodificao(){
    }};


#endif // ESTRUTURACODIFICACAO_H
