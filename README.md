# thread_pool
Implementation of a thread pool. The basic idea is you initialize the threadPool object with the number of threads you are willing to allow.
Next you feed jobs for the threadPool to complete. As jobs enter the queue, the threadPool will pair jobs with threads that are not currently running jobs until the queue is empty. The threads will still exist and wait in the background until the threadPool object is destroyed.

## Notes
1. If you want to check if all your tasks have been processed are being processed before adding more to the queue, use `is_queue_empty()`. This **DOES NOT GUARANTEE** that the threadpool is not busy working on the last of the jobs though.
2. If you want to check if any of the threads in the pool are in use and not waiting for jobs, use `pool_busy()`. This **DOES NOT GUARANTEE** that the threadpool is not still processing your jobs, it could be that momentarily all threads are waiting for new jobs.
3. If you passed in data to a thread and need the processed data back, or will modify data AFTER you start the threads, there will be undefined behavior. You can use the `! is_queue_empty() || pool_busy()` in a while loop to check if the threadpool is still busy working before trying to access anything.
4. Presumably there are significantly more jobs than threads, otherwise you can just manually create a thread for each job and join at the end.
