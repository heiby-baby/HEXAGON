#pragma once
#include "header.h"
using namespace std;

pair<int, int> AlphaBeta(Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int>& FreeFields, gamestats& gms, int depth, int alpha, int beta, bool move) {
    bool validGame = GameValid(hexagon, AiChekers, PlayerChekers, move);
    if (depth == 0 || !validGame) {
        return { Evalution(AiChekers,PlayerChekers) , -1 };
    }
    std::pair<int, int> evol;
    std::pair<int, int> bestmove = { move ? INT16_MIN : INT16_MAX, -1 };
    //‚˚Á‚‡ÎË ‰Îˇ ·ÓÚ‡
    if (!move) {
        for (auto i : AiChekers) {
            Vector<int> Moves;
            MovesGenerator(i, hexagon, Moves, sf::Color::White);
            for (auto& nowMove : Moves) {
                evol.second = nowMove;
                Vector<int> WinningMoves = MakeMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, move);
                evol.first = AlphaBeta(hexagon, AiChekers, PlayerChekers, FreeFields, gms, depth - 1,alpha,beta, !move).first;
                UndoMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, WinningMoves, move);
                alpha = min(evol.first, alpha);
                if (evol.first < bestmove.first) {
                    bestmove = evol;
                }
                if (beta < alpha) {
                    break;
                }
            }
        }
        return bestmove;
    }
    //¬€«€¬¿À» ƒÀﬂ »√–Œ ¿
    else {
        for (auto i : PlayerChekers) {
            Vector<int> Moves;
            MovesGenerator(i, hexagon, Moves, sf::Color::White);
            for (auto& nowMove : Moves) {
                evol.second = nowMove;
                Vector<int> WinningMoves = MakeMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, move);
                evol.first = AlphaBeta(hexagon, AiChekers, PlayerChekers, FreeFields, gms, depth - 1,alpha,beta, !move).first;
                UndoMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, WinningMoves, move);
                beta = max(evol.first, bestmove.first);
                if (evol.first > bestmove.first) {
                    bestmove = evol;
                }
                if (beta < alpha) {
                    break;
                }
            }
        }
        return bestmove;
    }
}



