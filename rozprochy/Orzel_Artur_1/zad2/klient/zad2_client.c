#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define BUFLEN 1025

int main(int argc, char** argv)
{
	if(argc != 4) {
		printf("Uzycie: %s <IP> <PORT> <NAZWA_PLIKU>\n", argv[0]);
		exit(1);
	}

	int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);	//pobieramy deskryptor socketu IPv4 dla TCP
	if(socket_descriptor == -1)
	{
		perror("socket error");
		exit(1);
	}

	struct sockaddr_in server_addr;
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	if(connect(socket_descriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)	//laczymy z serwerem
	{
		perror("bind error");
		close(socket_descriptor);
		exit(1);
	}

	FILE* file = fopen(argv[3], "wb");	//otwieramy plik do zapisu w trybie binarnym - utworzy jesli nie istnieje
	if(file == NULL) {
		perror("fopen error");
		close(socket_descriptor);
		exit(1);
	}

	char buffer[BUFLEN];
	size_t length;

	while((length = recv(socket_descriptor, buffer, BUFLEN, 0)) > 0)	//dopoki serwer nie zamknie polaczenia i przesyla dane
	{														//
		if(fwrite(buffer, 1, length, file) != length)		//zapisuj je do pliku - tyle ile przyszlo
		{
			perror("fwrite error");
			close(socket_descriptor);
			fclose(file);
			exit(1);
		}
	}
	close(socket_descriptor);
	fclose(file);
	printf("Przesylanie zakonczone sukcesem.\n");

	return EXIT_SUCCESS;
}
