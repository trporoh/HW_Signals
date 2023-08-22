#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void mysignal(int signal) {

	printf("Got the signal\n");

}

int main(int argc, char** argv) {

	mqd_t mq_folder;
	pid_t* receiverspid;

	struct mq_attr attr;
	struct sigaction action;

	char* massege = (char*)malloc(sizeof(pid_t));
	memset(massege, '\0', sizeof(pid_t));

	mq_folder = mq_open("/pidbuffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
	if (-1 == mq_folder) {
		perror("mq ERR");
		exit(EXIT_FAILURE);
	}
	do {
		mq_receive(mq_folder, massege, attr.mq_msgsize, NULL);

	} while (!strcmp(massege, ""));

	action.sa_handler = mysignal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	sigaction(SIGUSR1, &action, NULL);

	receiverspid = massege;

	kill(*receiverspid, SIGUSR1);

	exit(EXIT_SUCCESS);

}
