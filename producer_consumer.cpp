/* producer_consumer.cpp: multithreading with semaphores: 
The consumers must wait for the producer, and the producer must wait for the consumers to finish.
The consumers don't change the data and should run in parallel to save time.

author: Ulrike Hager
date: Feb. 2016

To compile:
g++ -std=c++11 -Wall -pthread -o producer_consumer producer_consumer.cpp
 */
#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <atomic>

std::condition_variable g_produced;
std::condition_variable g_consumed;

class Semaphore
{
public:
  Semaphore(int n_consumers = 1)
    : counter_(0), n_threads_(n_consumers)
  {}
  Semaphore(Semaphore&& toMove)
    : counter_(toMove.counter_.load() ), n_threads_(toMove.n_threads_)
  {}
  void wait_one(){
    std::unique_lock<std::mutex> lk(mutex_);
    int current = counter_;
    cv_.wait(lk, [this, current] {return counter_ > current;} );
    --counter_;
  }
  void wait_all(){
    std::unique_lock<std::mutex> lk(mutex_);
    cv_.wait(lk, [this] {return counter_ >= n_threads_;} );
    counter_ -= n_threads_;
  }
  void notify_one() {
    std::unique_lock<std::mutex> lk(mutex_);
    ++counter_ ;
    cv_.notify_one();  
  }
  void notify_all() {
    std::unique_lock<std::mutex> lk(mutex_);
    counter_ += n_threads_;
    cv_.notify_all();  
  }
private:
  std::atomic<int> counter_;
  std::mutex mutex_;
  std::condition_variable cv_;
  int n_threads_;
};

unsigned int consumers = 2;
Semaphore g_sem_consumed(consumers);
std::vector<Semaphore> g_sem_produced;


void producer(int& data, unsigned int n_consumers, unsigned int wait = 0)
{
  std::default_random_engine gen;
  std::uniform_int_distribution<int> distr(1,20);

  g_sem_consumed.wait_all();
  while (true) {
    {
      std::mutex mex;
      std::lock_guard<std::mutex> lk(mex);
      data = distr(gen);
      std::this_thread::sleep_for(std::chrono::milliseconds(wait));
      std::cout << "[producer] produced " << data << std::endl;
    }

    for (unsigned int i = 0; i < n_consumers; ++i ) {
      g_sem_produced.at(i).notify_one();
    }
    g_sem_consumed.wait_all();
  }
}


void consumer(const int& data, unsigned int num = 0, unsigned int wait = 0)
{
  g_sem_consumed.notify_one();
  while (true) {
    g_sem_produced.at(num).wait_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    std::cout << "consumer " << num << " data = " << data << std::endl;
    g_sem_consumed.notify_one();
  }
}



int main()
{
  int data = -1;

  std::vector<unsigned int> wait(consumers+1, 0);
  //  wait = {0,50,130,100};
  wait.at(0) = 0;
  wait.at(2) = 0;
  
  std::vector<std::thread> threads;
  threads.push_back( std::thread( producer, std::ref(data), consumers, wait.at(0)) ) ;

  for (unsigned int i = 0; i < consumers; ++i ) {
     g_sem_produced.emplace_back( Semaphore() );
     threads.push_back( std::thread( consumer, std::cref(data), i, wait.at(i+1)) ); 
  }

  for (unsigned int i = 0; i != consumers+1; ++i ) {
    threads.at(i).join();
  }
}

