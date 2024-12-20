#pragma once 
#include <string>
#include <vector>
struct TaskData
{
    std::string task_name;
    std::string list_name;
    int story_point;
};

struct ListData
{
    std::string list_name;
    std::vector<TaskData> tasks;
};


struct TaskDataModel 
{
    std::vector<TaskData> task_data_list;
    std::vector<ListData> list_data_list; 
};