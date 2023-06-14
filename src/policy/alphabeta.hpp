#pragma once
#include "../state/state.hpp"
#include <vector>

/**
 * @brief Policy class for AlphaBeta policy,
 * your policy class should have get_move method
 */
class AlphaBeta {
public:
    static Move get_move(State *state, int depth);
    static long long alphabetaPruing(State *state, int depth, int player, bool is_max, Move& best_move);
};