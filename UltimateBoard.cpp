#include "UltimateBoard.h"

UltimateBoard::UltimateBoard() : targetSubRow(-1), targetSubCol(-1), overallWinner(NO_WINNER) {}

bool UltimateBoard::isValidMove(GameMove m) const {
    if (m.row < 0 || m.row > 8 || m.col < 0 || m.col > 8) return false;

    int sR = m.row / 3;
    int sC = m.col / 3;
    int lR = m.row % 3;
    int lC = m.col % 3;

    // Règle 1 : La case doit être vide
    if (subBoards[sR][sC].getCell(lR, lC) != NO_WINNER) return false;

    // Règle 2 : La petite grille ne doit pas être déjà finie
    if (subBoards[sR][sC].isFinished()) return false;

    // Règle 3 : Respecter la grille cible imposée [cite: 27]
    if (targetSubRow != -1 && (sR != targetSubRow || sC != targetSubCol)) return false;

    return true;
}

void UltimateBoard::playMove(GameMove m, Winner player) {
    int sR = m.row / 3;
    int sC = m.col / 3;
    int lR = m.row % 3;
    int lC = m.col % 3;

    subBoards[sR][sC].playMove(lR, lC, player);

    // Déterminer la prochaine grille cible [cite: 29]
    if (subBoards[lR][lC].isFinished()) {
        // Si la grille cible est finie, le joueur a quartier libre [cite: 59]
        targetSubRow = -1;
        targetSubCol = -1;
    } else {
        targetSubRow = lR;
        targetSubCol = lC;
    }

    updateOverallWinner();
}

std::vector<GameMove> UltimateBoard::getLegalMoves() const {
    std::vector<GameMove> moves;
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            GameMove m{r, c};
            if (isValidMove(m)) moves.push_back(m);
        }
    }
    return moves;
}

void UltimateBoard::updateOverallWinner() {
    // Logique similaire à SubBoard mais appliquée aux gagnants des petites grilles [cite: 79]
    // À implémenter : vérification de 3 subBoards alignés gagnés par le même joueur.
}

bool UltimateBoard::isTerminal() const {
    if (overallWinner != NO_WINNER) return true;
    // Vérifier si toutes les grilles sont pleines
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(!subBoards[i][j].isFinished()) return false;
    return true;
}
