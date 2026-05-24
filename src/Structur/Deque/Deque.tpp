#include "Deque.hpp"

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
Deque<Storage, T>::Deque(const std::initializer_list<T> init) {
    for(auto item : init){
        data.append(item);
    }
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
Deque<Storage,T>::Deque(const Storage<T>& other) : data(other) {}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
T Deque<Storage, T>::back() {
    if(data.GetLength() == 0){
        //TODO:Обработка ошибки
    }
    return data.GetLast();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
T Deque<Storage, T>::front() {
    if(data.GetLength() == 0){
        //TODO:Обработка ошибки
    }
    return data.GetFirst();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
T Deque<Storage, T>::pop_back() {
    if(data.GetLength() == 0){
        //TODO:Обработка ошибки
    }
    T val = data.GetLast();
    data.RemoveLast();
    return val;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
T Deque<Storage, T>::pop_front() {
    if(data.GetLength() == 0){
        //TODO:Обработка ошибки
    }
    T val = data.GetFirst();
    data.RemoveFirst();
    return val;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
void Deque<Storage, T>::push_front(const T& value){
    data.prepend(value);
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
void Deque<Storage, T>::push_back(const T& value){
    data.append(value);
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
bool Deque<Storage, T>::empty() const{
    return data.GetLength() == 0;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
size_t Deque<Storage, T>::size() const{
    return data.GetLength();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage, T>::map(T (*func)(T)) const{
    Deque<Storage,T> res;
    for(auto item : data){
        res.push_back(func(item));
    }
    return res;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage,T>::where(bool (*pred)(T)) const{
    Deque<Storage, T> res;
    for(auto item : data){
        if(pred(item)){
            res.push_back(item);
        }
    }
    return res;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage,T>::reduce(T (*func)(T, T), T starter) const{
    T res = starter;
    for(auto item : data){
        res = func(res, item);
    }
    return res;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage,T>::Concat(const Deque& other) const {
    Deque res;
    for (auto item : data){
        res.push_back(item);
    }
    for (auto item : other.data){
        res.push_back(item);
    }
    return res;
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage,T>::GetSubsequence(size_t startIndex, size_t endIndex) const {
    if (startIndex > endIndex || endIndex >= size()){
        throw InvalidRangeException(startIndex, endIndex);
    }
    Deque res;
    size_t i = 0;
    for (auto item : data){
        if (i > endIndex){
            break;
        }
        if (i >= startIndex){
            res.push_back(item);
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
requires DequeConcept<Storage<T>, T>
auto Deque<Storage, T>::begin(){
    return data.begin();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage, T>::end(){
    return data.end();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage, T>::begin() const{
    return data.begin();
}

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
auto Deque<Storage, T>::end() const{
    return data.end();
}