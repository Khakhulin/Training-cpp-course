#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <string>
#include <mutex>
#include <unistd.h>
#include <system_error>
#include <functional>

//***********
//error code
//***********

enum messenger_error{
    continue_request = 101,
    ok = 200,
    gateway_timeout = 504,
    socket_error = 307,
    keep_alive_error = 408,
    bad_format = 217,
    not_authorized = 7,
    restricted_xml = 314,
    undefined_condition = 118,
    unsupported_stanza_type = 113,
    invalid_id = 37,
    invalid_from = 38,
    xmpp_stream_error = 201
    //..//
};

class xmpp_category_messenger: public std::error_category {
public:
    virtual const char* name() const noexcept (true);
    virtual std::string message(int ev) const;
};

const char* xmpp_category_messenger::name() const  noexcept (true){
    return "messenger on xmpp protocol";

};

std::string xmpp_category_messenger::message(int ev) const{
    switch(ev){
        case messenger_error::continue_request://messenger_error::continue_request:
            return "Continue";
        case messenger_error::ok:
            return "All OK";
        case messenger_error::gateway_timeout:
            return "Gateway time-out";
        case messenger_error::socket_error:
            return "Error due to TCP socket.";
        case messenger_error::keep_alive_error:
            return "no response to a keep alive.";
        case messenger_error::bad_format:
            return "";
        case messenger_error::restricted_xml:
            return "Error due to XML stream.";
        default:
            return "Unknown XMPP error";
    }
};

typedef void (*Task)();

void thread_work();

struct probability_calculator{
        typedef  std::function<void(std::error_code)> funct;
        template <typename T>
        probability_calculator(T handler){
            _function = static_cast< funct >(handler);
        };
        void operator()(int probability){
            srand (time(NULL));
            if(rand()%100 < probability){
                    std::error_code ec (201, xmpp_category_messenger());
                    _function(ec);
                }
        }
    private:
        funct _function;

        //(void*)(test);
};

class thread_pool{
public:
    thread_pool(int thread_num);
    ~thread_pool();
    template<typename T>
    void post(T handler);
    void run();
private:
    std::vector<std::thread> threadPool;
    //task queue
    std::queue<Task> tasks;
    int _thread_num;

    std::mutex _mutex;
    std::condition_variable cond_v;
    bool shut_down;
    //std::thread_t th[_thread_num];
};
thread_pool::thread_pool(int thread_num){
    _thread_num = thread_num;
    shut_down = false;
    for(int i = 0; i < thread_num; i++){

        threadPool.emplace_back(std::thread(&thread_pool::run,this));
    }
    //std::cout << "LOG::work has done" << std::endl;
}

void thread_pool::run(){
    Task Handler_task;
    while(true){
        {
            std::unique_lock<std::mutex> lock(_mutex);
            while(!shut_down && tasks.empty()){
                cond_v.wait(lock);
            }
            if(shut_down){
                return;
            }
            Handler_task = tasks.front();
            tasks.pop();
        }
        Handler_task();
    }
}

template<typename T>
void thread_pool::post(T handler){
    {
        std::unique_lock<std::mutex> lock(_mutex);
        tasks.push(handler);
    }
    cond_v.notify_one();
}
thread_pool::~thread_pool(){
    shut_down = true;
    cond_v.notify_all();
    for(int i = 0; i < _thread_num; i++)
        threadPool[i].join();

}

int main(){
    thread_pool th_p(7);
    std::string data;
    int i = 0;
    while(i < 3){
        int probability;
        std::cin >> probability;
         probability_calculator calculator([](const std::error_code &error){
             std::cout << error.message() << std::endl;
         });
        th_p.post((std::bind(calculator,probability)));
        i++;
    }
    std::cout << "/* message */" << std::endl;
    return 0;
}
void thread_work(){
    sleep(4);
    std::cout << "in thread" << std::endl;

}
