#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define s(_)waddstr(W,_)
#define c(_)waddch(W,_)
#define f(f,_)wprintw(W,f,_)
#define n c('\n')
#define r(_,n)for(int _=0;_<n;++_)
#define t(_)G+y*((x+S)%(S+1)+_*x)+(S+1-y)*i

WINDOW*W;char*M="\0"  ;int S,R,C,N,E,*L,*T  ,F[128],    *G=F;void _(){c('+');r(i,8*S-1
){c('-');}c('+');n;}  void l(){c('|');r(i,  S){r(j,8    ){c(32);  }c('\b');c('|');}n;}
void g(){_();r(i,S){  l();s("| ");r(j,S){   if(!*G){    s("    "  "  | ");}else if(*G>=
1024){f(" %2dk  | ",  *G/1024);}else{f(     "%4d  | "   ,*G);}++  G;}n;l();if(i<S-1){c
            ('|'  );  r(j,S){r    (j,8){c(  '-');}c(    '\b');if  (j<S-1){    c('+');}
            }c('|');  n;}}_();    G-=S*S;}  int m(int   x,int y,  int d){C    =0;r(i,S
            ){E=0;L=  0;r(j,S)    {T=t(j);  if(*T){if   (L&& *T== *L){if(d    ){*L*=2;
            *T=0;}L=  0;C=1;}     else{L=   t(E);if(    d){*L=*T  ;}++E;}}    }for(;E<
S;++E){T=t(E);C|=*T;  if(d){*T    =0;}}}    return!C;}void p(){E=0;r(i,S*S){if(!G[i]){
++E;}}if(E==0){return ;}N=rand    ()%E;r(i  ,S*S){if(!G[i]&&--E   ==N){G[i]=rand()%8?2
:4;}}}int main(int    argc,char   **argv){  srand(time(0));initscr();cbreak();noecho();
curs_set(0);getmaxyx  (stdscr,    R,C);S=   argc>1?(*argv[1]-'0'  ):4;if(S<=1||S>8){M=
"\1Invalid size giv"  "en.\n";    goto q;}  W=newwin(0,0,(R-4*S)  /2,(C-8*S)/2);if(!W)
{M="\1T"              "ermina"    "l too "              "small."  "\n";goto   q;}p();p
();while              (1){wclear  (W);g();              s("  h,"  "j,k,l:"    " move "
"      "              "  q: q"    "uit");               wrefresh  (W);switch  (wgetch(
W)){case              'q':goto    q;case'h'             :m(1,1,1  );goto e;   case'j':
m(-1,S,1);goto e;case 'k':m(1,S,1);goto e;              case'l':  m(-1,1,1);goto e;e:if
(C){p();}if(m(1,1,0)  &m(-1,1,0)&m(1,S,0)&              m(-1,S,0  )){M="\0Game over.\n"
;goto q;}usleep(2048  *8);break;}}q:if(W){              delwin(W  );}endwin();fputs(M+
1,stderr);return*M;} /*2^11*/
