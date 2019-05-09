#include <algorithm>
#include <fstream>
#include <string>
#include <map>
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manipulacodificacao.h"
#include "FileDecode.h"
#include "FileEncode.h"

string getFileData(string fileName){
	ifstream fileInput(fileName);
	string FileData;
	char byte;

	int i = 0;
	while(fileInput.get(byte)){
		FileData += byte;
		cout << i++ << endl;
	}

	fileInput.close();

	return FileData;
}

int main(int argc, char *argv[]){

	int choice = 1;

	string finName, foutName;
	string FileData;

	while(choice != 0){
		system("clear");
		FileData = "";

		cout << 1 << " - Codificar por Caracter" << endl;
		cout << 2 << " - Decoficar por Caracter" << endl;
		cout << 3 << " - Codificar por Palavra" << endl;
		cout << 4 << " - Decoficar por Palavra" << endl;
		cout << 0 << " - Sair" << endl;
		cin >> choice;

		if(choice != 0){
			cout << "Nome do arquivo de entrada" << endl;
			cin >> finName;
			
			cout << "Nome do arquivo de saida" << endl;
			cin >> foutName;
		}

		switch(choice){
			case 1:{

			FileData = getFileData(finName.c_str());

			ManipulaCodificacao b;

			cout << "Codificando" << endl;
			map<int,string> tokens = b.CountCodPorCaracter(&FileData);
			cout << "Gerando arvore" << endl;
			b.montarArvore();
			map<string,string> result = b.getResultCodificao();

			ofstream outputStream(foutName);

			FileEncode *encoder = new FileEncode(outputStream,result,tokens);

			cout << "Escrevendo" << endl;
			encoder->WriteCabecalho();
			encoder->WriteBits();

			delete encoder;

			outputStream.close();

			}
			break;

			case 2:{

			FILE *inputFILE = fopen(finName.c_str(),"r");
			FILE *outputFILE = fopen(foutName.c_str(),"w");
			cout << "Decodificando" << endl;
			FileDecode *decoder = new FileDecode(inputFILE, outputFILE);

			cout << "Escrevendo" << endl;
			decoder->ReadCabecalho();
			decoder->ReadBits();

			fclose(inputFILE);
			fclose(outputFILE);

			delete decoder;

			}
			break;

			case 3:{

			FileData = getFileData(finName.c_str());

			ManipulaCodificacao b;


			cout << "Codificando" << endl;
			map<int,string> tokens = b.CountCodPorPalavra(&FileData);
			cout << "Gerando Arvore" << endl;
			b.montarArvore();
			map<string,string> result = b.getResultCodificao();

			ofstream outputStream(foutName);

			FileEncode *encoder = new FileEncode(outputStream,result,tokens);

			cout << "Escrevendo" << endl;
			encoder->WriteCabecalho();
			encoder->WriteBits();

			delete encoder;

			outputStream.close();

			}
			break;

			case 4:{

			FILE *inputFILE = fopen(finName.c_str(),"r");
			FILE *outputFILE = fopen(foutName.c_str(),"w");
			cout << "Decodificando" << endl;
			FileDecode *decoder = new FileDecode(inputFILE, outputFILE);

			cout << "Escrevendo" << endl;
			decoder->ReadCabecalho();
			decoder->ReadBits();

			fclose(inputFILE);
			fclose(outputFILE);

			delete decoder;

			}
			break;
		}

	}

	return 0;
}
