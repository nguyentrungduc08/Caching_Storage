/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArrayList.h
 * Author: nguyentrungduc
 *
 * Created on July 15, 2018, 12:08 PM
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <memory>
#include <stdio.h>      /* printf */
#include <math.h>       /* log */

template<class T>
class ArrayList {
private:
    T                       *m_buffer;
    std::size_t             m_size;
    std::size_t             m_capacity;
    unsigned int            m_capacity_inc;
    unsigned int            m_Log;

public:
    /* default constructor */
    explicit ArrayList();
    
    explicit ArrayList(unsigned int size);

    /* capacity info functions */
    std::size_t size() const; 
    std::size_t capacity() const;
    unsigned int Log(); 
    bool empty() const;

    /* modifier functions*/
    void push_back(const T &t);
    void pop_back();
    void clear();

    /* iterator functions*/
    T* begin();
    T* end();

    void resize(std::size_t new_size);

    /* element access*/
    /* @node: handle invalid index*/
    T& operator[](int index){
        return this->m_buffer[index];
    }

    ArrayList<T> & operator = (const ArrayList<T> &);

    void reserve(unsigned int capacity);
    
    virtual ~ArrayList(){
    }
};


/* defaule ArrayList constructor, with an empty array allocated of 0 size. */
template<class T>
ArrayList<T>::ArrayList(){
    this->m_size = 0;
    this->m_capacity = 0;
    this->m_capacity_inc = 1;
    this->m_buffer = NULL;
}

template<class T>
ArrayList<T>::ArrayList(unsigned int size) {
    this->m_size = size;
    this->m_Log = ceil(log((double) size) / log(2.0)); // caculate newsize >= size
    this->m_capacity = 1 << this->m_Log;
    this->m_buffer = new T[this->m_capacity];
    this->m_capacity_inc = 1;
}

/* capacity private member getter*/
template<class T>
std::size_t 
ArrayList<T>::capacity() const {
    return this->m_capacity;
}

/* size private membet getter*/
template<class T>
std::size_t 
ArrayList<T>::size() const {
    return this->m_size;
}

/* check is arrayList is empty */
template<class T>
bool
ArrayList<T>::empty() const {
    return this->m_size == 0;
}

template<class T>
T*
ArrayList<T>::begin() {
    return this->m_buffer;
}

template<class T>
T*
ArrayList<T>::end() {
    return this->m_buffer + this->size();
}

template<class T>
void
ArrayList<T>::push_back(const T &t){
    if (this->m_size >= this->m_capacity){
        this->reserve(1 << this->m_Log);    
        ++this->m_Log;
    }
    this->m_buffer[this->m_size++] = t;
}

/* increase size of arraylist when full capacity*/
template<class T>
unsigned int 
ArrayList<T>::Log(){ 
    return this->m_Log;
}

/* realocate new size of array and copy data from old memory*/
template<class T>
void 
ArrayList<T>::reserve(unsigned int capacity) {
    T *newBuffer = new T[capacity];

    for (unsigned int i = 0; i < this->m_size; ++i)
        newBuffer[i] = this->m_buffer[i];

    this->m_capacity = capacity;
    delete[] this->m_buffer;
    this->m_buffer = newBuffer;
}

/* overload operator = for assign 2 arraylist*/
template<class T>
ArrayList<T>& ArrayList<T>::operator = (const ArrayList<T> & arr) {
    delete[] this->m_buffer;
    this->m_size = arr.size();
    this->m_Log = arr.Log();
    this->m_capacity = arr.capacity();
    this->m_buffer = new T [this->m_capacity];
    for (unsigned int i = 0; i < arr.size(); ++i)
        this->m_buffer[i] = arr[i];
    return *this;
}


#endif /* ARRAYLIST_H */
