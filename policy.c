#include "types.h"
#include "stat.h"
#include "user.h"

//enum scheduling_policy{defualt_policy, priority_scheduling, CFS};

int
main(int argc, char **argv)
{
	int policy_number;

	if(argc < 2){
    	printf(1, "No policy entered!\n");
    	exit(1);
    }

    if(argc > 2){
    	printf(1, "Too many arguments!\n");
    	exit(1);
    }

    policy_number = atoi(argv[1]);
    if (policy(policy_number) == 0){
      if(policy_number == 0){
          printf(1, "Policy has been successfully changed to Default Policy\n");

      }else if(policy_number == 1){
          printf(1, "Policy has been successfully changed to Priority Policy\n");

      }else if(policy_number == 2){
          printf(1, "Policy has been successfully changed to CFS Policy\n");
      }

      exit(0);
   	}
   	else{
   		printf(1, "Error replacing policy, no such a policy number(%d)\n",policy_number);
   		exit(1);
   	}
}