#include "./portmacro.h"
#include "./task.h"
#include "./projdefs.h"

#if (configSUPPORT_STATIC_ALLOCATION == 1)

askHandle_t xTaskCreateStatic(
	TaskFunction_t pxTaskCode,
	const char *const pcName, const uint32_t ulStackDepth, void *const pvParameters, StackType_t *const puxStackBuffer, TCB_t *const pxTaskBuffer)
{
	TCB_t *pxNewTCB;
	TaskHandle_t xReturn; // 定义一个任务句柄xReturn，用于指向任务的TCB。任务句柄的数据类型为TaskHandle_t，在task.h中定义，实际上就是一个空指针
	if ((pxTaskBuffer != NULL) && (puxStackBuffer != NULL))
	{
		pxNewTCB = (TCB_t *)pxTaskBuffer;
		pxNewTCB->pxStack = (StackType_t *)puxStackBuffer;

		prvInitialiseNewTask(pxTaskCode,   // 任务入口
							 pcName,	   // 任务名称
							 ulStackDepth, // 任务栈大小
							 pvParameters, // 任务形参
							 &xReturn,	 // 任务句柄
							 pxNewTCB);	// 任务栈起始地址
	}
	else
	{
		xReturn = NULL;
	}

	return xReturn;
}


static void prvInitialiseNewTask(TaskFunction_t pxTaskCode, // 任务入口
                                 const char * const pcName, // 任务名称
                                 const uint32_t ulStackDepth, // 任务栈大小
                                 void * const pvParameters, // 任务形参
                                 TaskHandle_t * const pxCreatedTask, // 任务句柄
                                 TCB_t *pxNewTCB ) // 任务控制块指针

{
    StackType_t *pxTopOfStack;
     UBaseType_t x;

     // 获取栈顶地址
     pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
     /* 向下做8字节对齐 */(8)
     pxTopOfStack = ( StackType_t * ) 16                      ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );

     /* 将任务名存储在TCB中 */(9)
     for ( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
     {
         pxNewTCB->pcTaskName[ x ] = pcName[ x ];

         if ( pcName[ x ] == 0x00 )
         {
             break;
         }
     }
     /* 任务名的长度不能超过configMAX_TASK_NAME_LEN */(10)
     pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = "\0";

     /* 初始化TCB中的xStateListItem节点 */(11)
     vListInitialiseItem( &( pxNewTCB->xStateListItem ) );
     /* 设置xStateListItem节点的拥有者 */(12)
     listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB );


     /* 初始化任务栈 */(13)
     pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack,
                              pxTaskCode,
                              pvParameters );

     /* 让任务句柄指向任务控制块 */(14)
     if ( ( void * ) pxCreatedTask != NULL )
     {
         *pxCreatedTask = ( TaskHandle_t ) pxNewTCB;
     }
 }
#endif
