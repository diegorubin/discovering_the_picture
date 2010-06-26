/*
 * main.c
 *
 *  Created on: Jun 20, 2010
 *      Author: Diego Rubin
 */

int main(int argc, char **argv){
	for(;;){

		struct pollfd pfds[2];

		pfds[0].fd = STDIN_FILENO;
	 	pfds[0].events = POLLIN;

		pfds[1].fd = socket;
		pfds[1].events = POLLIN;

		//fazer if menor q 0
		poll(pfds, 2, -1);

		if (pfds[0].revents != 0){
			char buffer[1024], buffer2[1024];

			if(fgets(buffer, sizeof buffer, stdin) == NULL)
				break;

			snprintf(buffer2, sizeof buffer2, "%s disse: %s\n", nickname, chop(buffer));
			send(socket, buffer2, strlen(buffer2), 0);

		}

		if (pfds[1].revents != 0) {
			char buffer[1024];

			int r = recv(socket, buffer, sizeof buffer - 1,0);
			if(r <= 0)
				break;
			buffer[r] = 0;
			puts(buffer);
		}
	}
	return 0;
}
