# thread_pool
Implementation of a thread pool. The basic idea is you initialize the threadPool object with the number of threads you are willing to allow.
Next you feed jobs for the threadPool to complete. As jobs enter the queue, the threadPool will pair jobs with threads that are not currently running jobs until the queue is empty. The threads will still exist and wait in the background until the threadPool object is destroyed.

## Notes
1. If you passed in data to a thread and need the processed data back, or will modify AFTER you start the threads, there will be undefined behaviour. You should use the `busy()` function to check if the threadpool is still busy.
2. Presumably there are significantly more jobs than threads, otherwise you can just manually create a thread for each job and join at the end.


