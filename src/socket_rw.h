#ifndef _SOCKET_RW_H_
#define _SOCKET_RW_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*read timeout default 5 seconds*/
#define TIMEOUT 5

int isvalidip(const char *str);
int make_server_socket(int port);
int tcpip_connect_to_server(const char *serverhostip, int port, int mode=0);
typedef void *(*Threadfunc) (void *);
pthread_t start_thread(int detached, Threadfunc func, void *arg, size_t size);

int read_all(int fd, char *buf, int n);
int write_all(int fd, char *buf, int n);

#ifdef __cplusplus
}
#endif

#endif
