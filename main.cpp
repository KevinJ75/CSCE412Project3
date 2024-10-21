#include "LoadBalancer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    int numServers, runTime;
    std::cout << "Enter the number of web servers: ";
    std::cin >> numServers;
    std::cout << "Enter the number of clock cycles to run the simulation: ";
    std::cin >> runTime;

    // Create an output file stream
    std::ofstream outFile("load_balancer_output.txt");
    if (!outFile) {
        std::cerr << "Failed to open file for writing!" << std::endl;
        return 1;
    }

    LoadBalancer lb(numServers);

    // Preload the request queue (usually servers * 100)
    for (int i = 0; i < numServers * 100; ++i) {
        lb.generateRequest(outFile);
    }

    lb.run(runTime, outFile);

    outFile.close(); 

    return 0;
}
