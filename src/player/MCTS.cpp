#include "../policy/MCTS.hpp"

#include <fstream>
#include <iostream>


#include "../config.hpp"
#include "../state/state.hpp"

std::shared_ptr<State> root;

/**
 * @brief Read the board from the file
 *
 * @param fin
 */
void read_board(std::ifstream& fin) {
    Board board;
    int player;
    fin >> player;

    for (int pl = 0; pl < 2; pl++) {
        for (int i = 0; i < BOARD_H; i++) {
            for (int j = 0; j < BOARD_W; j++) {
                int c;
                fin >> c;
                // std::cout << c << " ";
                board.board[pl][i][j] = c;
            }
            // std::cout << std::endl;
        }
    }
    root = std::make_unique<State>(board, player);
    root->get_legal_actions();
}

/**
 * @brief choose a spot by Monte Carlo tree search and write to file
 *
 * @param fout
 */
static const std::vector<double> simulation_times = {1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14};
void write_valid_spot(std::ofstream& fout) {
    // Keep updating the output until getting killed.
    Move move;
    for (const double& st : simulation_times) {
        // Choose a spot by Monte Carlo tree search.
        move = MCTS::get_move(root, st);
        fout << move.first.first << " " << move.first.second << " "
             << move.second.first << " " << move.second.second << std::endl;

        // Remember to flush the output to ensure the last action is written to file.
        fout.flush();
    }
}

/**
 * @brief Main function for player
 *
 * @param argv
 * @return int
 */
int main(int, char** argv) {
    // srand(RANDOM_SEED);
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    read_board(fin);
    write_valid_spot(fout);

    fin.close();
    fout.close();
    return 0;
}