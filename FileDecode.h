#ifndef FILEDECODE_H
#define FILEDECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

//Classe que descodifica um arquivo
class FileDecode{

	FILE *fin;
	FILE *fout;
	map<string,string> cabecalho;

public:
	FileDecode(FILE *fin, FILE *fout){
		this->fin = fin;
		this->fout = fout;
	}

	//Le o cabeçalho de tradução
	void ReadCabecalho(){
		int j;
		string a, b;
		char aux1[128], aux2[128];
		fscanf(fin,"%d", &j);

		for (int i = 0; i < j; i++){
			fscanf(fin,"%s%*c%*c%*c", aux1);
			fgets(aux2,128,fin);
			a = (string) aux1;
			b = DecodeString((string) aux2);
			cabecalho[a] = b;
		}

	}

	//Decodifica uma string do cabeçalho 
	string DecodeString(string x){
		if(x[x.length()-1] == '\n')
			x.erase((x.length()-1),1);

		for (int i = 0; i < x.length() - 1; i++){
			if(x[i] == '\\' && x[i+1] == '"') x.erase(i,1);
			if(x[i] == '\\' && x[i+1] == 'n') x.replace(i,2,"\n");
			if(x[i] == '\\' && x[i+1] == '\\') x.replace(i,2,"\\");
		}

		if(x[0] == '\"') 
			x.erase(0,1);
		if(x[x.length()-1] == '\"') 
			x.erase((x.length()-1),1);

		return x;
	}

	//Le dados e converte uma string de 0's e 1's em suas respectivas tradução, em seguida escreve no arquivo
	void ReadBits(){

		string Search4;
		string outputStream = "";
		char buffer1 = 0;
		char buffer2 = 0;
		int end = 0;

		int bit2byte_counter = 0;

		fscanf(fin,"%c", &buffer1);
		if(feof(fin)) printf("Arquivo Vazio"); 
		fscanf(fin,"%c", &buffer2);
		if(feof(fin)) buffer2 = 0;

		while(1){
			Search4 += to_string((buffer1 & 1 << 8) >> 8);
			buffer1 = buffer1 << 1;
			buffer1 |= ((buffer2 & 1 << 8) >> 8);
			buffer2 = buffer2 << 1;
			if(cabecalho.count(Search4)){
				outputStream += cabecalho.find(Search4)->second;
				Search4 = "";
			}
			if(bit2byte_counter++ == 7){
				fscanf(fin, "%c", &buffer2);
				if(feof(fin) && end ) break;
				if(feof(fin)) end++;
				bit2byte_counter = 0;
			} 
		}

		fprintf(fout, "%s", outputStream.c_str());

	}

	~FileDecode(){
	};};

#endif