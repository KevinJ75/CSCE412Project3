#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <fstream>

/**
 * @class WebServer
 * @brief Represents a web server that processes requests.
 */
class WebServer {
public:
    bool isBusy;          /**< Indicates whether the web server is busy processing a request. */
    int remainingTime;    /**< Remaining time for the current request being processed. */
    int serverID;         /**< The unique ID of the web server. */

    /**
     * @brief Constructor to initialize the web server with a unique ID.
     * @param id The server's unique ID.
     */
    WebServer(int id);

    /**
     * @brief Processes a request assigned to this server.
     * @param request The request to be processed.
     * @param outFile The output file stream for logging the process.
     */
    void processRequest(const Request& request, std::ofstream& outFile);

    /**
     * @brief Updates the server's status based on clock cycle progression.
     * @param outFile The output file stream for logging status updates.
     */
    void update(std::ofstream& outFile);

    /**
     * @brief Checks if the server is available to take new requests.
     * @return True if the server is free, false if busy.
     */
    bool isAvailable() const;
};

#endif
