#pragma once
#include "pch.h"
class Algorithms {

private:


public:
	bool bubbleSortWithPrint(std::vector<std::string>& arr, std::string* buff);

	void merge(std::vector<std::pair<int, char>>& arr, int left, int mid, int right);

	void mergeSort(std::vector<std::pair<int, char>>& arr, int left, int right);

	int partition(std::vector<std::pair<int, char>>& arr, int low, int high);

	void quickSort(std::vector<std::pair<int, char>>& arr, int low, int high);

	void shellSort(std::vector<std::pair<int, char>>& arr);

	void heapSort(std::vector<std::pair<int, char>>& arr);
};