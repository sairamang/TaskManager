
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include "TaskManager.h"


// Main code
int main(int, char**)
{
    TaskManager myTaskManager;
    myTaskManager.runeventloop();
    return 0;
}
