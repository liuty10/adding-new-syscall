#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/syscall.h>
#include<proctimes.h>
#define __NR_getproctimes 326//syscall number

int main(){
	pid_t tid,pid;
	int status;
	struct proctimes time1, time2;
	tid = getpid();

	syscall(__NR_getproctimes, tid, &time1);
	pid = fork();	
	if(pid!=0){
		syscall(__NR_getproctimes, tid, &time2);
		printf("Getproctimes used time: %ld\n", time2.proc.real_time-time1.proc.real_time);
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
        }
	exit(0);
}
