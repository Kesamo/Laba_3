#include "Stack.hpp"

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
Stack<Storage, T>::Stack(const std::initializer_list<T> init) {
    for(auto item : init){
        data.append(item);
    }
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
Stack<Storage,T>::Stack(const Storage<T>& other) : data(new Storage<T>(other)) {}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
T Stack<Storage, T>::top() {
    if(data.GetLength() == 0){
        //TODO:Обработка ошибки
    }
    return data.GetLast();
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
T Stack<Storage, T>::pop(){
    T value = data.GetLast();
    data.RemoveLast();
    return value;

}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
void Stack<Storage, T>::push(const T& value){
    data.append(value);
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
bool Stack<Storage, T>::empty() const{
    return data.GetLength() == 0;
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
size_t Stack<Storage, T>::size(){
    return data.GetLength();
}