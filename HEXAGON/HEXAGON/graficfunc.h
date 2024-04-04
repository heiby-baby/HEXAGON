#pragma once
#include "header.h"

void maketable(Vector<sf::ConvexShape>& hexagon) {
    
    sf::ConvexShape shape;
    shape.setPointCount(6);          // ������������� ���������� �����
    const float radius = 40;         // ������ �����������������
    const float angle = 2 * PI / 6;  // ���� ����� ��������� ��������������
    const float  indention = 2 *  (radius - radius * sqrt(3) / 2);          //������ ����� ����������������
    // ������ ���������� �������� ��������������
    for (int i = 0; i < 6; ++i) {
        float x =  radius * std::cos(i * angle);
        float y =  radius * std::sin(i * angle);
        shape.setPoint(i, sf::Vector2f(x, y)); // ������������� ���������� �����
    }
    //1 ���   
    sf::Vector2f pos = { 300,300 };
    for (int i = 0; i < 5; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=   2 * radius + indention;
    }
    //2 ���
    pos = { 300,300 };
    pos = { pos.x + 2 * radius , pos.y -  radius  };
    for (int i = 0; i < 6; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    //3 ���
    pos = { 300,300 };
    pos = { pos.x + 4 * radius , pos.y -  2 * radius };
    for (int i = 0; i < 7; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention ;
    }
    //4 ���
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
    //5 ���
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
    //6 ���
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
     //7 ���
    pos = { 300,300 };
    pos = { pos.x + 12 * radius , pos.y -  2 * radius };
    for (int i = 0; i < 7; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius+ indention;
    }
    //8 ���
    pos = { 300,300 };
    pos = { pos.x + 14 * radius , pos.y -  radius  };
    for (int i = 0; i < 6; i++) {
        shape.setPosition(pos);
        hexagon.push_back(shape);
        pos.y +=  2 * radius + indention;
    }
    //9 ���   
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