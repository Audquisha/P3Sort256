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

void Algorithms::mergeSort(std::vector<std::string> data, std::string* buff)
{
	ImGui::Text("Merge Sort Called!");

	//Helper Function for each pass

	
    for (int i = 0; i < data.size(); i++) {
        *buff += data[i]; *buff += "\n";
    }
	 
}

void Algorithms::quickSort(std::vector<std::string> data)
{
	ImGui::Text("Quick Sort Called!");

}
