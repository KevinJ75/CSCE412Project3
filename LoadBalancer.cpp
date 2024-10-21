#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Constructor to initialize the load balancer with a base number of servers.
 * @param numServers Number of web servers to initialize.
 */
LoadBalancer::LoadBalancer(int numServers) : baseNumServers(numServers) {
    srand(static_cast<unsigned>(time(nullptr)));  // Seed for random number generation
    for (int i = 1; i <= numServers; ++i) {
        servers.emplace_back(i);  // Create servers with unique IDs
    }
}

/**
 * @brief Generates a new random request and adds it to the request queue.
 * @param outFile Output file stream for logging the request generation.
 */
void LoadBalancer::generateRequest(std::ofstream& outFile) {
    std::string ipIn = generateRandomIp();
    std::string ipOut = generateRandomIp();
    int time = rand() % 10 + 1;  // Random processing time between 1 and 10 cycles
    char jobType = (rand() % 2 == 0) ? 'P' : 'S';  // Random job type (P or S)
    Request newRequest(ipIn, ipOut, time, jobType);

    requestQueue.push(newRequest);
    outFile << "Generated Request from " << ipIn << " to " << ipOut 
            << " (Time: " << time << " cycles, Type: " << jobType << ")\n";
}

/**
 * @brief Generates a burst of requests and adds them to the request queue.
 * @param outFile Output file stream for logging the burst request generation.
 * @param numRequests Number of requests to generate during the burst period.
 */
void LoadBalancer::generateBurstRequests(std::ofstream& outFile, int numRequests) {
    for (int i = 0; i < numRequests; ++i) {
        generateRequest(outFile);
    }
}

/**
 * @brief Assigns requests from the queue to available servers.
 * @param outFile Output file stream for logging the assignment of requests.
 */
void LoadBalancer::assignRequests(std::ofstream& outFile) {
    for (WebServer& server : servers) {
        if (server.isAvailable() && !requestQueue.empty()) {
            Request req = requestQueue.front();
            requestQueue.pop();
            // outFile << "Server " << server.serverID 
            //         << " is Processing request from " << req.ipIn << " to " << req.ipOut 
            //         << " (Time: " << req.time << " cycles)\n";
            server.processRequest(req, outFile);
        }
    }
}

/**
 * @brief Adds extra servers during a burst period.
 * @param extraServers Number of servers to add.
 */
void LoadBalancer::scaleUpServers(int extraServers, std::ofstream& outFile) {
    for (int i = 1; i <= extraServers; ++i) {
        servers.emplace_back(baseNumServers + i);  // Add extra servers
    }
    outFile << "Scaling up number of servers.\n";
}

/**
 * @brief Removes extra servers after handling a burst period.
 * @param extraServers Number of servers to remove.
 */
void LoadBalancer::scaleDownServers(int extraServers, std::ofstream& outFile) {
    for (int i = 0; i < extraServers; ++i) {
        servers.pop_back();  // Remove extra servers
    }
}

/**
 * @brief Generates a random IP address.
 * @return A randomly generated IP address.
 */
std::string LoadBalancer::generateRandomIp() {
    return std::to_string(rand() % 256) + "." + std::to_string(rand() % 256) + "." + 
           std::to_string(rand() % 256) + "." + std::to_string(rand() % 256);
}

/**
 * @brief Runs the load balancer simulation for a specified number of cycles.
 * @param cycles The number of clock cycles to simulate.
 * @param outFile Output file stream for logging the simulation process.
 */
void LoadBalancer::run(int cycles, std::ofstream& outFile) {
    int burstPoint = cycles / 2;  // Generate burst halfway through
    for (int i = 0; i < cycles; ++i) {
        
        outFile << "Cycle " << i + 1 << ":\n";
        if (i == burstPoint) {
            outFile << "Burst of 8000 requests generated.\n";
            generateBurstRequests(outFile, 8000);
            scaleUpServers(5, outFile);  // Add 5 servers
        }

        if (rand() % 5 == 0) {
            generateRequest(outFile);  // Randomly generate new requests
        }
        assignRequests(outFile);   // Assign requests to servers

        for (WebServer& server : servers) {
            server.update(outFile);  // Update the status of each server
        }

        if (i == burstPoint + 2000) {
            outFile << "Scaling down the extra servers.\n";
            scaleDownServers(5, outFile);  // Scale down the extra servers
        }
    }
    outFile << "Queue size: " << requestQueue.size() << std::endl;
}
