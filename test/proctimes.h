#include<unistd.h>

struct proc_time{
	pid_t pid;
	unsigned long real_time;
};
struct proctimes{
	struct proc_time proc;
}
