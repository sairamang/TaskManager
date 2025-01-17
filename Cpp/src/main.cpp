#include "TaskManagerConfig.h"
#include "TaskDataHandler.h"
#include "TaskDataStore.h"
#include "TaskManager.h"
#include <iostream>
// Main code
using namespace std;
int main(int, char**)
{
    TaskManager myTaskManager;
    TaskManagerConfig myTaskManagerConfig;
    myTaskManagerConfig.parse();
    auto& config = myTaskManagerConfig.GetConfig();
    std::cout<<"Task Data Path "<<config.task_data<<std::endl;
    TaskDataHandler data_handler(config.task_data);
    data_handler.parse();
    TaskDataModel model;
    TaskDataStore::getModel(model);
    myTaskManager.runeventloop();
    return 0;
}
