/***************************************************************************
 *  $MCI Módulo de implementação: DES  Desenha
 *
 *  Arquivo gerado:              Desenha.c
 *  Letras identificadoras:      DES
 *
 *  Projeto: Ludo - INF1301
 *  Autores: pct, mr, gb
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data        Observações
 *      4.0     mr    10/dez/2016    Padronização do código
 *      3.0     mr,gb 06/dez/2016    Inspeção do código
 *      2.0     pct   03/dez/2016    Correção de bugs
 *      1.0     pct   01/dez/2016    Implementação inicial
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "TABULEIRO.H"
#include "TABAUXILIAR.H"
#define DESENHA_OWN
#include "DESENHA.H"
#undef  DESENHA_OWN

/* Cores para a API do Windows */
#define COLOR_RESET 15
#define COLOR_RED 12
#define COLOR_BLUE 11
#define COLOR_YELLOW 14
#define COLOR_GREEN 10

static void Desempata( short resultados[], int indices[], int qtdjogadores ); /* forward declaration */

/****************************************************/
/********** Funções privadas auxiliares *************/

/************* Função: DES &DesenhaDivisoria ******************/
static void DesenhaDivisoria( void )
{
   int i;
   printf("%c ", 254);
   for( i = 0; i < 29; i++ )
   {
      printf("%c ", 254);
   }
   printf("%c\n", 254);
} /* Fim DesenhaDivisoria */

/************* Função: DES &JogaDado ******************/
static void JogaDado( short *resultado )
{
   srand( (unsigned int) time(NULL) );
   *resultado = (rand()%6 + 1);
} /* Fim JogaDado */

/************* Função: DES &VerificaEmpate ******************/
static void VerificaEmpate( short resultados[], int qtdjogadores )
{
   /* Verifica se tem empate, caso haja ele pega os índices que obtiveram empate */
   /* e chama a função Desempata */
   int i, k = 0;
   short valor;
   int indices[4] = { 0, 0, 0, 0 };
   char Empate = 0; /* false */
   while ( k < qtdjogadores )
   {
      valor = resultados[k];
      for( i = 0; i < qtdjogadores; i++ )
      {
         if ( resultados[i] == valor && i != k )
         {
            indices[i] = 1; /* esse indice obteve empate */
            Empate = 1; /* true */
         }
      }
      k++;
   }
   if ( Empate >= 1 )
   {
      Desempata( resultados, indices, qtdjogadores );
   }
} /* Fim VerificaEmpate */

/************* Função: DES &Desempata ******************/
static void Desempata( short resultados[], int indices[], int qtdjogadores )
{
   int i;
   for( i = 0; i < qtdjogadores; i++ )
   {
      if( indices[i] == 1 )
      {
         printf("!! HOUVE EMPATE !!\n");
         switch( i )
         {
            case 0:
               printf("RED:");
               DES_PerguntaDado( &resultados[i] );
               break;
            case 1:
               printf("BLU:");
               DES_PerguntaDado( &resultados[i] );
               break;
            case 2:
               printf("YEL:");
               DES_PerguntaDado( &resultados[i] );
               break;
            case 3:
               printf("GRE:");
               DES_PerguntaDado( &resultados[i] );
               break;
         }
      }
   }
   VerificaEmpate( resultados, qtdjogadores );
} /* Fim Desempata */

/************* Função: DES &Busca ******************/
static int Busca( short vetor[], int tamanho, short valor )
{
   int i;
   for ( i = 0; i < tamanho; i++ )
   {
      if ( vetor[i] == valor )
      {
         return i;
      } /* if */
   } /* for */
   return -1;
} /* Fim Busca */

/************* Função: DES &PreencheOrdem ******************/
static void PreencheOrdem( char ordem[], short resultados[], int qtdjogadores )
{
   short i = 1, k = 3;
   int indices = 0;
   int ret;
   do {
	ret = Busca( resultados, 4, i );
      if ( ret > -1 )
      {
         indices++;
         switch( ret )
         {
            case 0:
               ordem[k] = 'R';
               break;
            case 1:
               ordem[k] = 'B';
               break;
            case 2:
               ordem[k] = 'Y';
               break;
            case 3:
               ordem[k] = 'G';
               break;
         } /* switch */
         k--;
      }
      i++;
   } while ( indices != qtdjogadores ); /* do */
} /* Fim PreencheOrdem */

/************************************************************/

/************************************************************/
/**************** Funções públicas do módulo ****************/

/************* Função: DES &DES_DesenhaPlacar ******************/
void DES_DesenhaPlacar( short ScoreRed, short ScoreGreen, short ScoreBlue, short ScoreYellow )
{
   int i;
   /* divisória de "-" */
   for( i = 0; i < 29; i++ )
   {
      printf( "%c ", '-' );
   }
   printf( "%c\n", '-' );
   printf( "!! PLACAR !! \n\n" );
   printf(" | RED : %d | BLU : %d | YEL : %d | GRE : %d |\n\n", ScoreRed, ScoreBlue, ScoreGreen, ScoreYellow );

} /* Fim DES_DesenhaPlacar */

/************* Função: DES &DES_LimpaPrompt ******************/
void DES_LimpaPrompt( void )
{
   system("cls");
} /* Fim DES_LimpaPrompt */

void DES_DesenhaAreaPecas( Tabuleiro *tab )
{
	int i;
	int vRed[4], vBlue[4], vGreen[4], vYellow[4];
	
	TAB_PreencheVetorPecas( tab, vRed, vBlue, vGreen, vYellow, 1 );
	printf(">>Pecas em Jogo\n");
	for ( i = 0; i < 4; i++ )
	{
		if ( i == 0 )
		{
			printf( "RED: | " );
			if ( vRed[i] == 0 )
			{
				printf( " B |  " );
			} else {
				if ( vRed[i] < 0 )
				{
				   printf( " %d |  ", vRed[i] + 1 );
				} else {
				printf( " %d |  ", vRed[i] );
				}
			} /* if */
			printf( "BLU: | " );
			if ( vBlue[i] == 0 )
			{
				printf( " B |  " );
			} else {
				if ( vBlue[i] < 0 )
				{
				   printf( " %d |", vBlue[i] + 1 );
				} else {
				printf( " %d |  ", vBlue[i] );
				}
			} /* if */
			printf( "GRE: | " );
			if ( vGreen[i] == 0 )
			{
				printf( " B |  " );
			} else {
				if ( vGreen[i] < 0 )
				{
				   printf( " %d |", vGreen[i] + 1 );
				} else {
				printf( " %d |", vGreen[i] );
				}
			} /* if */
			printf( "YEL: | " );
			if ( vYellow[i] == 0 )
			{
				printf( " B |  " );
			} else {
				if ( vYellow[i] < 0 )
				{
				   printf( " %d |  ", vYellow[i] + 1 );
				} else {
				printf( " %d |", vYellow[i] );
				}
			} /* if */
		} else {
			if ( vRed[i] == 0 )
			{
				printf( "        B |  " );
			} else {
				if ( vRed[i] < 0 )
				{
				   printf( "        %d |  ", vRed[i] + 1 );
				} else {
				   printf( "        %d |  ", vRed[i] );
				}
			} /* if */
			if ( vBlue[i] == 0 )
			{
				printf( "        B |  " );
			} else {
				if ( vBlue[i] < 0 )
				{
				   printf( "        %d |  ", vBlue[i] + 1 );
				} else {
				   printf( "        %d |  ", vBlue[i] );
				}
			} /* if */
			if ( vGreen[i] == 0 )
			{
				printf( "        B |  " );
			} else {
				if ( vGreen[i] < 0 )
				{
				   printf( "        %d |  ", vGreen[i] + 1 );
				} else {
				   printf( "        %d |  ", vGreen[i] );
				}
			} /* if */
			if ( vYellow[i] == 0 )
			{
				printf( "        B |  " );
			} else {
				if ( vYellow[i] < 0 )
				{
				   printf( "        %d |  ", vYellow[i] + 1 );
				} else {
				   printf( "        %d |  ", vYellow[i] );
				}
			} /* if */
		} /* if */
		printf( "\n" );
	} /* for */
}

/************* Função: DES &DES_PerguntaDado ******************/
void DES_PerguntaDado( short *resultado )
{
   char success = 0;
   int cmd;
   char c = 0;
   do {
	  if ( c != '\n' )
	  {
         printf( "Deseja jogar o dado?\n" );
         printf( "Digite 1 para continuar...\n" );
	  } /* if */
      scanf( "%c", &c );
	  cmd = c - '0';
      if( cmd == 1 )
      {
         JogaDado(resultado);
         printf("!! RESULTADO : %d !!\n", *resultado);
         success = 1;
      } else {
		  if ( c != '\n' )
		  {
             printf("!! %d Não é reconhecido. !!\n", cmd);
		  }
      }
   } while ( !success );
} /* Fim DES_PerguntaDado */

/************* Função: DES &DES_ObterOrdem ******************/
void DES_ObterOrdem( char ordem[], int qtdjogadores )
{
   int i;
   short resultados[4] = { -1, -2, -3, -4 };
   /* Começa pelo sentido horário a perguntar se deseja jogar o dado */
   DES_LimpaPrompt();
   printf("!! Definindo a ordem de jogadores !!\n");
   for ( i = 0; i < qtdjogadores; i++ )
   {
      if ( i == 0 )
      {
         printf("RED:");
      } else if ( i == 1 )
      {
         printf("BLU:");
      } else if ( i == 2 )
      {
         printf("YEL:");
      } else {
         printf("GRE:");
      } /* if */
      Sleep( 100 );
      DES_PerguntaDado( &resultados[i] );
   } /* for */
   VerificaEmpate( resultados, qtdjogadores );
   PreencheOrdem( ordem, resultados, qtdjogadores );
} /* Fim DES_ObterOrdem */

/************* Função: DES &DES_DesenhaOrdem ******************/
void DES_DesenhaOrdem( char ordem[] )
{
   int i;
   printf( "ORDEM -> " );
   for ( i = 0; i < 4; i++ )
   {
      printf( "| %c | ", ordem[i] );
   }
   printf("\n");
} /* Fim DES_DesenhaOrdem */

/************* Função: DES &DES_DesenhaTabuleiro ******************/
void DES_DesenhaTabuleiro( Tabuleiro *tb )
{
   HANDLE prompt;
   int i, p = 0;
   /* variaveis para desenho do caminho neutro */
   int colesquerda, colmeio, coldireita;
   int linsuperior, linmeio, lininferior;
   int Neutro[52];
   /* variaveis para desenho dos caminhos finais */
   int FinalRed[6], FinalGreen[6], FinalBlue[6], FinalYellow[6];
   /* variaveis para desenho das Peças de cada jogador */
   int PecasRed[4], PecasGreen[4], PecasBlue[4], PecasYellow[4];

   prompt = GetStdHandle(STD_OUTPUT_HANDLE);

   /* Preenche os vetores para desenho */
   TAB_PreencheVetorNeutro( tb, Neutro );
   TAB_PreencheVetorPecas( tb, PecasRed, PecasBlue, PecasGreen, PecasYellow, 0 );
   TAB_PreencheVetorFinal( tb, FinalRed, FinalBlue, FinalGreen, FinalYellow );

   SetConsoleTextAttribute( prompt, COLOR_RESET );

   DesenhaDivisoria();

   /* parte superior */
   colesquerda = 48;
   colmeio = 49;
   coldireita = 50;
   for( i = 0; i < 6; i++ )
   {
      if ( i == 1 )
      {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c | %d ", 
               254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, Neutro[colesquerda]);
         SetConsoleTextAttribute( prompt, COLOR_RED );
         printf( "|*%d*|*%d*| ",FinalRed[i], Neutro[coldireita] );
         SetConsoleTextAttribute( prompt, COLOR_RESET );
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c\n", 254, 254, 254, 254, 254, 254, 254, 
               254, 254, 254, 254, 254 );
      } else if ( i > 1 )
      {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c | %d ", 
               254, 254, 254, 254, 254, 254, PecasGreen[p], 254, 254, 254, 254, 254, Neutro[colesquerda] );
         SetConsoleTextAttribute( prompt, COLOR_RED );
         printf( "|*%d*|", FinalRed[i] );
         SetConsoleTextAttribute( prompt, COLOR_RESET );
         printf( " %d | %c %c %c %c %c %c %c %c %c %c %c %c\n", Neutro[coldireita], 254, 254, 254, 254, 254, 254, 254, PecasRed[p], 254, 254, 
               254, 254 );
         p++;
      } else {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c | %d | %d | %d | %c %c %c %c %c %c %c %c %c %c %c %c\n", 
               254, 'G', 'R' , 'E', 254, 254, 254, 254, 254, 254, 254, 254, Neutro[colesquerda], Neutro[colmeio], 
               Neutro[coldireita], 254, 'R', 'E', 'D', 254, 254, 254, 254, 254, 254, 254, 254 );
      } /* if */
      colesquerda--;
      coldireita++;
      if ( coldireita == 52 )
      {
         coldireita = 0;
      } /* if */
   } /* for */

   /* parte do meio */
   linsuperior = 37;
   linmeio = 36;
   lininferior = 35;

   /* linha superior */
   printf( "%d ", Neutro[linsuperior] );
   SetConsoleTextAttribute( prompt, COLOR_GREEN );
   printf( "|*%d*|", Neutro[linsuperior+1] );
   SetConsoleTextAttribute( prompt, COLOR_RESET );
   printf( " %d | %d | %d | %d | \\", Neutro[linsuperior+2],
         Neutro[linsuperior+3], Neutro[linsuperior+4], Neutro[linsuperior+5] );
   linsuperior += 5;
   printf( "  / | %d | %d | %d | %d | %d | %d\n", Neutro[linsuperior-38],  Neutro[(linsuperior+1)-38], 
         Neutro[(linsuperior+2)-38], Neutro[(linsuperior+3)-38], Neutro[(linsuperior+4)-38], 
         Neutro[(linsuperior+5)-38] );

   /* linha meio */
   printf( "%d ", Neutro[linmeio] );
   SetConsoleTextAttribute( prompt, COLOR_GREEN );
   printf( "|*%d*|*%d*|*%d*|*%d*|*%d*", FinalGreen[1], FinalGreen[2], FinalGreen[3], FinalGreen[4], FinalGreen[5] );
   SetConsoleTextAttribute( prompt, COLOR_BLUE );
   printf( "              *%d*|*%d*|*%d*|*%d*|*%d*| ", FinalBlue[5], FinalBlue[4], FinalBlue[3], FinalBlue[2], FinalBlue[1] );
   SetConsoleTextAttribute( prompt, COLOR_RESET );
   printf( "%d\n", Neutro[linmeio-26] );

   /* linha inferior */
   printf( "%d | %d | %d | %d | %d | %d | /  ", Neutro[lininferior], Neutro[lininferior-1], Neutro[lininferior-2],
         Neutro[lininferior-3], Neutro[lininferior-4], Neutro[lininferior-5] );
   lininferior -= 5;
   printf( "\\ | %d | %d | %d | %d ", Neutro[lininferior-14], Neutro[(lininferior-1)-14], 
         Neutro[(lininferior-2)-14], Neutro[(lininferior-3)-14] );
   SetConsoleTextAttribute( prompt, COLOR_BLUE );
   printf( "|*%d*|", Neutro[(lininferior-4)-14] );
   SetConsoleTextAttribute( prompt, COLOR_RESET );
   printf( " %d\n", Neutro[(lininferior-5)-14] );

   /* parte inferior */
   colesquerda = 29;
   colmeio = 23;
   coldireita = 17;
   p--;
   for( i = 0; i < 6; i++ )
   {
      if ( i == 4 )
      {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c ", 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254 );
         SetConsoleTextAttribute( prompt, COLOR_YELLOW );
         printf("|*%d*|*%d*|",  Neutro[colesquerda], FinalYellow[i-3] );
         SetConsoleTextAttribute( prompt, COLOR_RESET );
         printf( " %d | %c %c %c %c %c %c %c %c %c %c %c %c\n", Neutro[coldireita], 254, 254, 254, 254, 254, 254, 
               254, 254, 254, 254, 254, 254 );
      } else if ( i < 5 )
      {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c | %d ", 
               254, 254, 254, 254, 254, 254, PecasYellow[p], 254, 254, 254, 254, 254, Neutro[colesquerda] );
         SetConsoleTextAttribute( prompt, COLOR_YELLOW );
         printf( "|*%d*|", FinalYellow[5-i] );
         SetConsoleTextAttribute( prompt, COLOR_RESET );
         printf( " %d | %c %c %c %c %c %c %c %c %c %c %c %c\n", Neutro[coldireita], 254, 254, 254, 254, 254, 254, 254, PecasBlue[p], 254,
               254, 254, 254 );
         p--;
      } else {
         printf( "%c %c %c %c %c %c %c %c %c %c %c %c | %d | %d | %d | %c %c %c %c %c %c %c %c %c %c %c %c\n",
               254, 'Y', 'E', 'L', 254, 254, 254, 254, 254, 254, 254, 254, Neutro[colesquerda], Neutro[colmeio],
               Neutro[coldireita], 254, 'B', 'L', 'U', 254, 254, 254, 254, 254, 254, 254, 254 );
      } /* if */
      coldireita++;
      colesquerda--;
   } /* for */
   DesenhaDivisoria();
} /* Fim DES_DesenhaTabuleiro */
