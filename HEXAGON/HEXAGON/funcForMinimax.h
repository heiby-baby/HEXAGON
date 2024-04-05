#pragma once
#include "header.h"

int Evalution(Vector<int> AiChekers, Vector<int> PlayerChekers) {
	return PlayerChekers.size() - AiChekers.size();
}

bool GameValid(Vector<sf::ConvexShape>& hexagon, Vector<int> AiChekers, Vector<int> PlayerChekers, int move) {
	Vector<int> FieldsForMove;
	if (AiChekers.size() == 0) {
		return false;
	}
	else if (PlayerChekers.size() == 0) {
		return false;
	}
	bool flag = false;
	if (move) {
		for (auto& i : PlayerChekers) {
			MovesGenerator(i, hexagon, FieldsForMove, sf::Color::White);
			if (!FieldsForMove.empty())
			{	
				return true;
			};
		}
	}
	else {
		for (auto& i : AiChekers) {
			MovesGenerator(i, hexagon, FieldsForMove, sf::Color::White);
			if (!FieldsForMove.empty()) return true;
		}
	}
	return false;
}


auto MakeMove(int VertexMove, Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int>& FreeFields, bool move) {
	FreeFields.erase(binarySearch(FreeFields, VertexMove));
	Vector<int> WinningVertex;
	if (!move) {
		AiChekers.push_back_with_Sort(VertexMove);
		hexagon[VertexMove].setFillColor(sf::Color::Blue);
		MovesGenerator(VertexMove, hexagon, WinningVertex, sf::Color::Red);
		for (auto& i : WinningVertex) {
			hexagon[i].setFillColor(sf::Color::Blue);
			PlayerChekers.erase(binarySearch(PlayerChekers, i));
			AiChekers.push_back_with_Sort(i);
		}
	}
	else {
		PlayerChekers.push_back_with_Sort(VertexMove);
		hexagon[VertexMove].setFillColor(sf::Color::Red);
		MovesGenerator(VertexMove, hexagon, WinningVertex, sf::Color::Blue);
		for (auto& i : WinningVertex) {
			hexagon[i].setFillColor(sf::Color::Red);
			AiChekers.erase(binarySearch(AiChekers, i));
			PlayerChekers.push_back_with_Sort(i);
		}
	}
	return WinningVertex;
}

void UndoMove(int VertexMove, Vector<sf::ConvexShape>& hexagon, Vector<int>& AiChekers,	Vector<int>& PlayerChekers, Vector<int>& FreeFields, Vector<int>& WinningMoves, bool move) {
	FreeFields.push_back_with_Sort(VertexMove);
	hexagon[VertexMove].setFillColor(sf::Color::White);
	if (!move) {
		AiChekers.erase(binarySearch(AiChekers, VertexMove));
		for (auto& i : WinningMoves) {
			hexagon[i].setFillColor(sf::Color::Red);
			PlayerChekers.push_back_with_Sort(i);
			AiChekers.erase(binarySearch(AiChekers, i));
		}
	}
	else {
		PlayerChekers.erase(binarySearch(PlayerChekers, VertexMove));
		for (auto& i : WinningMoves) {
			hexagon[i].setFillColor(sf::Color::Blue);
			AiChekers.push_back_with_Sort(i);
			PlayerChekers.erase(binarySearch(PlayerChekers, i));
		}
	}
}