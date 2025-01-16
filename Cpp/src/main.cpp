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
    for(auto& it : model.task_data_list)
    {
        cout<<"************* Tasks*************** "<<endl;
        cout<<"Task name "<<it.task_name<<endl;
        cout<<"list Name" <<it.list_name<<endl;
        cout<<"story point"<<it.story_point<<endl;
    }

    for (auto& it:model.list_data_list)
    {
        cout<<"************Lists***************"<<endl;
        cout<<"List Name "<<it.list_name<<endl;
        for(auto&it2:it.tasks){
            cout<<"Tasks :"<<it.list_name<<endl;
            cout<<"Task Name"<<it2.task_name<<endl;
        }
    }
    myTaskManager.runeventloop();
    return 0;
}
