#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ws2tcpip.h>
#include "sig_utils.h"
#include "network.h"
#include "handle_client.h"


int server_socket_fd;

int main() {
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

    if ((server_socket_fd = create_server_socket()) == -1) {
        return 1;
    }

    if (init_signal_handler() != 0) {
        return 1;
    }

    struct sockaddr_storage client_addr = {0};

    while(1) {
        socklen_t addr_size = sizeof(client_addr);
        int new_client_socket_fd = accept(server_socket_fd, (struct sockaddr *) &client_addr, &addr_size);

        if (new_client_socket_fd == -1) {
            continue;
        }

        print_client_ip(new_client_socket_fd);

#ifndef _WIN32
        // Linux multi-process handling using fork()
        if (fork() == 0) { 
            close(server_socket_fd); 
            if (handle_client(new_client_socket_fd) == -1) {
                exit(1);
            }
            exit(0);
        }
        close(new_client_socket_fd);
#else
        // Windows fallback: handle request synchronously in main thread
        handle_client(new_client_socket_fd);
        closesocket(new_client_socket_fd);
#endif
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}