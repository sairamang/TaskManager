#include <TaskManagerConfig.h>
#include <JSONHelper.h>
#include <iostream>
#include <filesystem>
TaskManagerConfig::TaskManagerConfig(std::string config_path)
{
    std::cout << "Task Manager Config" << std::endl;
    m_config_path = config_path;
}
TaskManagerConfig::TaskManagerConfig()
{
    m_config_path = std::filesystem::current_path();
    m_config_path += std::string("/") + TASKMANAGER_CONFIG_JSON;
}
TaskManagerConfig::~TaskManagerConfig()
{
    std::cout << "Task Manager Config deletion" << std::endl;
}

TaskManagerConfig_t &TaskManagerConfig::GetConfig()
{
    return m_task_manager_config;
}
void TaskManagerConfig::parse()
{
    rapidjson::Document config_json;
    if (JSONHelper::jsonFiletoDoc(m_config_path, config_json)){
        m_task_manager_config.task_data = config_json["TaskData"].GetString();
        m_task_manager_config.useremail = config_json["UserEmail"].GetString();
        m_task_manager_config.username = config_json["Username"].GetString();
    }

}