#pragma once
#include <vector>

#include "../state/state.hpp"
/**
 * @brief Policy class for random policy,
 * your policy class should have get_move method
 */
class MCTS {
   public:
    static Move get_move(State* state, int limit);
};

class Node : public State {
   public:
    Node* parent = nullptr;
    std::vector<Node*> children;
    int visit_times = 0;
    int win_times = 0;
    double ucb = 1e9;
    bool simulation();
    Move move;
    Node(State* state, Node* parent = nullptr, Move move = Move())
        : State(*state), parent(parent), move(move){};
    void expand();
    Node* select();
    void backpropagate(bool win);
    void update(bool win);
    void delete_children();
};