#include "hal_drivers.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"

#include "nwk.h"
#include "APS.h"
#include "ZDApp.h"

#include "Debug.h"

#include "bdb_interface.h"

#include "zcl_app.h"

/*********************************************************************
 * GLOBAL VARIABLES
 */

// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr[] = {
        macEventLoop,
        nwk_event_loop,
        Hal_ProcessEvent,
        APS_event_loop,
        ZDApp_event_loop,
        zcl_event_loop,
        bdb_event_loop,
        zclApp_event_loop
};

const uint8 tasksCnt = sizeof(tasksArr) / sizeof(tasksArr[0]);
uint16 *tasksEvents;

/*********************************************************************
 * FUNCTIONS
 *********************************************************************/

/*********************************************************************
 * @fn      osalInitTasks
 *
 * @brief   This function invokes the initialization function for each task.
 *
 * @param   void
 *
 * @return  none
 */
void osalInitTasks(void) {
    uint8 taskID = 0;
    DebugInit();

    tasksEvents = (uint16 *) osal_mem_alloc(sizeof(uint16) * tasksCnt);
    osal_memset(tasksEvents, 0, (sizeof(uint16) * tasksCnt));
    macTaskInit(taskID++);
    nwk_init(taskID++);
    Hal_Init(taskID++);
    APS_Init(taskID++);
    ZDApp_Init(taskID++);
    zcl_Init(taskID++);
    bdb_Init(taskID++);
    zclApp_Init(taskID);
}
