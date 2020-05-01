#include "types.h"
#include "user.h"
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
