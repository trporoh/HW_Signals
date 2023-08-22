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
	sigset_t* newset;
	sigset_t* oldset;

	char* massege;

	int* signumber;

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

	sigemptyset(newset);
	sigaddset(newset, 10);
	sigprocmask(SIG_BLOCK, newset, oldset);

	while (1) {

		sigwait(newset, signumber);
		if (signumber != NULL) {
			break;
		}

	}
	printf("Signal received %d!\n", *signumber);

	exit(EXIT_SUCCESS);

}