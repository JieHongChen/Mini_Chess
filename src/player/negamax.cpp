#include "../policy/negamax.hpp"

#include <fstream>
#include <iostream>

#include "../config.hpp"
#include "../state/state.hpp"

std::unique_ptr<State> root;

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
 * @brief choose a spot by Negamax and write to file
 *
 * @param fout
 */
static const std::vector<int> depths = {3, 5, 6, 7, 8, 9, 10};
void write_valid_spot(std::ofstream& fout) {
    // Keep updating the output until getting killed.
    Move move;
    for (const int& depth : depths) {
        // Choose a spot by Negamax.
        move = Negamax::get_move(root, depth);
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
