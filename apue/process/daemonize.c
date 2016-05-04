#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void daemonize(const char *cmd){
    int i, fd0, fd1, fd2;
    pid_t pid, sid;
    struct rlimit rl;
    struct sigaction sa;

    /* Clear file creation mask */
    umask(0);

	/* fork off the parent process */
	pid = fork();
	if(pid < 0){
		perror("fork error");
		exit(EXIT_FAILURE);
	}else if(pid != 0){ /* parent */
		exit(EXIT_SUCCESS);
	}
	
	/* Create a new SID and become a session leader to lose controlling TTY.*/
	sid = setsid();
	if(sid < 0){
		perror("setsid error");
		exit(EXIT_FAILURE);
	}

    /*
     * Change the current working directory to the root so 
     * we won't prevent file systems from being unmounted.
     */
    if(chdir("/") < 0){
        perror("can't change directory to /");
		exit(EXIT_FAILURE);
    }
	

    /* Get maximum number of file descriptors. and close all open file descriptors */
    if(getrlimit(RLIMIT_NOFILE, &rl) < 0){
        perror("can't get file limit");
        exit(-1);
    }
    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i = 0; i < rl.rlim_max; i++)
        close(i);


    /* Ensure future opens won't allocate controlling TTYs. */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0){
        perror("can't ignore SIGHUP");
        exit(-1);
    }


    /* Attach file descriptors 0, 1, 2 to /dev/null. */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /* Initialize the log file */

}
