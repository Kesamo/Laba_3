#pragma once
#include <concepts>
#include <initializer_list>
#include <stdexcept>
#include "Sequence.hpp"
#include "SequenceArray/MutableSequenceArray.hpp"

template <typename Storage, class T>
concept DequeConcept = requires(Storage cont, const Storage constcont, T item){
    Storage{};
    Storage{constcont};

    cont.append(item);
    cont.prepend(item);
    cont.RemoveLast();
    cont.RemoveFirst(); 

    {constcont.GetLength()} -> std::convertible_to<size_t>;
    {constcont.GetLast()} -> std::convertible_to<T>;
    {constcont.GetLast()} -> std::convertible_to<T>;

    constcont.begin();
    constcont.end();
};

template<template<class> class Storage, class T>
requires DequeConcept<Storage<T>, T>
class Deque{
private:
    Storage<T> data;

public:
    Deque() = default;
    Deque(const std::initializer_list<T> init);
    Deque(const Storage<T>& other);
    Deque(T* item, size_t count);

    T front();
    T back();

    void push_back(const T& value);
    void push_front(const T& value);

    T pop_back();
    T pop_front();

    bool empty() const;
    size_t size() const;

    auto map(T (*func)(T)) const;
    auto where(bool (*pred)(T)) const;
    auto reduce(T (*func)(T, T), T starter) const;

    auto Concat(const Deque& other) const;
    auto GetSubsequence(size_t startIndex, size_t endIndex) const;
    // bool serch(Stack<Storage, T> sub) const;

    auto begin();
    auto end();

    auto begin() const;
    auto end() const;

};

#include "Deque.tpp"