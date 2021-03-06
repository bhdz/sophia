
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libss.h>
#include <libsf.h>
#include <libsr.h>
#include <libst.h>

typedef struct {
	sshtnode node;
	char key[32];
} htnode;

ss_htsearch(ssht_search, 
            ((sscast(t->i[pos], htnode, node)->node.hash == hash) &&
             (strcmp(sscast(t->i[pos], htnode, node)->key, key) == 0)));

static void
ssht_test0(stc *cx ssunused)
{
	ssa a;
	ss_aopen(&a, &ss_stda);

	ssht ht;
	t( ss_htinit(&ht, &a, 8) == 0 );

	int i = 0;
	while (i < 3431) {
		if (ss_htisfull(&ht)) {
			t( ss_htresize(&ht, &a) == 0 );
		}
		htnode *n = ss_malloc(&a, sizeof(htnode));
		int len = snprintf(n->key, sizeof(n->key), "key_%d", i);
		n->node.hash = ss_fnv(n->key, len);
		int pos = ssht_search(&ht, n->node.hash, n->key, len, NULL);
		ss_htset(&ht, pos, &n->node);
		i++;
	}

	i = 0;
	while (i < 3431) {
		htnode key;
		int len = snprintf(key.key, sizeof(key.key), "key_%d", i);
		key.node.hash = ss_fnv(key.key, len);
		int pos = ssht_search(&ht, key.node.hash, key.key, len, NULL);
		t( ht.i[pos] != NULL );
		t( strcmp(sscast(ht.i[pos], htnode, node)->key, key.key) == 0 );
		i++;
	}

	i = 0;
	while (i < ht.size) {
		if (ht.i[i])
			ss_free(&a, ht.i[i]);
		i++;
	}

	ss_htfree(&ht, &a);
}

stgroup *ssht_group(void)
{
	stgroup *group = st_group("ssht");
	st_groupadd(group, st_test("test0", ssht_test0));
	return group;
}
