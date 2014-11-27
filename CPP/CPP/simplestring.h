/*
 *For practicing the exercises of The C++ Programming language
 *Author: Tao HE
 *Date: May 3th, 2014
 *
*/

#ifndef SIMPLESTRING_H
#define SIMPLESTRING_H


#include <string>
#include <iostream>


namespace simplestd{
class String {
    struct Srep{
        char *s;
        int sz;
        int n;

        Srep(int nsz, const char *p){
            n = 1;
            sz = nsz;
            s = new char[sz+1];
            strcpy(s,p);
        }

        ~Srep(){
            delete[] s;
        }

        Srep* get_own_copy(){
            if(n == 1) return this;
            n--;
            return new Srep(sz,s);
        }

        void assign(int nsz,const char *p){
            if(sz != nsz){
                delete[] s;
                sz = nsz;
                s = new char[sz+1];
            }
            strcpy(s,p);
        }

    private:
        Srep(const Srep&);
        Srep& operator =(const Srep&);
    };
    Srep *rep;
public:
    class Cref{
        friend class String;
        String &s;
        int i;
        Cref(String &ss, int ii) : s(ss), i(ii){}
    public:
        operator char() const {
            return s.read(i);
        }

        void operator =(char c) {
            s.write(i,c);
        }
    };
    class Range {};
    String();
    String(const char*);
    String(const String&);
    String& operator =(const char*);
    String& operator =(const String&);
    String& operator +=(const String&);
    String& operator +=(const char*);
    friend std::ostream& operator <<(std::ostream &os, const String &x){
        os<<x.rep->s<<std::endl;
        return os;
    }
    friend std::istream& operator >>(std::istream &is, const String &x){
        is>>x.rep->s;
        return is;
    }
    friend bool operator ==(const String &x, const char *s){
        return strcmp(x.rep->s,s) == 0;
    }
    friend bool operator ==(const String &x, const String &y){
        return strcmp(x.rep->s,y.rep->s) == 0;
    }
    friend bool operator !=(const String &x, const char *s){
        return strcmp(x.rep->s,s) != 0;
    }
    friend bool operator !=(const String &x, const String &y){
        return strcmp(x.rep->s,y.rep->s) != 0;
    }

    ~String();

    void check(int i) const {
        if(i<0 || rep->sz<=i)
            throw Range();
    }

    char read(int i) const {
        return rep->s[i];
    }

    void write(int i,char c){
        rep = rep->get_own_copy();
        rep->s[i] = c;
    }

    Cref operator [](int i){
        check(i);
        return Cref(*this,i);
    }

    char operator [](int i) const {
        check(i);
        return rep->s[i];
    }

    int size() const {
        return rep->sz;
    }
 };
}

#endif // SIMPLESTRING_H
