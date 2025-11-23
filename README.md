# Bankers Algorithm

## Installation
Clone this repository using 

` git clone https://github.com/Goatmanwaffles/OperatingSystemsAssignment2 `

and save the cloned repository on your device.

## Compilation
Use g++ to compile this program using 

` g++ -o bankersAlgorithm.exe bankersAlgorithm.cpp`

This will create an executable you can run by using

` ./bankersAlgorithm.exe `

## Explanation of Program
This program demonstrates the ideas behind the banker Algorithm used in deadlock avoidance. The idea behind this algorithm is to simulate resource allocation before granting resources to ensure that the system will always have a valid process execution error(safe state). This ensures the system never enters an unsafe state where deadlock becomes possible.

Bankers Algorithm relies on knowing the amount of resource available in the system, the resources currently allocated to each process and the max resource each process may eventually request. It uses this data to find the amount of each resource needed by a process (max-allocated)

### Data Input
This program inputs data using `input.txt`. This text file is structured into sections using a "-" character, with the data below being store per process. For example
```
-allocated

7, 4, 5
```
Denotes that process 0 has 7, 4, and 5 resource allocated.
To change the input values edit `input.txt`
### Code
```
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
```
This chunk of code initilizes the vectors we use to store the Available, Max, Allocated, and Needed data. It also initilizes the number of processes and number of resources we have (This will need to be edited if you change the input format).

```
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
```
This code handles our file input and parsing to get the data from `input.txt`. We make use of an enum Modeto track what data we are reading in and search for a "-" character to denote when we are changing section. If we dont find that dash we construct a vector of our data and push it into the correct vector based on our enum.

```
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
```
Here we calculate and populate the need vector by doing index by index subtraction between max and allocation.

```
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
```
Finally we perform the logic needed to determine a safe or unsafe state. We create a vectore of booleans to track which processes are already considered ran in our resource allocation. The first two for loops let us iterate fully over the vector of processes, if a process is not finished we check if it could run by comparing what we need to what is available. If the process could run we append the process ID to a vector for later printing the results and we add that processes allocated resource to the total available resource, and mark the process completed.

## Final Answer
Using this program and the sample data provided we find that the system is safe with the run order P3 -> P4 -> P1 -> P2 -> P0.