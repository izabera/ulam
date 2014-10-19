#define gsize 1000
#define m 10000
#define nsize 10000
#define nmax (2*nsize)  \

#include <stdio.h>
unsigned int ubit[nsize + 1], vbit[nsize + 1];
char table[256];
int count[gsize], example[gsize];

int main () {
	register unsigned int j, jj, k, kk, kq, kr, del, c, n, u, prevu, gap;

	for ( j = 2 ; j < 256 ; j <<= 1 ) table[j] = 1 + table[j >> 1];

	gap = 1;
	count[1] = 1;
	example[1] = 2;
	ubit[0] = 0x6;
	kr = n = prevu = 2;
	kq = 0;
	kk = 4;

	while ( 1 ) {

		for( j = c = 0, jj = j + kq ; j < kq ; j ++ , jj ++ ) {
			if ( jj >= nsize ) goto update_done;
			del = ( ubit[j] << kr ) + c;
			c = ( ubit[j] >> ( 31 - kr ) ) >> 1;

			u = ( ubit[jj] ^ del ) & ~ vbit[jj];
			vbit[jj] |= ubit[jj] & del;
			ubit[jj] = u;

		}
		if ( jj >= nsize ) goto update_done;
		u = ubit[kq] & ( kk - 1 );
		del = ( u << kr ) + c;
		c = ( u >> ( 31 - kr ) ) >> 1;

		u = ( ubit[jj] ^ del ) & ~ vbit[jj];
		vbit[jj] |= ubit[jj] & del;
		ubit[jj] = u;

		if ( c != 0 ) {
			jj ++;
			del = c;

			u = ( ubit[jj] ^ del) & ~ vbit[jj];
			vbit[jj] |= ubit[jj] & del;
			ubit[jj] = u;

		}
update_done:

		u = ubit[kq] & - ( kk + kk );
		while ( ! u ) {
			if ( ++ kq >= nsize ) goto done;
			u = ubit[kq];
		}
		kk = u & - u;
		if ( kk & 0xffff0000 ) {
			kr = 16;
			u = kk >> 16 ;
		}
		else {
			kr = 0;
			u = kk;
		}
		if ( u & 0xff00 ) {
			kr += 8;
			u >>= 8;
		}
		if ( u & 0xf0) {
			kr += 4;
			u >>= 4;
		}
		kr += table[u];
    		n ++;

		k = kr + ( kq << 5 );
		del = k - prevu;
		count[del] ++;
		example[del] = k;
		if ( del > gap) {
			if ( del >= gsize ) {
				fprintf ( stderr, "Unexpectedly large gap (%d)! Recompile me...\n", del );
				return 1;
			}
			gap = del;
			printf ( "New gap %d: U_%d=%d, U_%d=%d\n", gap, n - 1, prevu, n, k);
			fflush ( stdout );
		}
		prevu = k;
		if ( ( n % m ) == 0 ) {
			printf ( "U_%d=%d is about %.5g*%d\n", n, k, ( (double) k ) / n, n );
			fflush ( stdout );
		}
	}

done:

	for ( j = 1 ; j <= gap ; j ++ )
		if ( count[j] )
			printf ("gap %d occurred %d time%s, last was %d\n", j, count[j], count[j] == 1 ? "" : "s" , example[j] );

	printf ("There are %d Ulam numbers less than %d.\n", n, nmax );

	return 0;
}

