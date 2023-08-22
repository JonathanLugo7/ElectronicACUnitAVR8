/*
 * Tasks.c
 *
 * Created: 2/9/2017 11:28:20 p.m.
 *  Author: IoT SolucioneX
 */ 

#include "tasks.h"

#if defined(DEBUG) || defined(DEBUG_TASK)
#include "comms/usart.h"
extern char str[MAX_BUFFER];
#endif


//--- Global local variables ---//
static TASK g_tasks[TASK_MAX_TASKS];      // Total of tasks

//-- Task Helpers --//
static pTASK FindTask(tTaskId id) {
   if (id == 0 || id > TASK_MAX_TASKS) {
      return NULL;
   }

   return &g_tasks[id-1];
}


//-- Task API implementation --//

void TaskInit(void) {
   for (int i = 0; i < TASK_MAX_TASKS; i++) {
      memset(&g_tasks[i], 0, sizeof(TASK));
      g_tasks[i].status = TS_IDLE;
   }

#if defined(DEBUG_TASK)
   USARTPrintString("TSK-Init\n");
#endif
}

tTaskId TaskCreate(const char* name, tTime start, tTime runEvery, TASK_TYPE type, 
                   const TaskCallback taskFn, void* const parameter) {

   static tTaskId taskId = 0; // Task index

   // Max tasks reached
   if (taskId >= TASK_MAX_TASKS) {
      return 0;
   }

   // Add new task to the tasks list
   pTASK pTsk = &g_tasks[taskId];
   pTsk->id = ++taskId;
   pTsk->start = start;
   pTsk->runEvery = runEvery;
   pTsk->type = type;
   pTsk->callback = taskFn;
   pTsk->parameter = parameter;

#if defined(DEBUG_TASK)
   pTsk->name = name;
   sprintf(str, "TSK-Crtd: Id::%d::%s. Typ: %d. Stats: %d. Addrss: %p\n", pTsk->id, pTsk->name, pTsk->type, pTsk->status, pTsk);
   USARTPrintString(str);
#endif

   return pTsk->id;
}

void TaskSetStatus(tTaskId id, TASK_STATUS status) {
   pTASK pTsk = FindTask(id);
   if (pTsk) {
      pTsk->status = status;

      // Ready to Run?
      if (status == TS_READY) {
         pTsk->start = TimerNow();
      }
   }
}

TASK_STATUS TaskGetStatus(tTaskId id) {
   pTASK pTsk = FindTask(id);
   if (pTsk) {
      return pTsk->status;
   }
   else {
      return TS_UNDEFINED;
   }
}

pTASK TaskGetTask(tTaskId id) {
   pTASK pTsk = FindTask(id);
   if (pTsk) {
      return pTsk;
   }

   return NULL;
}

void TaskDelete(tTaskId id) {
   TaskSetStatus(id, TS_IDLE);
}

void TaskSetParameter(tTaskId id, void * parameter) {
   pTASK pTsk = FindTask(id);
   if (pTsk) {
      pTsk->parameter = parameter;
   }
}

void TaskSetTimers(tTaskId id, tTime start, tTime runEvery) {
   pTASK pTsk = FindTask(id);
   if (pTsk) {
      pTsk->start = start != 0 ? start : pTsk->start;
      pTsk->runEvery = runEvery != 0 ? runEvery : pTsk->runEvery;
   }
}


/*** 

   Scheduler API

* ***/
void RunScheduler(void) {

   // Check all tasks
   for (int i = 0; i < TASK_MAX_TASKS; i++) {
      
      pTASK pTsk = &g_tasks[i];
      if (pTsk == NULL || pTsk->status != TS_READY) {
         continue;
      }

      // Execute?
      if (TimerElapsed(pTsk->start) >= pTsk->runEvery) {
          
         pTsk->status = TS_RUNNING;
         pTsk->callback(pTsk);
         pTsk->start = TimerNow();

         // Periodic task are always running, aperiodic task run once and then stop until they are signal again
         if (pTsk->type == TT_PERIODIC) {
            pTsk->status = TS_READY;
         }
         else {
            if (pTsk->status != TS_IDLE) {
              pTsk->status = TS_READY;
            }
         }
      }
   }
}
