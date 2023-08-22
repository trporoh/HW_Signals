#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char** argv) {

	mqd_t mq_folder;
	pid_t *receiverspid;

	struct mq_attr attr;

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

	receiverspid = massege;

	kill(*receiverspid, 9);

	exit(EXIT_SUCCESS);
}