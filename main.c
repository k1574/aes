#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ESC  "\033"
static char *argv0;
static char *seq_names[] = {
	"home",
	"to",
	"up",
	"down",
	"right",
	"left",
	"next",
	"prev",
	"col",
	"report",
	"save",
	"undo",
	"echo",
	"end",
	"bold",
	"underline",
	"reversed",
	"fg-black",
	"fg-red",
	"fg-green",
	"fg-yellow",
	"fg-blue",
	"fg-magenta",
	"fg-cyan",
	"fg-white",
	"fg-bright-black",
	"fg-brght-red",
	"fg-bright-green",
	"fg-bright-yellow",
	"fg-bright-blue",
	"fg-bright-magenta",
	"fg-bright-cyan",
	"fg-bright-white",
	"bg-black",
	"bg-red",
	"bg-green",
	"bg-yellow",
	"bg-blue",
	"bg-magenta",
	"bg-cyan",
	"bg-white",
	"bg-bright-black",
	"bg-brght-red",
	"bg-bright-green",
	"bg-bright-yellow",
	"bg-bright-blue",
	"bg-bright-magenta",
	"bg-bright-cyan",
	"bg-bright-white",
	"clr-scr",
	"clr-til-scr-end",
	"clr-til-scr-beg",
	"clr-ent-scr",
	"clr-cur-line",
	"clr-til-line-end",
	"clr-til-line-beg",
	"clr-ent-line",
	0
} ;

static char *seqs[] = {
	ESC "[H",
	ESC "[%sH",
	ESC "[%sA",
	ESC "[%sB",
	ESC "[%sC",
	ESC "[%sD",
	ESC "[%sE",
	ESC "[%sF",
	ESC "[%sG",
	ESC "[%sR",
	ESC "[s",
	ESC "[u",
	"%s",
	ESC "[0m",
	ESC "[1m",
	ESC "[4m",
	ESC "[7m",
	ESC "[30m",
	ESC "[31m",
	ESC "[32m",
	ESC "[33m",
	ESC "[34m",
	ESC "[35m",
	ESC "[36m",
	ESC "[37m",
	ESC "[90m",
	ESC "[91m",
	ESC "[92m",
	ESC "[93m",
	ESC "[94m",
	ESC "[95m",
	ESC "[96m",
	ESC "[97m",
	ESC "[40m",
	ESC "[41m",
	ESC "[42m",
	ESC "[43m",
	ESC "[44m",
	ESC "[45m",
	ESC "[46m",
	ESC "[47m",
	ESC "[100m",
	ESC "[101m",
	ESC "[102m",
	ESC "[103m",
	ESC "[104m",
	ESC "[105m",
	ESC "[106m",
	ESC "[107m",
	/* Clearing sequences. */
	ESC "[J",
	ESC "[0J",
	ESC "[1J",
	ESC "[2J",
	ESC "[K",
	ESC "[0K",
	ESC "[1K",
	ESC "[2K",
	0
} ;

static int argnum[] = {
	/* Cursor. */
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	/* Echo. */
	1,
	/* Decorative. */
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	/* Deleting. */
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
} ;

void
usage(void)
{
	fprintf(stderr, "usage: %s {<seqname1> [arg1] ... [seqnameN [argN]] | -l}\n", argv0);
	exit(1);
}

int
stridx(char *s, char *ss[])
{
	char **p = ss ;
	while(*p){
		if(!strcmp(s, *p))
			return p - &ss[0] ;
		++p;
	}
	return -1 ;
}

void
list(void)
{
	char **s = seq_names;
	while(*s){
		printf("%d\t%s\n", argnum[s-seq_names], *s);
		++s;
	}
}

int
main(int argc, char *argv[])
{
	int idx, i;
	argv0 = argv[0] ;
	if(argc < 2)
		usage();
	else if(!strcmp("-l", argv[1])){
		list();
		return 0 ;
	}
	
	for( i=1 ; i<argc ; ++i ){
		if( (idx = stridx(argv[i], seq_names)) < 0)
			usage();

		if(argnum[idx]){
			if(i+1<argc) printf(seqs[idx], argv[++i]);
			else usage();
		} else {
			printf("%s", seqs[idx]);
		}
	}
	
	return 0 ;
}
