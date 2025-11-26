#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <iostream>
using namespace std;

template <class T>
class Iterator{
    T* curr;
public:
    Iterator(T* c = nullptr) : curr(c) {}

    Iterator<T> &operator = (Iterator<T> it){
        curr = it.curr;
        return *this;
    }
    
    Iterator<T> &operator ++ (){
    	curr++;
    	return *this;	
	}

	Iterator<T> &operator = (const Iterator<T>& it){
		curr = it.curr;
		return *this;
	}

	Iterator<T> operator ++ (int){
		Iterator<T> temp = *this;
		curr++;
		return temp;
	}
	T& operator*() {
        return *curr;
    }
    
    bool operator !=(const Iterator<T>& it) const {
	return curr != it.curr;
	}
	
	int operator-(const Iterator<T>& other) const {
	    return curr - other.curr;
	}
};


template <class T>
class Vector {
private:
    int capacity,size;
    T *vector;
public:
    Vector(){
    	capacity = size = 0;
    	vector = 0;
	}
	Vector(int n, T a = T()){
		capacity = size = n;
		vector = new T[capacity];
		for(int i = 0; i < size; i++){
			vector[i] = a;
		}
	}
	
	Vector(const Vector &other) {
	    size = other.size;
	    capacity = other.capacity;
	    if (capacity) {
	        vector = new T[capacity];
	        for (int i = 0; i < size; i++) {
	            vector[i] = other.vector[i];
	        }
	    } else {
	        vector = nullptr;
	    }
	}
	
	int Size(){
		return size;
	}
	
	void double_the_capacity() {
	    if (capacity == 0)
	        capacity = 1;
	    else
	        capacity *= 2;
	
	    T *temp = new T[capacity];
	    for (int i = 0; i < size; i++)
	        temp[i] = vector[i];
	    delete[] vector;
	    vector = temp;
	}
	
	void push_back(T value) {
	    if (size == capacity)
	        double_the_capacity();
	    vector[size] = value;
	    size++;
	}
	
	void pop_back (){
		if(size > 0)
		size--;
	}
	
	void insert(int k, T x){
	    if(size == capacity) {
	        if (capacity == 0) {
	            capacity = 1;
	            vector = new T[capacity];
	        } else {
	            double_the_capacity();
	        }
	    }
	    
	    for(int i = size - 1; i >= k; i--){
	        vector[i+1] = vector[i];
	    }	    
	    vector[k] = x;
	    size++;
	}
	
	void resize(int n, T x = T()){
		if(n > capacity){
			T *newVec = new T[n];
			for(int i = 0; i < size; i++){
				newVec[i] = vector[i]; 
			}
			for(int i = size ; i < n; i++){
				newVec[i] = x; 
			}			
			delete[] vector;
			vector = newVec;
			size = capacity = n;
		}
		else{
            if (n > size) {
                for (int i = size; i < n; i++)
                    vector[i] = x;
            }
            size = n;
		}
	}
	
	Vector& operator = (const Vector &other){
	    if (this == &other) return *this;
	    delete[] vector;	
	    size = other.size;
	    capacity = other.capacity;
	    if (capacity) {
	        vector = new T[capacity];
	        for(int i = 0 ; i < size; i++){
	            vector[i] = other.vector[i];
	        }
	    } 
		else {
	        vector = nullptr;
	    }
	    return *this;
	}
	
	Iterator<T> begin() {
		return vector;
	}
	Iterator<T> end(){
		return vector+size;
	}
	
	T& operator[](int index) {
	    return vector[index];
	}
	
	const T& operator[](int index) const {
	    return vector[index];
	}
	
	Iterator<T> find (const T &value){
	    for(Iterator <T> it = begin(); it != end(); ++it){
	        if(*it == value){
	            return it;
	        }
	    }
	    return end();
	}
	
    ~Vector(){
        delete[] vector;
    }
};

#endif
