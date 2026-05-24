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
Stack<Storage,T>::Stack(const Storage<T>& other) : data(other) {}

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
size_t Stack<Storage, T>::size() const{
    return data.GetLength();
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage, T>::map(T (*func)(T)) const{
    Stack<Storage,T> res;
    for(auto item : data){
        res.push(func(item));
    }
    return res;
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage,T>::where(bool (*pred)(T)) const{
    Stack<Storage, T> res;
    for(auto item : data){
        if(pred(item)){
            res.push(item);
        }
    }
    return res;
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage,T>::reduce(T (*func)(T, T), T starter) const{
    T res = starter;
    for(auto item : data){
        res = func(res, item);
    }
    return res;
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage,T>::Concat(const Stack& other) const {
    Stack res;
    for (auto item : data){
        res.push(item);
    }
    for (auto item : other.data){
        res.push(item);
    }
    return res;
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage,T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= size()){
        throw InvalidRangeException(startIndex, endIndex);
    }
    Stack res;
    size_t i = 0;
    for (auto item : data){
        if (i > endIndex){
            break;
        }
        if (i >= startIndex){
            res.push(item);
        }
        ++i;
    }
    return res;
}

// template<template<class> class Storage, class T>
// requires StackConcept<Storage<T>, T>
// bool Stack<Storage, T>::serch(Stack<Storage, T> sub) const{
//     if (sub.size() > size()) return false;
//     if (sub.empty()) return true;
    
//     size_t n = size();
//     size_t m = sub.size();

//     for(size_t  start = 0; start + m <= n; ++start){
//         bool flag = true;
//         size_t i = 0;
//         for(auto x : c){
//         }
//     }

// }

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage, T>::begin(){
    return data.begin();
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage, T>::end(){
    return data.end();
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage, T>::begin() const{
    return data.begin();
}

template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
auto Stack<Storage, T>::end() const{
    return data.end();
}