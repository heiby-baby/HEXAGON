#pragma once
#include "header.h"
using namespace std;
//оценка ход
std::pair<int, int> MiniMax(Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int>& FreeFields, gamestats& gms, int depth, bool move) {
    
    bool validGame = GameValid(hexagon, AiChekers, PlayerChekers, move);
    if (depth == 0 || !validGame) {
        return { Evalution(AiChekers,PlayerChekers) , -1};
    }
    Vector<std::pair<int, int>> moveEval;
    std::pair<int, int> evol;
    //вызвали для бота
    if (!move) {
        for (auto i : AiChekers) {
            Vector<int> Moves;
            MovesGenerator(i, hexagon, Moves, sf::Color::White);
            for (auto& nowMove : Moves) {
                evol.second = nowMove;
                Vector<int> WinningMoves = MakeMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, move);
                evol.first = MiniMax(hexagon, AiChekers, PlayerChekers, FreeFields, gms, depth - 1, !move).first;
                UndoMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, WinningMoves, move);
                moveEval.push_back(evol);
            }
        }
    }
    //ВЫЗЫВАЛИ ДЛЯ ИГРОКА
    else {
        for (auto i : PlayerChekers) {
            Vector<int> Moves;
            MovesGenerator(i, hexagon, Moves, sf::Color::White);
            for (auto& nowMove : Moves) {
                evol.second = nowMove;
                Vector<int> WinningMoves = MakeMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, move);
                evol.first = MiniMax(hexagon, AiChekers, PlayerChekers, FreeFields, gms, depth - 1, !move).first;
                UndoMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, WinningMoves, move);
                moveEval.push_back(evol);
            }
        }
    }
    int bestMoveIndex = 0;
    for (int i = 1; i < moveEval.size(); ++i) {
        if (!move && (moveEval[i].first < moveEval[bestMoveIndex].first)) {
            bestMoveIndex = i;
        }
        else if (move && (moveEval[i].first > moveEval[bestMoveIndex].first)) {
            bestMoveIndex = i;
        }
    }
    
    return moveEval[bestMoveIndex];
}

