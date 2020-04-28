#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "date.h"

struct rtcdate datetime;

int main(void)
{
    now(&datetime);
    printf(1, "%d-%d-%d %d:%d:%d\n",
        datetime.year, datetime.month, datetime.day,
        datetime.hour, datetime.minute, datetime.second);
    exit();
}
