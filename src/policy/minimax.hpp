#pragma once
#include "../state/state.hpp"
#include <vector>

// /**
//  * @brief Tree node for minimax tree
//  */
// class MMTNode {
// public:
//     MMTNode(State *state, int depth, bool is_max, Move prev_move = {{0, 0}, {0, 0}});
//     ~MMTNode();
//     void minimax(std::vector<Move>& path);

// private:
//     bool is_max;
//     int depth;
//     int value;
//     State *state;
//     Move prev_move;
//     Move best_move;
//     std::vector<MMTNode*> children;
// };

/**
 * @brief Policy class for minimax policy,
 * your policy class should have get_move method
 */
class Minimax {
public:
    static Move get_move(State *state, int depth);
    static long long minimax(State *state, int depth, int player, bool is_max, Move& best_move);
};