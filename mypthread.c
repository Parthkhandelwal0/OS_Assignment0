// File:	mypthread.c

// List all group members' names:
// iLab machine tested on:

#include "mypthread.h"

// INITAILIZE ALL YOUR VARIABLES HERE
// YOUR CODE HERE
#define STACK_SIZE SIGSTKSZ

//this is used to assign unique tid value to each thread 
mypthread_t threadIdValue = 1;

struct runqueue * jobQueue;

mypthread * currentThread = NULL;

ucontext_t schedulerContext;

//Arrays to store the terminated threads and the exit values of all the threads
void * thread_exitValues[100];
int threadsTerminated[100];

void addQueue(mypthread * newThread, runqueue * queue);

//void addQueue(thread * newThread, runqueue * queue);

/* create a new thread */
int mypthread_create(mypthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg)
{
	   // YOUR CODE HERE	
	
	   // create a Thread Control Block
	   // create and initialize the context of this thread
	   // allocate heap space for this thread's stack
	   // after everything is all set, push this thread into the ready queue

	   //creating the thread  
	mypthread * newThread = (mypthread *)malloc(sizeof (mypthread));

	//Allocating memory for thread control block
	newThread -> threadControlBlock = (tcb *)malloc(sizeof(tcb));


	//setting up the context and stack for this thread
	ucontext_t nctx;
	if (getcontext(&nctx) < 0){
		perror("getcontext");
		exit(1);
	}
	void * thisStack = malloc(STACK_SIZE);
	nctx.uc_link = NULL;
	nctx.uc_stack.ss_sp = thisStack;
	nctx.uc_stack.ss_size = STACK_SIZE;
	nctx.uc_stack.ss_flags = 0;

	//Modifying the context of thread by passing the function and arguments
	if (arg == NULL){
		makecontext(&nctx, (void *)function, 0);
	}else{
		makecontext(&nctx, (void *)function, 1,arg);
	}
	
	//assigning a unique id to this thread
	*thread = threadIdValue;
	(newThread -> threadControlBlock) -> threadId = *thread;
	threadIdValue++;

	//updating the status to READY state
	(newThread -> threadControlBlock) -> status = READY;

	//Updating the priority of thread
	(newThread -> threadControlBlock) -> priority = 1; //check

	//Update the tcb context for this thread
	(newThread -> threadControlBlock) -> ctx = nctx;

	addQueue(newThread, jobQueue);

	return 0;
};

/* current thread voluntarily surrenders its remaining runtime for other threads to use */
int mypthread_yield()
{
	// YOUR CODE HERE
	
	// change current thread's state from Running to Ready
	(currentThread -> threadControlBlock) -> status = READY;

	// save context of this thread to its thread control block
	// switch from this thread's context to the scheduler's context
	swapcontext(&((currentThread -> threadControlBlock)->ctx), &schedulerContext);


	return 0;
};

/* terminate a thread */
void mypthread_exit(void *value_ptr)
{
	// YOUR CODE HERE
	int i = currentThread->threadControlBlock->threadId;
	// preserve the return value pointer if not NULL
	if(value_ptr!=NULL){
		thread_exitValues[i]=value_ptr;
	}
	else{
		thread_exitValues[i]=NULL;
	}
	//adding this thread to terminated threads array
	threadsTerminated[i]=1;

	// deallocate any dynamic memory allocated when starting this thread
	freeCurrentThread(currentThread);
	
	return;
};

void freeCurrentThread(mypthread * thread){

	//Deallocating all the dynamic memory created for this thread
	free(((thread -> threadControlBlock) -> ctx).uc_stack.ss_sp);
	free(thread -> threadControlBlock);
	free(thread);

}

/* Wait for thread termination */
int mypthread_join(mypthread_t thread, void **value_ptr)
{
	// YOUR CODE HERE

	// wait for a specific thread to terminate
	while(threadsTerminated[thread]){
	}

	if(value_ptr!=NULL){
		*value_ptr=thread_exitValues[thread];
	}
	// deallocate any dynamic memory created by the joining thread
	freeCurrentThread(thread);

	return 0;
};

/* initialize the mutex lock */
int mypthread_mutex_init(mypthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)
{
	// YOUR CODE HERE
	
	//initialize data structures for this mutex

	return 0;
};

/* aquire a mutex lock */
int mypthread_mutex_lock(mypthread_mutex_t *mutex)
{
		// YOUR CODE HERE
	
		// use the built-in test-and-set atomic function to test the mutex
		// if the mutex is acquired successfully, return
		// if acquiring mutex fails, put the current thread on the blocked/waiting list and context switch to the scheduler thread
		
		return 0;
};

/* release the mutex lock */
int mypthread_mutex_unlock(mypthread_mutex_t *mutex)
{
	// YOUR CODE HERE	
	
	// update the mutex's metadata to indicate it is unlocked
	// put the thread at the front of this mutex's blocked/waiting queue in to the run queue

	return 0;
};


/* destroy the mutex */
int mypthread_mutex_destroy(mypthread_mutex_t *mutex)
{
	// YOUR CODE HERE
	
	// deallocate dynamic memory allocated during mypthread_mutex_init

	return 0;
};

/* scheduler */
static void schedule()
{
	// YOUR CODE HERE
	
	// each time a timer signal occurs your library should switch in to this context
	
	// be sure to check the SCHED definition to determine which scheduling algorithm you should run
	//   i.e. RR, PSJF or MLFQ

	// if (sched == RR)
	//		sched_rr();
	// else if (sched == MLFQ)
	// 		sched_mlfq();

	return;
}

/* Round Robin scheduling algorithm */
static void sched_RR()
{
	// YOUR CODE HERE
	
	// Your own implementation of RR
	// (feel free to modify arguments and return types)
	// #if defined(MLFQ)
	// #elseif definde(PSJF)
	// #endif
	
	return;
}

/* Preemptive PSJF (STCF) scheduling algorithm */
static void sched_PSJF()
{
	// YOUR CODE HERE

	// Your own implementation of PSJF (STCF)
	// (feel free to modify arguments and return types)

	return;
}

/* Preemptive MLFQ scheduling algorithm */
/* Graduate Students Only */
static void sched_MLFQ() {
	// YOUR CODE HERE
	
	// Your own implementation of MLFQ
	// (feel free to modify arguments and return types)

	return;
}

// Feel free to add any other functions you need

// YOUR CODE HERE
