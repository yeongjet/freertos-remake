const fs = require('fs')
const data = `
1 static void prvInitialiseNewTask(TaskFunction_t pxTaskCode,(1)
2                                  const char * const pcName,(2)
3                                  const uint32_t ulStackDepth,(3)
4                                  void * const pvParameters,(4)
5                                  TaskHandle_t * const pxCreatedTask,(5)
6                                  TCB_t *pxNewTCB )(6)
7
8 {
9     StackType_t *pxTopOfStack;
10     UBaseType_t x;
11
12     /* 获取栈顶地址 */(7)
13     pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1 );
14     /* 向下做8字节对齐 */(8)
15     pxTopOfStack = ( StackType_t * ) \
16                      ( ( ( uint32_t ) pxTopOfStack ) & ( ~( ( uint32_t ) 0x0007 ) ) );
17
18     /* 将任务名存储在TCB中 */(9)
19     for ( x = ( UBaseType_t ) 0; x < ( UBaseType_t ) configMAX_TASK_NAME_LEN; x++ )
20     {
21         pxNewTCB->pcTaskName[ x ] = pcName[ x ];
22
23         if ( pcName[ x ] == 0x00 )
24         {
25             break;
26         }
27     }
28     /* 任务名的长度不能超过configMAX_TASK_NAME_LEN */(10)
29     pxNewTCB->pcTaskName[ configMAX_TASK_NAME_LEN - 1 ] = '\0';
30
31     /* 初始化TCB中的xStateListItem节点 */(11)
32     vListInitialiseItem( &( pxNewTCB->xStateListItem ) );
33     /* 设置xStateListItem节点的拥有者 */(12)
34     listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB );
35
36
37     /* 初始化任务栈 */(13)
38     pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack,
39                              pxTaskCode,
40                              pvParameters );
41
42
43     /* 让任务句柄指向任务控制块 */(14)
44     if ( ( void * ) pxCreatedTask != NULL )
45     {
46         *pxCreatedTask = ( TaskHandle_t ) pxNewTCB;
47     }
48 }`

const deleteRowHeader = length => data.split('\n').map(item => item.substr(length+1)).join('\n')

fs.writeFileSync('out.txt', deleteRowHeader(1))