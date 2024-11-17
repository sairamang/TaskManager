#include "gtest/gtest.h"
#include "TaskManager.h"
#include "TaskDataHandler.h"
#include "TaskDataStore.h"
#include "TaskDataModel.h"
#include "JSONHelper.h"

TEST(TaskManagerMain,Start)
{
    TaskManager mymgr;
    // mymgr.runeventloop();
}
TEST(TaskDataConfigMain , Start){
    
}
TEST(TaskDataHandlerMain,Start){
    TaskDataHandler mydatahandler("/root/repo/TaskManager/Cpp/build/TaskData.json");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
