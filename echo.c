#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
  int server_sock;
  int client_sock;

  const size_t BUFFER_SIZE = 1024;
  char message[BUFFER_SIZE];

  int str_len;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  socklen_t client_addr_size;
  int port = atoi(argv[2]);

  server_sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);

  while (1) {
    client_addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);

    while ((str_len = read(client_sock, message, BUFFER_SIZE)) != 0) {
      write(client_sock, message, str_len);
    }

    close(client_sock);
  }

  close(server_sock);
  return 0;
}
