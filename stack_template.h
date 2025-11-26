#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <iostream>

using namespace std;

template <class T>
class stack{
private:
    int n, cap; // size va capacity
    T *st;
public:
    stack(){
        n = cap = 0;
        st = nullptr;
    }
    void push(T x){
        if (cap == n){
            cap = (cap == 0) ? 1 : cap*2;
            T *st_new = new T[cap];
		for(int i = 0 ; i < n; i++){
			st_new[i] = st[i];
		}
		delete[] st;
		st = st_new;
        }        
        st[n++] = x;
    }

    T top(){
        return st[n - 1];
    }

    void pop(){
        n--;
    }

    bool empty(){
        return n == 0;
    }
    
    ~stack() {
	    delete[] st;
	}
};

#endif
