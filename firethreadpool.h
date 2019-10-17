#include <condition_variable>
#include <functional>
#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <queue>
#include <cctype>

class FireThreadPool
{
public:
    using Task = std::function<void()>;

    explicit FireThreadPool(std::size_t numThreads)
    {
        start(numThreads);
    }

    ~FireThreadPool()
    {
        stop();
    }

    template <class T>
    auto enqueue(T task) -> std::future<decltype(task())>
    {
        auto wrapper = std::make_shared<std::packaged_task<decltype(task())()>>(std::move(task));
        std::unique_lock<std::mutex> lock{mEventMutex};
        mTasks.emplace([=] {
            (*wrapper)();
        });
        mEventVar.notify_one();
        return wrapper->get_future();
    }

private:
    std::vector<std::thread> mThreads;
    std::condition_variable mEventVar;
    std::mutex mEventMutex;
    bool mStopping = false;
    std::queue<Task> mTasks;

    void start(std::size_t numThreads)
    {
        for (auto i = 0u; i < numThreads; ++i)
        {
            mThreads.emplace_back([=] {
                while (true)
                {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock{mEventMutex};
                        mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty(); });
                        if (mStopping && mTasks.empty())
                            break;
                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }

                    task();
                }
            });
        }
    }

    void stop() noexcept
    {
        std::unique_lock<std::mutex> lock{mEventMutex};
        mStopping = true;

        mEventVar.notify_all();

        for (auto &thread : mThreads)
            thread.join();
    }
};