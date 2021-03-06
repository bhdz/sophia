#ifndef SR_H_
#define SR_H_

/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

typedef struct sr sr;

struct sr {
	srerror *e;
	sfstorage fmt_storage;
	sf fmt;
	srscheme *scheme;
	srseq *seq;
	ssa *a;
	ssinjection *i;
	void *compression;
	sscrcf crc;
};

static inline void
sr_init(sr *r,
        srerror *e,
        ssa *a,
        srseq *seq,
        sf fmt,
        sfstorage fmt_storage,
        srscheme *scheme,
        ssinjection *i,
        sscrcf crc,
        void *compression)
{
	r->e           = e;
	r->a           = a;
	r->seq         = seq;
	r->scheme      = scheme;
	r->fmt         = fmt;
	r->fmt_storage = fmt_storage;
	r->i           = i;
	r->compression = compression;
	r->crc         = crc;
}

#endif
