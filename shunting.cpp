#include <iostream>
#include <string>
#include "bignum.h"
using namespace std;

class stack{

  private:
    size_t tos_;
    size_t len_;
    string *ptr_;
  public:
	   stack();
	   stack(size_t);
	   ~stack();

	   string pull();
	   void push(const string &);
	   bool empty() const;
	   size_t length() const;
};


stack::stack()
	: tos_(0),
	  len_(0),
	  ptr_(0)
{
}

stack::stack(size_t len)
	: tos_(0),
	  len_(0),
	  ptr_(0)
{
	ptr_ = new string[len_ = len];
}

stack::~stack(){delete[] ptr_;}

string stack::pull(){return ptr_[--tos_];}

void stack::push(const string &top){ptr_[tos_++] = top;}

bool stack::empty() const{return tos_ == 0 ? true : false;}

size_t stack::length() const{return tos_;}

class queue{
  private:
    stack egress_;
    stack ingress_;
  public:
	  queue();
    queue(size_t);
	  queue &operator=(const queue &);
	  ~queue();

	  string pull();
	  void push(const string &);
	  bool empty() const;
	  size_t length() const;
};

queue::queue(){}

queue::queue(size_t len)
:
	egress_(len),
  ingress_(len)
{
}

queue::~queue(){}

string queue::pull()
{
	if (egress_.empty()) {
		while (ingress_.empty() == false)
			egress_.push(ingress_.pull());
	}
	return egress_.pull();
}

void queue::push(const string &item){ingress_.push(item);}

bool queue::empty() const{return egress_.empty() && ingress_.empty() ? true : false;}

size_t queue::length() const{return egress_.length() + ingress_.length();}


int main(){

  /*COMENTARIOS!! las pilas y colas andan bien pero habría que robustecerlas mucho más, no están contamplados muchos casos de error, eso
  lo puedo hacer, solo queria probar la funcionalidad en este caso. Lo mismo con SHUNTING YARD sólo lo probe con una cadena perfecta sin
  errores ni espacios, las validaciones las pensamos despues. Lo que necesito que alguien haga si o si es la parte marcada en ((1*)) */
  //cadena de prueba:
  string s = "(11a+2)/((38+5)*(2+3))";

/***********************SHUNTING YARD*********************************/
  size_t contador= 0;
  queue c(s.length());
  stack p(s.length());

  for(size_t i = 0; i < s.length(); i++){
      if('(' == s[i])
        contador = 0;


      string strchar;
      string num="";
      strchar.push_back(s[i]);

      while(strchar.find_first_of("0123456789") != string::npos)
      {
        num.push_back(s[i]);
        i++;
        strchar="";
        strchar.push_back(s[i]);
        if(strchar.find_first_of("0123456789") == string::npos){
          c.push(num);
          num = "";
        }
      }


      if((strchar.find_first_of("+-*/") != string::npos)){
        contador++;
        p.push(strchar);
      }


      if(')' == s[i])
        while(contador){
          //SI LA COLA ALMACENA BIGNUMS ENTONCES NO SE VA A PODER PULLEAR EL CONTENIDO DE LA PILA EN LA COLA
          //SE TIENE QUE IR REALIZANDO LA OPERACION A MEDIDA QUE SE EJECUTA SHUNTING YARD ASI NO SE ALMACENAN
          //CARACTERES DE OPERACION, SINO SOLAMENTE BIGNUMS!!
          c.push(p.pull());
          contador--;
        }
  }
  while(!p.empty())
    c.push(p.pull());

/*************************************************************************/

  cout << s << endl;
  for(size_t i = 0; i < 11; i++)
    cout << c.pull()<<endl;
  cout << endl;

/*
    stack p2(s.length());

    bignum res;
    bignum num1;
    bignum num2;
    char aux;

    for(size_t i = 0; i < s.length(); i++){
      //ACA LO MISMO, LA COLA ALMACENA BIGNUMS
      aux = c.pull();
      if( '0' == aux || '1' == aux || '2' == aux || '3' == aux || '4' == aux || '5' == aux || '6' == aux || '7' == aux || '8' == aux || '9' == aux){
        //ESTA PILA DEBERIA ALMACENAR BIGNUMS!!
        p2.push(aux);
      }
      //ESTE CODIGO FUE PENSADO PARA CUANDO LA COLA ALMACENABA CHARSSSS. ESTA PARTE DE DECISION DEL OPERADOR SE DEBE METER ADENTRO DE SHUNTING YARD
      if(aux=='+')
        num1 = p2.pull();
        num2 = p2.pull();
        res = num1 + num2;
        //p2.push(res);
      if(aux=='-')
        num1 = p2.pull();
        num2 = p2.pull();
        res = num1 - num2;
        //p2.push(res);
      if(aux=='*')
        num1 = p2.pull();
        num2 = p2.pull();
        res = num1 * num2;
        //p2.push(res);
    }
*/
  return 0;
}
