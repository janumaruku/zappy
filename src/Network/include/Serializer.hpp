/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#ifndef MY_TEAMS_SERIALIZER_HPP
#define MY_TEAMS_SERIALIZER_HPP

#include "jsonParser.hpp"

namespace network {
enum class Method: uint8_t {
    GET,
    POST,
    PUT,
    DELETE
};

enum class StatusCode: uint16_t {
    STATUS_OK          = 200,
    UNAUTHORIZED       = 401,
    NOT_FOUND          = 404,
    METHOD_NOT_ALLOWED = 405
};
}

using Request = struct Request {
    network::Method method;
    std::string path;
    nlohmann::json body;
};

using Response = struct Response {
    network::StatusCode statusCode;
    std::string statusMessage;
    nlohmann::json body = {};
};


namespace nlohmann {
template<>
struct adl_serializer<Request> {
    static void to_json(json &j, const Request &r);
    static void from_json(const json &j, Request &r);
};

template<>
struct adl_serializer<Response> {
    static void to_json(json &j, const Response &r);
    static void from_json(const json &j, Response &r);
};

}

#endif
