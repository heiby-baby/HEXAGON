#pragma once
#include "header.h"


void maketable(Vector<sf::ConvexShape>& hexagon) {
    
    sf::ConvexShape shape;
    shape.setFillColor(sf::Color::White);
    shape.setPointCount(6);          // Устанавливаем количество точек
    const float radius = 40;         // Радиус шестиугольникаряд
    const float angle = 2 * PI / 6;  // Угол между вершинами шестиугольника
    const float  indention = 2 *  (radius - radius * sqrt(3) / 2);          //отступ между шестиугольниками
    // Задаем координаты вершинам шестиугольника
    for (int i = 0; i < 6; ++i) {
        float x =  radius * std::cos(i * angle);
        float y =  radius * std::sin(i * angle);
        shape.setPoint(i, sf::Vector2f(x, y)); // Устанавливаем координаты точки
    }
    //1 ряд   
    sf::Vector2f pos = { 300,300 };
    for (int i = 0; i < 5; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=   2 * radius + indention;
    }
    //2 ряд
    pos = { 300,300 };
    pos = { pos.x + 2 * radius , pos.y -  radius  };
    for (int i = 0; i < 6; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    //3 ряд
    pos = { 300,300 };
    pos = { pos.x + 4 * radius , pos.y -  2 * radius };
    for (int i = 0; i < 7; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention ;
    }
    //4 ряд
    pos = { 300,300 };
    pos = { pos.x + 6 * radius , pos.y  -  3 * radius };
    for (int i = 0; i < 8; i++) {
        if (i == 4)
        {
            pos.y +=  2 * radius + indention;
            continue;
        }
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    //5 ряд
    pos = { 300,300 };
    pos = { pos.x + 8 * radius , pos.y -  4 * radius };
    for (int i = 0; i < 9; i++) {
        if (i == 3)
        {
            pos.y +=  2 * radius + indention;
            continue;
        }
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention ;
    }
    //6 ряд
    pos = { 300,300 };
    pos = { pos.x + 10 * radius , pos.y -  3 * radius};
    for (int i = 0; i < 8; i++) {
        if (i == 4)
        {
            pos.y +=  2 * radius + indention;
            continue;
        }
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
     //7 ряд
    pos = { 300,300 };
    pos = { pos.x + 12 * radius , pos.y -  2 * radius };
    for (int i = 0; i < 7; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius+ indention;
    }
    //8 ряд
    pos = { 300,300 };
    pos = { pos.x + 14 * radius , pos.y -  radius  };
    for (int i = 0; i < 6; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    //9 ряд   
     pos = {16 * radius + 300,300 };
    for (int i = 0; i < 5; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    hexagon[0].setFillColor(sf::Color::Blue);
    hexagon[32].setFillColor(sf::Color::Blue);
    hexagon[53].setFillColor(sf::Color::Blue);
    hexagon[4].setFillColor(sf::Color::Red);
    hexagon[25].setFillColor(sf::Color::Red);
    hexagon[57].setFillColor(sf::Color::Red);
}

void Rendering(Vector<sf::ConvexShape>& hexagon, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < hexagon.size(); i++) {
        window.draw(hexagon[i]);
        const float radius = 40;         // Радиус шестиугольникаряд
        const float  indention = 2 * (radius - radius * sqrt(3) / 2);
        // Создаем текст для индекса
        sf::Text text;
        text.setFont(font); // Устанавливаем шрифт
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);

        // Получаем глобальные границы шестиугольника
        sf::FloatRect bounds = hexagon[i].getGlobalBounds();

        // Вычисляем центр границ шестиугольника
        sf::Vector2f center(bounds.left + bounds.width / 2 - indention, bounds.top + bounds.height / 2 - indention);

        // Устанавливаем позицию текста в центр границ шестиугольника
        text.setPosition(center.x, center.y);

        // Устанавливаем индекс в текст
        text.setString(std::to_string(i));

        // Рисуем текст на экране
        window.draw(text);
    }
}

void setColor(int vertex, Vector<sf::ConvexShape>& hexagon, Vector<int>& FieldsForMove) {
    FieldsForMove.push_back(vertex);
}

void MovesGenerator(int vertex, Vector<sf::ConvexShape>& hexagon, Vector<int>& FieldsForMove, sf::Color ShapeColor) {
    sf::Color color = ShapeColor;
    switch (vertex)
    {
    case(0):
    {
        if (hexagon[1].getFillColor() == color) setColor(1, hexagon, FieldsForMove);
        if (hexagon[5].getFillColor() == color) setColor(5, hexagon, FieldsForMove);
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);
        break;
    }
    case(1):
    {
        if (hexagon[0].getFillColor() == color) setColor(0, hexagon, FieldsForMove);
        if (hexagon[2].getFillColor() == color) setColor(2, hexagon, FieldsForMove);
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);        break;

    }
    case(2):
    {
        if (hexagon[1].getFillColor() == color) setColor(1, hexagon, FieldsForMove);
        if (hexagon[3].getFillColor() == color) setColor(3, hexagon, FieldsForMove);
        if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);        break;

    }
    case(3): {
        if (hexagon[2].getFillColor() == color) setColor(2, hexagon, FieldsForMove);
        if (hexagon[4].getFillColor() == color) setColor(4, hexagon, FieldsForMove);
        if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);        
        break;
    }
    case(4):
    {
        if (hexagon[3].getFillColor() == color) setColor(3, hexagon, FieldsForMove);
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);
        if (hexagon[10].getFillColor() == color) setColor(10, hexagon, FieldsForMove);        break;

    }
    case(5):
    {
        if (hexagon[0].getFillColor() == color) setColor(0, hexagon, FieldsForMove);
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);
        if (hexagon[11].getFillColor() == color) setColor(11, hexagon, FieldsForMove);        break;

    }
    case(6):
    {
        if (hexagon[0].getFillColor() == color) setColor(0, hexagon, FieldsForMove);
        if (hexagon[5].getFillColor() == color) setColor(5, hexagon, FieldsForMove);
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);
        if (hexagon[1].getFillColor() == color) setColor(1, hexagon, FieldsForMove);        break;

    }
    case(7):
    {
        if (hexagon[1].getFillColor() == color) setColor(1, hexagon, FieldsForMove);
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);
        if (hexagon[14].getFillColor() == color) setColor(14, hexagon, FieldsForMove);
        if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);
        if (hexagon[2].getFillColor() == color) setColor(2, hexagon, FieldsForMove);        break;

    }
    case(8):
    {
        if (hexagon[2].getFillColor() == color) setColor(2, hexagon, FieldsForMove);
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);
        if (hexagon[15].getFillColor() == color) setColor(15, hexagon, FieldsForMove);
        if (hexagon[14].getFillColor() == color) setColor(14, hexagon, FieldsForMove);
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);
        if (hexagon[3].getFillColor() == color) setColor(3, hexagon, FieldsForMove);        break;

    }
    case(9):
    {
        if (hexagon[3].getFillColor() == color) setColor(3, hexagon, FieldsForMove);
        if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);
        if (hexagon[15].getFillColor() == color) setColor(15, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(16, hexagon, FieldsForMove);
        if (hexagon[10].getFillColor() == color) setColor(10, hexagon, FieldsForMove);
        if (hexagon[4].getFillColor() == color) setColor(4, hexagon, FieldsForMove);        break;

    }
    case(10):
    {
        if (hexagon[4].getFillColor() == color) setColor(4, hexagon, FieldsForMove);
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);
        if (hexagon[17].getFillColor() == color) setColor(17, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(16, hexagon, FieldsForMove);        break;

    }
    case(11):
    {
        if (hexagon[5].getFillColor() == color) setColor(5, hexagon, FieldsForMove);
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[18].getFillColor() == color) setColor(18, hexagon, FieldsForMove);        break;

    }
    case(12):
    {
        if (hexagon[5].getFillColor() == color) setColor(5, hexagon, FieldsForMove);
        if (hexagon[11].getFillColor() == color) setColor(11, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[20].getFillColor() == color) setColor(20, hexagon, FieldsForMove);
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);        break;

    }
    case(13):
    {
        if (hexagon[6].getFillColor() == color) setColor(6, hexagon, FieldsForMove);
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);
        if (hexagon[20].getFillColor() == color) setColor(20, hexagon, FieldsForMove);
        if (hexagon[21].getFillColor() == color) setColor(21, hexagon, FieldsForMove);
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);
        if (hexagon[14].getFillColor() == color) setColor(14, hexagon, FieldsForMove);        break;

    }
    case(14):
    {
        if (hexagon[7].getFillColor() == color) setColor(7, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);
        if (hexagon[21].getFillColor() == color) setColor(21, hexagon, FieldsForMove);
        if (hexagon[15].getFillColor() == color) setColor(15, hexagon, FieldsForMove);
        if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);        break;

    }
    case(15):
    {
        if (hexagon[14].getFillColor() == color) setColor(14, hexagon, FieldsForMove);
         if (hexagon[8].getFillColor() == color) setColor(8, hexagon, FieldsForMove);
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(16, hexagon, FieldsForMove);
        if (hexagon[22].getFillColor() == color) setColor(22, hexagon, FieldsForMove);        break;

    }
    case(16):
    {
        if (hexagon[9].getFillColor() == color) setColor(9, hexagon, FieldsForMove);
        if (hexagon[15].getFillColor() == color) setColor(15, hexagon, FieldsForMove);
        if (hexagon[22].getFillColor() == color) setColor(22, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);
        if (hexagon[17].getFillColor() == color) setColor(17, hexagon, FieldsForMove);
        if (hexagon[10].getFillColor() == color) setColor(10, hexagon, FieldsForMove);        break;

    }
    case(17):
    {
        if (hexagon[10].getFillColor() == color) setColor(10, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(16, hexagon, FieldsForMove);
        if (hexagon[24].getFillColor() == color) setColor(24, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);        break;

    }
    case(18):
    {
        if (hexagon[11].getFillColor() == color) setColor(11, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[25].getFillColor() == color) setColor(25, hexagon, FieldsForMove);        break;

    }
    case(19):
    {
        if (hexagon[18].getFillColor() == color) setColor(18, hexagon, FieldsForMove);
        if (hexagon[11].getFillColor() == color) setColor(11, hexagon, FieldsForMove);
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[27].getFillColor() == color) setColor(27, hexagon, FieldsForMove);
        if (hexagon[20].getFillColor() == color) setColor(20, hexagon, FieldsForMove);
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);        break;

    }
    case(20):
    {
        if (hexagon[12].getFillColor() == color) setColor(12, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[21].getFillColor() == color) setColor(21, hexagon, FieldsForMove);
        if (hexagon[27].getFillColor() == color) setColor(27, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);        break;

    }
    case(21):
    {
        if (hexagon[20].getFillColor() == color) setColor(20, hexagon, FieldsForMove);
        if (hexagon[13].getFillColor() == color) setColor(13, hexagon, FieldsForMove);
        if (hexagon[14].getFillColor() == color) setColor(14, hexagon, FieldsForMove);
        if (hexagon[28].getFillColor() == color) setColor(28, hexagon, FieldsForMove);        break;

    }
    case(22):
    {
        if (hexagon[15].getFillColor() == color) setColor(15, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(16, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);
        if (hexagon[29].getFillColor() == color) setColor(29, hexagon, FieldsForMove);        break;

    }
    case(23):
    {
        if (hexagon[22].getFillColor() == color) setColor(22, hexagon, FieldsForMove);
        if (hexagon[24].getFillColor() == color) setColor(18, hexagon, FieldsForMove);
        if (hexagon[17].getFillColor() == color) setColor(17, hexagon, FieldsForMove);
        if (hexagon[16].getFillColor() == color) setColor(24, hexagon, FieldsForMove);
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);        break;

    }
    case(24):
    {
        if (hexagon[17].getFillColor() == color) setColor(17, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[32].getFillColor() == color) setColor(32, hexagon, FieldsForMove);        break;

    }
    case(25):
    {
        if (hexagon[18].getFillColor() == color) setColor(18, hexagon, FieldsForMove);
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[33].getFillColor() == color) setColor(33, hexagon, FieldsForMove);        break;

    }
    case(26):
    {
        if (hexagon[25].getFillColor() == color) setColor(25, hexagon, FieldsForMove);
        if (hexagon[18].getFillColor() == color) setColor(18, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[27].getFillColor() == color) setColor(27, hexagon, FieldsForMove);
        if (hexagon[33].getFillColor() == color) setColor(33, hexagon, FieldsForMove);
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);        break;

    }
    case(27):
    {
        if (hexagon[20].getFillColor() == color) setColor(20, hexagon, FieldsForMove);
        if (hexagon[19].getFillColor() == color) setColor(19, hexagon, FieldsForMove);
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);
        if (hexagon[35].getFillColor() == color) setColor(35, hexagon, FieldsForMove);        break;

    }
    case(28):
    {
        if (hexagon[21].getFillColor() == color) setColor(21, hexagon, FieldsForMove);
        if (hexagon[36].getFillColor() == color) setColor(36, hexagon, FieldsForMove);
        if (hexagon[29].getFillColor() == color) setColor(29, hexagon, FieldsForMove);        break;

    }
    case(29):
    {
        if (hexagon[22].getFillColor() == color) setColor(22, hexagon, FieldsForMove);
        if (hexagon[28].getFillColor() == color) setColor(28, hexagon, FieldsForMove);
        if (hexagon[37].getFillColor() == color) setColor(37, hexagon, FieldsForMove);
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);        break;

    } 
    case(30):
    {
        if (hexagon[29].getFillColor() == color) setColor(29, hexagon, FieldsForMove);
        if (hexagon[22].getFillColor() == color) setColor(22, hexagon, FieldsForMove);
        if (hexagon[37].getFillColor() == color) setColor(37, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);        break;

    }
    case(31):
    {
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);
        if (hexagon[32].getFillColor() == color) setColor(32, hexagon, FieldsForMove);
        if (hexagon[23].getFillColor() == color) setColor(23, hexagon, FieldsForMove);
        if (hexagon[24].getFillColor() == color) setColor(24, hexagon, FieldsForMove);
        if (hexagon[39].getFillColor() == color) setColor(39, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);        break;

    }
    case(32):
    {
        if (hexagon[24].getFillColor() == color) setColor(24, hexagon, FieldsForMove);
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[39].getFillColor() == color) setColor(39, hexagon, FieldsForMove);        break;

    }
    case(33):
    {
        if (hexagon[25].getFillColor() == color) setColor(25, hexagon, FieldsForMove);
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);
        if (hexagon[40].getFillColor() == color) setColor(40, hexagon, FieldsForMove);        break;

    }
    case(34):
    {
        if (hexagon[26].getFillColor() == color) setColor(26, hexagon, FieldsForMove);
        if (hexagon[27].getFillColor() == color) setColor(27, hexagon, FieldsForMove);
        if (hexagon[33].getFillColor() == color) setColor(33, hexagon, FieldsForMove);
        if (hexagon[35].getFillColor() == color) setColor(35, hexagon, FieldsForMove);
        if (hexagon[40].getFillColor() == color) setColor(40, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);        break;

    } 
    case(35):
    {
        if (hexagon[27].getFillColor() == color) setColor(27, hexagon, FieldsForMove);
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);
        if (hexagon[36].getFillColor() == color) setColor(36, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);        break;

    }
    case(36):
    {
        if (hexagon[35].getFillColor() == color) setColor(35, hexagon, FieldsForMove);
        if (hexagon[28].getFillColor() == color) setColor(28, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);
        if (hexagon[43].getFillColor() == color) setColor(43, hexagon, FieldsForMove);        break;

    }
    case(37):
    {
        if (hexagon[29].getFillColor() == color) setColor(29, hexagon, FieldsForMove);
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);
        if (hexagon[44].getFillColor() == color) setColor(44, hexagon, FieldsForMove);
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);        break;

    }
    case(38):
    {
        if (hexagon[37].getFillColor() == color) setColor(37, hexagon, FieldsForMove);
        if (hexagon[39].getFillColor() == color) setColor(39, hexagon, FieldsForMove);
        if (hexagon[30].getFillColor() == color) setColor(30, hexagon, FieldsForMove);
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);
        if (hexagon[46].getFillColor() == color) setColor(46, hexagon, FieldsForMove);        break;

    }

    case(39):
    {
        if (hexagon[31].getFillColor() == color) setColor(31, hexagon, FieldsForMove);
        if (hexagon[32].getFillColor() == color) setColor(32, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);
        if (hexagon[46].getFillColor() == color) setColor(46, hexagon, FieldsForMove);        break;

    }
    case(40):
    {
        if (hexagon[33].getFillColor() == color) setColor(33, hexagon, FieldsForMove);
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);
        if (hexagon[47].getFillColor() == color) setColor(47, hexagon, FieldsForMove);        break;

    }
    case(41):
    {
        if (hexagon[34].getFillColor() == color) setColor(34, hexagon, FieldsForMove);
        if (hexagon[35].getFillColor() == color) setColor(35, hexagon, FieldsForMove);
        if (hexagon[40].getFillColor() == color) setColor(40, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);
        if (hexagon[47].getFillColor() == color) setColor(47, hexagon, FieldsForMove);
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        break;
    }
    case(42):
    {
        if (hexagon[36].getFillColor() == color) setColor(36, hexagon, FieldsForMove);
        if (hexagon[35].getFillColor() == color) setColor(35, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);
        if (hexagon[43].getFillColor() == color) setColor(43, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        break;
    }
    case(43):
    {
        if (hexagon[36].getFillColor() == color) setColor(36, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);
        if (hexagon[44].getFillColor() == color) setColor(44, hexagon, FieldsForMove);
        if (hexagon[50].getFillColor() == color) setColor(50, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        break;
    }
    case(44):
    {
        if (hexagon[43].getFillColor() == color) setColor(43, hexagon, FieldsForMove);
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);
        if (hexagon[37].getFillColor() == color) setColor(37, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        break;
    }
    case(45):
    {
        if (hexagon[44].getFillColor() == color) setColor(44, hexagon, FieldsForMove);
        if (hexagon[46].getFillColor() == color) setColor(46, hexagon, FieldsForMove);
        if (hexagon[37].getFillColor() == color) setColor(37, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[52].getFillColor() == color) setColor(52, hexagon, FieldsForMove);
        break;
    }
    case(46):
    {
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);
        if (hexagon[38].getFillColor() == color) setColor(38, hexagon, FieldsForMove);
        if (hexagon[39].getFillColor() == color) setColor(39, hexagon, FieldsForMove);
        if (hexagon[52].getFillColor() == color) setColor(52, hexagon, FieldsForMove);
        break;
    }
    case(47):
    {
        if (hexagon[40].getFillColor() == color) setColor(40, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        if (hexagon[53].getFillColor() == color) setColor(53, hexagon, FieldsForMove);
        break;
    }
    case(48):
    {
        if (hexagon[47].getFillColor() == color) setColor(47, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        if (hexagon[41].getFillColor() == color) setColor(41, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);
        if (hexagon[53].getFillColor() == color) setColor(53, hexagon, FieldsForMove);
        if (hexagon[54].getFillColor() == color) setColor(54, hexagon, FieldsForMove);
        break;
    }
    case(49):
    {
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        if (hexagon[50].getFillColor() == color) setColor(50, hexagon, FieldsForMove);
        if (hexagon[43].getFillColor() == color) setColor(43, hexagon, FieldsForMove);
        if (hexagon[42].getFillColor() == color) setColor(42, hexagon, FieldsForMove);
        if (hexagon[55].getFillColor() == color) setColor(55, hexagon, FieldsForMove);
        if (hexagon[54].getFillColor() == color) setColor(54, hexagon, FieldsForMove);
        break;
    }
    case(50):
    {
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[43].getFillColor() == color) setColor(43, hexagon, FieldsForMove);
        if (hexagon[44].getFillColor() == color) setColor(44, hexagon, FieldsForMove);
        if (hexagon[55].getFillColor() == color) setColor(55, hexagon, FieldsForMove);
        if (hexagon[56].getFillColor() == color) setColor(56, hexagon, FieldsForMove);
        break;
    }
    case(51):
    {
        if (hexagon[50].getFillColor() == color) setColor(50, hexagon, FieldsForMove);
        if (hexagon[52].getFillColor() == color) setColor(52, hexagon, FieldsForMove);
        if (hexagon[44].getFillColor() == color) setColor(44, hexagon, FieldsForMove);
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);
        if (hexagon[56].getFillColor() == color) setColor(56, hexagon, FieldsForMove);
        if (hexagon[57].getFillColor() == color) setColor(57, hexagon, FieldsForMove);
        break;
    }
    case(52):
    {
        if (hexagon[45].getFillColor() == color) setColor(45, hexagon, FieldsForMove);
        if (hexagon[46].getFillColor() == color) setColor(46, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[57].getFillColor() == color) setColor(57, hexagon, FieldsForMove);
        break;
    }
    case(53):
    {
        if (hexagon[47].getFillColor() == color) setColor(47, hexagon, FieldsForMove);
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        if (hexagon[54].getFillColor() == color) setColor(54, hexagon, FieldsForMove);
        break;
    }
    case(54):
    {
        if (hexagon[48].getFillColor() == color) setColor(48, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        if (hexagon[55].getFillColor() == color) setColor(55, hexagon, FieldsForMove);
        break;
    }
    case(55):
    {
        if (hexagon[54].getFillColor() == color) setColor(54, hexagon, FieldsForMove);
        if (hexagon[56].getFillColor() == color) setColor(56, hexagon, FieldsForMove);
        if (hexagon[49].getFillColor() == color) setColor(49, hexagon, FieldsForMove);
        if (hexagon[50].getFillColor() == color) setColor(50, hexagon, FieldsForMove);
        break;
    case(56):
    {
        if (hexagon[55].getFillColor() == color) setColor(55, hexagon, FieldsForMove);
        if (hexagon[50].getFillColor() == color) setColor(50, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[57].getFillColor() == color) setColor(57, hexagon, FieldsForMove);
        break;
    }
    case(57):
    {
        if (hexagon[52].getFillColor() == color) setColor(52, hexagon, FieldsForMove);
        if (hexagon[51].getFillColor() == color) setColor(51, hexagon, FieldsForMove);
        if (hexagon[56].getFillColor() == color) setColor(56, hexagon, FieldsForMove);
        break;
    }
    }
    default:
        break;
    }   

    FieldsForMove.quickSort();
}