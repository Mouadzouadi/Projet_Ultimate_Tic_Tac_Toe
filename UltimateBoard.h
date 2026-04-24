#ifndef ULTIMATEBOARD_H
#define ULTIMATEBOARD_H

#include <vector>
#include "SubBoard.h"

class UltimateBoard {
private:
    SubBoard subBoards[3][3];
    int targetSubRow; // -1 si n'importe quelle grille est autorisée
    int targetSubCol;
    Winner overallWinner;

public:
    UltimateBoard();

    // Logique de jeu
    bool isValidMove(GameMove m) const;
    void playMove(GameMove m, Winner player);

    // Outils pour l'algorithme IA
    std::vector<GameMove> getLegalMoves() const;
    bool isTerminal() const; // Fin de partie ?

    // Getters
    int getTargetRow() const { return targetSubRow; }
    int getTargetCol() const { return targetSubCol; }
    Winner getWinner() const { return overallWinner; }

private:
    void updateOverallWinner();
};

#endif
