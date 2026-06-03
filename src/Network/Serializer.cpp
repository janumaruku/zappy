/*
** EPITECH PROJECT, 2026
** NTWK
** File description:
** 
*/

#include <exception>
#include <format>
#include <string>
#include "Serializer.hpp"

#include "include/Router.hpp"

namespace nlohmann {

void adl_serializer<Request>::to_json(json &j, const Request &req)
{
    j["method"] = req.method;
    j["path"]   = req.path;
    j["body"]   = req.body;
}


void adl_serializer<Request>::from_json(const json &j, Request &req)
{
    try {
        req.method = j.at("method").get<network::Method>();
        req.path   = j.at("path").get<std::string>();
        req.body   = j.at("body").get<json>();
    } catch (std::exception &e) {
		throw;
	}
}

void adl_serializer<Response>::to_json(json &j, const Response &rep)
{
    j["status_code"]    = rep.statusCode;
    j["status_message"] = rep.statusMessage;
    j["body"]           = rep.body;
}

void adl_serializer<Response>::from_json(const json &j, Response &rep)
{
    try {
        rep.statusCode    = j.at("status_code").get<network::StatusCode>();
        rep.statusMessage = j.at("status_message").get<std::string>();
        rep.body          = j.at("body").get<json>();
    } catch (std::exception &e) {
		throw;
	}
}
}
