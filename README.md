# codexion
C program to handle POSIX

## Investigate
### Basics
pthread_create
	·The pthread_create() function starts a new thread in the calling
       process.  The new thread starts execution by invoking
       start_routine(); arg is passed as the sole argument of
       start_routine().
	   On success, pthread_create() returns 0; on error, it returns an
       error number, and the contents of *thread are undefined.
pthread_join
	·The pthread_join() function shall suspend execution of the calling thread until the target thread terminates, unless 	the target thread has already terminated.
	When a pthread_join() returns successfully, the target thread has been terminated. The results of multiple simultaneous calls to pthread_join() specifying the same target thread are undefined. If the thread calling pthread_join() is canceled, then the target thread shall not be detached.
pthread_mutex_*
	·A mutex is a MUTual EXclusion device, and is useful for protecting
       shared data structures from concurrent modifications, and
       implementing critical sections and monitors.
       A mutex has two possible states: unlocked (not owned by any
       thread), and locked (owned by one thread).  A mutex can never be
       owned by two different threads simultaneously.  A thread
       attempting to lock a mutex that is already locked by another
       thread is suspended until the owning thread unlocks the mutex
       first.
pthread_cond_*
	A condition (short for "condition variable") is a synchronization
       device that allows threads to suspend execution and relinquish the
       processors until some predicate on shared data is satisfied.
	·pthread_cond_init: Initializes the condition variable cond, using
       the condition attributes specified in cond_attr, or default
       attributes if cond_attr is NULL.
	·pthread_cond_broadcast: restarts all the threads that are waiting
       on the condition variable cond.  Nothing happens if no threads are
       waiting on cond.
	·pthread_cond_wait: atomically unlocks the mutex (as per
       pthread_mutex_unlock()) and waits for the condition variable cond
       to be signaled.  The thread execution is suspended and does not
       consume any CPU time until the condition variable is signaled.
	·pthread_cond_timedwait: atomically unlocks mutex and waits on
       cond, as pthread_cond_wait() does, but it also bounds the duration
       of the wait. The abstime parameter specifies an absolute time, with the same origin as
       time(2) and gettimeofday(2).
	·pthread_cond_destroy: destroys a condition variable, freeing the
       resources it might hold.  No threads must be waiting on the
       condition variable on entrance to pthread_cond_destroy().
### System services
Operating Systems
	·System OS provides CPU and threads management. (Requires extends)
Processes vs Threads
	|                         | Process                    | Thread                              |
	| ----------------------- | -------------------------- | ----------------------------------- |
	| Memoria                 | Aislada                    | Compartida dentro del process       |
	| Comunicación            | Más costosa                | Directa mediante memoria compartida |
	| Creación                | Generalmente más pesada    | Más ligera                          |
	| Riesgo de interferencia | Menor                      | Mayor                               |
	| Sincronización          | IPC cuando comparten datos | Mutex, condvars, etc.               |
Critical Sections
	·Requires mutex to protect from differents changes simultaniously.
	·Race Conditions
Deadlock
	·When a thread is permanently waiting for resources to wake up, specially important as an dongle can be taken for any 2 coders.
Coffman Conditions
	·If occur generate a deadloc, must eliminate at least one from: mutual exclusion, hold and wait, no preemption or cicular wait.
Starvation
	·A thread deads because can never reach resources. Schedule and heap.
Scheduling
	·FiFo: 
	·EDF: 

                 CONCURRENCY
                     │
          ┌──────────┴──────────┐
          ▼                     ▼
   Critical Sections      Shared Resources
          │                     │
          ▼                     ▼
   Race Conditions       Resource Allocation
                                │
                 ┌──────────────┼──────────────┐
                 ▼              ▼              ▼
              Mutexes       Scheduling      Condition
                              │              Variables
                         ┌────┴────┐
                         ▼         ▼
                       FIFO       EDF
                         │
                         └──────┬──────
                                ▼
                    Deadlock / Starvation
                         │
                         ▼
                  Coffman Conditions

### DATA structure
Binary Heap
Min Heap
Priority Queue
Heapify Up
Heapify Down
### Schedule: EDF/FiFo
Earliest Deadline First scheduling
EDF real time scheduling
EDF schedulability
EDF priority scheduling
hard real-time scheduling
soft real-time scheduling
### Phases
Fase 0 — Investigate
Threads
Mutexes
Condition variables
Race conditions
Deadlocks/Coffman
Starvation
FIFO
EDF
Priority queues
Time/deadlines
Fase 1 — Model
Definir entidades
Definir estado
Definir invariantes
Definir máquina de estados
Definir ownership de cada dato
Definir qué mutex protege qué estado
Fase 2 — Start Code
Contexto global mediante estructura
Coders
Dongles
Scheduler
Monitor
Logger
Shutdown
Fase 3 — Implementación
Parser
Heap
Recursos
Scheduler
Threads
Monitor
Logging
Termination
Cleanup
Fase 4 — Eng
Tests
Stress tests
Race detection
Leak detection
Edge cases
Timing tests
Revisión de invariantes
Refactorización