#pragma once
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>
#include <string>

class JSONHelper
{
public:
    static std::string jsonDocToString(const rapidjson::Document &doc);
    static bool jsonFiletoDoc(const std::string &file_path, rapidjson::Document &doc);
};