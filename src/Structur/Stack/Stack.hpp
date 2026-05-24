#pragma once
#include <concepts>
#include "Sequence.hpp"
#include "SequenceArray/MutableSequenceArray.hpp"

template <typename Storage, class T>
concept StackConcept = requires(Storage cont, const Storage constcont, T item){
     Storage{};
     Storage{constcont};

     cont.append(item);
     cont.RemoveLast();

     {constcont.GetLength()} -> std::convertible_to<size_t>;
     {constcont.GetLast()} -> std::convertible_to<T>;

     constcont.begin();
     constcont.end();
};


template<template<class> class Storage, class T>
requires StackConcept<Storage<T>, T>
class Stack{
private:
     Storage<T> data;

public:
     Stack() = default;
     Stack(const std::initializer_list<T> init);
     Stack(const Storage<T>& other);
     Stack(T* item, size_t count);

     T top();
     T pop();
     void push(const T& value);
     bool empty() const;
     size_t size() const;

     auto map(T (*func)(T)) const;
     auto where(bool (*pred)(T)) const;
     auto reduce(T (*func)(T, T), T starter) const;

     auto Concat(const Stack& other) const;
     auto GetSubsequence(size_t startIndex, size_t endIndex) const;
     // bool serch(Stack<Storage, T> sub) const;

     auto begin();
     auto end();

     auto begin() const;
     auto end() const;

};

#include "Stack.tpp"