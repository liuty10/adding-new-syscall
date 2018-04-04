#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/syscall.h>
#include<sys/mman.h>
#include<proctimes.h>
#define __NR_getproctimes 326//syscall number

int main(){
	pid_t tid,pid;
	struct proctimes time1, time2;
	int status;
	tid = getpid();
	char* ptr = (char*)mmap(NULL, 1024*1024*1024, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1,0);
	if(ptr == (void*)-1){
		printf("mmap failed!\n");
		return 0;
	}	
	memset(ptr,'a',1024*1024*1024);

	syscall(__NR_getproctimes, tid, &time1);
	pid = fork();	
	if(pid!=0){
		syscall(__NR_getproctimes, tid, &time2);
		printf("Getproctimes used time: %ld\n", time2.proc.real_time-time1.proc.real_time);
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		munmap(ptr,1024*1024*1024);
        }
	exit(0);
}
