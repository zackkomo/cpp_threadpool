#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "thread_pool.h"
#include <Eigen/Core>

/**
 * @brief a job for threads to complete.
 * 
 * @param a 
 * @param b 
 */
void somefunction(double &a, double b){
    for (int i=0;i<100;i++){
        a +=  b;
    }
}

int main (int argc, char *argv[]) {
    //-----------------------------------------------------------------//
    //---------------------How to use thread pool----------------------//
    //-----------------------------------------------------------------//
    /* Test params */
    int N = 1000000; // # of jobs
    double  data[N];
    /* # threads in pool */
    threadPool pool{1};

    for(int i=0; i<N; i++){
        data[i] = i;
        double &var = data[i];
        pool.add_job([&var]() {somefunction(var,2.0);});
    }
    // Wait for all tasks to complete before continuing if you want.
    while(!pool.is_queue_empty() || pool.pool_busy()){
        std::cout << "\rWaiting.. " << N-pool.jobs_in_queue()+pool.threads_busy() << "/" << N << " jobs done         ";
        std::cout.flush();
    };
    std::cout << "\rWaiting.. " << N-pool.jobs_in_queue()+pool.threads_busy() << "/" << N << " jobs done" << std::endl;
    
    std::cout << "Done.." << std::endl;


    //-----------------------------------------------------------------//
    //---------------------How to use sync future----------------------//
    //-----------------------------------------------------------------//

    return 0;
}