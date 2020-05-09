#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
    int status;

  if(argint(0, &status) < 0)
    return -1;
  exit(status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  char *status;
 
  if(argptr(0, &status,4) < 0)
    return -1;
  return wait((int*)status);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

//@@ System Call Definition
int
sys_memsize(void)
{
  return myproc()->sz;
}

int
sys_set_ps_priority(void)
{
  int priority;
  
  if(argint(0, &priority) < 0)
    return -1;

  if (priority < 1 || priority > 10)
    return -1;

  myproc()->ps_priority = priority;
  return 0;

}

int
sys_set_cfs_priority(void)
{
  int priority;

  if (argint(0, &priority) < 0)
    return -1;

  if (priority < 1 || priority > 3)
    return -1;
  myproc()->cfs_priority = priority;
  return 0;
}

int
sys_policy(void)
{
  int policy;

  if (argint(0, &policy) < 0)
    return -1;

  if (policy < 0 || policy > 2)
    return -1;
  sched_type = policy;
  return 0;
}

int
sys_proc_info(void)
{
  char * performance;

  if(argptr(0, &performance,sizeof(performance)) < 0)
    return -1;

  ((struct perf*)performance)->ps_priority = myproc()->ps_priority;
  ((struct perf*)performance)->stime = myproc()->stime;
  ((struct perf*)performance)->retime = myproc()->retime;
  ((struct perf*)performance)->rtime = myproc()->rtime;
  return 0;
}
//@@ End System Call Definition

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
