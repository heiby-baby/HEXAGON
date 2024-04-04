#pragma once
#include "header.h"

auto MakeMove(int VertexMove, Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int> FreeFields, bool move) {
	FreeFields.erase(binarySearch(FreeFields, VertexMove));
	Vector<int> WinningVertex;
	if (!move) {
		AiChekers.push_back_with_Sort(VertexMove);
		hexagon[VertexMove].setFillColor(sf::Color::Blue);
		MovesGenerator(VertexMove, hexagon, WinningVertex, sf::Color::Red);
		for (auto& i : WinningVertex) {
			hexagon[i].setFillColor(sf::Color::Blue);
		}
	}
	else {
		PlayerChekers.push_back_with_Sort(VertexMove);
		hexagon[VertexMove].setFillColor(sf::Color::Red);
		MovesGenerator(VertexMove, hexagon, WinningVertex, sf::Color::Blue);
		for (auto& i : WinningVertex) {
			hexagon[i].setFillColor(sf::Color::Red);
		}
	}
	return WinningVertex;
}

void UndoMove(int VertexMove, 
	Vector<sf::ConvexShape>& hexagon,
	Vector<int>& AiChekers, 
	Vector<int>& PlayerChekers,
	Vector<int> FreeFields,
	Vector<int> WinningMoves,
	bool move) {
	FreeFields.push_back_with_Sort(VertexMove);
	hexagon[VertexMove].setFillColor(sf::Color::White);
	for (auto& i : WinningMoves) {
		hexagon[i].setFillColor(sf::Color::White);
	}
	if (!move) {
		AiChekers.erase(binarySearch(AiChekers, VertexMove));
	}
	else {
		PlayerChekers.erase(binarySearch(PlayerChekers, VertexMove));
	}
}