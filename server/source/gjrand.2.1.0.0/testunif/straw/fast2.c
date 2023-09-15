/* Miscellaneous stuff for gjrand random numbers version 1.3.0.0 or later. */
/* Copyright (C) 2004-2007 G. Jones. */
/* Licensed under the GNU General Public License version 2 or 3. */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "../../src/my_int_types.h"

/* This one writes a file for use by the tests in testunif */

/* first arg is required file size in bytes or "inf" to write forever. */
/* second optional arg is random seed. */

/* This is basically a non-linear feedback shift register generator. */
/* The register is very large. The period is probably very long, but */
/* hard to calculate and quite likely variable depending on seed. */
/* To make certain the period in actual use will be extremely long, */
/* the register is perturbed before each 4KB of output. */

/* On X86 systems, this one runs insanely fast. You don't need a generator */
/* this fast. Your system I/O, even through pipes to another program, */
/* probably is too slow to keep up. And if you want pseudo-random numbers, */
/* you probably want to do something clever when you get them, which will */
/* take much longer than this generator. */

/* This is a minor tweak of fast.c to try to pass sh5da -r with more data. */
/* It's probably fairly good for most purposes, but use with care. */

static void
crash(char *s)
{
    fprintf(stderr, "crash [%s]\n", s);
    exit(1);
}

static uint32_t buf[1026];

static void
dobuffirst(void)
{
    uint32_t a;

    a=buf[1024]+buf[1025];
    if (a==0) buf[1025]+=1234567890;
    buf[1024]=a;
    buf[0]^=a;
}

#define ROT(x,y) ((x)=(x<<y)|(x>>(32-y)))

static void
dobuf(void)
{
    uint32_t a, b, c, d, *p;

    a=buf[1020]; b=buf[1021]; c=buf[1022]; d=buf[1023];

    p=buf;

    do
    {
	a*=9; b*=9;
	ROT(b,19); a^=p[0]; d+=c;
	b^=p[1]; a+=d; c=9*c+12345;
	ROT(d,23); c^=p[2]; b+=a;
	d^=p[3]; c+=b;
	p[0]=a; p[1]=b; p[2]=c; p[3]=d;

	a*=9; b*=9;
	ROT(b,19); a^=p[4]; d+=c;
	b^=p[5]; a+=d; c=9*c+12345;
	ROT(d,23); c^=p[6]; b+=a;
	d^=p[7]; c+=b;
	p[4]=a; p[5]=b; p[6]=c; p[7]=d;

	a*=9; b*=9;
	ROT(b,19); a^=p[8]; d+=c;
	b^=p[9]; a+=d; c=9*c+12345;
	ROT(d,23); c^=p[10]; b+=a;
	d^=p[11]; c+=b;
	p[8]=a; p[9]=b; p[10]=c; p[11]=d;

	a*=9; b*=9;
	ROT(b,19); a^=p[12]; d+=c;
	b^=p[13]; a+=d; c=9*c+12345;
	ROT(d,23); c^=p[14]; b+=a;
	d^=p[15]; c+=b;

	p+=16;
	p[-4]=a; p[-3]=b; p[-2]=c; p[-1]=d;
    } while (p<buf+1024);
}

static void
doseed(uint32_t seed)
{
    memset(buf, 0, sizeof(buf));
    buf[1025]=987654321;
    buf[0]=buf[1024]=seed;

    dobuf(); dobuf(); dobuf();
}

#undef ROT

static void
blat(int64_t s, uint32_t seed)
{
    doseed(seed);

    while (s)
    {
	size_t c;

	dobuffirst();
	dobuf();

	if ((uint64_t)s>4096) c=4096; else c=s;
	if (fwrite(buf, 1, c, stdout)!=c) crash("fwrite fails");

	if (s>0) s-=c;
    }
}

int
main(int argc, char **argv)
{
    double ds;
    int64_t s;
    unsigned long seed;

    if (argc>2) sscanf(argv[2], "%lu", &seed);
    else seed=time(0)+getpid();
    if (argc<2) crash("give a size arg in bytes, or 'inf'");
    if (sscanf(argv[1], "%lf", &ds)==1) s=(int64_t)ds;
    else
    {
	if (strcmp(argv[1],"inf")) crash("not a number");
	s= -1;
    }

    blat(s, seed);

    return 0;
}
