#pragma once

#include <vector>

#include "../state/state.hpp"

class Node {
private:
    std::shared_ptr<State> state;
    Node* const parent;
    const Move move;
    const bool opponent;
    std::vector<Node*> children;
    int w = 0;
    int n = 0;
    // double ucb = 1e9;

public:
    Node(std::shared_ptr<State> state, Node* parent = nullptr, Move move = Move(), bool opponent = false);
    ~Node();

    const std::vector<Node*> get_children() const { return children; }
    Move get_move() const { return move; }
    int get_n() const { return n; }
    int get_w() const { return w; }

    double ucb() const ;
    Node* select();
    void expand();
    bool rollout();
    void backpropagate(bool win);
    void printTree(int depth = 0);
};

/**
 * @brief Policy class for Monte Carlo tree search policy,
 * your policy class should have get_move method
 */
class MCTS {
public:
    static Move get_move(const std::shared_ptr<State>& state, size_t simulation_times);
};

// std::shared_ptr<Node> MCTS::root;

