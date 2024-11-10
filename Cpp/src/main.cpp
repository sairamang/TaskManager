#include "TaskManager.h"
#include "TaskManagerConfig.h"
#include <iostream>
// Main code
int main(int, char**)
{
    // TaskManager myTaskManager;
    TaskManagerConfig myTaskManagerConfig("/root/TaskManager.json");
    myTaskManagerConfig.parse();
    auto& config = myTaskManagerConfig.GetConfig();
    std::cout<<"Task Data Path "<<config.task_data<<std::endl;
    // myTaskManager.runeventloop();
    return 0;
}
