#include "types.h"
#include "user.h"
#include "date.h"

#define LEAPYEAR(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

static int MONTH[12] = {
   0,
   31,
   31 + 28,
   31 + 28 + 31,
   31 + 28 + 31 + 30,
   31 + 28 + 31 + 30 + 31,
   31 + 28 + 31 + 30 + 31 + 30,
   31 + 28 + 31 + 30 + 31 + 30 + 31,
   31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
   31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
   31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
   31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30//,
   // 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31
};

long long unixtime_convert(struct rtcdate *time) {
   long long ret = 0;
   
   int ry = time -> year;
   while (ry > 400) {
      ry -= 400;
      ret += 12622780800;
   }
   
   for (int year = 1; year < ry; year++) {
      if (LEAPYEAR(year)) {
         ret += 366 * 86400;
      } else {
         ret += 365 * 86400;
      }
   }
   
   ret += 86400 * (MONTH[time->month - 1] + (time->day - 1)) + time->hour * 3600 + time->minute * 60 + time->second;
   
   if (LEAPYEAR(time->year) && (time->month > 2)) ret += 86400;
   
   return ret - 62135596800;
}

long long unix_time_now() {
    struct rtcdate datetime;
    now(&datetime);
    return unixtime_convert(&datetime) * 1000;
}

////////////////////////////////////////////////////////////////////////////////////////////////

typedef void (*timer_event)(void*);

struct timer_data {
    int interval;
    timer_event enterance;
    void* arg;
};

void timer_main(struct timer_data *p) {
    long long last = unix_time_now();
    long long now;

    while (1) {
        p->enterance(p->arg);
        now = unix_time_now();

        while ((now - last) < p->interval) {
            //
            now = unix_time_now();
        }

        last = now;
    }
}

int set_timer(void *arg, timer_event enterance, int interval){
    struct timer_data *p = malloc(sizeof(struct timer_data));
    p->interval = interval;
    p->arg = arg;
    p->enterance = enterance;
    return thread_create(timer_main, p);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int a = 0;

void schedule_event(void *arg) {
    printf(1, "\n\n");
    a++;
}

int main(void)
{
    set_timer(0, schedule_event, 1);
    while (1) {
        printf(1, "%d", a);
    };
    exit();
}
