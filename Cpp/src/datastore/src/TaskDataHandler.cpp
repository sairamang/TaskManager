#include <TaskDataHandler.h>
#include <TaskDataStore.h>
#include <JSONHelper.h>

TaskDataHandler::TaskDataHandler(std::string task_data_path)
{
    m_path = task_data_path;
}
void TaskDataHandler::parse()
{
    rapidjson::Document task_data_json;
    JSONHelper::jsonFiletoDoc(m_path,task_data_json);
    TaskDataStore::updateModel(task_data_json);
}