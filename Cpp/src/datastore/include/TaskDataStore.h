#pragma once
#include <TaskDataModel.h>
#include <document.h>
class TaskDataStore
{
private:
    static TaskDataStore instance;
    static TaskDataModel my_model;

public:
    static void store(TaskData task_data);
    static void store(ListData list_data);
    static void updateModel(rapidjson::Document& json_doc);
    static TaskDataStore &getInstance();
    static void getModel(TaskDataModel& model);
};