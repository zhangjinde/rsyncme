/* @file        rm_tcp.h
 * @brief       Send data over TCP.
 * @author      Piotr Gregor <piotrgregor@rsyncme.org>
 * @date        18 Apr 2016 00:45 AM
 * @copyright   LGPLv2.1 */


#ifndef RSYNCME_TCP_H
#define RSYNCME_TCP_H


#include "rm_defs.h"
#include "rm_core.h"
#include "rm_serialize.h"

#include <fcntl.h>
#include <netdb.h>


struct rm_ch_ch_ref;


enum rm_error rm_tcp_rx(int fd, void *dst, size_t bytes_n);
enum rm_error rm_tcp_tx(int fd, void *src, size_t bytes_n);

/* tx checksums only */
int rm_tcp_tx_ch_ch(int fd, const struct rm_ch_ch_ref *e);
/* tx checksums & ref */
int rm_tcp_tx_ch_ch_ref(int fd, const struct rm_ch_ch_ref *e);

enum rm_error rm_tcp_tx_msg_ack(int fd, enum rm_pt_type pt, enum rm_error status, uint16_t port);

/* @brief       Set socket blocking mode.
 * @details     @on is either 0 or 1, if it is 0 blocking mode is turned off
 *              and socket becomes nonblocking, if @on == 1 socket blocking
 *              mode is turned on */
int rm_tcp_set_socket_blocking_mode(int fd, uint8_t on);

enum rm_error rm_core_connect(int *fd, const char *host, uint16_t port, int domain, int type, const char **err_str) __attribute__((nonnull(1,2,6)));
enum rm_error rm_tcp_connect(int *fd, const char *host, uint16_t port, int domain, const char **err_str) __attribute__((nonnull(1,2,5)));
enum rm_error rm_tcp_connect_nonblock_timeout_once(int fd, struct addrinfo *res, uint16_t timeout_s, uint16_t timeout_us) __attribute__ ((nonnull(2)));
enum rm_error rm_tcp_connect_nonblock_timeout(int *fd, const char *host, uint16_t port, int domain, uint16_t timeout_s, uint16_t timeout_us, const char **err_str) __attribute__((nonnull(1,2,7)));

enum rm_error rm_tcp_read(int fd, void *dst, size_t bytes_n);
enum rm_error rm_tcp_write(int fd, const void *src, size_t bytes_n);


#endif  /* RSYNCME_TCP_H */
