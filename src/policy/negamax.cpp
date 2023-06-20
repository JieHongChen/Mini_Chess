#include "./negamax.hpp"

#include <cstdlib>

#include "../state/state.hpp"

#define INF 1e9

/**
 * @brief Get a move from Negamax policy
 *
 * @param state Now state
 * @param depth Search depth
 * @return Move
 */
Move Negamax::get_move(std::shared_ptr<State>& state, int depth) {
    Move best_move = {{0, 0}, {0, 0}};
    negamax(state, depth, (state->player ? -1 : 1), best_move);
    return best_move;
}

/**
 * @brief store the best move search by Negamax in best_move
 * 
 * @param state 
 * @param depth 
 * @param player 
 * @param best_move 
 * @return long long 
 */
long long Negamax::negamax(std::shared_ptr<State>& state, int depth, int player, Move& best_move) {
    if (depth == 0) {
        return player * state->evaluate();
    }
    state->get_legal_actions();
    Move m;
    long long value = -INF;
    for (auto action : state->legal_actions) {
        std::shared_ptr<State> next_state = state->next_state(action);
        if (next_state->win() == player) {
            best_move = action;
            return INF;
        } else if (next_state->win() == -player) {
            continue;
        }
        long long child_value = -negamax(next_state, depth - 1, -player, m);
        if (child_value > value) {
            value = child_value;
            best_move = action;
        }
    }
    return value;
}
