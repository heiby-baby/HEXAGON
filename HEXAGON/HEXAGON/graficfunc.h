#pragma once
#include "header.h"

void maketable(Vector<sf::ConvexShape>& hexagon) {
    
    sf::ConvexShape shape;
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
}

void Rendering(Vector<sf::ConvexShape>& hexagon, sf::RenderWindow& window) {
    for (int i = 0; i < hexagon.size(); i++) {
        window.draw(hexagon[i]);
    }
}