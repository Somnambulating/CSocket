#ifndef CORE_UNIX_H_
#define CORE_UNIX_H_

#define __APPLE_USE_RFC_3542 /* IPV6_PKTINFO */

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <grp.h>
#include <inttypes.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h> /* TCP_NODELAY */
#include <pwd.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h> /* offsetof() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/filio.h> /* FIONBIO */
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/mount.h> /* statfs() */
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
// #include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>
// #include <xlocale.h>

#ifndef IOV_MAX
#define IOV_MAX 64
#endif

#if (HAVE_SELECT)
#include <sys/select.h>
#endif

#define LISTEN_BACKLOG -1

#ifndef HAVE_INHERITED_NONBLOCK
#define HAVE_INHERITED_NONBLOCK 1
#endif

#ifndef HAVE_CASELESS_FILESYSTEM
#define HAVE_CASELESS_FILESYSTEM 1
#endif

#define HAVE_OS_SPECIFIC_INIT 1
#define HAVE_DEBUG_MALLOC 1

typedef int c_socket_t;

extern char **environ;

#endif /* CORE_UNIX_H_ */