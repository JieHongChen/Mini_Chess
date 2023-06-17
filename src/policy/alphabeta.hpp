#pragma once
#include "../state/state.hpp"
#include <vector>

/**
 * @brief Policy class for AlphaBeta policy,
 * your policy class should have get_move method
 */
class AlphaBeta {
public:
    static Move get_move(const std::unique_ptr<State>& state, int depth);
    static long long alphabetaPruning(const std::unique_ptr<State>& state, int depth, long long alpha, long long beta, int player, Move& best_move);
    // static long long alphabetaPruning(std::unique_ptr<State>& state, int depth, long long alpha, long long beta, int player, bool is_max, Move& best_move);
};