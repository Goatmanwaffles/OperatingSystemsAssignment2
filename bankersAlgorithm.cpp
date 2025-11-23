//Let N be the number of processes in the system and M be the number of resource types

//Includes
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(){
    bool debug = false;
    int n = 5; //Number of processes
    int m = 3; //Number of resources
    //Data Structures

    //Available: 1D array of size M holds number of available resources of each type
    std::vector<int> available = {3, 2, 2};
    //Max: 2D array of size N*M that hold the maximum demand of each process in a system
    std::vector<std::vector<int>> max = {{7, 5, 3}, {3, 3, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    //Allocation: A 2D array of size n*m that defines the number of resource of each type currently allocated to each process
    std::vector<std::vector<int>> allocation = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 2, 1}, {0, 0, 2}};
    //Need: 2D array of size N*M that indicates the remaining resource need of each process
    std::vector<std::vector<int>> need;

    //Initilize test values from instructions
    //3 Resource types A B C
    //5 Processes p0 p1 p2 p3 p4
    //   Allocation       Max        Available
    //   A   B   C     A   B   C     A   B   C
    //p0 0   1   0     7   5   3     3   2   2
    //p1 2   0   0     3   3   2
    //p2 3   0   2     9   0   2
    //p3 2   2   1     2   2   2
    //p4 0   0   2     4   3   3
    //Find Need
    if(allocation.size() == max.size()){ //Size validation
        for(int i=0; i<max.size();++i){
            std::vector<int> value;
            for(int j=0; j<max[i].size();++j){
                value.push_back(max[i][j] - allocation[i][j]);
            }
            need.push_back(value);
        }
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
    std::cout << "SAFE SQUENCE: ";
    for(int i=0; i<n; i++){
        std::cout << "P" << progID[i];
        if( i != n-1){
            std::cout << " -> ";
        }
    }

    return 0;
}

