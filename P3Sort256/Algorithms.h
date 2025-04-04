#pragma once
#include "pch.h"
class Algorithms {

private:
    

public:
	bool bubbleSortWithPrint(std::vector<std::string>& arr, std::string* buff);

	void merge(int data[], int left, int mid, int right);

	void mergeSort(int data[], int left, int right);

	int partition(int data[], int low, int high);

	void quickSort(int data[], int low, int high);
};