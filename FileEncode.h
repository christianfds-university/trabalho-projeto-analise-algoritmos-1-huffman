#ifndef FILEENCODE_H
#define FILEENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

//Classe que gera o arquivo codificado
class FileEncode{

	ofstream *f;
	map<string,string> MapaOcorrencias;
	map<int,string> tokens;

public:
	FileEncode(ofstream &f,	map<string,string> MapaOcorrencias, map<int,string> tokens){
		this->f = &f;
		this->MapaOcorrencias = MapaOcorrencias;
		this->tokens = tokens; 
	}

	//Codifica uma string para não haver erro de leitura
	string EncodeString(string x){
		for (int i = 0; i < x.length(); i++){
			if(x[i] == '\\') x.replace(i,1,"\\\\");
			if(x[i] == '"') x.replace(i,1,"\\\"");
			if(x[i] == '\n') x.replace(i,1,"\\n");
		}

		x = "\"" + x + "\"";

		return x;
	}

	//Escreve o cabeçalho de uma codificação
	void WriteCabecalho(){
		(*f) << MapaOcorrencias.size() << '\n';
		for(auto const &ent1 : MapaOcorrencias){
			(*f) << ent1.second << " = " << EncodeString(ent1.first) << '\n';
		}
	}

	//Le dados e converte e uma string de 0's e 1's, em seguida converte em bytes e escreve no arquivo
	void WriteBits(){
		string bitList = "";

		for(auto const &ent1 : tokens){
	        string aux = ent1.second;
	        bitList += MapaOcorrencias.find(aux)->second;
	    }

		char buffer = 0;
		int bit2byte_counter = 0;
		int i;

		for (i = 0; i < bitList.size(); i++){
			buffer = buffer << 1;
			buffer |= bitList.at(i) == '1';
			if(bit2byte_counter++ == 7){
				(*f) << buffer;
				buffer = 0;
				bit2byte_counter = 0;
			}
		}

		if(bit2byte_counter != 0){
			while(bit2byte_counter != 0){
				buffer = buffer << 1;
				bit2byte_counter++;
			}
			(*f) << buffer;
		}

	}

	~FileEncode(){
	};
};

#endif