#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "posfijoEntero.h"

using namespace std;

class Instruccion;

class Nodo{
    protected: 
        Instruccion *dato;
		int valor;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(Instruccion *a) {dato=a; next=NULL;};
        void set_dato(Instruccion *a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        Instruccion* get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
		void setValor(int v){valor = v;};
		int getValor(){return valor;};
};


class Lista{
    private: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            void add(Instruccion* d);
            bool esvacia(void);
            Nodo* cabeza(void);
            Lista *resto(void);
            string toPrint(string p);   
            void impre(void);
            int size();
            void borrar(void); //borra la cabeza
            void borrar_last();//borra el ultimo
            Lista *copy(void);
            void tomar(int n);
            Nodo* last();
};

//-------- Metodos de Lista -------------------
Nodo* Lista::last()
{ if(!this->esvacia()){
    if(this->resto()->esvacia())return this->cabeza();
    return this->resto()->last();
  }return 0;
}
int Lista::size()
{ 
     if (this->esvacia()) return 0;
     return 1+this->resto()->size();
}
/*void Lista::impre(void)
{ Nodo *aux;
  aux=czo;
    while(aux->get_next()!=NULL){
         cout<<aux->get_dato()->getInstruccion()<<endl;
         aux=aux->get_next();
    }
}*/
void Lista::add(Instruccion* d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}
Nodo* Lista::cabeza(void)
{ 
 /* if(this->esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return 0; 
  }*/
  return czo;
}
Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}
string Lista::toPrint(string p)
{ 
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<" - "<< this->resto()->toPrint(p) << endl;
       return stm.str();
     }
}
void Lista::borrar(void)
{ //borra el nodo cabeza
  if(!this->esvacia()){
         Nodo *tmp=czo;
         czo=czo->get_next();
         delete tmp;
  }
}
void Lista::borrar_last()
{ // borra el ultimo nodo
   if(!this->esvacia()){
      if((czo->get_next())->get_next()==NULL){
         delete czo->get_next();
         czo->set_next(NULL);
      }
      else this->resto()->borrar_last(); 
   }  
}

class Cola:public Lista{
  public:
      Cola(void){Lista();};
      Cola(Nodo* n):Lista(n){};
      ~Cola(void);
      Nodo* tope();
      bool colavacia(){this->esvacia();};
      void encolar(Instruccion* a) ;
      void desencolar();
      Nodo* ultimo();
      string imprimir(string s);
      Cola* restoC();
};
//--------------------- Metodos de Cola -----------------------
Nodo* Cola::tope(void)
{  return this->last();
}
void Cola::encolar(Instruccion* a)
{  this->add(a);
}
void Cola::desencolar(void)
{  this->borrar_last();
}
Nodo* Cola::ultimo(void)
{   return this->cabeza();
}
string Cola::imprimir(string s)
{  return this->toPrint(s);
}
Cola *Cola::restoC(void)
{ 
      Cola *l=new Cola(ultimo()->get_next());
      return (l);
}
class Instruccion{
	protected: string instruccion;
	public: 
			Instruccion(string s){instruccion = s;};
			string getInstruccion(){return instruccion;};
			int identificaIns();
			void ejecutaIns(int i, Cola* listaVar);
			Nodo* buscaVar(Cola* lista, char c); //devulve el nodo de la variable a asignar
};
//---------------métodos de instruccion-------------------
int Instruccion::identificaIns(){
		if(getInstruccion().at(3) == 'I' && getInstruccion().at(4) == 'N'){
			cout << "Declaracion de variable" << endl;
			return 0; 
		}	
		if(getInstruccion().at(3) >= 'a' && getInstruccion().at(3) <= 'z'){
			cout << "Asignacion" << endl;
			return 1;
		}
		if(getInstruccion().at(3) == 'I' && getInstruccion().at(4) == 'F'){
			cout<<"Condicional" << endl;
			return 2;
		}
		if(getInstruccion().at(3) == 'J'){
			cout << "Jump" << endl;
			return 3;
		}
		if(getInstruccion().at(3) == 'S'){
			cout<<"Show" << endl;
			return 4;
		}
			
}

Nodo* Instruccion::buscaVar(Cola* lista, char c){
	if(lista->ultimo()->get_dato()->getInstruccion().at(7) == c)
		return lista->ultimo();
	else buscaVar(lista->restoC(),c);	
}

class Asignacion:public Instruccion{
	public:
		Asignacion(string s):Instruccion(s){};
		void asigna(Cola* lista); // realiza la asignacion
};
//-----------metodos asignacion--------------

void Asignacion::asigna(Cola* lista){
	string instruccion = getInstruccion();
	stringstream ss;
	int inicio, resultado;
	
	for(int i=0; i<instruccion.size(); i++){ //identifica algo
		if(instruccion.at(i) == '=')
			inicio = i+1;
	}
	
	for(int j= inicio; j<instruccion.size(); j++){ //lee la cedena despues del signo igual
		if(instruccion.at(j)>='a' && instruccion.at(j)<='z'){
			int valor = buscaVar(lista, instruccion.at(j))->getValor();
			ss << valor ;
		}
		else if(instruccion.at(j)!= 32){ //agrega todos los caracteres que no sean el vacio
			ss << instruccion.at(j);
		}
	}
	resultado = posfijoEntero(ss.str());
	buscaVar(lista, this->getInstruccion().at(inicio-3))->setValor(resultado); //asigno valor a variable mas a la izquierda

}

class Condicional:public Instruccion{
	public:
		Condicional(string s):Instruccion(s){};
		bool evaluarCondicion(Cola* lista);
		int identificaThen();
};
//-----------metodos condicional--------------
bool Condicional::evaluarCondicion(Cola* lista){
	string instruccion = getInstruccion();
	int inicio, fin;
	stringstream ss;
	bool resultado;
	
	for(int i=0; i<instruccion.size(); i++){ //identifica el comienzo y fin de la condicion
		if(instruccion.at(i) == '(')
			inicio = i+1;
		if(instruccion.at(i) == ')')
			fin = i;
	}
	
	for(int j=inicio; j<fin; j++){
		if(instruccion.at(j)>='a' && instruccion.at(j)<='z'){
			int valor = buscaVar(lista, instruccion.at(j))->getValor();
			ss << valor ;
		}
		else if(instruccion.at(j)!= 32) //agrega todos los caracteres que no sean el vacio
			ss << instruccion.at(j);
	}	
	resultado = posfijoBoolean(ss.str());
	return resultado;
	
}

int Condicional::identificaThen(){
	int inicio;
	stringstream ss;
	bool resultado;
	
	for(int i=0; i<instruccion.size(); i++){ //identifica el comienzo de la instruccion
		if(instruccion.at(i) == 'E')
			inicio = i;
	}
	
	for(int j=inicio; j<instruccion.size(); j++){ //copia la instruccion despues del then
		ss<<instruccion.at(j);
	}
	return (new Instruccion(ss.str()))->identificaIns();
	
}


void Instruccion::ejecutaIns(int i, Cola* listaVar){
	switch(i){
			case 0: //Declaracion de variable
				listaVar->encolar(this);
				break;
			case 1:{	//Asignacion
				Asignacion* a= new Asignacion(this->getInstruccion());
				//listaVar->impre();
				//cout << a->getInstruccion();
				a->asigna(listaVar);
				break;
			}
			case 2:{//condicional
				Condicional* c= new Condicional(this->getInstruccion());
				if(c->evaluarCondicion(listaVar)){
					ejecutaIns(c->identificaThen(), listaVar);
					//cout<<"TOdo Ok";
				}
				break;
			}
			case 3: //jump
				break;
			case 4: //show
				break;
		}
}
int main(){
	
	fstream archivo;
	string instruccion;
	Cola *listaIns = new Cola(); //puntero a lista con instrucciones
	Cola *listaVar = new Cola();
	
	archivo.open("programa.txt", ios::in); //abre archivo en modo lectura
	
	if(archivo.fail()){
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){ // mientras no sea el final del archivo
		getline(archivo, instruccion);
		listaIns->encolar(new Instruccion(instruccion));
	}
	archivo.close(); 

	//Este bloque ejecuta las instrucciones
	while(!listaIns->esvacia()){
		int i = listaIns->tope()->get_dato()->identificaIns();
		listaIns->tope()->get_dato()->ejecutaIns(i, listaVar);
		listaIns->desencolar();
	
	}
	
	
}


