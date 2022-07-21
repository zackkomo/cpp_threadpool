#include "thread_pool.h"

/**
 * @brief Each thread is running this function.
 * If something is added to the queue, a thread
 * is notified and wakes up to complete the task.
 * Then it goes back to sleep and awaits for another
 * task, or death.
 * 
 */
void threadPool::threadLoop() {
    while (true) {
        std::function<void()> job;
        {
            // aquire a lock on the mutex
            std::unique_lock<std::mutex> l(m_);
            // wait until woken up AND (there are jobs to complete or called to die)
            cv_.wait(l, [this] {
                return !queue_.empty() || terminate_;
            });
            if (terminate_) {
                return;
            }
            job = queue_.front();
            queue_.pop();
        }
        // once outside scope, the lock releases and can complete job
        job();
    }
}

/**
 * @brief Function to add job to the queue.
 * If function being added has arguements, pass
 * in as a lambda.
 * @param job 
 */
void threadPool::add_job(const std::function<void()>& job) {
    // Acquire lock and add job to queue
    {
        std::unique_lock<std::mutex> l(m_);
        queue_.push(job);
    }
    // Notify a thread to take the job
    cv_.notify_one();
}

/**
 * @brief Checks if the queue of jobs is empty or not.
 * 
 */
bool threadPool::busy() {
    bool poolbusy;
    {
        std::unique_lock<std::mutex> l(m_);
        poolbusy = queue_.empty();
    }
    return !poolbusy;
}