#include "header.h"
#include <cmath>

using namespace std;
using namespace sf;

int Evalution(Vector<int> AiChekers, Vector<int> PlayerChekers) {
    return PlayerChekers.size() - AiChekers.size();
}

int GameValid(Vector<sf::ConvexShape>& hexagon, Vector<int> AiChekers, Vector<int> PlayerChekers, int move) {
    Vector<int> FieldsForMove;
    if (AiChekers.size() == 0) {
        return INT16_MAX;
    }
    else if(PlayerChekers.size() == 0) {
        return INT16_MIN;
    }
    if (move) {
        for (auto& i : PlayerChekers) {
            MovesGenerator(i, hexagon, FieldsForMove, sf::Color::White);
            if (!FieldsForMove.empty()) break;
        }
        return Evalution(AiChekers, PlayerChekers);
    }
    else {
        for (auto& i : AiChekers) {
            MovesGenerator(i, hexagon, FieldsForMove, sf::Color::White);
            if (!FieldsForMove.empty()) break;
        }
        return Evalution(AiChekers, PlayerChekers);
    }
}
//оценка ход
std::pair<int, int> MiniMax(Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int> FreeFields, gamestats& gms,int depth, bool move) {
    int validGame = GameValid(hexagon, AiChekers, PlayerChekers, move);
    if (depth == 0) {
        return { validGame , -1};
    }
    else if (validGame == INT16_MAX || validGame == INT16_MIN) {
        return { validGame, -1 };
    }
    Vector<std::pair<int, int>> moveEval;
    std::pair<int, int> evol;
    //вызвали для бота
    if (!move) {
        for (auto i : AiChekers) {
            Vector<int> Moves;
            MovesGenerator(i, hexagon, Moves, sf::Color::White);
            for (auto& nowMove : Moves) {
                evol.second = i;
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
                evol.second = i;
                Vector<int> WinningMoves = MakeMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, move);
                evol.first = MiniMax(hexagon, AiChekers, PlayerChekers, FreeFields, gms, depth - 1, move).first;
                UndoMove(nowMove, hexagon, AiChekers, PlayerChekers, FreeFields, WinningMoves, move);
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



int main() {
    // Графические и интерфейсные параметры
    const int Width = 1000;                 // Параметры экрана
    const int Height = 1200;

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Hexagon"); // Создаем окно
    sf::Font font;
    if (!font.loadFromFile("AGENCYB.TTF")) {
        // Если загрузка не удалась, выведите сообщение об ошибке
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }
    
    Vector<sf::ConvexShape> hexagon;
    Vector<int> FreeFields;
    Vector<int> AiChekers;
    Vector<int> PlayerChekers;
    Vector<int> FieldsForMove;
        for (int i = 0; i < 58; i++) {
            if (i == 0 || i == 4 || i == 25 || i == 32 || i == 53 || i == 57) continue;
            FreeFields.push_back(i);
        }
        AiChekers = { 0, 32, 53 };
        PlayerChekers = { 4, 25, 57 };
        maketable(hexagon);

    gamestats gms;
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Закрытие окна при нажатии на крестик
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
               
                //выбираем фишку для хода
                if(gms.inActive == false)
                {
                    if (gms.move) {
                        for (int i = 0; i < PlayerChekers.size(); i++) {
                            if (hexagon[PlayerChekers[i]].getGlobalBounds().contains(mousePos)) {
                                std::cout << mousePos.x << " " << mousePos.y << std::endl;
                                MovesGenerator(PlayerChekers[i], hexagon, FieldsForMove, Color::White);
                                cout << FieldsForMove << endl;
                                for (auto& a : FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::Green);
                                }
                                gms.inActive = true;
                            }
                        }
                    }
                    else {
                        for (int i = 0; i < AiChekers.size(); i++) {
                            if (hexagon[AiChekers[i]].getGlobalBounds().contains(mousePos)) {
                                std::cout << mousePos.x << " " << mousePos.y << std::endl;
                                MovesGenerator(AiChekers[i], hexagon, FieldsForMove,Color::White);
                                for (auto& a : FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::Green);
                                }
                                gms.inActive = true;
                            }
                        }
                    }
                }
                //выбираем на какое поле сходить
                else {
                    if (gms.move) {
                        for (auto& i : FieldsForMove) {
                            if (hexagon[i].getGlobalBounds().contains(mousePos)) {
                                gms.vertexMove = i;
                                hexagon[i].setFillColor(sf::Color::Red);
                                gms.inActive = false;
                                cout << FieldsForMove << endl;
                                FieldsForMove.erase(binarySearch(FieldsForMove, gms.vertexMove));
                                FreeFields.erase(binarySearch(FreeFields, gms.vertexMove));
                                PlayerChekers.push_back_with_Sort(gms.vertexMove);
                                for (auto& i : FieldsForMove) {
                                    hexagon[i].setFillColor(sf::Color::White);
                                }
                                FieldsForMove.clear();
                                gms.move = !gms.move;
                                MovesGenerator(gms.vertexMove, hexagon, FieldsForMove, sf::Color::Blue);
                                for (auto& a: FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::Red);
                                    PlayerChekers.push_back_with_Sort(a);
                                    AiChekers.erase(binarySearch(AiChekers, a));
                                }
                                FieldsForMove.clear();
                                break;
                            }

                        }
                    }
                    else {
                        for (auto& i : FieldsForMove) {
                            if (hexagon[i].getGlobalBounds().contains(mousePos)) {
                                gms.vertexMove = i;
                                hexagon[i].setFillColor(sf::Color::Blue);
                                gms.inActive = false;
                                FieldsForMove.erase(binarySearch(FieldsForMove, gms.vertexMove));
                                FreeFields.erase(binarySearch(FreeFields, gms.vertexMove));
                                AiChekers.push_back_with_Sort(gms.vertexMove);
                                for (auto& i : FieldsForMove) {
                                    hexagon[i].setFillColor(sf::Color::White);
                                }
                                FieldsForMove.clear();
                                gms.move = !gms.move;
                                MovesGenerator(gms.vertexMove, hexagon, FieldsForMove, sf::Color::Red);
                                for (auto& a : FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::Blue);
                                    AiChekers.push_back_with_Sort(a);
                                    PlayerChekers.erase(binarySearch(PlayerChekers, a));
                                }
                                FieldsForMove.clear();
                                break;
                            }
                        }
                    }
                }
            }
        }

        window.clear(); // Очищаем окно от предыдущих кадров
        Rendering(hexagon, window, font);
        window.display(); // Отображаем нарисованное
    }

    return 0;
}
