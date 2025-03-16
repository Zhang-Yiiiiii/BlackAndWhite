#include "user.h"

User::User()
{
    //初始化
    for(int i=0;i<SELECTBTNNUMBER;i++)
    {
        gameRecord[i+1] = -1;
    }
}
