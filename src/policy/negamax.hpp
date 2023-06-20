#pragma once
#include "../state/state.hpp"
#include <memory>
#include <vector>

/**
 * @brief Policy class for Negamax policy,
 * your policy class should have get_move method
 */
class Negamax {
public:
    static Move get_move(std::shared_ptr<State>& state, int depth);
    static long long negamax(std::shared_ptr<State>& state, int depth, int player, Move& best_move);
};