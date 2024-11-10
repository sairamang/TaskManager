#pragma once 
#include <unordered_map>
#include <string>

struct TaskManagerConfig_t {
    std::string task_data;
};


class TaskManagerConfig 
{
    public: 
        TaskManagerConfig() = delete;
        TaskManagerConfig(std::string);
        ~TaskManagerConfig();

        void parse();
        TaskManagerConfig_t& GetConfig();


    private:
        std::string m_config_path;
        TaskManagerConfig_t m_task_manager_config;

};

