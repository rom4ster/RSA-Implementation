#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "encrypt_text.h"




static unsigned long long int modpow(int base, int power, int mod)
{
        int i;
        unsigned long long int result = 1;
        for (i = 0; i < power; i++)
        {
                result = (result * base) % mod;
        }
        return result;
}

/*int main (int argc, char *argv[])
{
        int m, n, e;
        unsigned long long int c;

        FILE *inp = fopen("public.txt", "r");
        fscanf(inp, "%d %d", &n, &e);
        fclose(inp);

	printf("ciphertext c = ");

	int i;
	FILE *outp = fopen("ciphertext.txt", "w");

	for (i = 0; argv[1][i]!= '\0'; i++)
	{
        	c = modpow(argv[1][i],e,n);
		printf("%llu ", c);
		fprintf(outp, "%llu\n", c);
	}

        printf("\n");
        fclose(outp);

        return 0;
}*/



char * encrypt_text(char * text, int n , int e) {


unsigned long long int c;

  char * buf = malloc(strlen(text) * (sizeof(unsigned long long int) + 1));
  int len = 0;
  for (int i = 0; text[i] != '\0'; i++)
	{
        	c = modpow(text[i],e,n);
		len += sprintf(buf + len, "%llu\n", c);
	}

  return buf;

}
