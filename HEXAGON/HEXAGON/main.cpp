#include "header.h"
#include <cmath>

struct fields {
    Vector<sf::ConvexShape> hexagon;
    Vector<int> FreeFields;
};

int main() {
    // Графические и интерфейсные параметры
    const int Width = 1500;                 // Параметры экрана
    const int Height = 1000;

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Hexagon"); // Создаем окно
    fields Fields;
    maketable(Fields.hexagon);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Закрытие окна при нажатии на крестик
        }

        window.clear(); // Очищаем окно от предыдущих кадров
        Rendering(Fields.hexagon, window);
        window.display(); // Отображаем нарисованное
    }

    return 0;
}
