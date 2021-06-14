#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include "bignum.h"
#include "shunting.h"
using namespace std;


bool contains(string s, string cont){
  if(s.find_first_of(cont) != string::npos){
    return true;
  }else
    return false;
}

size_t count_op(stack<string> s){
  size_t count=0;
  stack<string> aux;

  while(!s.empty()){
    if(contains(s.top(),"+-*/")){
      aux.push(s.top());
      s.pop();
      count++;
    }else{
      aux.push(s.top());
      s.pop();
    }
  }

  while(!aux.empty()){
    s.push(aux.top());
    aux.pop();
  }

  return count;
}

size_t count_num(stack<string> s){
  size_t count=0;
  stack<string> aux;

  while(!s.empty()){
    if(contains(s.top(),"0123456789")){
      aux.push(s.top());
      s.pop();
      count++;
    }else{
      aux.push(s.top());
      s.pop();
    }
  }

  while(!aux.empty()){
    s.push(aux.top());
    aux.pop();
  }

  return count;
}

stack<string> shunting_yard(string &s){
  queue<string> c;
  stack<string> p;
  string strchar="", num="";

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
        if(!contains(strchar,")0123456789")){ //Si atras no tiene numeros ni ')'
          num+="-";
          strchar="";
          continue;
        }else {//si tiene numeros atras o ')'
          strchar="";
          strchar.push_back(s[i]);
          if(!p.empty() && strchar=="-"){
            if(contains(p.top(),"+-*/")&&!contains(p.top(),"0123456789")){
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

      if(contains(strchar,"0123456789")){

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


      if(contains(strchar,"+*/")){

        if(!p.empty() && strchar=="+"){
          if(contains(p.top(),"+-*/")&&!contains(p.top(),"0123456789")){
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

  stack<string> operacion;
  stack<string> aux;

  while(!c.empty()){
    aux.push(c.front());
    cout<<aux.top()<<endl;
    c.pop();
  }

  while(!aux.empty()){
    operacion.push(aux.top());
    aux.pop();
  }

  return operacion;
}

string operate(stack<string> operacion){

  bignum res;
  stack<string> aux;
  //stack<string> resultados;
  bignum a;
  bignum b;

  if(count_num(operacion)==1){
    while(!operacion.empty()){
      if(contains(operacion.top(),"0123456789")){
        return operacion.top();
      }
      operacion.pop();
    }
  }


  while(operacion.size()!=1){
    res.set_signo(true);
    a.set_signo(true);
    a.set_signo(true);

    if(contains(operacion.top(),"0123456789")){

      aux.push(operacion.top());
      operacion.pop();

      if(contains(operacion.top(),"0123456789")){
        aux.push(operacion.top());
        operacion.pop();

        if(contains(operacion.top(),"+-*/")&&!contains(operacion.top(),"0123456789")){
          a=aux.top();
          aux.pop();
          b=aux.top();
          aux.pop();

          if(operacion.top()=="+"){
            res= a+b;
            operacion.pop();
            operacion.push(res.to_string());
          }else if(operacion.top()=="-"){
            res= b-a;
            operacion.pop();
            operacion.push(res.to_string());
          }else if(operacion.top()=="*"){
            res= a*b;
            operacion.pop();
            operacion.push(res.to_string());
          }else if(operacion.top()=="/"){
            res=b/a;
            operacion.pop();
            operacion.push(res.to_string());
          }
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
