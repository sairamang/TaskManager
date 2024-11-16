#pragma once 
#include <unordered_map>
#include <string>
#define TASKMANAGER_CONFIG_JSON "TaskManager.json"
struct TaskManagerConfig_t {
    std::string task_data;
    std::string username;
    std::string useremail;
};


class TaskManagerConfig 
{
    public: 
        TaskManagerConfig();
        TaskManagerConfig(std::string);
        ~TaskManagerConfig();

        void parse();
        TaskManagerConfig_t& GetConfig();


    private:
        std::string m_config_path;
        TaskManagerConfig_t m_task_manager_config;

};

