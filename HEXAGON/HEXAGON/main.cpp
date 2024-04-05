#include "header.h"
#include "Minimax.h"
#include "AlphaBeta.h"
#include <cmath>

using namespace std;
using namespace sf;

int main() {
    // Графические и интерфейсные параметры
    const int Width = 1240;                 // Параметры экрана
    const int Height = 1000;
    setlocale(0, "rus");
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
    

    while (window.isOpen() || gms.Final != true) {

        if (gms.move || gms.inActive == true) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close(); // Закрытие окна при нажатии на крестик
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = { static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
                    if (gms.inActive == false) {
                        for (int i = 0; i < PlayerChekers.size(); i++) {
                            if (hexagon[PlayerChekers[i]].getGlobalBounds().contains(mousePos)) {
                                MovesGenerator(PlayerChekers[i], hexagon, FieldsForMove, Color::White);
                                for (auto& a : FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::Green);
                                }
                                gms.inActive = true;
                            }
                            if (FieldsForMove.empty()) {
                                gms.inActive = false;
                            }
                        }
                    }
                    else {
                        for (auto& i : FieldsForMove) {
                            if (hexagon[i].getGlobalBounds().contains(mousePos)) {
                                gms.vertexMove = i;
                                gms.inActive = false;
                                hexagon[i].setFillColor(sf::Color::Red);
                                FieldsForMove.erase(binarySearch(FieldsForMove, gms.vertexMove));
                                for (auto& a : FieldsForMove) {
                                    hexagon[a].setFillColor(sf::Color::White);
                                }
                                FieldsForMove.clear();
                                MakeMove(gms.vertexMove, hexagon, AiChekers, PlayerChekers, FreeFields, gms.move);
                                if (GameValid(hexagon, AiChekers, PlayerChekers, !gms.move) == false) {
                                    gms.Final = true;
                                    if (Evalution(AiChekers, PlayerChekers) > 0) {
                                        cout << "Выйграл игрок" << endl;;
                                    }
                                    else if (Evalution(AiChekers, PlayerChekers) < 0) {
                                        cout << "Выйграл бот" << endl;
                                    }
                                    else {
                                        cout << "Ничья" << endl;
                                    }
                                    return 0;
                                }
                                gms.move = !gms.move;
                                break;
                            }
                        }
                    }
                }

            }
        }
        else {
            //std::pair<int, int> botMove = MiniMax(hexagon, AiChekers, PlayerChekers, FreeFields, gms, 3, gms.move);
            std::pair<int, int> botMove = AlphaBeta(hexagon, AiChekers, PlayerChekers, FreeFields, gms, 7, INT16_MAX, INT16_MIN, gms.move);
            MakeMove(botMove.second, hexagon, AiChekers, PlayerChekers, FreeFields, gms.move);
            if (GameValid(hexagon, AiChekers, PlayerChekers, !gms.move) == false) {
                gms.Final = true;
                if (Evalution(AiChekers, PlayerChekers) > 0) {
                    cout << "Выйграл игрок" << endl;;
                }
                else if (Evalution(AiChekers, PlayerChekers) < 0) {
                    cout << "Выйграл бот" << endl;
                }
                else {
                    cout << "Ничья" << endl;
                }
                return 0;
            }
            gms.move = !gms.move;
        }
        window.clear(); // Очищаем окно от предыдущих кадров
        Rendering(hexagon, window, font);
        window.display(); // Отображаем нарисованное
    }
    return 0;
}
