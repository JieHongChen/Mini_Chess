// Alpha Beta Pruning with Negamax
#include "./submission.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

#include "../state/state.hpp"

#define INF 1e9

/**
 * @brief Get a move from alphabeta policy
 *
 * @param state Now state
 * @param depth Search depth
 * @return Move
 */
Move AlphaBeta_::get_move(const std::shared_ptr<State>& state, int depth) {
    Move best_move = {{0, 0}, {0, 0}};
    alphabetaPruning(state, depth, -INF, INF, (state->player ? -1 : 1), best_move);
    return best_move;
}

/**
 * @brief search best move by Negamax and AlphaBeta Pruning and store in `best_move`.
 *
 * @param state
 * @param depth
 * @param alpha
 * @param beta
 * @param player
 * @param is_max
 * @param best_move
 * @return long long
 */
long long AlphaBeta_::alphabetaPruning(const std::shared_ptr<State>& state, int depth, long long alpha, long long beta, int player, Move& best_move) {
    if (depth == 0) {
        return player * state->evaluate();
    }
    if (state->legal_actions.empty()) {
        state->get_legal_actions();
    }
    Move m;
    long long value = -INF;
    std::vector<std::pair<long long, std::pair<Move, std::shared_ptr<State>>>> v;
    for (auto action : state->legal_actions) {
        std::shared_ptr<State> next_state = state->next_state(action);
        if (next_state->win() == player) {
            best_move = action;
            return INF;
        } else if (next_state->win() == -player) {
            continue;
        }
        v.emplace_back(std::make_pair(player * next_state->evaluate(), std::make_pair(action, next_state)));
    }
    auto comp = [](const std::pair<long long, std::pair<Move, std::shared_ptr<State>>>& a,
                   const std::pair<long long, std::pair<Move, std::shared_ptr<State>>>& b)
        -> bool { return a.first > b.first; };
    std::sort(v.begin(), v.end(), comp);
    for (const auto& [_, p] : v) {
        Move action = p.first;
        std::shared_ptr<State> next_state = p.second;
        long long child_value = -alphabetaPruning(next_state, depth - 1, -beta, -alpha, -player, m);
        if (child_value > value) {
            value = child_value;
            best_move = action;
        }
        alpha = std::max(alpha, value);
        if (alpha >= beta) {
            break;
        }
    }
    return value;
}
