//
// Created by GentlyGuitar on 4/21/2017.
//

#include "thread.h"
#include "javaThread.h"
#include "osThread.h"
#include "../os.h"
#include "vmThread.h"
#include "../init.h"

// Threads
#ifdef PTHREAD_OKAY
std::map<pthread_t, Thread*> Threads::_threads_table;

void Threads::register_thread(Thread * thread) {
    _threads_table[thread->osthread()->pthread_id()] = thread;

}
#endif

JavaThread* Threads::_thread_list = NULL;
int Threads::_number_of_threads = 0;

jint Threads::create_vm(JavaVMInitArgs *args, bool *canTryAgain) {
    // Initialize global data structures and create system classes in heap
    init::vm_init_globals();

    // Attach the main thread to this os thread
    JavaThread* main_thread = new JavaThread();
    main_thread->set_thread_state(JavaThread::_thread_in_vm);
    Threads::add(main_thread);

    // Initialize global modules such as heap
    jint status = init::init_globals();

    VMThread::create();
    Thread* vmthread = VMThread::vm_thread();

    os::create_thread(vmthread, os::vm_thread);

    os::start_thread(vmthread);

    /* for debug use */
    int ret;
    pthread_join(vmthread->osthread()->pthread_id(), (void**)&ret);
}

void Threads::add(JavaThread *p, bool force_daemon) {
    p->set_next(_thread_list);
    _thread_list = p;
    _number_of_threads++;
}


// Thread

Thread::Thread() {

}

Thread::~Thread() {

}

void Thread::run() {
    ZPPL("I am running");
}


#ifdef PTHREAD_OKAY

Thread* Thread::current() {
    Thread* thread = Threads::get_pthread_by_id(pthread_self());
    assert(thread != NULL, "Thread::current(): thread is NULL");
    return thread;
}


#endif