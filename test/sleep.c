#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include <proctimes.h>
#include<sys/time.h>
#define __NR_getproctimes 326//syscall number

int main(){
	pid_t tid;
	struct proctimes time1, time2;
	tid = getpid();

	syscall(__NR_getproctimes, tid, &time1);
	sleep(5);	
	syscall(__NR_getproctimes, tid, &time2);
	printf("Getproctimes used time: %ld\n", time2.proc.real_time-time1.proc.real_time);
        

	struct timeval tpstart, tpend;
	float timeuse;
	gettimeofday(&tpstart, NULL);
        sleep(5);
	gettimeofday(&tpend,NULL);
	timeuse=1000000*(tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
	timeuse/=1000000;
	printf("Gettimeofday used time: %f\n", timeuse);
	return 0;
}
