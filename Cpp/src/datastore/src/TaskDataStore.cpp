#include <TaskDataStore.h>

TaskDataStore TaskDataStore::instance;
TaskDataModel TaskDataStore::my_model;

TaskDataStore &TaskDataStore::getInstance()
{
    return instance;
}
void TaskDataStore::store(TaskData task_data)
{
    my_model.task_data_list.push_back(task_data);
}
void TaskDataStore::store(ListData list_data)
{
    my_model.list_data_list.push_back(list_data);
}
void TaskDataStore::getModel(TaskDataModel &model){
    model = my_model;
}
void TaskDataStore::updateModel(rapidjson::Document &json_doc)
{
    auto &tasks_list = json_doc["tasks"];
    for (int i = 0; i < tasks_list.Size(); i++)
    {
        TaskData my_task;
        my_task.task_name = json_doc["tasks"][i]["taskname"].GetString();
        my_task.list_name = json_doc["tasks"][i]["listname"].GetString();
        my_task.story_point = json_doc["tasks"][i]["storypoint"].GetInt();
        my_model.task_data_list.push_back(my_task);
    }
    if (json_doc["lists"].IsArray())
    {
        auto lists_list = json_doc["lists"].GetArray();

        for (int i = 0; i < lists_list.Size(); i++)
        {
            auto &list_obj = lists_list[i];
            ListData my_list;
            my_list.list_name = list_obj["listname"].GetString();
            auto tasks_vec = list_obj["taskname"].GetArray();

            for (int j = 0; j < tasks_vec.Size(); j++)
            {
                TaskData mytask;
                mytask.task_name = tasks_vec[j].GetString();
                my_list.tasks.push_back(mytask);
            }
            my_model.list_data_list.push_back(my_list);
        }
    }
}