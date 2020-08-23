#include "libcxx.h"
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#define MAX_EVENTS 5
#define MAXLINE2 5
int main()
{
    struct epoll_event event;
    struct epoll_event events[MAX_EVENTS];
    int event_count;
    rio_t rio;
    char buf[MAXLINE2 + 1];

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        return -1;
    }

    event.events = EPOLLIN;
    event.data.fd = 0;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event))
    {
        close(epoll_fd);
        return -3;
    }

    for (;;)
    {
        printf("\nPolling for input...\n");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
        printf("%d ready events\n", event_count);
        for (int i = 0; i < event_count; ++i)
        {
            int fd = events[i].data.fd;
            printf("Reading file descriptor %d\n", fd);
            // Rio_readinitb(&rio, fd);
            // int nbytes = Rio_readlineb(&rio, buf, MAXLINE2+1);
            // when using level triggering, what is still left to read
            //      will be read in the next round
            int nbytes = read(fd, buf, MAXLINE2);
            printf("%d bytes read\n", nbytes);
            buf[nbytes] = '\0';
            printf("Read '%s'\n", buf);
        }
    }

    if (close(epoll_fd))
    {
        return -2;
    }
    return 0;
}