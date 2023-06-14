#include "./alphabeta.hpp"

#include <cstdlib>

#include "../state/state.hpp"

#define INF 1e9

/**
 * @brief Get a move from alphabeta policy
 *
 * @param state Now state
 * @param depth Search depth
 * @return Move
 */
Move AlphaBeta::get_move(State *state, int depth) {
    Move best_move = {{0, 0}, {0, 0}};
    alphabetaPruing(state, depth, (state->player ? -1 : 1), true, best_move);
    return best_move;
}

long long AlphaBeta::alphabetaPruing(State *state, int depth, int player, bool is_max, Move& best_move) {
    if (depth == 0) {
        return player * state->evaluate();
    }
    state->get_legal_actions();
    // if (state->legal_actions.empty()) {
    //     std::cout << "No legal actions" << std::endl;
    //     return (is_max ? INF : -INF);
    // }
    Move m;
    if (is_max) {
        long long value = -INF;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            long long child_value = alphabetaPruing(next_state, depth - 1, player, !is_max, m);
            delete next_state;
            if (child_value > value) {
                value = child_value;
                best_move = action;
            }
        }
        return value;
    } else {
        long long value = INF;
        for (auto action : state->legal_actions) {
            State *next_state = state->next_state(action);
            long long child_value = alphabetaPruing(next_state, depth - 1, player, !is_max, m);
            delete next_state;
            if (child_value < value) {
                value = child_value;
                best_move = action;
            }
        }
        return value;
    }
}
