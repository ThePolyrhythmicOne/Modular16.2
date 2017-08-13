#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RODADA.H"
#include "DESENHA.H"
#include "TABULEIRO.H"

int main( void )
{
   char ordem[4] = { '\0', '\0', '\0', '\0' };
   short score[4] = { 0, 0, 0, 0 };
   int qtdjogadores = 5;
   char c = 0;
   Tabuleiro *tb = NULL;
   
   if ( TAB_criaTabuleiro( &tb ) != TAB_CondRetOK )
   {
      printf( "Erro ao criar o tabuleiro.\n" );
      exit(-1);
   } else {
      if ( TAB_inicializaTabuleiro( &tb ) != TAB_CondRetOK )
      {
         printf( "Erro ao inicializar o tabuleiro.\n" );
         exit(-1);
      } /* if */
      while( qtdjogadores <= 1 || qtdjogadores >= 5 )
      {
		 if ( c != '\n' )
		 {
            printf( ">> Quantos jogadores a jogar? \n" );
		 }
         scanf( "%c", &c );
		 qtdjogadores = c - '0';
      }
      DES_ObterOrdem( ordem, qtdjogadores );
      while ( ROD_RealizaRodada( tb, ordem, score, qtdjogadores ) != ROD_CondRetVitoria );
      TAB_DestroiTab( &tb );
   } /* if */
   
   return 0;
}
