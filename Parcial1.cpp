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

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            void del(void);
            void add(tipolista d);
            bool esvacia(void);
            tipolista cabeza(void);
            Lista *resto(void);
            Nodo *last(void);
            void borrarLast();
            string toPrint(string p);
};

class Pila:public Lista{
      public:
             Pila(){Lista();};
             void apilar(tipolista x){add(x);};
             tipolista tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};
};

//-----------------metodos de Lista-------------------------

void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void Lista::add(tipolista d) //agrega un nodo al final de la lista
{
	Nodo *nuevo=new Nodo(d);
	last()->set_next(nuevo);

}
bool Lista::esvacia(void)
{
    return czo->es_vacio();
}

tipolista Lista::cabeza(void)
{
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return "" ;
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{
      Lista *l=new Lista(czo->get_next());
      return (l);
}

// funcion precedencia
// prcd(o1,'(') = 0 para todo o1 != de ')'
// prcd(o1,')') = 1 para todo o1 != de '('
// prcd('(',o2) = 0 para todo 02
// prcd(o1,o2)  = 1 para todo o1 >= precedencia que o2
int prcd(int o1,int o2)
{ if(o2=='(')
	 if(o1==')') return 1;
            else return 0;
  if(o2==')')
	 if(o1=='(') return 0;
		    else return 1;
  if(o1=='(') return 0;

  if((o1=='*')||(o1=='/')) return 1;
  if(((o1=='+')||(o1=='-'))&&((o2=='+')||(o2=='-'))) return 1;
						                        else return 0;
}

string Lista::toPrint(string p){
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<endl<< this->resto()->toPrint(p);

       return stm.str();
     }
}
Nodo* Lista::last(void){
	if(czo->get_next()==NULL) return czo;
	else resto()->last();
}

//------------------Fin metodos de lista----------------------------

int main(){
	fstream archivo;
	string instruccion;
	Lista *listaIns = new Lista(); //puntero a lista con instrucciones

	archivo.open("programa.txt", ios::in); //abre archivo en modo lectura

	if(archivo.fail()){
		cout << "No se pudo abrir el archivo";
		exit(1);
	}

	while(!archivo.eof()){ // mientras no sea el final del archivo
		getline(archivo, instruccion);
		listaIns->add(instruccion);
	}
	//cout<<listaIns->cabeza();
	cout<<listaIns->toPrint("fin");
	cout<< listaIns->last()->get_dato();

	archivo.close();


}
