/*
 * Tasks.h
 *
 * Created: 2/9/2017 11:27:44 p.m.
 *  Author: IoT SolucioneX (jlugo)
 */ 


#ifndef TASKS_H_
#define TASKS_H_

//--- Includes ---//
#include "HAL/config.h"
#include "timers.h"


//--- Defines ---//
#define TASK_ERROR            0
#ifdef DEBUG_TASK
#define TASK_MAX_TASKS        6
#else
#define TASK_MAX_TASKS        5
#endif
#define TASK_MAX_TASK_NAME    32

//Task declaration
typedef enum tagTaskStatus { 
   TS_IDLE, TS_READY, TS_RUNNING, TS_WAITING, TS_UNDEFINED
} TASK_STATUS;

typedef enum tagTaskType {
   TT_PERIODIC, TT_SPORADIC, TT_APERIODIC, TT_UNDEFINED
} TASK_TYPE;

typedef uint8_t tTaskId;               //Task identification number
typedef struct tagTASK TASK, *pTASK;   //Forward declaration
typedef void (*TaskCallback)(pTASK);   //Task callback function prototype

//--- Task structure ---//
typedef struct tagTASK {
   tTaskId        id;        //Task identification number
   #if DEBUG_TASK
      const char * name;     //Name, for debug propose only
   #endif
   tTime          start;     //When (time) to run
   tTime          runEvery;  //When (time) to run, for periodic task
   TASK_STATUS    status;    //Actual task status
   TASK_TYPE      type;      //Task type
   TaskCallback   callback;  //Callback function
   void *         parameter; //Parameter task data
} TASK, *pTASK;

//void (*fun_ptr_arr[])(int, int) = {fn1, fn2, fn3};


//---- Functions Prototypes ---//

void TaskInit(void);
tTaskId TaskCreate(const char* name, tTime start, tTime runEvery, TASK_TYPE, const TaskCallback, void* const parameter);
void TaskSetStatus(tTaskId, TASK_STATUS);
TASK_STATUS TaskGetStatus(tTaskId);
void TaskDelete(tTaskId);
void TaskSetParameter(tTaskId, void * parameter);
void TaskSetTimers(tTaskId, tTime start, tTime runEvery);

//Scheduler
void RunScheduler(void);


#endif /* TASKS_H_ */