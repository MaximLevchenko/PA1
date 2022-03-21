#include <stdio.h>
void foo ( int a, int b, int * c )
 {
   *c = a + b;
 }

int bar ( int x, int y )
 {
   static int * z;
   foo ( x, y, z );
   return *z;
 }

int main ( void )
 {
   printf ( "%d", bar ( 10, 19 ) );
   return 0;
 }