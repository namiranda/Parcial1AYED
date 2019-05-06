#include <iostream>
#include <sstream>

using namespace std;

typedef long int tipolista;

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
};

class Pila:public Lista{
      public:
             Pila(){Lista();};
             void apilar(tipolista x){add(x);};
             tipolista tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};
};                  


void Lista::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
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
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return ' '; 
  }
  return czo->get_dato();
}

Lista *Lista::resto(void)
{ 
      Lista *l=new Lista(czo->get_next());
      return (l);
}
int main()
{
    string cadena,pf;
    Pila *p=new Pila();
    bool resultado;

  cout<<endl<<"Ingrese expresion= "; cin>>cadena;
// chequeo de la correspondencia de los ()  
  int error=0;
  for(int i=0;(i<cadena.length())&&(!error);i++){
          if (cadena.at(i)=='{') p->apilar('{');       
          if (cadena.at(i)=='[') p->apilar('[');
          if (cadena.at(i)=='(') p->apilar('(');
          
          if (cadena.at(i)=='}'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='{') error=1;
                                     else p->desapilar();                     
          }                               
          if (cadena.at(i)==']'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='[') error=1;
                                     else p->desapilar();                     
          }                               
          if (cadena.at(i)==')'){
                                 if (p->pilavacia()) error=1;
                                 else
                                     if(p->tope()!='(') error=1;
                                     else p->desapilar();                     
          }                               
    }  
    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK";
    else cout<<endl<<"ERROR";
   
    cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo    
      char d,p1;
      for(int j=0;j<cadena.length();j++)
      {   d=cadena.at(j);
	      if (d!='>' || d!='<' || d!= '!' || d!='='){
             pf.push_back(d);
	      }else
	         { while((!p->pilavacia()))
	                {p1=p->tope();p->desapilar();pf.push_back(p1);}
	           if((p->pilavacia())||(d!=')')) p->apilar(d);
		       else p->desapilar();
	      }
      }
      while(!p->pilavacia())
	      {p1=p->tope();p->desapilar();pf.push_back(p1);}
	      
      cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;
      
// Evaluacion de la expresion en posfijo      
  int o1,o2;
  
  for(int i=0;(i<pf.length())&&(!error);i++){ 
     d=pf.at(i);
     if(d>='0' && d<='9') p->apilar(d-'0');
     if(d=='>'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1>o2;
     }
     if(d=='<'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1<o2;
     }        
     if(d=='='){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1==o2;
     }
	  if(d=='!'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1!=o2;
     }              
  }
  cout<<endl<<"\n\nResultado= "<<resultado<<endl;
 
  cout<<endl;
  system("PAUSE");
  return 0;
}
