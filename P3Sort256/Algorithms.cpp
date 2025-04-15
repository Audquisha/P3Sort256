#include "Algorithms.h"

// Bubble Sort function without callback, printing the array after each pass
bool Algorithms::bubbleSortWithPrint(std::vector<std::string>& arr, std::string* buff) {
    size_t n = arr.size();
    bool swapped;

    // Outer loop for passes
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;

        // Inner loop for comparisons
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are in the wrong order
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Print the array after each pass
        if (swapped) {
            break;
        }


        // If no elements were swapped, the list is already sorted

    }
    for (int i = 0; i < arr.size(); i++) {
        *buff += arr[i]; *buff += "\n";
    }
    return swapped;
}

//code inspired from sorting lecture slides
void Algorithms::merge(std::vector<std::pair<int, char>>& arr, int left, int mid, int right) {
    //create a left array from left to mid and a right array from mid + 1 to right
    int leftSize = mid - left +1;
    int rightSize = right - mid;

    std::vector<std::pair<int, char>> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<std::pair<int, char>> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftSize && j < rightSize) {
        if (leftArr[i].first <= rightArr[j].first) {
            arr[k++] = leftArr[i++];
        }
        else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightSize) {
        arr[k++] = rightArr[j++];
    }
}

//takes in an array of int, each int corresponds to the weight of the char as designated by the sha256 algorithm
void Algorithms::mergeSort(std::vector<std::pair<int, char>>& arr, int left, int right)
{
       //printf("Quick Left %i Right %i\n", left, right);

   // ImGui::Text("Merge Sort Called!");
    if (left < right) {
        //divide into two arrays at middle
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //merge the two subarrays
        merge(arr, left, mid, right);
    }
}

//code inspired from sorting lecture slides
int Algorithms::partition(std::vector<std::pair<int, char>>& arr, int low, int high) {
    int pivot = arr[high].first;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].first < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Algorithms::quickSort(std::vector<std::pair<int, char>>& arr, int low, int high)
{
 //   printf("Quick Low %i High %i\n", low, high);
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}
