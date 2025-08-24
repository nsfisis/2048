#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#define f(f,_)printf(f,_)
#define s(_)f("%s",_)
#define n s("\r\n")
#define r(_,n)for(int _=0;_<n;++_)
#define t(_)(G+y*((x+S)%(S+1)+_*x)+(S+1-y)*i)

int S,N,E,C,*L,*T,F[  128],*G= F,R ;struct  termios O   ;void x(  ){if(!R++)tcsetattr(
0,2,&O),s("\e[?25h\e" "[?1049l");}void _()  {s("+");    r(i,8*S-  1)s("-");s("+");n;}
void l(){s("|");r(i,  S){r(j,7)s(" ");s("|" );}n;}int   m(int x,  int y,int d){C=0;r(i
,S){E=0;L=0;r(j,S)if  (*(T=t(j)))if(L&&*T   ==*L){if    (d){*L*=  2;T=0;}L=0;C=1;}else
            {L=t(E);  if(d)*L=    *T;++E;}  for(;E<S    ;++E){T=  t(E);C|=    *T;if(d)
            *T=0; }}  return!C    ;}void p  (){ E =0    ;r( i,S*  S)if (!G    [i])++E;
            if(E==0)  return;N    =rand()%  E;r(i,S*    S)if(!G[  i]&&--E==   N)G[i]=
            rand()%8  ?2:4;}int   main(int  argc,char   **argv){  srand(time(0));atexit
(x); s("\e[?1049h");  tcgetattr   (0, &O);  struct termios o=O;o  .c_iflag&=-1331;o.
c_oflag&=-2;o.c_cflag |=48;o.     c_lflag&= -32780;o.c_cc[6]=0;o  .c_cc[5]=1;tcsetattr
(0,2,&o);s("\e[?25l"  );S=argc>   1?(*argv  [1]-48):4;if(S<2||S>  8){fputs("invalid b"
"oard size\n",stderr  );return    1;}p();p  ();for(;;){s("\e[2"   "J\e[H");_();r(i,S){
l();s("| "            );r(j,S)    {if(!*G)              s("    "  "  | ");else if(*G>=
1024)f(" "            "%2dk  "    "| ",*G/              1024);else f("%4d  | ",*G);++G
;}n;l();              if(i<S-1    ){s("|")              ;r(j,S){  r(j,7)s(    "-");if(
j<S-1)s(              "+");}s(    "|");n;}              }_();G-=  S*S;s("  "  "h,j,k,"
"l: move");r(i,9)s(" ");s("q: quit");fflush             (stdout)  ;char k;while(read(0
,&k,1)!=1);switch(k)  {case'q':goto q;case              'h':m(1,  1,1);goto e;case'j':
m(-1,S,1);goto e;case 'k':m(1,S,1);goto e;              case'l':  m(-1,1,1);goto e;e:if
(C)p();if(m(1,1,0)&m  (-1,1,0)&m(1,S,0)&m(              -1,S,0))  goto q;usleep(2048*8
);break;}}q:x();s("\e[2J\e[H");}/* 2048 in 2 kb by nsfisis */
