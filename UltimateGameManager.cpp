#include "UltimateGameManager.h"
#include <iostream>
#include <vector>

UltimateGameManager::UltimateGameManager() {
    // Par défaut, on va supposer que tu es PLAYER et l'adversaire est IA
    // (À adapter selon la convention exacte de la librairie de ton professeur)
    myColor = PLAYER;
    opponentColor = IA;
}

void UltimateGameManager::playTournament(int nbGames, Level level, Mode mode, bool alwaysPlayFirst, const std::string& alias) {
    // 1. On initialise le moteur graphique du professeur
    game.initialize(nbGames, level, mode, alwaysPlayFirst, alias);

    // 2. Boucle principale du tournoi (ex: les 100 parties en arène)
    while (!game.isAllGameFinish()) {

        resetForNewGame(); // On nettoie notre "cerveau" pour la nouvelle manche

        // 3. Boucle d'une manche unique
        while (!game.isFinish()) {
            GameMove opponentMove;

            // game.getMove() bloque jusqu'à ce que ce soit notre tour.
            // Il remplit 'opponentMove' avec le dernier coup joué.
            game.getMove(opponentMove);

            // Sécurité : on vérifie que ce n'est pas le tout premier coup du jeu
            // (Si on commence, l'adversaire n'a rien joué, les coordonnées peuvent être invalides comme -1,-1)
            if (opponentMove.row >= 0 && opponentMove.col >= 0 && opponentMove.row < 9 && opponentMove.col < 9) {
                // On met à jour notre cerveau avec le coup de l'adversaire
                internalBoard.playMove(opponentMove, opponentColor);
            }

            // 4. Ton IA réfléchit et choisit son coup
            GameMove myMove = calculateBestMove();

            // 5. On met à jour notre cerveau avec notre propre décision
            internalBoard.playMove(myMove, myColor);

            // 6. On envoie officiellement notre coup au moteur du prof
            game.setMove(myMove);
        }
    }
}

void UltimateGameManager::resetForNewGame() {
    // Remplace l'ancien plateau par un plateau tout neuf
    internalBoard = UltimateBoard();
}

GameMove UltimateGameManager::calculateBestMove() {
    /* * ==========================================
     * ZONE DE CODE DE TON ALGORITHME D'IA
     * ==========================================
     * C'est ici que tu utiliseras les méthodes :
     * internalBoard.getLegalMoves()
     * internalBoard.playMove(...)
     * internalBoard.undoMove(...) // (à ajouter pour Minimax)
     */

    std::vector<GameMove> legalMoves = internalBoard.getLegalMoves();

    // IA "Random" de test : on joue le premier coup légal qu'on trouve
    if (!legalMoves.empty()) {
        return legalMoves[0];
    }

    // Sécurité anti-crash au cas où
    return {0, 0};
}
