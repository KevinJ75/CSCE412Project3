#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a web request to be handled by the load balancer.
 */
struct Request {
    std::string ipIn;    /**< Source IP address of the request. */
    std::string ipOut;   /**< Destination IP address of the request. */
    int time;            /**< Processing time in clock cycles. */
    char jobType;        /**< Job type ('P' for processing, 'S' for streaming). */

    /**
     * @brief Constructor to initialize a request.
     * @param in Source IP address.
     * @param out Destination IP address.
     * @param t Processing time.
     * @param type Job type.
     */
    Request(const std::string& in, const std::string& out, int t, char type);
};

#endif
