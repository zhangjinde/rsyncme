/*
 * @file        rm_defs.h
 * @brief       Basic includes and definitions.
 * @author      Piotr Gregor < piotrek.gregor at gmail.com >
 * @version     0.1.2
 * @date        2 Jan 2016 11:29 AM
 * @copyright	LGPLv2.1
 */

#ifndef RSYNCME_DEFS_H
#define RSYNCME_DEFS_H


/* To make off_t (used in calls to fseeko) 64 bits type
 * on 32-bit architectures.
 * This will make the names of the (otherwise 32 bit) functions
 * and data types refer to their 64 bit counterparts.
 * off_t will be off64_t, lseek() will use lseek64(), etc.
 * The 32 bit interface is no longer available. */
#define _FILE_OFFSET_BITS 64

#include <stdlib.h>             /* everything */
#include <stdio.h>              /* most I/O */
#include <sys/types.h>          /* syscalls */
#include <sys/stat.h>           /* umask, fstat */
#include <sys/socket.h>         /* socket.h etc. */
#include <netinet/in.h>         /* networking */
#include <linux/netdevice.h>
#include <arpa/inet.h>
#include <string.h>             /* memset, etc. */
#include <fcntl.h>              /* open, R_ONLY */
#include <unistd.h>             /* close */
#include <errno.h>
#include <assert.h>
#include <pthread.h>            /* POSIX threads */
#include <stddef.h>             /* offsetof */
#include <signal.h>
#include <syslog.h>
#include <stdint.h>
#include <ctype.h>              /* isprint */


#include "twlist.h"
#include "twhash.h"


#define RM_BIT_0	(1u << 0)  
#define RM_BIT_1	(1u << 1)
#define RM_BIT_2	(1u << 2)
#define RM_BIT_3	(1u << 3)
#define RM_BIT_4	(1u << 4)
#define RM_BIT_5	(1u << 5)
#define RM_BIT_6	(1u << 6)
#define RM_BIT_7	(1u << 7)

/* TCP messages */
#define RM_MSG_PUSH                 2           /* rsync push */
#define RM_MSG_PULL                 3           /* rsync pull */
#define RM_MSG_BYE                  255         /* close the controlling connection */

#define RM_SESSION_HASH_BITS        10          /* 10 bits hash, array size == 1024 */
#define RM_NONOVERLAPPING_HASH_BITS 16          /* 16 bits hash, array size == 65536 */
#define RM_FILE_LEN_MAX             150         /* max len of names of @x, @y files */

#define RM_ADLER32_MODULUS          65521L      /* biggest prime int less than 2^16 */
#define RM_FASTCHECK_MODULUS        65536L      /* 2^16, this makes rolling calculation possible */
#define RM_ADLER32_NMAX             5552L       /* biggest integer that allows for deferring
                                                 * of modulo reduction so that s2 will still fit in
                                                 * 32 bits when modulo is being done with 65521 value */

/* CORE */
#define RM_CORE_ST_INITIALIZED      0           /* init function returned with no errors */
#define RM_CORE_ST_SHUT_DOWN        255         /* shutting down, no more requests */
#define RM_CORE_CONNECTIONS_MAX     1           /* max number of simultaneous connections */
#define RM_CORE_HASH_OK             84
#define RM_CORE_DAEMONIZE           0           /* become daemon or not, turn it to off
                                                   while debugging for convenience */
#define RM_STRONG_CHECK_BITS        16

/* defaults */
#define RM_DEFAULT_L                512         /* default block size in bytes */
#define RM_L1_CACHE_RECOMMENDED     8192        /* buffer size, so that it should fit into
                                                 * L1 cache on most architectures */

#define rm_container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#define rm_max(a,b)	({ __typeof__ (a) _a = (a);	\
			__typeof__ (b) _b = (b);	\
			_a > _b ? _a : _b; })
#define rm_min(a,b)	({ __typeof__ (a) _a = (a);	\
			__typeof__ (b) _b = (b);	\
			_a > _b ? _b : _a; })

typedef uint8_t rm_push_flags;  /* Bit  meaning
                                 * 0    force creation of @y if it doesn't exist
                                 * 1
                                 * 2
                                 * 3
                                 * 4
                                 * 5
                                 * 6
                                 * 7 */
typedef uint8_t rm_push_flags;

#endif  // RSYNCME_DEFS_H
