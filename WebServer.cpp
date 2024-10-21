#include "WebServer.h"
#include <iostream>

/**
 * @brief Constructor that initializes the server with a unique ID.
 * @param id The server's unique ID.
 */
WebServer::WebServer(int id) : isBusy(false), remainingTime(0), serverID(id) {}

/**
 * @brief Processes a request assigned to this server.
 * @param request The request to be processed.
 * @param outFile Output file stream for logging the process.
 */
void WebServer::processRequest(const Request& request, std::ofstream& outFile) {
    isBusy = true;
    remainingTime = request.time;
    outFile << "Server " << serverID << " has started processing a request from " 
            << request.ipIn << " to " << request.ipOut << " (Time: " << remainingTime << " cycles)\n";
}

/**
 * @brief Updates the server's status as time progresses.
 * @param outFile Output file stream for logging the update.
 */
void WebServer::update(std::ofstream& outFile) {
    if (isBusy) {
        --remainingTime;
        if (remainingTime <= 0) {
            isBusy = false;
            outFile << "Server " << serverID << " has completed the request.\n";
        }
    }
}

/**
 * @brief Checks if the server is available for new requests.
 * @return True if the server is free, false if busy.
 */
bool WebServer::isAvailable() const {
    return !isBusy;
}
