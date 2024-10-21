#include "Request.h"

/**
 * @brief Constructor to initialize a web request with specific IP addresses, processing time, and job type.
 * 
 * @param in Source IP address of the request.
 * @param out Destination IP address of the request.
 * @param t Processing time in clock cycles.
 * @param type Job type, 'P' for processing and 'S' for streaming.
 */
Request::Request(const std::string& in, const std::string& out, int t, char type)
    : ipIn(in), ipOut(out), time(t), jobType(type) {}
