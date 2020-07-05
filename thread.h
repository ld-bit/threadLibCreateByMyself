#include<iostream>
#include<time.h>
#include<pthread.h>
using namespace std;
namespace DongGe
{
class thread{
	typedef void*(*func)(void*);
public:
	//构造函数
	thread(func run,void* p)
	{
      pthread_create(&tid,NULL,run,p);
	}
	thread(func run)
	{
	pthread_create(&tid,NULL,run,NULL);
	}
	//阻塞
	void join()
	{
		pthread_join(tid,NULL);
	}
	void detach()
	{
     pthread_detach(tid);
	}
	long get_id()
	{
     return pthread_self();
	}
private:
 pthread_t tid;
};
class Mutex
{
public:
	Mutex()
	{
		pthread_mutex_init(&mutex,NULL);
	}
	~Mutex()
	{
		pthread_mutex_destroy(&mutex);
	}
	inline void lock()
	{
	   pthread_mutex_lock(&mutex);
	}
	inline void unlock()
	{
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_t getmutex()
	{
		return mutex;
	}
private:
pthread_mutex_t mutex;
};
class Cond
{
public:
	Cond()
	{
		pthread_cond_init(&cond,NULL);
	}
	~Cond()
	{
	pthread_cond_destroy(&cond);
	}
	inline void wait(pthread_mutex_t mutex)
	{
		pthread_cond_wait(&cond,&mutex);
	}
	inline void wake()
	{
		pthread_cond_signal(&cond);
	}
	inline void wakeall()
	{
		pthread_cond_broadcast(&cond);
	}
	int timewait(size_t time,pthread_mutex_t mutex)
	{
		struct  timespec abstime;
	    clock_gettime(CLOCK_REALTIME,&abstime);
		abstime.tv_sec+=time;
		int ret=pthread_cond_timedwait(&cond,&mutex,&abstime);
		return ret;
	}
private:
	pthread_cond_t cond;
};
};
