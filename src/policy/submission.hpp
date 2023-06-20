// Alpha Beta Pruning with Negamax
#pragma once
#include "../state/state.hpp"
#include <vector>

/**
 * @brief Policy class for AlphaBeta policy,
 * your policy class should have get_move method
 */
class AlphaBeta_ {
public:
    static Move get_move(const std::shared_ptr<State>& state, int depth);
    static long long alphabetaPruning(const std::shared_ptr<State>& state, int depth, long long alpha, long long beta, int player, Move& best_move);
};