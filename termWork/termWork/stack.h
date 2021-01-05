#pragma once
#include "elem.h"
#ifndef STACK_H
#define STACK_H
template <class T>
class stack {
private:
    size_t size;
    elem<T>* top;
public:
    stack() {
        size = 0;
        top = nullptr;
    }

    ~stack() {
        clear();
    }

    elem<T>* getTop() {
        return top;
    }

    void pop()
    {
        elem<T>* temp = top;
        top = top->getNext();
        delete temp;
        size--;
    }

    void push(T value) {
        top = new elem<T>(value, top);
        size++;
    }

    size_t getSize() {
        return size;
    }
    bool isEmpty() {
        if (size == 0) return true;
        else return false;
    }

    void clear() {
        while (!isEmpty()) pop();
    }

};

#endif // !STACK_H
