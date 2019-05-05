#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){
	fstream archivo;
	string instruccion;

	archivo.open("programa.txt", ios::in); //abre archivo en modo lectura

	if(archivo.fail()){
		cout << "No se pudo abrir el archivo";
		exit(1);
	}

	while(!archivo.eof()){ // mientras no sea el final del archivo
		getline(archivo, instruccion);
		cout << instruccion << endl;
	}


	archivo.close();
}
