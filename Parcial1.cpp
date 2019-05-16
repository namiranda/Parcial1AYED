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
            void concat(Lista *l1);
            
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
void Lista::concat(Lista *l1)
{// le transfiere los datos de l1 a this
   if (!(l1->esvacia())){
      this->concat(l1->resto());
      this->add(l1->cabeza()->get_dato());
   }
}
Lista *Lista::copy(void)
{ 
      Lista *aux=new Lista();
      aux->concat(this);
      return aux;
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
      Cola* copyC();
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
Cola *Cola::copyC(void)
{ 
      Cola *aux=new Cola();
      aux->concat(this);
      return aux;
}
//---------------------------------clase INSTRUCCION------------------------------------
class Instruccion{
	protected: string instruccion;
				int index;
	public: 
			Instruccion(string s, int i);
			string getInstruccion(){return instruccion;};
			int identificaIns();
			void ejecutaIns(int i, Cola* listaVar, Cola* listaAux );
			Nodo* buscaVar(Cola* lista, char c); //devulve el nodo de la variable a asignar
			int getIndice(){return index;}
};
Instruccion::Instruccion(string s, int i){
	instruccion = s;
	index = i;
}
int Instruccion::identificaIns(){
		string instruccion = getInstruccion();
		stringstream ss;
		
		for(int j=0; j<instruccion.size(); j++)
		 	if(instruccion.at(j)!= 32) //agrega todos los caracteres que no sean el vacio
				ss << instruccion.at(j);
		
		instruccion = ss.str();
		
		if(instruccion.at(0) == 'I' && instruccion.at(1) == 'N')//Declaracion de variable
			return 0; 
		if(instruccion.at(0) >= 'a' && instruccion.at(0) <= 'z')	//Asignacion;
			return 1;
		if(instruccion.at(0) == 'I' &&instruccion.at(1) == 'F') //Condicional;
			return 2;
		if(instruccion.at(0) == 'J')//Jump
			return 3;
		if(instruccion.at(0) == 'S'){	//Show
			return 4;
		}
}

Nodo* Instruccion::buscaVar(Cola* lista, char c){
	if(lista->ultimo()->get_dato()->getInstruccion().at(3) == c)
		return lista->ultimo();
	else buscaVar(lista->restoC(),c);	
}

//---------------------------------clase ASIGNACION------------------------------------
class Asignacion:public Instruccion{
	public:
		Asignacion(string s, int i):Instruccion(s, i){};
		void asigna(Cola* lista); // realiza la asignacion
};

void Asignacion::asigna(Cola* lista){
	string instruccion = getInstruccion();
	stringstream ss;
	int  resultado;
	
	for(int j=2; j<instruccion.size(); j++){ //lee la cedena despues del signo igual
		if(instruccion.at(j)>='a' && instruccion.at(j)<='z'){
			int valor = buscaVar(lista, instruccion.at(j))->getValor();
			ss << valor ;
		}
		else if(instruccion.at(j)!= 32){ //agrega todos los caracteres que no sean el vacio
			ss << instruccion.at(j);
		}
	}
	resultado = posfijoEntero(ss.str());
	cout<<"var = " << resultado << endl;
	buscaVar(lista, this->getInstruccion().at(0))->setValor(resultado); //asigno valor a variable mas a la izquierda
	
}
//--------------------------------clase CONDICIONAL---------------------------------
class Condicional:public Instruccion{
	public:
		Condicional(string s, int i):Instruccion(s,i){};
		bool evaluarCondicion(Cola* lista);
		int identificaThen();
};
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
	
	for(int j=11; j<instruccion.size(); j++){ //copia la instruccion despues del then
		ss<<instruccion.at(j);
	}
	return (new Instruccion(ss.str(),0))->identificaIns();
	
	
}
void leerInstrucciones(Cola* listaIns, Cola* listaVar);
//----------------------------------clase JUMP----------------------------------
class Salto:public Instruccion{
	public:
		Salto(string s,int i):Instruccion(s,i){};
		void saltar(Cola* listaVar, Cola* listaAux);
	
};
void Salto::saltar(Cola* listaVar, Cola* listaAux){
	int inicio;
	stringstream ss;
	for(int i=0; i<this->getInstruccion().size(); i++){
		if(getInstruccion().at(i) == 'P'){
			inicio = i+1;
		}
	}
	for(int j=inicio; j<this->getInstruccion().size();j++){
		ss <<getInstruccion().at(j);
	}
	int aux;
	ss >> aux;
	int posicion = static_cast<int>(aux);

	
	while(!listaAux->esvacia()){
		
		if(listaAux->tope()->get_dato()->getIndice()!=posicion){
			listaAux->desencolar();
		}
		if(listaAux->tope()->get_dato()->getIndice()==posicion){
			leerInstrucciones(listaAux, listaVar);
		}			
	}
}

//-----------------------------------clase SHOW---------------------------------
class Show:public Instruccion{
	public:
		Show(string s, int i):Instruccion(s, i){};
		void mostrar(Cola* listaVar);
	};
void Show::mostrar(Cola* listaVar){
	string instruccion = getInstruccion();
	stringstream ss;
	int resultado;
	
	for(int j=4 ; j<instruccion.size(); j++){ //lee lo que debe mostrar
		if(instruccion.at(j)>='a' && instruccion.at(j)<='z'){
			int valor = buscaVar(listaVar, instruccion.at(j))->getValor();
			ss << valor ;
		}
		else if(instruccion.at(j)!= 32){ //agrega todos los caracteres que no sean el vacio
			ss << instruccion.at(j);
		}
	}
	resultado = posfijoEntero(ss.str());
	
	cout<<resultado<< endl;
}
//-------------------------------------------------------------------------------------
void Instruccion::ejecutaIns(int i, Cola* listaVar, Cola* listaAux){
	switch(i){
			case 0:{ //Declaracion de variable
				listaVar->encolar(this);
				break;
			}
			case 1:{	//Asignacion
				Asignacion* a= new Asignacion(this->getInstruccion(),this->getIndice());
				a->asigna(listaVar);
				break;
			}
			case 2:{//condicional
				Condicional* c= new Condicional(this->getInstruccion(), this->getIndice());
				if(c->evaluarCondicion(listaVar)){
					ejecutaIns(c->identificaThen(), listaVar, listaAux);
				}
				break;
			}
			case 3:{ //jump
				Salto* s= new Salto(this->getInstruccion(), this->getIndice());
				s->saltar(listaVar, listaAux);
				break;
			}
			case 4:{//show
				Show* m = new Show(this->getInstruccion(), this->getIndice());
				m->mostrar(listaVar);
				break;
			}
		}
}
void leerInstrucciones(Cola* listaIns, Cola* listaVar){
	Cola* listaAux = listaIns->copyC();
	while(!listaIns->esvacia()){
		cout<<listaIns->tope()->get_dato()->getInstruccion() << endl;
		int i = listaIns->tope()->get_dato()->identificaIns();
		listaIns->tope()->get_dato()->ejecutaIns(i, listaVar, listaAux);
		listaIns->desencolar();
	}
	exit(0);
}
int main(){
	
	fstream archivo;
	string instruccion;
	Cola *listaIns = new Cola(); //puntero a lista con instrucciones
	Cola *listaVar = new Cola();
	int indice = 0;
	
	
	archivo.open("programa.txt", ios::in); //abre archivo en modo lectura
	
	if(archivo.fail()){
		cout << "No se pudo abrir el archivo";
		exit(1);
	}
	
	while(!archivo.eof()){ // mientras no sea el final del archivo
		getline(archivo, instruccion);
		stringstream ss;
		
		for(int j=0; j<instruccion.size(); j++)
		 	if(instruccion.at(j)!= 32) //agrega todos los caracteres que no sean el vacio
				ss << instruccion.at(j);
		
		instruccion = ss.str();
		indice++;
		listaIns->encolar(new Instruccion(instruccion, indice));
	}
	archivo.close(); 
	
	leerInstrucciones(listaIns, listaVar);
}
