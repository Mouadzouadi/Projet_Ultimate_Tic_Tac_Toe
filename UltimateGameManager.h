#ifndef ULTIMATEGAMEMANAGER_H
#define ULTIMATEGAMEMANAGER_H

#include "UltimateBoard.h"
#include "main.h" // Fournit l'accès à `game` et aux enums (Level, Mode, etc.)
#include <string>

class UltimateGameManager {
private:
    UltimateBoard internalBoard; // Le "cerveau" de l'IA
    Winner myColor;              // Savoir si ton IA joue les croix ou les ronds
    Winner opponentColor;

public:
    UltimateGameManager();

    // Lance le tournoi complet (remplace le contenu actuel de ton main)
    void playTournament(int nbGames, Level level, Mode mode, bool alwaysPlayFirst, const std::string& alias);

private:
    void resetForNewGame();
    GameMove calculateBestMove(); // C'est ici que tu coderas Minimax ou MCTS
};

#endif
