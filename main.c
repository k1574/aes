#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <raw_aes.h>

static char *argv0;

/* Need no replace the array definition by
  by definition with indexes later, now I'm lazy. */
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
	"end",
	"bold",
	"underline",
	"reversed",
	"clr-scr",
	"clr-til-scr-end",
	"clr-til-scr-beg",
	"clr-ent-scr",
	"clr-cur-line",
	"clr-til-line-end",
	"clr-til-line-beg",
	"clr-ent-line",
	"make-cur-invisible",
	"make-cur-visible",
	"restore-screen",
	"save-screen",
	"enable-alt-buf",
	"disable-alt-buf",
	0
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
		printf("%d\t%s\n", aes_raw_esc_seqs[s-seq_names].narg, *s);
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

		if(aes_raw_esc_seqs[idx].narg == 1){
			if(i+1 < argc)
				printf(aes_raw_esc_seqs[idx].fmt, atoi(argv[++i]));
			else usage();
		} else if(aes_raw_esc_seqs[idx].narg==2) {
			if(i+2 < argc)
				printf(aes_raw_esc_seqs[idx].fmt, atoi(argv[++i]), atoi(argv[++i]));
			else usage() ;
		} else {
			printf(ESC "%s", aes_raw_esc_seqs[idx].fmt);
		}
	}
	
	return 0 ;
}
