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

//mergesort complexity O(nlogn)
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

//partition selected using median of threes
int Algorithms::partition(std::vector<std::pair<int, char>>& arr, int low, int high) {
    //find median of three
    int mid = (high + low) / 2;
    int lowElement = arr[low].first;
    int midElement = arr[mid].first;
    int highElement = arr[high].first;
    int pivotIndex = high;
    if ((lowElement <= midElement && midElement <= highElement) ||
        (highElement <= midElement && midElement <= lowElement)) {
        pivotIndex = mid;
    }
    else if ((midElement <= lowElement && lowElement <= highElement) ||
             (highElement <= lowElement && lowElement <= midElement)) {
        pivotIndex = low;
    }
    std::swap(arr[pivotIndex], arr[high]);
    //performs partition
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

//quicksort complexity O(nlogn)
void Algorithms::quickSort(std::vector<std::pair<int, char>>& arr, int low, int high)
{
 //   printf("Quick Low %i High %i\n", low, high);
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

//shellsort complexity between O(nlogn) and O(n^2)
void Algorithms::shellSort(std::vector<std::pair<int, char>>& arr) {
    int gap = arr.size() / 2;
    while (gap > 0) {
        for (int i = gap; i < arr.size(); i++) {
            std::pair<int, char> temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap].first > temp.first) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}

//custom compare to create min priority queue
struct compare {
    bool operator()(const std::pair<int, char>& a, const std::pair<int, char>& b) {
        return a.first > b.first;
    }
};

//heapsort using priority queue for heap building, complexity O(nlogn)
void Algorithms::heapSort(std::vector<std::pair<int, char>>& arr) {
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, compare> pq;
    for (auto e : arr) {
        pq.push(e);
    }
    arr.clear();
    while (!pq.empty()) {
        arr.push_back(pq.top());
        pq.pop();
    }
}

//countingSort used for the implementation of radixSort
//only numbers 0 through 9 are accounted for, since it only examines one digit at a time
void Algorithms::countingSort(std::vector<std::pair<int, char>>& arr, int exp) {
    std::vector<std::pair<int, char>> temp(arr.size());
    int count[10] = { 0 }; //only examining digits 0-9
    //count frequency of each digit
    for (int i = 0; i < arr.size(); i++) {
        count[(arr[i].first / exp) % 10]++;
    }
    //count[i] contains position of digit
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    //temp vector is the output
    for (int i = arr.size() - 1; i >= 0; i--) {
        temp[count[(arr[i].first / exp) % 10] - 1] = arr[i];
        count[(arr[i].first / exp) % 10]--;
    }
    //update arr to be temp
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = temp[i];
    }
}

//radixSort implemented knowing the max number is 63
void Algorithms::radixSort(std::vector<std::pair<int, char>>& arr) {
    int max = 63;
    for (int exp = 1; max / exp > 0; exp *= 10) { //call countingSort for 1s and 10s places
        countingSort(arr, exp);
    }
}