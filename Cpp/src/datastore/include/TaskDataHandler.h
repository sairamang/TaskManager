#pragma once 
#include <string>

class TaskDataHandler
{
    public:
        TaskDataHandler()=delete;
        TaskDataHandler(std::string task_data_path); 
        void parse();

    private:
        std::string m_path;


};