#include "./MCTS.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <vector>

#include "../state/state.hpp"

#define D_MAX std::numeric_limits<double>::max()
#define D_MIN std::numeric_limits<double>::min()

static std::random_device rd;
static std::mt19937 gen(rd());
// static std::mt19937 gen(RANDOM_SEED);

float Q_sqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;             // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);  // what the fuck?
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));  // 1st iteration
    // y = y * (threehalfs - (x2 * y * y));  // 2nd iteration, this can be removed
    return 1 / y;
}

static const double C = 4;

static std::shared_ptr<Node> root;

#include <fstream>
std::ofstream tree_log("treelog.txt");
bool do_tree_log = false;

/**
 * @brief Get a move from MCTS policy
 *
 * @param state Now state
 * @param depth Search depth
 * @return Move
 */
#include <iostream>
Move MCTS::get_move(const std::shared_ptr<State>& state, size_t simulation_times) {
    root = std::make_shared<Node>(state);
    for (size_t i = 0; i < simulation_times; ++i) {
        // if (i < 20) {
        if ((i + 1) % 1000 == 0) {
            do_tree_log = true;
            tree_log << root->get_n() << " " << root->get_w() << std::endl;
            // tree_log << "//////////" << std::endl;
            // root->printTree();
        } else
            do_tree_log = false;
        Node* cur = root->select();
        bool simulation_result = cur->rollout();
        cur->backpropagate(simulation_result);
    }
    Move best_move = {{0, 0}, {0, 0}};
    double value = D_MIN;
    // tree_log << root->get_children().size() << std::endl;
    for (const Node* node : root->get_children()) {
        double val = node->ucb();
        // tree_log << "\t" << val << "\t" << value << std::endl;
        // tree_log << node->move.first.first << " " << node->move.first.second << " "
        //           << node->move.second.first << " " << node->move.second.second << std::endl;
        if (val > value) {
            val = value;
            best_move = node->get_move();
        }
    }
    // tree_log << std::endl;
    // tree_log << best_move.first.first << " " << best_move.first.second << " "
    //           << best_move.second.first << " " << best_move.second.second << std::endl;
    return best_move;
}

Node::Node(std::shared_ptr<State> state, Node* parent, Move move, bool opponent)
    : state(state), parent(parent), move(move), opponent(opponent) {}
Node::~Node() {
    for (Node* child : children) {
        delete child;
    }
}

double Node::ucb() const {
    if (n) {
        // return (opponent ? n - w : w) / n + C * sqrt(log(parent->n) / n);
        return (opponent ? n - w : w) / n + C * Q_sqrt(log(parent->n) / n);
    }
    return D_MAX;
}

/**
 * @brief Select a node to rollout
 *
 * @return Node*
 */
Node* Node::select() {
    Node* cur = this;
    while (!cur->children.empty()) {
        cur = *std::max_element(cur->children.begin(), cur->children.end(),
                                [](Node* a, Node* b) { return a->ucb() < b->ucb(); });
    }

    // old node
    if (cur->n) {
        cur->expand();
        return cur->children[0];
    }
    // new node
    return cur;
}

void Node::expand() {
    state->get_legal_actions();
    children.reserve(state->legal_actions.size());
    for (const Move& move : state->legal_actions) {
        children.emplace_back(new Node(state->next_state(move), this, move, !opponent));
    }
}

bool Node::rollout() {
    int root_player = (opponent ? 1 - state->player : state->player);
    std::shared_ptr<State> cur = state;
    for (int i = 0; i < 50; ++i) {
        cur->get_legal_actions();
        if (cur->legal_actions.empty()) {
            tree_log << "empty" << std::endl;
            return cur->player != root_player;
        }
        cur = cur->next_state(cur->legal_actions[gen() % cur->legal_actions.size()]);
        int winner = cur->win();
        if (winner) {
            if (do_tree_log) {
                tree_log << "win" << std::endl;
            }
            return (root_player == 0 ? winner > 0 : winner < 0);
        }
    }
    return (root_player == 0 ? cur->evaluate() > 0 : cur->evaluate() < 0);
}

void Node::backpropagate(bool win) {
    ++n;
    if (win) {
        ++w;
    }
    if (parent) {
        parent->backpropagate(win);
    }
}

void Node::printTree(int depth) {
    for (int i = 0; i < depth; ++i) {
        tree_log << " ";
    }
    // tree_log << move.first.first << " " << move.first.second << " " << move.second.first << " "
    //           << move.second.second << " ";
    tree_log << w << " " << n << std::endl;
    for (Node* child : children) {
        if (!child) continue;
        child->printTree(depth + 1);
    }
}
