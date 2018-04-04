#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<proctimes.h>
#define __NR_getproctimes 326

void func1(){
	unsigned long i=1000000;
	double z;
	while(i--){
		z=i*(1000000-i);	
	}
}

void func2(){
	unsigned long i=1000000;
	double z;
	while(i--){
		z=i+1;	
	}
}


int main(){
	pid_t tid;
	struct proctimes time1, time2;
	tid = getpid();

	syscall(__NR_getproctimes, tid, &time1);
	func1();	
	syscall(__NR_getproctimes, tid, &time2);
	printf("Mutiplication used time: %ld\n", time2.proc.real_time-time1.proc.real_time);
        
	syscall(__NR_getproctimes, tid, &time1);
	func2();	
	syscall(__NR_getproctimes, tid, &time2);
	printf("Addition used time: %ld\n", time2.proc.real_time-time1.proc.real_time);

	return 0;
}
