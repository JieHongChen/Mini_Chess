#pragma once
#include "../state/state.hpp"
#include <memory>
#include <vector>

/**
 * @brief Policy class for minimax policy,
 * your policy class should have get_move method
 */
class Minimax {
public:
    static Move get_move(std::unique_ptr<State>& state, int depth);
    static long long minimax(std::unique_ptr<State>& state, int depth, int player, bool is_max, Move& best_move);
};