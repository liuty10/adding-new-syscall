# hello-world
Adding a new system call to Linux kernel 4.4.102

1.	tar –xf linux-4.4.102.tar.gz and cd linux-4.4.102

2.	add syscall number
a)	modify arch/x86/entry/syscalls/syscall_64.tbl
 323	common	userfaultfd		sys_userfaultfd
 324	common	membarrier		sys_membarrier
 325	common	mlock2			sys_mlock2
+326	64	getproctimes		sys_getproctimes

3.	declare syscall service routine in ./include/linux/syscalls.h
 +asmlinkage long sys_getproctimes(pid_t pid, struct proctimes __user * time);
 
4.	Implement syscall getproctimes in “kernel/sys.c”. I only listed parts of the function here.
SYSCALL_DEFINE2(getproctimes, pid_t, pid, struct proctimes __user*, time){
        printk("This getpoctimes syscall is created by Tianyi Liu!\n");
        struct pid * kpid;
        struct stask_struct * task;
        struct proctimes tmp;
        if(pid !=0){
                kpid = find_get_pid(pid);
                if(kpid == NULL)
                        return EINVAL;
                task = pid_task(kpid, PIDTYPE_PID);
        }else{
                task = current;
        }
        tmp.proc.pid = task_pid_nr(task);
        struct timeval ktv;
        do_gettimeofday(&ktv);
        tmp.proc.start_time             = task_start_time(task);
        tmp.proc.real_time              = ktv.tv_sec * 1000000 + ktv.tv_usec;
        copy_to_user(time, (const void*)&tmp, sizeof(tmp));
        return 0;
}

5.	Config the kernel: make menuconfig
If there occurs some error about missing ncurses, you should install ncurese using the following command: 
apt-get insall libncurses5-dev

6.	Compile the kernel: make 
If openssl is reported missing, please install it using following command:
apt-get install libssl-dev

7.	Compile kernel modules
Make modules

8.	Install modules and kernels
Make modules_install && make install

9.	Update grub and reboot
Update-grub2
Reboot

10.	Test program1: sleep(5)
The first one is 5000176 microsecond
The second one is 5.000268 seconds
They are the same.
	
11.	Test arithmetic operation for multiplication and addition
	The multiplications take longer time than additions.

12.	Test the fork()
The fork() function takes about 50 microseconds.

13.	Test fork() with mmap pollution
Because of the pollution, the fork() takes longer time.