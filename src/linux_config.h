#ifndef LINUX_CONFIG_H_
#define LINUX_CONFIG_H_

#include <arpa/inet.h>
#include <crypt.h>
#include <ctype.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h> /* IOV_MAX */
#include <malloc.h> /* memalign() */
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h> /* TCP_NODELAY, TCP_CORK */
#include <signal.h>
#include <stdarg.h>
#include <stddef.h> /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/utsname.h> /* uname() */
#include <time.h>        /* tzset() */
#include <unistd.h>

#if defined(HAVE_SELECT)
#include <sys/select.h>
#endif

extern char **environ;

#endif /* LINUX_CONFIG_H_ */