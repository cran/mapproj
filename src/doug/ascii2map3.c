#include <stdio.h>
#include <stdlib.h>

short getshort(void);
void error(char*);

int main()
{
	int i,j, n;
	int oi = 127, oj = 127;
	long loc = 0;
	while((i=getchar()) != EOF) {
		j = getchar();
		n = getshort();
		if(i!= oi||j!=oj) {
			printf("%d %d %ld\n",(char)i,(char)j,loc);
			oi = i;
			oj = j;
		}
		loc += 4;
		if(n > 0) {
			while(--n >= 0) {
				getshort();
				getshort();
				loc += 4;
			}
		} else {
			getshort();
			getshort();
			loc += 4;
			while(++n <= 0) {
				getchar();
				getchar();
				loc += 2;
			}
		}
	}
	return 0;
}

short getshort(void)
{
	int c = getchar();
	int d = getchar();
	if(c==EOF || d==EOF) 
		error("premature eof");
	return c | d<<8;
}

void error(char *s)
{
	fflush(stdout);
	fprintf(stderr,"ascii2map3: %s\n", s);
	exit(1);
}
