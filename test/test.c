#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#define __NR_getproctimes 326//syscall number

int main(){
	pid_t tid;
	int nicevalue;
	int prio = 0;
	int nice = 0;
	tid = getpid();

	syscall(__NR_getproctimes, tid, 0, -5, &prio, &nice);
	printf("pid: %d\n prio: %d\n nice:%d\n", tid, prio, nice);
	
	syscall(__NR_getproctimes, tid, 1, -5, &prio, &nice);
	printf("pid: %d\n prio: %d\n nice:%d\n", tid, prio, nice);
	return 0;
}
