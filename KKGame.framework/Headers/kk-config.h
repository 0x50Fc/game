//
//  kk-config.h
//  KKGame
//
//  Created by 张海龙 on 2017/12/6.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#ifndef kk_config_h
#define kk_config_h


#ifndef READONLY
#define READONLY const
#endif

#ifdef __APPLE__

#include <TargetConditionals.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>
#include <dns.h>
#include <dns_util.h>
#include <resolv.h>
#include <sys/stat.h>
#include <utime.h>
#include <zlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <math.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <sys/ioctl.h>
#include <sys/sockio.h>
#include <net/ethernet.h>
#include <sys/types.h>
#ifdef __OPENSSL__
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#endif

#define closesocket(a) close(a)
#define kk_socket_t    int

#define EXPORT

#define UNUSED(a) (void)a;

#define BITS_LOW
//#define BITS_HIGH

#ifndef PATH_MAX
#define PATH_MAX    2048
#endif

#ifndef PATH_SPLIT
#define PATH_SPLIT  '/'
#endif

#elif defined(__WIN32__)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <memory.h>
#include <windows.h>
#include <winsock.h>
#include <io.h>
#include "zlib/zlib.h"
#include <stdarg.h>
#include <assert.h>
#include <io.h>

#define mkdir(a,b) mkdir(a)

#define kk_socket_t    int

#define sleep(a) Sleep((a) * 1000)
#define usleep(a) Sleep(a)

#define atoll atol

#define BITS_LOW

typedef long socklen_t;

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef PATH_MAX
#define PATH_MAX    1024
#endif

#ifndef PATH_SPLIT
#define PATH_SPLIT  '\\'
#endif

#elif defined __LINUX__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <utime.h>
#include <zlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <math.h>
#include <net/if.h>
#ifdef __OPENSSL__
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#endif

#define closesocket(a) close(a)
#define kk_socket_t    int

#define EXPORT

#define UNUSED(a) (void)a;

#define BITS_LOW
//#define BITS_HIGH

#ifndef PATH_MAX
#define PATH_MAX    1024
#endif

#ifndef PATH_SPLIT
#define PATH_SPLIT  '/'
#endif

#elif defined __QT__


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <utime.h>
#include <zlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <assert.h>
#include <netdb.h>
#include <fcntl.h>


#define closesocket(a) close(a)
#define kk_socket_t    int

#define EXPORT


#elif defined(__ANDROID__)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/stat.h>
#include <utime.h>
#include <zlib.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <math.h>
#include <errno.h>
#ifdef __OPENSSL__
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#endif

#define closesocket(a) close(a)
#define kk_socket_t    int

#define EXPORT

#define UNUSED(a) (void)a;

#define HAS_PTHREAD

#define BITS_LOW
//#define BITS_HIGH

//#define hatoi atoi

#ifndef PATH_MAX
#define PATH_MAX    1024
#endif

#ifndef PATH_SPLIT
#define PATH_SPLIT  '/'
#endif

#ifndef MIN
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#endif

#define log2(a)        (log(a) / log(2.0))

#endif


#endif /* kk_config_h */
