#pragma once

#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>

class ThreadPool
{
public:
    ThreadPool(std::size_t threadSize = std::thread::hardware_concurrency(), std::size_t taskSize = 128)
        : _stop(false), _workerThreads(std::move(threadSize)), _maxTaskSize(std::move(taskSize))
    {
        auto Func = [this]() {
            while (true)
            {
                std::function<void()> task;
                std::unique_lock<std::mutex> l(this->_mutex);
                this->_condition.wait(l, [this]() { return this->_stop || !this->_queue.empty(); });

                if (this->_queue.empty())
                {
                    return;
                }
                task = std::move(this->_queue.front());
                this->_queue.pop();

                this->_condition.notify_one();
                task();
            }
        };

        for (std::size_t i = 0; i < this->_threadSize; i++)
        {
            _workerThreads.emplace_back(Func);
        }
    }

    ~ThreadPool()
    {
        stop();
    }

    std::size_t &maxTaskSize()
    {
        return _maxTaskSize;
    }

    std::size_t &threadSize()
    {
        return _threadSize;
    }

    template<typename Fun, typename... Args>
    auto enqueue(Fun &&_fun, Args &&...args) -> std::future<typename std::result_of<Fun(Args...)>::type>
    {
        typedef typename std::result_of<Fun(Args...)>::type return_type;

        auto task = std::make_shared<std::packaged_task<return_type()>>{
                std::bind(std::forward<Fun>(_fun), std::forward<Args>(args)...)};
        std::future<return_type> res = task->get_future();

        std::unique_lock<std::mutex> l(this->_mutex);

        this->_condition.wait(l, [this] { return this->_stop || this->_queue.size() < this->_maxTaskSize; });
        if (this->_stop)
        {
            return res;
        }
        _queue.push([task]() { (*task)(); });

        _condition.notify_one();
        return res;
    }

    void stop()
    {
        std::unique_lock<std::mutex> l(this->_mutex);
        _stop = true;
        _condition.notify_all();
        for (auto &t: _workerThreads)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

private:
    std::size_t _threadSize;
    std::size_t _maxTaskSize;
    std::vector<std::thread> _workerThreads;
    std::queue<std::function<void()>> _queue;
    std::mutex _mutex;
    std::condition_variable _condition;
    bool _stop;
};