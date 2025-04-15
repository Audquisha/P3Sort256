#include "gui.h"

//Generate a string of length min-max with ASCII Values between 33-125
std::string randomStringGen(int min, int max) {

    std::string result = "";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    std::uniform_int_distribution<> charRand(33, 125);


    int charCount = dist(gen);
    
    for (int i = 0; i < charCount; i++) {
        result += (char)(charRand(gen));
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> dataGeneration() {

    std::vector<std::pair<std::string, std::string>> randomTuples;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100000);

    int entryCount = dist(gen);
    
    for (int i = 0; i < entryCount; i++) {
        std::pair<std::string, std::string> temp;
        temp.first = randomStringGen(1, 10);
        temp.second = randomStringGen(1, 100);
        randomTuples.push_back(temp);
    }

    return randomTuples;
}

void writeDataFile(std::vector<std::pair<std::string, std::string>> data) {

    std::string buffer;
    for (int i = 0; i < data.size(); i++) {
        buffer += data[i].first + "," + data[i].second + "\n";
    }

    std::ofstream fout;

    fout.open("data.txt", std::ios::binary | std::ios::out);

    fout.write(buffer.c_str(), buffer.size());

    fout.close();
}

void writeKeyFile(std::vector<int> orderOfKeys) {

    std::string buffer;
    for (int i = 0; i < orderOfKeys.size(); i++) {
        buffer += "["+ std::to_string(i) + "] " + std::to_string(orderOfKeys[i]) + "\n";
    }

    std::ofstream fout;

    fout.open("keys.txt", std::ios::binary | std::ios::out);

    fout.write(buffer.c_str(), buffer.size());

    fout.close();
}

std::vector<std::pair<std::string, std::string>> readDataFile() {

    std::ifstream fin;
    
    fin.open("data.txt", std::ios::binary | std::ios::in);
   
    std::stringstream buffer;
    buffer << fin.rdbuf();

    std::string content = buffer.str();

    fin.close();

    std::vector<std::pair<std::string, std::string>> temp;
    while (content.size()) {
        std::istringstream iss(content);

        std::string line;
        std::getline(iss, line);

        size_t comma_pos = line.find(',');

        std::pair<std::string, std::string> tempPair;
        tempPair.first = line.substr(0, comma_pos);
        tempPair.second = line.substr(comma_pos + 1);
        temp.push_back(tempPair);
        content.erase(0, line.size() + 1);
    }
    return temp;
}



enum displayTab : uint8_t {

    keyOrder = 0,
    stringInput = 1


};

std::string progressBuff;
std::vector<int> orderOfKeys;
displayTab currProfile = keyOrder;
std::vector<std::pair<std::string, std::string>> randomStrings =
{ //Names        //Passwords
 {"A3f2P0zB9K", "fuckme1"},
 {"D9J8M3iV4X", "fuckme2"},
 {"C2wD9G5rL0", "fuckme3"},
 {"P0hC8zF9L1", "fuckme4"},
 {"J1Z4K7bY9T", "fuckme5"},
 {"T4B3N5kM1Q", "fuckme6"},
 {"V3zY5N4WqR", "fuckme7"},
 {"S9X2B0kC1N", "fuckme8"},
 {"O4A6dZ5F2T", "fuckme9"},
 {"N2S5R8bP0C", "fuckme10"},
 {"M6V2W8rD5T", "fuckme11"},
 {"I058M4zK7W", "fuckme12"},
 {"U9F15L3J4X", "fuckme13"},
 {"D9F12L3J4X", "fuckme14"},
};
bool isHashed = false;
bool isSorted = false;
std::string consoleOutput;

void gui::menuDrawing()
{
   

    Algorithms algo;
    HashAlgorithm hashAlgo;
  


    auto style = ImGui::GetStyle();
    ImFont* Font = ImGui::GetFont();

    ImVec2 menuDimensions = ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);


    ImGui::SetNextWindowSize(menuDimensions);


    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoDecoration);
    {
        ImGui::Text("SHA256 Implementation By Max Schwarz, Christian Taylor, Ryan Kratz");
       
        ImGui::SetCursorPos(ImVec2(menuDimensions.x / 5 * .3f + menuDimensions.x / 5+ 1.1*menuDimensions.x / 3, menuDimensions.y / 16));
        ImGui::BeginChild("#Console", ImVec2(menuDimensions.x / 3, 14 * menuDimensions.y / 16), true, ImGuiWindowFlags_NoDecoration);
        {
            ImGui::Text("%s", consoleOutput.c_str());
        }
        ImGui::EndChild();

        // Converts string passwords to hashes by refrence and returns a random vector with #s from 0-31 in random assortment that map to each char
        // ex. if we have a hashed password of abcdefghi and a key vector of {8,7,6,5,4,3,2,1,0} then the sorted password should end as ihgfedcba
       // std::vector<int> orderOfKeys = hashAlgo.convertInputToHash(randomStrings);
        ImGui::SetCursorPos(ImVec2(menuDimensions.x / 5 * .3f + menuDimensions.x / 5, menuDimensions.y / 16));

      //  ImGui::SetCursorPos(ImVec2(menuDimensions.x / 5 * 3.8f, menuDimensions.y / 16));
        ImGui::BeginChild("#Strings", ImVec2(menuDimensions.x / 3, 14 * menuDimensions.y / 16), true, ImGuiWindowFlags_NoDecoration);
        {
            float xPos = ImGui::GetCursorPosX();
            if (ImGui::Button("Key Order", ImVec2(.45* menuDimensions.x / 3, menuDimensions.y / 16))) {
                currProfile = keyOrder;
            }
            ImGui::SameLine();
            ImGui::SetCursorPosX(xPos+ .5 * menuDimensions.x / 3);

            if (ImGui::Button("String Input", ImVec2(.45 * menuDimensions.x / 3, menuDimensions.y / 16))) {
                currProfile = stringInput;
            }
            if (currProfile == keyOrder) {
                for (int i = 0; i < orderOfKeys.size(); i++) {
                    ImGui::Text("[%i] %i", i, orderOfKeys[i]);

                }
            }
            else if (currProfile == stringInput) {
                for (int i = 0; i < randomStrings.size(); i++) {
                    ImGui::Text("[%i] %s %s", i, randomStrings[i].first.c_str(), randomStrings[i].second.c_str());
                }
                
            }
          
        }
        ImGui::EndChild();

        ImGui::SetCursorPos(ImVec2(menuDimensions.x / 5 * .2f, menuDimensions.y / 16));
        ImGui::BeginChild("#Data", ImVec2(menuDimensions.x / 5, 9.5 * menuDimensions.y / 16), true, ImGuiWindowFlags_NoDecoration);
        {
            if (ImGui::Button("Randomly Generate Data", ImVec2(.9*menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16) )){
                //Random Generate Data Function
                randomStrings = dataGeneration();
                consoleOutput += "[+] Data of Size " + std::to_string(randomStrings.size()) + " Generated Succesfully!\n";

                isHashed = false;
                isSorted = false;

            }
            
            if (ImGui::Button("Import Data", ImVec2(.9*menuDimensions.x / 5, .4 * 3 *menuDimensions.y / 16))) {
                //Add Random Generate Data Function
                randomStrings = readDataFile();
                consoleOutput += "[+] Data of Size " + std::to_string(randomStrings.size()) + " Imported Succesfully!\n";

                isHashed = false;
                isSorted = false;
            }

            if (ImGui::Button("Hash Data", ImVec2(.9 * menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16))) {
                if (!isHashed) {
                    clock_t tempTime = clock();
                    orderOfKeys = hashAlgo.convertInputToHash(randomStrings);
                    tempTime = clock() - tempTime;
                    consoleOutput += "[+] Hashing Completed In " + std::to_string((float)tempTime/ CLOCKS_PER_SEC) + " Seconds!\n";

                    isHashed = true;
                    consoleOutput += "[+] Successfully Hashed!\n";

                }
                else {
                    consoleOutput += "[!] Already Hashed!\n";
                }
            }
            if (ImGui::Button("Write Data File", ImVec2(.9 * menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16))) {
                clock_t tempTime = clock();
                writeDataFile(randomStrings);
                tempTime = clock() - tempTime;
                consoleOutput += "[+] Data Written to File In " + std::to_string((float)tempTime / CLOCKS_PER_SEC) + " Seconds!\n";

                consoleOutput += "[+] Data Written To File!\n";

            }
            if (ImGui::Button("Write Keys File", ImVec2(.9 * menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16))) {
                writeKeyFile(orderOfKeys);
                consoleOutput += "[+] Keys Written To File!\n";

            }
            if (ImGui::Button("Merge Sort", ImVec2(.9 * menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16))) {
                if (isHashed) {
                    if (!isSorted) {
                        clock_t tempTime = clock();


                        for (int j = 0; j < randomStrings.size(); j++) {
                            std::vector<std::pair<int, char>> arr;

                            int i = 0;
                            for (int k = 0; k < randomStrings[j].second.size(); k++) {
                                arr.push_back({ orderOfKeys[i++], randomStrings[j].second[k] });
                            }
                            algo.mergeSort(arr, 0, arr.size() - 1);
                            std::string finished;
                            for (int k = 0; k < arr.size(); k++) {
                                finished += arr[k].second;
                            }
                            randomStrings[j].second = finished;
                        }
                        isSorted = true;
                        tempTime = clock() - tempTime;
                        consoleOutput += "[+] Merge Sort Completed In " + std::to_string((float)tempTime / CLOCKS_PER_SEC) + " Seconds!\n";

                        consoleOutput += "[+] Successfully Sorted!\n";

                    }
                    else {
                        consoleOutput += "[!] Already Sorted!\n";

                    }
                }
                else {
                    consoleOutput += "[!] Must Be Hashed Before Being Sorted!\n";

                }
               


            }
            if (ImGui::Button("Quick Sort", ImVec2(.9 * menuDimensions.x / 5, .4 * 3 * menuDimensions.y / 16))) {
                if (isHashed) {

                    if (!isSorted) {
                        clock_t tempTime = clock();

                        progressBuff = "";

                        for (int j = 0; j < randomStrings.size(); j++) {
                            std::vector<std::pair<int, char>> arr;

                            int i = 0;
                            for (int k = 0; k < randomStrings[j].second.size(); k++) {
                                arr.push_back({ orderOfKeys[i++], randomStrings[j].second[k] });
                            }
                            algo.quickSort(arr, 0, arr.size() - 1);
                            std::string finished;
                            for (int k = 0; k < arr.size(); k++) {
                                finished += arr[k].second;
                            }
                            randomStrings[j].second = finished;
                        }
                        isSorted = true;
                        tempTime = clock() - tempTime;
                        consoleOutput += "[+] Quick Sort Completed In " + std::to_string((float)tempTime / CLOCKS_PER_SEC) + " Seconds!\n";

                        consoleOutput += "[+] Successfully Sorted!\n";

                    }
                    else {
                        consoleOutput += "[!] Already Sorted!\n";

                    }
                }
                else {
                    consoleOutput += "[!] Must Be Hashed Before Being Sorted!\n";

                }

            }

        }
        ImGui::EndChild();

       

    }
    ImGui::End();
}