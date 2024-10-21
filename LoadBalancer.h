#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "Request.h"
#include <queue>
#include <vector>
#include <string>

/**
 * @class LoadBalancer
 * @brief This class represents a load balancer that manages web servers and request queues.
 */
class LoadBalancer {
public:
    std::queue<Request> requestQueue; /**< Queue to store incoming requests */
    std::vector<WebServer> servers;   /**< Vector of web servers managed by the load balancer */
    int baseNumServers;               /**< The base number of servers initialized */

    /**
     * @brief Constructor that initializes the load balancer with a given number of servers.
     * @param numServers The number of servers to initialize.
     */
    LoadBalancer(int numServers);

    /**
     * @brief Generates a new random request and adds it to the request queue.
     * @param outFile The output file stream to log the request generation.
     */
    void generateRequest(std::ofstream& outFile);

    /**
     * @brief Generates a burst of requests and adds them to the queue.
     * @param outFile The output file stream to log the burst request generation.
     * @param numRequests The number of requests to generate in the burst.
     */
    void generateBurstRequests(std::ofstream& outFile, int numRequests);

    /**
     * @brief Assigns requests from the queue to available web servers.
     * @param outFile The output file stream to log the assignment process.
     */
    void assignRequests(std::ofstream& outFile);

    /**
     * @brief Adds extra servers to handle load during burst periods.
     * @param extraServers The number of servers to add.
     */
    void scaleUpServers(int extraServers, std::ofstream& outFile);

    /**
     * @brief Removes extra servers once the burst period is handled.
     * @param extraServers The number of servers to remove.
     */
    void scaleDownServers(int extraServers, std::ofstream& outFile);

    /**
     * @brief Generates a random IP address in the format x.x.x.x.
     * @return A string representing a random IP address.
     */
    std::string generateRandomIp();

    /**
     * @brief Runs the load balancer simulation for a given number of clock cycles.
     * @param cycles The number of clock cycles to run the simulation.
     * @param outFile The output file stream to log the simulation progress.
     */
    void run(int cycles, std::ofstream& outFile);
};

#endif
