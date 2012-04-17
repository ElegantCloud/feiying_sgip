#include "common.h"
#include "socket_rw.h"

/* check if a string is a valid IP address (dotted-decimal) */
int isvalidip(const char *str)
{
    struct in_addr in;
#ifdef T_LINUX
    /* inet_aton(char str, struct in_addr *in)
       if str is a legal ip address, return value is a non-zero
       otherwise , return 0  
       --QY */

    return inet_aton(str, &in) == 0 ? -1 : 0;
#endif
#ifdef _SOLARIS
    /* inet_pton(int type, char str, void *addr)
       judge whether the char str is a legal ip address
       if int type == AF_INET, addr must have at least 4 bytes
       Return 1: str is a right ip-address
       0: str is not a right ip-address
       --QY */
    return inet_pton(AF_INET, str, &in) == 1 ? 0 : -1;
#endif
    return 0;
}

int make_server_socket(int port)
{
    struct sockaddr_in addr;
    int s;
    int reuse;

    s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1) {
        //error("socket failed");
        goto err;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &reuse,
                   sizeof(reuse)) == -1) {
        //error("setsockopt failed for server address");
        goto err;
    }

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
        //error("bind failed");
        goto err;
    }

    if (listen(s, 10) == -1) {
        //error("listen failed");
        goto err;
    }

    return s;

  err:
    if (s >= 0)
        (void) close(s);
    return -1;
}

int tcpip_connect_to_server(const char *serverhostip, int port, int mode)
{
    struct sockaddr_in addr,selfaddr;
    struct hostent *hostinfo;
    struct linger dontlinger;
    int val;
    int s;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
        goto err;

    /*
    memset((char *)&selfaddr, 0, sizeof(selfaddr));
    selfaddr.sin_family = AF_INET;
    selfaddr.sin_port = 0;
    inet_aton("10.89.10.1", &selfaddr.sin_addr);
    if(bind(s, (struct sockaddr *) &selfaddr, sizeof(selfaddr)) == -1)
      goto err;
    */

    dontlinger.l_onoff = 1;
    dontlinger.l_linger = 0;
    setsockopt(s, SOL_SOCKET, SO_LINGER, &dontlinger, sizeof(dontlinger));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    inet_aton(serverhostip, &addr.sin_addr);

    if (connect(s, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        goto err;
    if(mode)
    {
      /* set to non-block mode */
      val = fcntl(s, F_GETFL, 0);
      fcntl(s, F_SETFL, val | O_NONBLOCK);
    }
    return s;

  err:
    if (s >= 0)
        close(s);
    return -1;
}

/*
* Start a new thread, running function func, and giving it the argument
* `arg'. If `size' is 0, `arg' is given as is; otherwise, `arg' is copied
* into a memory area of size `size'.
* 
* If `detached' is non-zero, the thread is created detached, otherwise
* it is created detached.
*/

pthread_t start_thread(int detached, Threadfunc func, void *arg, size_t size)
{
    void *copy;
    pthread_t id;

    pthread_attr_t attr;
    int ret;

    if (size == 0)
        copy = arg;
    else {
        copy = calloc(1, size);
        if (copy == NULL) {
            //error("malloc failed");
            goto err;
        }
        memcpy(copy, arg, size);
    }

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    if (detached) {
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    }
    do {
        ret = pthread_create(&id, &attr, func, copy);
        if (ret == EAGAIN) {
            //error( "Too many threads, waiting to create one...");
            sleep(1);
        }
    } while (ret == EAGAIN);
    if (ret != 0) {
        //error("pthread_create failed");
        goto err;
    }

    return id;

  err:
    return (pthread_t) - 1;
}

static int timeread(int fd, void *buf, size_t siz)
{
    fd_set r;
    struct timeval timo;

    timo.tv_sec = TIMEOUT;
    timo.tv_usec = 0;

    if (fd < 0)
        return 0;
    //FD_ZERO(&r);
    memset((char *)&r, 0, sizeof(r));
    FD_SET(fd, &r);

    if (select(fd + 1, &r, NULL, NULL, &timo) != 1) {
        /*error("Network timeout signal after %d seconds", TIMEOUT); */
        errno = ETIME;
        return -1;
    }

    return read(fd, buf, siz);
}

int read_all(int fd, char *buf, int n)
{
  int nleft;
  int nbytes;
  char *ptr;
  struct timeval timeo = {5,0};
  socklen_t len = sizeof(timeo);

  setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeo, len);
  ptr=buf;
  nleft=n;
  for(;nleft>0;)
  {
    nbytes=read(fd,ptr,nleft);
    if(nbytes<0)
    {
      if(errno==EINTR)
        nbytes=0;
      else
      {
        return -1;
      }
    }
    else if(nbytes==0)
      break;

    nleft-=nbytes;
    ptr+=nbytes;
  }

  return (n-nleft);
}

int write_all(int fd, char *buf, int n)
{
  int nleft,nbytes;
  char *ptr;
  struct timeval timeo = {5,0};
  socklen_t len = sizeof(timeo);

  setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);
  nleft=n;
  ptr=buf;
  for(;nleft>0;)
  {
    nbytes=write(fd,ptr,nleft);
    if(nbytes<=0)
    {
      if(errno==EINTR)
        nbytes=0;
      else
        return -1;
    }
    nleft-=nbytes;
    ptr+=nbytes;
  }

  return n;
}
