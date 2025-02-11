#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "decrypt_text.h"


static unsigned long long int modpow(unsigned long long int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}

int inverse(int a, int mod)     /*find inverse of number a in % mod*/
{                               /*inverse of a = i*/
        int aprev, iprev, i = 1, atemp, itemp;

        aprev = mod, iprev = mod;
        while (a != 1)
        {
                atemp = a;
                itemp = i;
                a = aprev - aprev / atemp * a;
                i = iprev - aprev / atemp * i;
                aprev = atemp;
                iprev = itemp;
                while (i < 0)
                        i += mod;
        }

        return i;
}

/*int main ()
{
        int d, n, p, q, h, m, qInv, m1m2;
        unsigned long long int c, dP, dQ, m1, m2;
        FILE *inp;

        inp = fopen("private.txt", "r");
        fscanf(inp, "%d %d", &n, &d);
        fclose(inp);

        inp = fopen("pq.txt", "r");
        fscanf(inp, "%d %d", &p, &q);
        fclose(inp);

	printf("message: ");
	inp = fopen("ciphertext.txt", "r");

	while (fscanf(inp, "%llu", &c) != EOF)
	{
        	dP = d % (p - 1);
        	dQ = d % (q - 1);
        	qInv = inverse(q,p);
        	m1 = modpow(c,dP,p);
        	m2 = modpow(c,dQ,q);
        	m1m2 = m1 - m2;
        	if (m1m2 < 0)
                	m1m2 += p;
       		h = (qInv * m1m2) % p;
        	m = m2 + h * q;
		printf("%c", m);
	}
	fclose(inp);
	printf("\n");
        /*printf("dP: %u\n", dP);
        printf("dQ: %u\n", dQ);
        printf("qInv: %u\n", qInv);
        printf("m1: %u\n", m1);
        printf("m2: %u\n", m2);
        printf("h: %u\n", h);

        return 0;
}*/



char *  decrypt_text(char * text, int n, int d, int p, int q) {
  int h, m, qInv, m1m2;
  unsigned long long int c, dP, dQ, m1, m2;
  char * buf = malloc(sizeof(text));
  int len = 0;
  int sc = 0;
  //char * t = text - sizeof(unsigned long long int);

          //sc = sscanf((t=t+sizeof(unsigned long long int)), "%llu\n", &c);



          char * token = strtok(text, "\n");
          do {


             sc = sscanf(token, "%llu", &c);
             //printf("%llu, ", c);

             dP = d % (p - 1);
             dQ = d % (q - 1);
             qInv = inverse(q,p);
             m1 = modpow(c,dP,p);
             m2 = modpow(c,dQ,q);
             m1m2 = m1 - m2;
             if (m1m2 < 0)
                     m1m2 += p;
             h = (qInv * m1m2) % p;
             m = m2 + h * q;

            len += sprintf(buf+len,"%c", m);

          } while (token = strtok(NULL, "\n"));


  buf[len] = '\0';
  int newLen = strlen(buf);
  char * ret = malloc(sizeof(char) * (newLen+1));
  strcpy(ret, buf);
  free(buf);
  return ret;


}
