#include "Thread.h"

//Constructor
Thread::Thread() {
	//Set up flags
	this->running = true;
	this->paused = false;

	//Initialise mutex
	pthread_mutex_init(&mutex, NULL);
}

//Destructor
Thread::~Thread() {
	//Get rid of mutex
	pthread_mutex_destroy(&mutex);
}

//Start the thread
//Returns true if successful, false otherwise
bool Thread::start() {
	//Create the thread and check for errors
	int err = pthread_create(&thread, 0, Thread::start_thread, this);
	if (err) {
		fprintf(stderr,"Thread creation failed (%d)\n", err);
		return false;
	}
	return true;
}

bool Thread::stop() {
	//Tell thread to terminate
	this->running = false;

	//Wait for thread to terminate
	pthread_join(thread, NULL);

	return true;
}

//Lock the thread
void Thread::lock(bool flag) {
	if (flag) {
		pthread_mutex_lock(&mutex);
	} else {
		pthread_mutex_unlock(&mutex);
	}
}

//Pause the thread
void Thread::pause(bool flag) {
	paused = flag;
}

//Start function, does some crazy casting to make C threads work
//properly in C++
void *(Thread::start_thread)(void *obj) {
	reinterpret_cast<Thread *>(obj)->Thread::run();
}

//The run function
//Calls the threadedFunction (defined by the subclass)
//implements pausing
void Thread::run() {
	while (running) {
		threadedFunction();
		while (paused) {
			usleep(1000);		
		}
	}
}

