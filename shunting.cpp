#include "shunting.h"
using namespace std;

stack<string>* shunting_yard(string &s){
  queue<string> c;
  stack<string> p;
  string strchar, num;

  for(size_t i = 0; i < s.length(); i++){
      if('(' == s[i]){
        p.push("(");
        continue;
      }

      if(s[i]=='-'&& i==0){
          num+="-";
          continue;
      }

      if(s[i]=='-'&& i>0){
        strchar.push_back(s[i-1]);
        if(!contains(strchar, "(0123456789")){ //Si atras no tiene numeros
          cout<<"hola"<<endl;
          if(num[0]=='-'){
            num[0]='+';
            strchar="";
            continue;
          }
          num+="-";
          strchar="";
          continue;
        }else {//si tiene numeros atras o ')'
          strchar="";
          strchar.push_back(s[i]);
          if(!p.empty() && strchar=="-"){
            if(contains(p.top(),"+-*/")&&!contains(p.top(),NUMBERS)){
              while(!p.empty()){
                if(p.top()=="(")
                  break;
                c.push(p.top());
                p.pop();
              }
              p.push(strchar);
              strchar="";
              continue;
            }
          }
          p.push("-");
          strchar="";
          continue;
        }
      }

      strchar.push_back(s[i]);

      if(contains(strchar,NUMBERS)){

        num+=strchar;
        strchar="";
        if(i!=s.length()-1){
          strchar.push_back(s[i+1]);
          if(!contains(strchar,")+-*/")){
            strchar="";
            continue;
          }else{
            c.push(num);
            strchar="";
            num="";
            continue;
          }
        }else{
          c.push(num);
          strchar="";
          num="";
          continue;
        }
      }

      if(contains(strchar,OPERATORS)){

        if(!p.empty() && strchar=="+"){
          if(contains(p.top(),"+-*/")&&!contains(p.top(),NUMBERS)){
            while(!p.empty()){
              if(p.top()=="(")
                break;
              c.push(p.top());
              p.pop();
            }
            p.push(strchar);
            strchar="";
            continue;
          }
        }
        p.push(strchar);
        strchar="";
        continue;
      }

      if(s[i] == ')'){
        while(p.top()!="("){
          c.push(p.top());
          p.pop();
        }
        p.pop();
        strchar="";
      }
  }

  while(!p.empty()){
    c.push(p.top());
    p.pop();
  }

  stack<string> *operacion= new stack<string>();
  stack<string> aux;

  while(!c.empty()){
    aux.push(c.front());
    cout<<aux.top()<<endl;
    c.pop();
  }

  while(!aux.empty()){
    operacion->push(aux.top());
    aux.pop();
  }

  return operacion;
}

string operate(stack<string>& operacion, string metodo){

  bignum res;
  bignum a;
  bignum b;
  stack<string> aux;

  if(metodo==METHOD_KARATSUBA){
    a.set_mult_strategy(new karatsuba());
  }else{//Por default se usa el metodo standard
    a.set_mult_strategy(new standard());
  }

  if(count_num(operacion)==1){
    while(!operacion.empty()){
      if(contains(operacion.top(),NUMBERS)){
        return operacion.top();
      }
      operacion.pop();
    }
  }

  while(operacion.size()!=1){
    res = "+0";
    a = "+0";
    b = "+0";

    if(contains(operacion.top(),NUMBERS)){
      aux.push(operacion.top());
      operacion.pop();

      if(contains(operacion.top(),NUMBERS)){
        aux.push(operacion.top());
        operacion.pop();

        if(!contains(operacion.top(),NUMBERS)){
          b=aux.top();
          aux.pop();
          a=aux.top();
          aux.pop();

          if(operacion.top()=="+"){
            res= a+b;
            operacion.pop();
            operacion.push(res.to_string());
          }else if(operacion.top()=="-"){
            res= a-b;
            operacion.pop();
            operacion.push(res.to_string());
          }else if(operacion.top()=="*"){
              res = a * b;
              operacion.pop();
              operacion.push(res.to_string());
          }else if(operacion.top()=="/"){
            res=a/b;
            operacion.pop();
            operacion.push(res.to_string());
          }
          cout<<res<<endl;
        }else{
          operacion.push(aux.top());
          aux.pop();
          continue;
        }
      }else{
        //error no hay 2 numeros seguidos
      }
    }

    while(!aux.empty()){
      operacion.push(aux.top());
      aux.pop();
    }

  }
  return res.to_string();
}
