#pragma once
#include <chrono>
#include "Stack/Stack.hpp"
#include "Stack/StackAliases.hpp"
#include "MutableSequenceArray.hpp"

struct Ring{
    int size = 0;
    int color_idx = 0;

    Ring() = default;
    Ring(int s, int c) : size(s), color_idx(c) {}
};

struct Move{
    size_t from, to;
};

struct HanoiModel{
    size_t current_step = 0;
    int  disk_count = 3;
    bool solved = false;

    bool auto_playing = false;
    int auto_speed = 50;

    MutableSequenceArray<Move> move;
    MutableSequenceArray<ArrayStack<Ring>> rods{3};

    std::chrono::system_clock::time_point last_auto_step{};


private:
    void clearRods(){
        for(auto& item : rods){
            while(!item.empty()){
                item.pop();
            }
        }
    }
    
    void genMoves(size_t n, size_t from, size_t to, size_t via) {
        if (n == 0) return;
        genMoves(n - 1, from, via, to);
        move.append({from, to});
        genMoves(n - 1, via, to, from);
    }
    
public:
    const ArrayStack<Ring>& GetRod(size_t idx) const {
        return rods[idx];
    }

    void solve() {
        while (move.GetLength() > 0) move.RemoveLast();
        current_step = 0;
        solved = false;

        clearRods();

        for (int i = disk_count - 1; i >= 0; --i){
            rods[0].push(Ring{i, i % 7});
        }

        genMoves(disk_count, 0, 2, 1);

        solved = true;
    }

    void stepForward() {
        if (current_step >= totalSteps()) return;
        Move m = move.Get(current_step++);
        Ring r = rods[m.from].pop();
        rods[m.to].push(r);
    }

    void stepBack() {
        if (current_step <= 0) return;
        Move m = move.Get(--current_step);
        Ring r = rods[m.to].pop();
        rods[m.from].push(r);
    }

    size_t totalSteps() const {
        return move.GetLength();
    }

    std::chrono::milliseconds autoInterval() const {
        return std::chrono::milliseconds(1050 - auto_speed * 10);
    }
};

