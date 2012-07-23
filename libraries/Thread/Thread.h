/*
 *			Thread class for Linux
 * This abstract class allows subclasses to utilise multithreading.
 * Default behaviour is to execute the "threadedFunction" repeatedly
 * For single execution set "running" to false at the end of
 * "threadedFunction"
 * Supports mutex locks and pausing
 * Execution DOES NOT autostart, this allows you to perform some
 * initialisation in your subclass (such as opening files), prior to
 * beginning execution
 *
 */


#ifndef Thread_h
#define Thread_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

class Thread {
public:
	Thread();
	~Thread();
	bool start();
	bool stop();
	void lock(bool flag);
	void pause(bool flag);
protected:
	virtual void threadedFunction() = 0;
private:
	static void *start_thread(void *obj);
	void run();
	bool running, paused;
	pthread_mutex_t mutex;
	pthread_t thread;
};


#endif
