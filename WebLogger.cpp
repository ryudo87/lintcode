#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;


// Implement a web logger, which provide two methods:
// hit(timestamp), record a hit at given timestamp.
// get_hit_count_in_last_5_minutes(timestamp), get hit count in last 5 minutes.
// the two methods will be called with non-descending timestamp (in sec).

//用一个双端队列保存hit的信息，每次检查末尾的元素是否timestamp == 当前timestamp，然后判断是更新还是插入新的元素。get hit的时候从队头判断当前的timestamp是否在300秒之内，如果在的话就退出查找循环，如果不在则出队，这样就保证了当前队列的元素都在300秒以内。
struct Node {
    int timestamp;
    int count;
    
    Node(int timestamp) {
        count = 1;
        this->timestamp = timestamp;
    }
};
class WebLogger {
    deque<Node> dq;
    int totalCount;    
public:
    WebLogger() {
        totalCount = 0;
    }
    void hit(int timestamp) {
        totalCount++;
        if (dq.size()==0 || dq.back().timestamp != timestamp) {
            dq.push_back(Node(timestamp));
        } else {
            dq.back().count++;
        }

    }

    int get_hit_count_in_last_5_minutes(int timestamp) {
        while(!dq.empty() && dq.front().timestamp <= timestamp-300) {
            totalCount -= dq.front().count;
            dq.pop_front();
        }
        return totalCount;
    }
};

int main() {
    WebLogger log;
    log.hit(1);
    log.hit(2);
    std:cout<<log.get_hit_count_in_last_5_minutes(5)<<std::endl;
    return 0;
}


