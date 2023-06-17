#include "./MCTS.hpp"

#include <cstdlib>
#include <cmath>
#include <vector>
#include "../state/state.hpp"

int now_player;

Move MCTS::get_move(State* state, int limit) {
    now_player = state->player;
    Node* root = new Node(state);
    root->legal_actions.clear();
    root->get_legal_actions();
    root->expand();
    for (int i = 0; i < limit; i++) {
        Node* node = root;
        while (node->children.size() > 0) {
            node->visit_times++;
            node = node->select();
        }
        if(node->visit_times != 0){
            node->visit_times++;
            node->expand();
            node = node->select();
        }
        node->visit_times++;
        node->backpropagate(node->simulation());
    }
    std::vector<Move> best_moves;
    double best_winning_rate = (double)root->children[0]->win_times / root->children[0]->visit_times;
    best_moves.push_back(root->children[0]->move);
    for (auto child : root->children) {
        if (child->visit_times == 0) {
            continue;
        }
        double winning_rate = (double)child->win_times / child->visit_times;
        if (winning_rate > best_winning_rate) {
            best_moves.clear();
            best_winning_rate = winning_rate;
            best_moves.push_back(child->move);
        }
        else if(winning_rate == best_winning_rate){
            best_moves.push_back(child->move);
        }
    }
    root->delete_children();
    delete root;
    return best_moves[rand() % best_moves.size()];
}

bool Node::simulation() {
    State* state = new State(*this);
    if(state->legal_actions.empty()) state->get_legal_actions();
    while (state->game_state == UNKNOWN) {
        int index = rand() % state->legal_actions.size();
        State* next_state = state->next_state(state->legal_actions[index]);
        delete state;
        state = next_state;
        if(state->legal_actions.empty()) state->get_legal_actions();
    }
    int winner = player;
    delete state;
    return winner==now_player;
}

void Node::backpropagate(bool win) {
    Node* node = this;
    while (node->parent != nullptr) {
        node->update(win);
        node = node->parent;
    }
}

void Node::update(bool win) {
    if(win) this->win_times++;
    this->ucb = (double)this->win_times / this->visit_times +
                    sqrt(2 * log(this->parent->visit_times) / this->visit_times);
    
}

void Node::expand() {
    if(!this->legal_actions.size()) 
        this->get_legal_actions();
    for (auto move : this->legal_actions) {
        State* next_state = this->next_state(move);
        Node* child = new Node(next_state, this, move);
        delete next_state;
        this->children.push_back(child);
    }
}

Node* Node::select() {
    Node* node = this->children[0];
    for(auto child = ++this->children.begin(); child != this->children.end(); child++){
        if((*child)->ucb > node->ucb){
            node = *child;
        }
    }
    return node;
}

void Node::delete_children() {
    if(this->children.size() == 0) return;
    for (auto child : this->children) {
        child->delete_children();
        delete child;
    }
}