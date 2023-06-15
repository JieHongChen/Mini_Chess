#include "./minimax.hpp"

#include <cstdlib>

#include "../state/state.hpp"

#define INF 1e9

/**
 * @brief Get a move from minimax policy
 *
 * @param state Now state
 * @param depth Search depth
 * @return Move
 */
Move Minimax::get_move(std::unique_ptr<State>& state, int depth) {
    Move best_move = {{0, 0}, {0, 0}};
    minimax(state, depth, (state->player ? -1 : 1), true, best_move);
    return best_move;
}

/**
 * @brief store the best move search by Minimax in best_move
 * 
 * @param state 
 * @param depth 
 * @param player 
 * @param is_max 
 * @param best_move 
 * @return long long 
 */
long long Minimax::minimax(std::unique_ptr<State>& state, int depth, int player, bool is_max, Move& best_move) {
    if (depth == 0) {
        return player * state->evaluate();
    }
    state->get_legal_actions();
    Move m;
    if (is_max) {
        long long value = -INF;
        for (auto action : state->legal_actions) {
            std::unique_ptr<State> next_state = state->next_state(action);
            if (next_state->win() == player) {
                best_move = action;
                return INF;
            } else if (next_state->win() == -player) {
                continue;
            }
            long long child_value = minimax(next_state, depth - 1, player, !is_max, m);
            if (child_value > value) {
                value = child_value;
                best_move = action;
            }
        }
        return value;
    } else {
        long long value = INF;
        for (auto action : state->legal_actions) {
            std::unique_ptr<State> next_state = state->next_state(action);
            if (next_state->win() == -player) {
                best_move = action;
                return -INF;
            } else if (next_state->win() == player) {
                continue;
            }
            long long child_value = minimax(next_state, depth - 1, player, !is_max, m);
            if (child_value < value) {
                value = child_value;
                best_move = action;
            }
        }
        return value;
    }
}
