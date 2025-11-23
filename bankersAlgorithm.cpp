//Let N be the number of processes in the system and M be the number of resource types

//Includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

int main(){
    int n = 5; //Number of processes
    int m = 3; //Number of resources
    //Data Structures
    //Available: 1D array of size M holds number of available resources of each type
    std::vector<int> available;
    //Max: 2D array of size N*M that hold the maximum demand of each process in a system
    std::vector<std::vector<int>> max;
    //Allocation: A 2D array of size n*m that defines the number of resource of each type currently allocated to each process
    std::vector<std::vector<int>> allocation;
    //Need: 2D array of size N*M that indicates the remaining resource need of each process
    std::vector<std::vector<int>> need;

    //File IO to read in data
    std::ifstream input("input.txt");

    if(input.is_open()){std::cout << "File opened properly" << std::endl;} else {std::cout << "file could not open" << std::endl; return 0;}

    enum class Mode {none, allocation, max, available};
    Mode parseMode = Mode::none;
    std::string line;
    while(!input.eof()){
        std::getline(input, line);

        if(line[0] == '-'){//Changing what we are inputting
            if(line.find("allocation") != std::string::npos){
                parseMode = Mode::allocation;
            } else if(line.find("max") != std::string::npos){
                parseMode = Mode::max;
            } else if(line.find("available") != std::string::npos){
                parseMode = Mode::available;
            } else {
                std::cout << "Error Parsing: Likely incorrect input setup";
                return 0;
            }
        } else { //Filling data into vectors
            //Find and convert data
            std::vector<int> data = {line[0]-48, line[3]-48, line[6]-48};
            if(parseMode == Mode::allocation){
                allocation.push_back(data);
            } else if (parseMode == Mode::max){
                max.push_back(data);
            } else if (parseMode == Mode::available){
                available = data;
            }
        }
    }

    //File now ended, can close
    input.close();
    std::cout << "File closed" << std::endl;

    //Finds Need
    if(allocation.size() == max.size()){ //Size validation
        for(int i=0; i<max.size();++i){
            std::vector<int> value;
            for(int j=0; j<max[i].size();++j){
                value.push_back(max[i][j] - allocation[i][j]);
            }
            need.push_back(value);
        }
    }

    //Print Data
    std::cout << "Allocated: " << std::endl;
    for(int i = 0; i<allocation.size();i++){
        for(int j = 0; j < allocation[i].size(); j++){
            std::cout << allocation[i][j] << ", " << std::endl;
        }
    }

    std::cout << "Max: " << std::endl;
    for(int i = 0; i<max.size();i++){
        for(int j = 0; j < max[i].size(); j++){
            std::cout << max[i][j] << ", " << std::endl;
        }
    }

    std::cout << "Needed: " << std::endl;
    for(int i = 0; i<need.size();i++){
        for(int j = 0; j < need[i].size(); j++){
            std::cout << need[i][j] << ", " << std::endl;
        }
    }

    std::cout << "Available: " << std::endl;
    for(int i = 0; i<available.size();i++){
        std::cout << available[i] << ", " << std::endl;
    }

    std::vector<bool> finished(n, false);
    std::vector<int> progID(n);
    int currentInd = 0;


    for(int i=0; i<n;i++){
        for (int j=0; j<n; j++){
            if(finished[j] == false){
                bool flag = false;
                for(int k=0; k<m; k++) {
                    if(need[j][k] > available[k]){
                        flag = true;
                        break;
                    }
                }

                if(!flag){
                    progID[currentInd] = j;
                    currentInd++;
                    for(int x=0; x<m; x++){
                        available[x] += allocation[j][x];
                    }
                    finished[j] = true;
                }
            }
        }
    }

    bool safe = true;
    for(int i = 0; i<finished.size();i++){
        if(finished[i] == false){safe = false;}
    }
    std::cout << "SAFE SQUENCE: ";
    for(int i=0; i<n; i++){
        std::cout << "P" << progID[i];
        if( i != n-1){
            std::cout << " -> ";
        }
    }

    return 0;
}

