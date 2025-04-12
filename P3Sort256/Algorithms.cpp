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
void Algorithms::merge(int data[], int left, int mid, int right) {
    //create a left array from left to mid and a right array from mid + 1 to right
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    std::vector<int> leftArray(leftSize);
    std::vector<int> rightArray(rightSize);

    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = data[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = data[mid + 1 + i];
    }

    //Merge the arrays into data
    int i, j, k;
    i = 0; //current index for left array
    j = 0; //current index for right array
    k = left; //current index for data
    while (i < leftSize && j < rightSize) {
        //while both the left and right subarrays are not empty, append the smaller element to data and incrememnt the index
        if (leftArray[i] <= rightArray[j]) {
            data[k] = leftArray[i];
            i++;
        }
        else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }
    //when one of the subarrays becomes empty, append the remaining elements in the other array to the data
    while (i < leftSize) {
        data[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        data[k] = rightArray[j];
        j++;
        k++;
    }
}

//takes in an array of int, each int corresponds to the weight of the char as designated by the sha256 algorithm
void Algorithms::mergeSort(int data[], int left, int right)
{
	ImGui::Text("Merge Sort Called!");
    if (left < right) {
        //divide into two arrays at middle
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);

        //merge the two subarrays
        merge(data, left, mid, right);
    }
}

//code inspired from sorting lecture slides
int Algorithms::partition(int data[], int low, int high) {
    int mid = low + (high - low) / 2; //calculate middle index

    //calculate the median of threes for optimal quicksort
    int pivot = high;
    if ((data[low] <= data[mid] && data[mid] <= data[high]) || (data[high] <= data[mid] && data[mid] <= data[low])) {
        pivot = data[mid];
    }
    else if ((data[mid] <= data[low] && data[low] <= data[high]) || (data[high] <= data[low] && data[low] <= data[mid])) {
        pivot = data[low];
    }

    int up = low, down = high;
    
    while (up < down) {
        for (int i = up; i < high; i++) {
            if (data[up] > pivot) {
                break;
            }
            up++;
        }
        for (int i = high; i > low; i--) {
            if (data[down] < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            int temp = data[up];
            data[up] = data[down];
            data[down] = temp;
        }
    }
    int temp = data[low];
    data[low] = data[down];
    data[down] = temp;
    return down;
}

void Algorithms::quickSort(int data[], int low, int high)
{
	ImGui::Text("Quick Sort Called!");
    if (low < high) {
        int pivot = partition(data, low, high);
        quickSort(data, low, pivot - 1);
        quickSort(data, pivot + 1, high);
    }
}
