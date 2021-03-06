#ifndef SO_DB_H_
#define SO_DB_H_

/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

typedef struct sodbctl sodbctl;
typedef struct sodbasync sodbasync;
typedef struct sodb sodb;

struct sodbctl {
	srobj       o;
	void       *parent;
	uint32_t    created;
	uint32_t    scheduled;
	uint32_t    dropped;
	siprofiler  rtp;
} sspacked;

struct sodbasync {
	srobj o;
	sodb *parent;
};

struct sodb {
	srobj o;
	sostatus status;
	sodbctl ctl;
	sodbasync async;
	srobjlist cursor;
	sxindex coindex;
	sdc dc;
	sischeme scheme;
	si index;
	ssspinlock reflock;
	uint32_t ref;
	uint32_t ref_be;
	uint32_t txn_min;
	uint32_t txn_max;
	sr r;
} sspacked;

static inline int
so_dbactive(sodb *o) {
	return so_statusactive(&o->status);
}

srobj    *so_dbnew(so*, char*);
srobj    *so_dbmatch(so*, char*);
srobj    *so_dbmatch_id(so*, uint32_t);
void      so_dbref(sodb*, int);
uint32_t  so_dbunref(sodb*, int);
uint32_t  so_dbrefof(sodb*, int);
int       so_dbgarbage(sodb*);
int       so_dbvisible(sodb*, uint32_t);
void      so_dbbind(so*);
void      so_dbunbind(so*, uint32_t);
int       so_dbmalfunction(sodb*);
svv      *so_dbv(sodb*, sov*, int);

#endif
