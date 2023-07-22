# chapter 14 : **CO-OPERATIVE SCHEDULER**
<h2>Topics </h2>

<li>The scheduler data structure.</li>

```bash
typedef struct{
    void(*pTask)(void);
    uint32 Delay;
    uint32 Period;
    uint8 RunMe;
}sTask
```

<li>An initialization function.</li>

```bash
SCH_Init_T2();
```

<li>A single interrupt service routine (ISR), used to update the scheduler at regular time intervals.</li>

```bash
void SCH_Update(void)
```
<li>A function for adding tasks to the scheduler.</li>

```bash
Sch_Add_Task (Task_Name, Initial_Delay, Period);
```
<li>A dispatcher function that causes tasks to be executed when they are due to run.</li>

```bash
void SCH_Dispatch_Tasks(void)
```
<li>A function for removing tasks from the scheduler (not required in all applications).</li>

```bash
bit SCH_Delete_Task(const tByte TASK_INDEX)
```
