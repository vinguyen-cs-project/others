/* Vi Nguyen -- EUID: 11300388
 * CSCE3600.003
 * Minor4
 * Server and Client
 * Version: 1.0
 * Date: Jan 24, 2019
 */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

#define SOCKETNAME "minor4ServerSocket"

void printWrite(int ns, char xo, const char* msg) {
	printf("%c>%s", xo, msg);
	write(ns, msg, strlen(msg)+1);
}

bool check(const char board[3][3]) {
	for (int i =0; i<3; i++) {
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
			if(board[i][0] != ' ') return true;
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
			if(board[0][i] != ' ') return true;
	}
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
		if(board[0][0] != ' ') return true;
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
		if(board[0][2] != ' ') return true;
	return false;
}

int main(int argc, char *argv[])
{
	int s;                          /* Listen socket */
	int ns;                         /* Socket for first connection. */
	int ns2;                        /* Socket for second connection. */
	int maxfd;                      /* descriptors up to maxfd-1 polled*/
	int nread;                      /* # chars on read()*/
	int nready;                     /* # descriptors ready. */
	fd_set fds;                     /* Set of file descriptors to poll*/
	int cli_size[2];
	int portno;
	struct sockaddr_in serv_addr, cli_addr[2];
	char board[3][3] = {"   ", "   ", "   "};
	char buff[1025];
	char msg[1025];

	unlink(SOCKETNAME);

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket error\n");
		exit(EXIT_FAILURE);
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(buff, '0', sizeof(buff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	portno = atoi(argv[1]);
	serv_addr.sin_port = htons(portno);

	int on = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (bind(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("bind error\n");
		exit(EXIT_FAILURE);
	}

	if (listen(s, 10) == -1)
	{
		printf("listen error\n");
		exit(EXIT_FAILURE);
	}
	printf("Network Server Starting\n");
	printf("Waiting on Clients\n");
	cli_size[0] = sizeof(cli_addr[0]);
	if ((ns = accept(s, (struct sockaddr *) &cli_addr[0], &cli_size[0])) == -1)
	{
		printf("accept error\n");
		exit(EXIT_FAILURE);
	}
	printf("X<Connected \n");
	printWrite(ns, 'X', "You are player X. Waiting on player O to connect \n");
	cli_size[1] = sizeof(cli_addr[1]);
	if ((ns2 = accept(s, (struct sockaddr *) &cli_addr[1], &cli_size[1])) == -1)
	{
		printf("accept error\n");
		exit(EXIT_FAILURE);
	}
	printf("O<Connected \n");
	printWrite(ns2, 'O', "You are player O \n");
	maxfd = (ns > ns2 ? ns : ns2) +1;
    //create board and print
    sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
    printWrite(ns, 'X', buff);
    printWrite(ns2, 'O', buff);
	for (int i = 0; i<9; i++)
	{
		
		sleep(1);
		if (i % 2 ==0) printWrite(ns, 'X', "Your turn\n");
		else printWrite(ns2, 'O', "Your turn\n");
		//waiting on data from client
		while (1) {
			FD_ZERO(&fds);
			FD_SET(ns,&fds); FD_SET(ns2,&fds);
			select(maxfd, &fds, NULL, NULL, NULL);
			if (FD_ISSET(ns,&fds)) {
				read(ns, buff, 1025);
				printf("X<%s", buff);
				//help
				if (buff[0] == '?') {
					printWrite(ns, 'X', "?-Display this help \nR-Resign \nMove<R><C>-Move where <R> is a row A, B or C and <C> is a column 1, 2 or 3 \nExample Moves: MA1 MC3 MB1\n");
				}
				else if (i%2 !=0 ) printWrite(ns, 'X', "It's not your turn\n");
				else {
					///resign
					if (buff[0] == 'R') {
						printWrite(ns2, 'O', "You win, X resigned");
						goto close;
					}
					else if (buff[0] == 'M') {
						//Invalid Move
						if( buff[1] > 'C' || buff[2] > '3')
							printWrite(ns, 'X', "Invalid Move\n  Move should be M<R><C> with no spaces\n  Example: MA1 or MB3\n");
						else {
							//record move if in turn
							int c = buff[2]-'1';
							if(buff[1] == 'A' && board[ 0 ][c ] == ' ') {
								board[ 0 ][c ] = 'X';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else if (buff[1] == 'B' && board[ 1 ][c ] == ' ') {
								board[ 1 ][ c] = 'X';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else if (buff[1] == 'C' && board[ 2 ][c ] == ' ') {
								board[ 2 ][ c] = 'X';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else printWrite(ns, 'X', "That spot is already taken\n");
						}
					}
					else printWrite(ns, 'X', "Invalid Command\n");
				}
			}
			if (FD_ISSET(ns2,&fds)) {
				read(ns2, buff, 1025);
				printf("O<%s", buff);
				//help
				if (buff[0] == '?') {
					printWrite(ns2, 'O', "?-Display this help \nR-Resign \nMove<R><C>-Move where <R> is a row A, B or C and <C> is a column 1, 2 or 3 \nExample Moves: MA1 MC3 MB1\n");
				}
				//resign
				else if (i%2 == 0) printWrite(ns2, 'O', "It's not your turn\n");
				else {
					if (buff[0] == 'R') {
						printWrite(ns, 'X', "You win, O resigned");
						goto close;
					}
					//invalid move
					else if (buff[0] == 'M') {
						if(buff[1] > 'C' || buff[2] > '3')
							printWrite(ns2, 'O', "Invalid Move\n  Move should be M<R><C> with no spaces\n  Example: MA1 or MB3\n");
						else {
							//record move if in turn
							int c = buff[2]-'1';
							if(buff[1] == 'A' && board[ 0 ][c ] == ' ') {
								board[ 0 ][c ] = 'O';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else if (buff[1] == 'B' && board[ 1 ][c ] == ' ') {
								board[ 1 ][ c] = 'O';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else if (buff[1] == 'C' && board[ 2 ][c ] == ' ') {
								board[ 2 ][ c] = 'O';
                                sprintf(buff, "\n  board\n  1 2 3\n +-+-+-\nA|%c|%c|%c\n +-+-+-\nB|%c|%c|%c\n +-+-+-\nC|%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                                printWrite(ns, 'X', buff);
                                printWrite(ns2, 'O', buff);
								break;
							}
							else printWrite(ns2, 'O', "That spot is already taken\n");
						}
					}
					else printWrite(ns2, 'O', "Invalid Command\n");
				}
			}
		}

		//Update board and print on both server and client
        sleep(1);
		if(check(board)) {
			if (i%2 == 0) {
				printWrite(ns, 'X', "You win\n");
				printWrite(ns2, 'O', "You lose\n");

			}
			else {
				printWrite(ns2, 'O', "You win\n");
				printWrite(ns, 'X', "You lose\n");
			}
            sleep(1);
			goto close;
		}
	}
    sleep(1);
	printWrite(ns, 'X', "Tie game\n");
	printWrite(ns2, 'O', "Tie game\n");
    sleep(1);
close:
	close(ns);
	close(ns2);
	printf("Game Ended\n");
	return 0;
}

