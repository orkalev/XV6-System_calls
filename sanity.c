#include "types.h"
#include "stat.h"
#include "user.h"

void dummy_loop(){
  for (double z = 0; z < 10000.0; z+= 0.1){
    double x =  x + 3.14 * 89.64;   // useless calculations to consume CPU time
  }
}

int
main(int argc, char **argv)
{
  if (argc > 1){
    printf(1,"Usage: sanity to many arguments\n");
    exit(1);
  }

  int i, pid;
  struct perf * perf_arr[3];
  for(i=0; i<3; i++){
    perf_arr[i] = (struct  perf*)malloc(sizeof(struct perf));
  }

  //struct perf * performance = (struct  perf*)malloc(sizeof(struct perf));
  int status;
  printf(1,"PID   PS_PRIORITY     STIME     RETIME     RTIME\n");

  for (i=0; i<3; i++){
    pid = fork();

    if (pid > 0){ //child
      if(pid%3 == 0)
        set_ps_priority(1);
        else if(pid%3 == 1)
          set_ps_priority(5);
           else
            set_ps_priority(10);

      set_cfs_priority(3);
      dummy_loop();
      proc_info(perf_arr[i]);
      printf(1,"%d\t%d\t\t%d\t%d\t\t%d\n",pid,
                                                              perf_arr[i]->ps_priority,
                                                              perf_arr[i]->stime,
                                                              perf_arr[i]->retime,
                                                              perf_arr[i]->rtime);
      wait(&status);
      exit(0);
    }
    else{ //parent
      wait(&status);
    }
  }
  for(i=0; i<3; i++){
    free(perf_arr[i]);
  }
  free(perf_arr);
  exit(0);
}



