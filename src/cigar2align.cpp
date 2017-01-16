#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char** argv)
    {
    int i;
    for(i=1;i+1< argc;i+=2)
        {
        char* seq=argv[i];
        size_t pos=0UL;
        char* c=argv[i+1];
        while(*c!=0)
            {
            char* p2;
            if(!isdigit(*c))
                {
                fprintf(stderr,"bad cigar string: %s\n",argv[i+1]);
                return EXIT_FAILURE;
                }
            int n=strtol(c,&p2,10);
            if(n<=0)
                {
                fprintf(stderr,"bad cigar string: %s\n",argv[i+1]);
                return EXIT_FAILURE;
                }
            switch(*p2)
                {
                case 'M':
                    {
                    while(n>0)
                        {
                        fputc(seq[pos++],stdout);
                        --n;
                        }
                    break;
                    }
                case 'D':
                    {
                    while(n>0)
                        {
                        fputc('-',stdout);
                        --n;
                        }
                    break;
                    }
                case 'I':
                case 'P':
                    {
                    /* ignore */
                    break;
                    }
              default:
                {
                fprintf(stderr,"unsupported operator %c\n",*p2);
                return EXIT_FAILURE;
                }
                }
            c=p2+1;
            }
        fputc('\n',stdout);
        }
    return EXIT_SUCCESS;
    }