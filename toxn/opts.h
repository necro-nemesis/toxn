#ifndef TOXN_OPTS_H
#define TOXN_OPTS_H

extern const char *toxn_dir;
extern uint32_t toxn_logmask;
extern int net_max_uploads;
extern unsigned net_max_peers;
extern unsigned net_bw_limit_in;
extern unsigned net_bw_limit_out;
extern int net_port;
extern off_t cm_alloc_size;
extern int ipcprot;
extern int empty_start;
extern const char *tr_ip_arg;
extern int net_ipv4, net_ipv6;
extern unsigned net_numwant;

#endif
