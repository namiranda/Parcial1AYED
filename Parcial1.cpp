#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

typedef string tipolista;

class Nodo{
    protected: 
        tipolista dato;
        Nodo *next;
    public:
        Nodo() {next=NULL;};
        Nodo(tipolista a) {dato=a; next=NULL;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        tipolista get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class NodoVar:public Nodo{
	protected:  
			int valor;
	public: NodoVar (tipolista n) {Nodo();};
			NodoVar() {Nodo();};
			void setValor(int v){valor = v;};
			int getValor(){return valor;};
			
};

class Lista{
    private: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            void add(tipolista d);
            bool esvacia(void);
            tipolista cabeza(void);
            Lista *resto(void);
            string toPrint(string p);   
            void impre(void);
            int size();
            void borrar(void); //borra la cabeza
            void borrar_last();//borra el ultimo
            void concat(Lista *l1);
            Lista *copy(void);
            void tomar(int n);
            tipolista last();
};

//-------- Metodos de Lista -------------------
tipolista Lista::last()
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
         cout<<aux->get_dato()<<endl;
         aux=aux->get_next();
    }
}
void Lista::add(tipolista d)
{  
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{   
    return czo->es_vacio();
}
tipolista Lista::cabeza(void)
{ 
  if(this->esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return " "; 
  }
  return czo->get_dato();
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
void Lista::concat(Lista *l1)
{// le transfiere los datos de l1 a this
   if (!(l1->esvacia())){
      this->concat(l1->resto());
      this->add(l1->cabeza());
   }
}


class Cola:public Lista{
  public:
      Cola(void){Lista();};
      ~Cola(void);
      tipolista tope();
      bool colavacia(){this->esvacia();};
      void encolar(tipolista a) ;
      void desencolar();
      tipolista ultimo();
      string imprimir(string s);
};
//-------- Metodos de Cola --------------------
tipolista Cola::tope(void)
{  return this->last();
}
void Cola::encolar(tipolista a)
{  this->add(a);
}
void Cola::desencolar(void)
{  this->borrar_last();
}
tipolista Cola::ultimo(void)
{   return this->cabeza();
}
string Cola::imprimir(string s)
{  return this->toPrint(s);
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
		listaIns->encolar(instruccion);
	
	}
	archivo.close();	
	
	//Este bloque identifica las instrucciones
	while(!listaIns->esvacia()){
		if(listaIns->tope().at(3) == 'I' && listaIns->tope().at(4) == 'N'){
			cout << "Declaracion de variable" << endl;
			listaVar->encolar(listaIns->tope());
			listaVar->impre();
				
		}	
		if(listaIns->tope().at(3) >= 'a' && listaIns->tope().at(3) <= 'z')
			cout << "Asignacion" << endl;
		if(listaIns->tope().at(3) == 'I' && listaIns->tope().at(4) == 'F')
			cout<<"Condicional" << endl;
		if(listaIns->tope().at(3) == 'J')
			cout << "Jump" << endl;
		if(listaIns->tope().at(3) == 'S')
			cout<<"Show" << endl;
	 	listaIns->desencolar();
	}
	
	
}

