#pragma once
#include "header.h"

void print(Vector<int>& AiChekers, Vector<int>& PlayerChekers, Vector<int> FreeFields)
{
	std::cout << "AiChekers: " << AiChekers << std::endl;
	std::cout << "PlayerChekers: " << PlayerChekers << std::endl;
	std::cout << "FreeFields: " << FreeFields << std::endl;
}
template<typename T>
int binarySearch(const Vector<T>& vector, const T& key) {
	int low = 0;
	int high = vector.size() - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (vector[mid] == key) {
			return mid; // Ёлемент найден, возвращаем индекс
		}
		else if (vector[mid] < key) {
			low = mid + 1; // »скомый элемент находитс€ во второй половине
		}
		else {
			high = mid - 1; // »скомый элемент находитс€ в первой половине
		}
	}

	return -1; // Ёлемент не найден
}

