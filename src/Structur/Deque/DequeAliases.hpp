#pragma once
#include "MutableSequenceArray.hpp"
#include "MutableSequenceList.hpp"
#include "Deque.hpp"

template<typename T>
using ArrayDeque = Deque<MutableSequenceArray, T>;

template<typename T>
using ListDeque = Deque<MutableSequenceList, T>;