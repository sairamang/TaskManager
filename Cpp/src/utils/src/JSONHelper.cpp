#include <JSONHelper.h>
#include <fstream>
#include <iostream>
#include <filesystem>
std::string JSONHelper::jsonDocToString(const rapidjson::Document &doc)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();
}
bool  JSONHelper::jsonFiletoDoc(const std::string& file_path , rapidjson::Document& json_doc){
    int filesize = 0;
    std::ifstream my_file(file_path.c_str(), std::ios::binary | std::ios::ate);
    if (!std::filesystem::is_regular_file(file_path)){
        return false;
    }
    if (my_file.is_open())
    {
        filesize = my_file.tellg();
        my_file.seekg(0, std::ios::beg);

        char *buffer = new char[filesize + 1];
        my_file.read(buffer, filesize);
        buffer[filesize] = '\0';
        my_file.close();
        json_doc.Parse(buffer);
        std::cout << "string " << jsonDocToString(json_doc) << std::endl;
        return true;
    }
    return false;
}