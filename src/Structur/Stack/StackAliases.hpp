#pragma once
#include "MutableSequenceArray.hpp"
#include "MutableSequenceList.hpp"
#include "Stack.hpp"

template<typename T>
using ArrayStack = Stack<MutableSequenceArray, T>;

template<typename T>
using ListStack  = Stack<MutableSequenceList, T>;