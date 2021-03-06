// Copyright 2020 Joshua J Baker. All rights reserved.

#ifndef EVIO_H
#define EVIO_H

#include <sys/socket.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

struct evio_conn;

void evio_conn_close(struct evio_conn *conn);
void *evio_conn_udata(struct evio_conn *conn);
void evio_conn_set_udata(struct evio_conn *conn, void *udata);
void evio_conn_write(struct evio_conn *conn, const void *data, ssize_t len);
const char *evio_conn_addr(struct evio_conn *conn);

struct evio_events {
    int64_t (*tick)(int64_t nano, void *udata);
    bool (*sync)(int64_t nano, void *udata);
    void (*data)(int64_t nano, struct evio_conn *conn, 
                 const void *data, size_t len, void *udata);
    void (*opened)(int64_t nano, struct evio_conn *conn, void *udata);
    void (*closed)(int64_t nano, struct evio_conn *conn, void *udata);
    void (*serving)(int64_t nano, const char **addrs, int naddrs, void *udata);
    void (*error)(int64_t nano, const char *message, bool fatal, void *udata);
};

void evio_main(const char *addrs[], int naddrs, struct evio_events events, 
               void *udata);

void evio_set_allocator(void *(malloc)(size_t), void (*free)(void*));

#endif

