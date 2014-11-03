/*
 *For practicing the exercises of The C++ Programming language
 *Author: Tao HE
 *Date: May 3th, 2014
 *
*/

#include "simplestring.h"

using namespace std;
using namespace simplestd;

String::String(){
    rep = new Srep(0,"");
}

String::String(const String &x){
    x.rep->n++;
    rep = x.rep;
}

String::~String(){
    if(--rep->n == 0) delete rep;
}

String& String::operator =(const String &x){
    x.rep->n++;
    if(--rep->n == 0) delete rep;
    rep = x.rep;
    return *this;
}

String::String(const char* s){
    rep = new Srep(strlen(s),s);
}

String& String::operator =(const char* s){
    if(rep->n == 1)
        rep->assign(strlen(s),s);
    else{
        rep->n--;
        rep = new Srep(strlen(s),s);
    }
    return *this;
}

String& String::operator +=(const String &x){
    if(x.rep->sz == 0)
        return *this;
    int len = size() + x.size();
    char *p = new char[len+1];
    strcpy(p,rep->s);
    strcat(p,x.rep->s);
    if(--rep->n == 0) delete rep;
    rep = new Srep(len,p);
    return *this;
}

String& String::operator +=(const char *s){
    if(strlen(s) == 0)
        return *this;
    int len = size() + strlen(s);
    char *p = new char[len+1];
    strcpy(p,rep->s);
    strcat(p,s);
    if(--rep->n == 0) delete rep;
    rep = new Srep(len,p);
    return *this;
}




