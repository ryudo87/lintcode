#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

// Implement a rate limiter, provide one method:
// is_ratelimited(timestamp, event, rate, increment).
// timestamp: The current timestamp, which is an integer and in second unit.
// event: The string to distinct different event. for example, "login" or "signup".
// rate: The rate of the limit. 1/s (1 time per second), 2/m (2 times per minute), 10/h (10 times per hour), 100/d (100 times per day). 
//The format is [integer]/[s/m/h/d].
// increment: Whether we should increase the counter. (or take this call as a hit of the given event)
// The method should return true or false to indicate the event is limited or not.


class RateLimiter {
   //   event     timestamp->count 
    map<string, map<int, int>> count; //用hash保存每个事件在timestamp发生的次数。之后去扫描某个事件是否达到了limit
public:
    bool isRatelimited(int timestamp, string event, string rate, bool increment) {    
        int pos=rate.find("/");
        int times = stoi(rate.substr(0, pos));
        string per = rate.substr(pos+1, rate.size());
        int delta = 0;
        if (per=="s") {
            delta =1;
        } else if (per=="m") {
            delta=60;
        } else if (per=="h") {
            delta = 60*60;
        } else {
            delta = 60*60*24;
        }
        
        int total=0;
        // 只从大于等于 timestamp - delta + 1 的 key 开始扫描
        map<int, int>::iterator iter=count[event].lower_bound(timestamp-delta+1);
        for(;iter != count[event].end();iter++) {
            total += iter->second;
        }
        
        bool result = (total>=times);
        //increment: Whether we should increase the counter. (or take this call as a hit of the given event)
        if (increment && !result) {
            count[event][timestamp] ++;
        }
        return result;
    }
};

int main() {
    RateLimiter rateLimiter;
    std::cout<<rateLimiter.isRatelimited(1, "login", "3/m", true)<<std::endl;
    std::cout<<rateLimiter.isRatelimited(11, "login", "3/m", true)<<std::endl;
    std::cout<<rateLimiter.isRatelimited(21, "login", "3/m", true)<<std::endl;
    std::cout<<rateLimiter.isRatelimited(30, "login", "3/m", true)<<std::endl;
    return 0;
}
