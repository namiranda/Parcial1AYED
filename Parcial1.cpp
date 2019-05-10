#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "posfijoEntero.h"

using namespace std;

class Instruccion{
	protected: string instruccion;
	public: 
			Instruccion(string s){instruccion = s;};
			string getInstruccion(){return instruccion;};
};

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
void Lista::impre(void)
{ Nodo *aux;
  aux=czo;
    while(aux->get_next()!=NULL){
         cout<<aux->get_dato()->getInstruccion()<<endl;
         aux=aux->get_next();
    }
}
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
      //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
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
//-------- Metodos de Cola --------------------
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


class Asignacion:public Instruccion{
	public:
		Asignacion(string s):Instruccion(s){};
		int buscaValor(Cola* lista, char c); //devuelve el valor de la variable asignada
		Nodo* buscaVar(Cola* lista, char c); //devulve el nodo de la variable a asignar
		void asigna(Cola* lista); // realiza la asignacion
};
/*-----------metodos asignacion--------------
int Asignacion::buscaValor(Cola *lista, char c){
	if(lista->tope().at(7)==c) 
		return lista->tope()
}
*/
void Asignacion::asigna(Cola* lista){
	string instruccion = getInstruccion();
	stringstream ss;
	int resultado;
	
	for(int i= 6; i<instruccion.size(); i++){ //lee la cedena despues del signo igual
		if(instruccion.at(i)>='a' && instruccion.at(i)<='z'){
			int valor = buscaVar(lista, instruccion.at(i))->getValor();
			ss << valor ;
		}
		else if(instruccion.at(i)!= 32) //agrega todos los caracteres que no sean el vacio
			ss << instruccion.at(i);

	}
	cout << "operacion" << ss.str();
	resultado = posfijoEntero(ss.str());
	cout <<"resultado: " << resultado;
	buscaVar(lista, this->getInstruccion().at(3))->setValor(resultado); //asigno valor a variable mas a la izquierda
	/*
	if(this->getInstruccion().at(7)>='0' && this->getInstruccion().at(7)<='9') //numero entero
		buscaVar(lista, this->getInstruccion().at(3))->setValor(this->getInstruccion().at(7)-'0');
	if(this->getInstruccion().at(7)>='a' && this->getInstruccion().at(7)<='z'){
		if(this->getInstruccion().size()-1 == 7){
			int v = buscaVar(lista, this->getInstruccion().at(7))->getValor(); //valor de la variable a la derecha
			buscaVar(lista, this->getInstruccion().at(3))->setValor(v); //asigno valor a variable mas a la izquierda	
		}
	}
	*/
}

Nodo* Asignacion::buscaVar(Cola* lista, char c){
	if(lista->ultimo()->get_dato()->getInstruccion().at(7) == c)
		return lista->ultimo();
	else buscaVar(lista->restoC(),c);	
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

	//Este bloque identifica las instrucciones
	while(!listaIns->esvacia()){
		if(listaIns->tope()->get_dato()->getInstruccion().at(3) == 'I' && listaIns->tope()->get_dato()->getInstruccion().at(4) == 'N'){
			cout << "Declaracion de variable" << endl;
			listaVar->encolar(listaIns->tope()->get_dato());	
		}	
		if(listaIns->tope()->get_dato()->getInstruccion().at(3) >= 'a' && listaIns->tope()->get_dato()->getInstruccion().at(3) <= 'z'){
			cout << "Asignacion" << endl;
			Asignacion* a= new Asignacion(listaIns->tope()->get_dato()->getInstruccion());
			//listaVar->impre();
			//cout << a->getInstruccion();
			a->asigna(listaVar);
			//cout << listaVar->tope()->getValor();
			//cout << listaVar->ultimo()->getValor();
		}
		if(listaIns->tope()->get_dato()->getInstruccion().at(3) == 'I' && listaIns->tope()->get_dato()->getInstruccion().at(4) == 'F')
			cout<<"Condicional" << endl;
		if(listaIns->tope()->get_dato()->getInstruccion().at(3) == 'J')
			cout << "Jump" << endl;
		if(listaIns->tope()->get_dato()->getInstruccion().at(3) == 'S')
			cout<<"Show" << endl;
	 	listaIns->desencolar();
	}
	
	
}


