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

Semaphore g_sem_consumed(2);
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


void consumer0(const int& data, unsigned int num = 0, unsigned int wait = 0)
{
  g_sem_consumed.notify_one();
  while (true) {
    {
      g_sem_produced.at(num).wait_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(wait));
      std::cout << "[consumer1] data = " << data << std::endl;
    }
    g_sem_consumed.notify_one();
  }
}


void consumer1(const int& data, unsigned int num = 1, unsigned int wait = 0)
{
  g_sem_consumed.notify_one();
  while (true) {
    {
      g_sem_produced.at(num).wait_one();
      std::this_thread::sleep_for(std::chrono::milliseconds(wait));
      std::cout << "[consumer2] data = " << data << std::endl;
    }
    g_sem_consumed.notify_one();
  }
}


int main()
{
  int data = -1;
  unsigned int n_threads = 2;
  std::vector<unsigned int> wait{0,50,100};
  
  for (unsigned int i = 0; i < n_threads; ++i ) {
     g_sem_produced.emplace_back( Semaphore() );
  }
  std::thread t0( producer, std::ref(data), n_threads, wait.at(0));
  std::thread t1( consumer0, std::cref(data), 0, wait.at(1) );
  std::thread t2( consumer1, std::cref(data), 1, wait.at(2));

  t0.join();
  t1.join();
  t2.join();
}

