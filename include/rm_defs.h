/// @file       rm_defs.h
/// @brief      Shared includes, definitions.
/// @author     Piotr Gregor piotrek.gregor at gmail.com
/// @version    0.1.1
/// @date       2 Jan 2016 11:29 AM
/// @copyright  LGPL

#ifndef RSYNCME_DEFS_H
#define RSYNCME_DEFS_H


#include <stdlib.h>             // everything
#include <stdio.h>              // most I/O
#include <sys/types.h>          // syscalls
#include <sys/socket.h>         // socket.h etc.
#include <netinet/in.h>         // networking
#include <string.h>             // memset, etc.
#include <fcntl.h>              // open
#include <unistd.h>             // close
#include <errno.h>
#include <assert.h>
#include <pthread.h>            // POSIX threads
#include <stddef.h>             // offsetof


#include "twlist.h"
#include "twhash.h"


// TCP messages
#define RM_MSG_SESSION_ADD		1	// add rsync session
#define RM_MSG_BYE			255	// close the controlling connection

#define RM_SESSION_HASH_BITS		10	// 10 bits hash, array size == 1024

// CORE
#define RM_CORE_ST_INITIALIZED		0	// init function returned with no errors
#define RM_CORE_ST_SHUT_DOWN		255	// shutting down, no more requests
#define RM_CORE_CONNECTIONS_MAX		1	// max number of simultaneous connections

#define rm_container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})


#endif  // RSYNCME_DEFS_H
