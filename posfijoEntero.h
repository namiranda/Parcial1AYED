//#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

typedef long int tipolista;

class NodoE{
    protected: 
        tipolista dato;
        NodoE *next;
    public:
        NodoE() {next=NULL;};
        NodoE(tipolista a) {dato=a; next=NULL;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(NodoE *n) {next=n; };
        tipolista get_dato() {return dato; };
        NodoE *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class ListaE{
    protected: NodoE *czo;
    public:
            ListaE() {czo=new NodoE();};
            ListaE(NodoE *n) {czo=n;};
            void del(void);
            void add(tipolista d);
            bool esvacia(void);
            tipolista cabeza(void);
            ListaE *resto(void);
};

class Pila:public ListaE{
      public:
             Pila(){ListaE();};
             void apilar(tipolista x){add(x);};
             tipolista tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};
};                  


void ListaE::del(void)
{    NodoE *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void ListaE::add(tipolista d)
{  
     NodoE *nuevo=new NodoE(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool ListaE::esvacia(void)
{   
    return czo->es_vacio();
}

tipolista ListaE::cabeza(void)
{ 
  /*if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return ' '; 
  }*/
  return czo->get_dato();
}

ListaE *ListaE::resto(void)
{ 
      ListaE *l=new ListaE(czo->get_next());
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


int posfijoEntero(string cadena)
{
    string pf;
    Pila *p=new Pila();

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
//    if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK";
//    else cout<<endl<<"ERROR";
   
   // cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo    
      char d,p1;
      for(int j=0;j<cadena.length();j++)
      {   d=cadena.at(j);
	      if ((d>='0')&&(d<='9')){
             pf.push_back(d);
	      }else
	         { while((!p->pilavacia())&&(prcd(p->tope(),d)))
	                {p1=p->tope();p->desapilar();pf.push_back(p1);}
	           if((p->pilavacia())||(d!=')')) p->apilar(d);
		       else p->desapilar();
	      }
      }
      while(!p->pilavacia())
	      {p1=p->tope();p->desapilar();pf.push_back(p1);}
	      
//      cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;
      
// Evaluacion de la expresion en posfijo      
  int o1,o2;
  
  for(int i=0;(i<pf.length())&&(!error);i++){ 
     d=pf.at(i);
     if(d>='0' && d<='9') p->apilar(d-'0');
     if(d=='+'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               p->apilar(o1+o2);
     }
     if(d=='-'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               p->apilar(o1-o2);
     }        
     if(d=='*'){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               p->apilar(o1*o2);
     }              
  }

  return p->tope();
}

int posfijoBoolean(string cadena)
{
   	string pf;
    Pila *p=new Pila();
    bool resultado;

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
 //   if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK";
 //   else cout<<endl<<"ERROR";
   
  //  cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
//conversion de entrefijo a posfijo    
      char d,p1;
      for(int j=0;j<cadena.length();j++)
      {   d=cadena.at(j);
	      if ((d>='0')&&(d<='9'))pf.push_back(d);
	      else
	         {
	           if(p->pilavacia()) p->apilar(d);
		       else if(d=='=' || d=='!')p->apilar(d);
	      	 }
      }
      while(!p->pilavacia())
	      {p1=p->tope();p->desapilar();pf.push_back(p1);}
	      
    //  cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;
      
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
     		   if((pf.at(i-1)=='=')){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1==o2;
     }}
	  if(d=='!'){
	  		   if((pf.at(i-1)=='=')){
               o2=p->tope(); p->desapilar();
               o1=p->tope(); p->desapilar(); 
               resultado = o1!=o2;
     }}              
  }
 // cout<<endl<<"\n\nResultado= "<<resultado<<endl;
 // if(resultado){
 // 	cout<<endl<<"todo funciona OK"<<endl;
//  }
 
  return resultado;
}

