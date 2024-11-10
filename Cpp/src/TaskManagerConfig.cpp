#include <TaskManagerConfig.h>
#include <rapidjson.h>
#include <document.h>
#include <stream.h>
#include <filereadstream.h>
#include <stringbuffer.h>
#include <writer.h>
#include <iostream>
#include <fstream>

TaskManagerConfig::TaskManagerConfig(std::string config_path)
{
    std::cout << "Task Manager Config" << std::endl;
    m_config_path = config_path;
}
TaskManagerConfig::~TaskManagerConfig()
{
    std::cout << "Task Manager Config deletion" << std::endl;
}
std::string jsonDocToString(const rapidjson::Document &doc)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    return buffer.GetString();
}
TaskManagerConfig_t &TaskManagerConfig::GetConfig()
{
    return m_task_manager_config;
}
void TaskManagerConfig::parse()
{
    rapidjson::Document rapidjson_doc;
    int filesize = 0;
    std::ifstream my_file(m_config_path.c_str(), std::ios::binary | std::ios::ate);
    if (my_file.is_open())
    {
        filesize = my_file.tellg();
        my_file.seekg(0, std::ios::beg);

        char *buffer = new char[filesize + 1];
        my_file.read(buffer, filesize);
        buffer[filesize] = '\0';
        my_file.close();

        rapidjson_doc.Parse(buffer);

        m_task_manager_config.task_data = rapidjson_doc["TaskData"].GetString();
        std::cout << "string " << jsonDocToString(rapidjson_doc) << std::endl;
    }
}