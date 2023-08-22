#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {

	mqd_t mq_folder;
	pid_t receiverspid;

	char* massege; 

	mq_folder = mq_open("/pidbuffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
	if (-1 == mq_folder) {
		perror("mq ERR");
		exit(EXIT_FAILURE);
	}

	receiverspid = getpid();
	massege = &receiverspid;

	if (-1 == mq_send(mq_folder, (char*)&receiverspid, 5, 1)) {
		perror("send ERR");
		exit(EXIT_FAILURE);
	}

	while (1) {
		printf("Process is still running!\n");
		sleep(5);
	}

	exit(EXIT_SUCCESS);
	
}

