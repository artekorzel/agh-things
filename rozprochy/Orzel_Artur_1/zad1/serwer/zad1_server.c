#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define QUEUE_SIZE 1
#define BUFLEN 21

int listening_socket;

void interrupt(int signo)
{
	close(listening_socket);
	printf("Server zatrzymany.\n");
	exit(EXIT_SUCCESS);
}

void set_security_context(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Uzycie: %s <PORT>\n", argv[0]);
		exit(1);
	}

	if(signal(SIGINT, interrupt) == SIG_ERR)
	{
		perror("signal error");
		exit(1);
	}

	sigset_t set;
	if(sigfillset(&set) == -1)
	{
		perror("sigfillset error");
		exit(1);
	}

	if(sigdelset(&set, SIGINT) == -1)
	{
		perror("sigdelset error");
		exit(1);
	}

	if(sigprocmask(SIG_SETMASK, &set, NULL) == -1)
	{
		perror("sigprocmask error");
		exit(1);
	}
}

int main(int argc, char** argv)
{
	set_security_context(argc, argv);

	listening_socket = socket(AF_INET, SOCK_STREAM, 0);		//pobieramy deskryptor socketu IPv4 dla TCP
	if(listening_socket == -1)
	{
		perror("socket error");
		exit(1);
	}

	int yes = 1;
	setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));	//zwalniamy pozornie zajęty port

	struct sockaddr_in server_addr;
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(listening_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)	//wiazemy socket z adresem i portem
	{
		perror("bind error");
		close(listening_socket);
		exit(1);
	}

	if(listen(listening_socket, QUEUE_SIZE))	//w danej chwili tylko jednemu klientowi mozemy odpowiadac
	{
		perror("listen error");
		close(listening_socket);
		exit(1);
	}

	char buffer[BUFLEN];
	struct sockaddr_in client_addr;
	int client_socket, data_length;
	socklen_t client_addr_len;
	char one_byte_number;
	short two_byte_number;
	int four_byte_number;
	while(1)
	{
		client_socket = accept(listening_socket, (struct sockaddr*)&client_addr, &client_addr_len);
		if(client_socket == -1)
		{
			perror("accept error");
			close(listening_socket);
			exit(1);
		}

		data_length = recv(client_socket, buffer, BUFLEN, 0);
		buffer[data_length] = '\0';
		switch(data_length)
		{
			case -1:
				perror("recv error");
				close(client_socket);
				close(listening_socket);
				exit(1);
			case 0:
				printf("disconnected");
				close(client_socket);
				buffer[0] = '\0';
				break;
			case 4:		//maks 4 cyfry - 1 bajt, ewentualnie spacje z przodu
				one_byte_number = (char)atoi(buffer);
				printf("Recv - odebrano: %d\n", one_byte_number);
				++one_byte_number;
				sprintf(buffer, "%4d", one_byte_number);
				buffer[4] = '\0';
				break;
			case 6:		//maks 6 cyfr - 2 bajty, ewentualnie spacje z przodu
				two_byte_number = (short)atoi(buffer);
				printf("Recv - odebrano: %d\n", two_byte_number);
				++two_byte_number;
				sprintf(buffer, "%6d", two_byte_number);
				buffer[6] = '\0';
				break;
			case 11:	//maks 11 cyfr - 4bajty, ewentualnie spacje z przodu
				four_byte_number = (int)atoi(buffer);
				printf("Recv - odebrano: %d\n", four_byte_number);
				++four_byte_number;
				sprintf(buffer, "%11d", four_byte_number);
				buffer[11] = '\0';
				break;
			default:	//inne dane ignorujemy
				printf("Bledne dane - zignorowano");
				buffer[0] = '\0';
				break;
		}

		printf("Odsylamy: %s\n", buffer);
		if(send(client_socket, buffer, strlen(buffer), 0) == -1)
		{
			perror("send error");
			close(client_socket);
			close(listening_socket);
			exit(1);
		}

		close(client_socket);
	}

	return EXIT_SUCCESS;
}

