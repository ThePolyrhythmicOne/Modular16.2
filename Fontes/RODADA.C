/***************************************************************************
 *  $MCI Módulo de implementação: ROD  Rodada
 *
 *  Arquivo gerado:              RODADA.C
 *  Letras identificadoras:      ROD
 *
 *  Projeto: Ludo - INF1301
 *  Autores: pct, mr, gb
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data       Observações
 *      5.0  mr,pct,gb 19/dez/2016  Finalizações.
 *      4.0   mr,pct  10/dez/2016   Inspeção de código
 *      3.0   pct     05/dez/2016   Correções de bugs
 *      2.0   mr      23/nov/2016   Implementação da assertiva de recuperação por avanço
 *      1.0   pct     11/nov/2016   Padronização do código conforme aula
 *
 ***************************************************************************/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LISTA.H"
#include "LCIRCULAR.H"
#define  RODADA_OWN
#include "RODADA.H"
#undef   RODADA_OWN
#include "TABULEIRO.H"
#include "PECA.H"
#include "DESENHA.H"

/****************************************************/
/********** Funções privadas auxiliares *************/

/************* Função: ROD &CaminhoFinal ******************/
static LIS_tppLista CaminhoFinal( Tabuleiro* tb, char cor )
{
   /* Retorna referência para Lista de Peças da cor */
   void *ptr;
   LIS_IrInicioLista( tb->tblr );
   switch( cor )
   {
      case 'R':
         LIS_AvancarElementoCorrente( tb->tblr, 4 );
         break;
      case 'B':
         LIS_AvancarElementoCorrente( tb->tblr, 6 );
         break;
      case 'G':
         LIS_AvancarElementoCorrente( tb->tblr, 5 );
         break;
      case 'Y':
         LIS_AvancarElementoCorrente( tb->tblr, 7 );
      default:
         return NULL; /* erro */
   } /* switch */
   LIS_ObterValor( tb->tblr, &ptr );
   return ( LIS_tppLista ) ptr;
} /* Fim CaminhoFinal */

/************* Função: ROD &ListaPeca ******************/
static LCircular* ListaPeca( Tabuleiro* tb, char cor )
{
   /* Retorna referência para Lista de Peças da cor */
   void *ptr;
   LIS_IrInicioLista( tb->tblr );
   switch( cor )
   {
      case 'R':
         LIS_AvancarElementoCorrente( tb->tblr, 0 );
         break;
      case 'B':
         LIS_AvancarElementoCorrente( tb->tblr, 1 );
         break;
      case 'G':
         LIS_AvancarElementoCorrente( tb->tblr, 3 );
         break;
      case 'Y':
         LIS_AvancarElementoCorrente( tb->tblr, 2 );
         break;
      default:
         return NULL; /* erro */
   } /* switch */
   LIS_ObterValor( tb->tblr, &ptr );
   return ( LCircular * ) ptr;
} /* Fim ListaPeca */

/************* Função: ROD &CaminhoNeutro ******************/
static LCircular* CaminhoNeutro( Tabuleiro* tb )
{
   /* Retorna referência para o Caminho Neutro */
   void *ptr;
   LIS_IrInicioLista( tb->tblr );
   LIS_AvancarElementoCorrente( tb->tblr, 8 );
   LIS_ObterValor( tb->tblr, &ptr );
   return ( LCircular * ) ptr;
} /* Fim CaminhoNeutro */

/************* Função: ROD &CorrigeOffset ******************/
static void CorrigeOffset( LCircular* neutro, Peca* p )
{
   /* Corrige o Offset do nó corrente no caminho neutro */
   /* Aponta nó corrente para casa da Peça p */
   int offset;
   void *ptr;
   Casa *auxiliar;

   LCI_ObtemCorrente( neutro, &ptr );
   auxiliar = ( Casa * ) ptr;
   offset = auxiliar->casa - p->casa; 
   if( offset > 0 )
   {
      while( offset )
      {
         LCI_TrocarPeloAnterior( neutro );
         offset--;
      } /* while */
   } else {
      while( offset )
      {
         LCI_TrocarPeloProximo( neutro );
         offset++;
      } /* while */
   } /* if */
} /* Fim CorrigeOffset */

/************* Função: ROD &VerificaCasaInicial ******************/
static int VerificaCasaInicial( LCircular* pecas, char cor )
{
   int i;
   void *ptr;
   Peca *aux;

   for ( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( pecas, &ptr );
      aux = ( Peca * ) ptr;
      if ( cor == 'R' && aux->casa == 1 )
      {
         return 1;
      } /* if */
      if ( cor == 'G' && aux->casa == 40 )
      {
         return 1;
      } /* if */
      if ( cor == 'B' && aux->casa == 14 )
      {
         return 1;
      } /* if */
      if ( cor == 'Y' && aux->casa == 27 )
      {
         return 1;
      } /* if */
      LCI_TrocarPeloProximo( pecas );
   } /* for */
   return 0;
} /* Fim VerificaCasaInicial */

/************* Função: ROD &VerificaJogada ******************/
static ROD_CondRet VerificaJogada( Tabuleiro *tb, Peca* p, short dado, char cor )
{
   void *ptr;
   Casa *alugada;

   if ( tb == NULL )
   {
      return ROD_CondRetErro;
   } /* if */

   /* peça está no caminho final? */
   if ( p->casa < 0 )
   {
      if ( ( ( p->casa ) * ( -1 ) ) + dado > 7 )
      {
         return ROD_CondRetJogadaInvalida;
      } else {
         return ROD_CondRetJogadaValida;
      } /* if */
   } else { /* senão verifica se está na base */
      if ( dado == 1 || dado == 6 )
      {
         if ( p->casa == 0 )
         {
            if ( cor == 'R' )
            {
               if ( VerificaCasaInicial( ListaPeca( tb, 'R' ), 'R' ) )
               {
                  return ROD_CondRetJogadaInvalida;
               } /* if */
               return ROD_CondRetJogadaValida;
            } else if ( cor == 'G' )
            {
               if ( VerificaCasaInicial( ListaPeca( tb, 'G' ), 'G' ) )
               {
                  return ROD_CondRetJogadaInvalida;
               } /* if */
               return ROD_CondRetJogadaValida;
            } else if ( cor == 'B' )
            {
               if ( VerificaCasaInicial( ListaPeca( tb, 'B' ), 'B' ) )
               {
                  return ROD_CondRetJogadaInvalida;
               } /* if */
               return ROD_CondRetJogadaValida;
            } else {
               if ( VerificaCasaInicial( ListaPeca( tb, 'Y' ), 'Y' ) )
               {
                  return ROD_CondRetJogadaInvalida;
               } /* if */
               return ROD_CondRetJogadaValida;
            } /* if */
         } /* if */
      } /* if */
      if ( p->casa == 0 )
      {
         return ROD_CondRetJogadaInvalida;
      } /* if */
      /* dado não é 1 ou 6, ou não é uma peça na base */
      CorrigeOffset( CaminhoNeutro( tb ), p );
      while ( dado )
      {
         LCI_TrocarPeloProximo( CaminhoNeutro( tb ) );
         dado--;
      } /* while */
      LCI_ObtemCorrente( CaminhoNeutro( tb ), &ptr );
      alugada = ( Casa * ) ptr;
      /* peça pode capturar peça ocupando casa? */
      if ( alugada->p != NULL )
      {
         if ( alugada->p->cor == cor )
         {
            return ROD_CondRetJogadaInvalida;
         } /* if */
      }
      return ROD_CondRetJogadaValida;
   } /* if */

} /* Fim VerificaJogada */

/************* Função: ROD &PoeEmJogo Auxiliar ******************/
static ROD_CondRet ROD_PEJAuxiliar( Tabuleiro* tb, Casa* alugada, Peca* aux, short num, short CasaInicialNum )
{
   void *ptr;

   /* enquanto offset da casa alugada ate casa inicial */
   while ( num )
   {
      if ( alugada->casa < CasaInicialNum )
      {
         if ( LCI_TrocarPeloProximo( CaminhoNeutro( tb ) ) != LCI_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         num++;
      } else {
         if ( LCI_TrocarPeloAnterior( CaminhoNeutro( tb ) ) != LCI_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         num--;
      } /* if */
   } /* while */

   if ( LCI_ObtemCorrente( CaminhoNeutro( tb ), &ptr ) != LCI_CondRetOK )
   {
      return ROD_CondRetPMoveErro;
   } /* if */
   /* move peça para casa */
   alugada = ( Casa * ) ptr;
   if ( alugada->p != NULL )
   {
      alugada->p->casa = 0; /* volta para a base */
   }
   alugada->p = aux;
   alugada->p->casa = alugada->casa;

   return ROD_CondRetOK;
} /* Fim PEJAuxiliar */

/************* Função: ROD &MoveCaminhoNeutroAuxiliar ******************/
static ROD_CondRet ROD_MoveCaminhoNeutroAuxiliar( Tabuleiro *tb, Casa *cs, short dado )
{
   Casa *aux, *alugada, *LISalugada;
   void *ptr;
   char cor = 0;

   /* Move corrente para cs, necessário para algoritmo funcionar corretamente */
   //if ( LCI_VerificaLista( CaminhoNeutro( tb ) ) != LCI_CondRetOK )
   //{
      //LCI_RecuperaLista( CaminhoNeutro( tb ) );
   //}
   CorrigeOffset( CaminhoNeutro( tb ), cs->p );
   LCI_ObtemCorrente( CaminhoNeutro( tb ), &ptr );
   aux = ( Casa * ) ptr;
   while ( dado )
   {
      LCI_TrocarPeloProximo( CaminhoNeutro( tb ) );
      dado--;
   } /* while */
   if ( LCI_ObtemCorrente( CaminhoNeutro( tb ), &ptr ) != LCI_CondRetOK )
   {
      return ROD_CondRetPMoveErro;
   } /* if */
   alugada = ( Casa * ) ptr;
   switch ( alugada->casa )
   {
      case 52:
         cor = 'R';
         break;
      case 39:
         cor = 'G';
         break;
      case 13:
         cor = 'B';
         break;
      case 26:
         cor = 'Y';
         break;
      default:
         break;
   } /* switch */
   /* verifica se temos alguma peça na primeira casa da ListaFinal */
   /* Se sim, então temos que remove-la para base */
   if ( alugada->p != NULL &&  ( alugada->casa == 52 || alugada->casa == 39 || alugada->casa == 13 || alugada->casa == 26 ) )
   {
      alugada->p->casa = 0; /* retorna peça pra base */
      alugada->p = aux->p;
      if ( LIS_IrInicioLista( CaminhoFinal( tb, cor ) ) != LIS_CondRetOK )
      {
         return ROD_CondRetPMoveErro;
      } /* if */
      if ( LIS_ObterValor( CaminhoFinal( tb, cor ), &ptr ) != LIS_CondRetOK )
      {
         return ROD_CondRetPMoveErro;
      } /* if */
      LISalugada = ( Casa * ) ptr;
      LISalugada->p = aux->p;
      aux->p->casa = LISalugada->casa;
      aux->p = NULL;
   } else {
      if ( alugada->p != NULL ) 
      {
         alugada->p->casa = 0;
      }
      alugada->p = aux->p;
      aux->p->casa = alugada->casa;
      aux->p = NULL;
   } /* if */ 
   return ROD_CondRetOK;
} /* Fim MoveCaminhoNeutroAuxiliar */

/************* Função: ROD &Bota uma peca em jogo ******************/
static ROD_CondRet ROD_PoeEmJogo( Tabuleiro** tb, char cor )
{
   Peca *aux;
   Casa *alugada;
   void *ptr;
   int i;
   short casainicio;

   if ( *tb == NULL )
   {
      return ROD_CondRetErro;
   } /* if */

   switch( cor )
   {
      case 'R':
         casainicio = 1;
         break;
      case 'G':
         casainicio = 40;
         break;
      case 'B':
         casainicio = 14;
         break;
      case 'Y':
         casainicio = 27;
         break;
      default:
         return ROD_CondRetPMoveErro;
   } /* switch */

   for ( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( ListaPeca( *tb, cor ), &ptr );
      aux = ( Peca * ) ptr;
      /* seleciona primeira peça disponivel */
      if ( aux->casa == 0 )
      {
         if ( LCI_ObtemCorrente ( CaminhoNeutro( *tb ), &ptr ) != LCI_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         alugada = ( Casa * ) ptr;
         /* Se casa obtida for a inicial, bota peça, senão chama função auxiliar */
         if ( alugada->casa == casainicio )
         {
            if ( alugada->p != NULL )
            {
               alugada->p->casa = 0; /* volta para a base */
            }
            alugada->p = aux;
            alugada->p->casa = alugada->casa;
            return ROD_CondRetOK;
         } else {
            return ROD_PEJAuxiliar( *tb, alugada, aux, alugada->casa - casainicio, casainicio );
         } /* if */
      } /* if */

      if ( LCI_TrocarPeloProximo( ListaPeca( *tb, cor ) ) != LCI_CondRetOK )
      {
         return ROD_CondRetPMoveErro;
      } /* if */
   } /* for */

   return ROD_CondRetPMoveErro;

} /* Fim PoeEmJogo */

/************* Função: ROD &Move Peca Caminho Neutro ******************/
static ROD_CondRet ROD_MovePecaCaminhoNeutro( Tabuleiro **tb, short dado, Casa *cs, char cor )
{
   Casa *aux, *alugada;
   short cont = 0;
   short casafinal;
   void *ptr;

   if ( *tb == NULL )
   {
      return ROD_CondRetErro;
   } /* if */
   switch ( cor )
   {
      case 'R':
         casafinal = 52;
         break;
      case 'G':
         casafinal = 39;
         break;
      case 'B':
         casafinal = 13;
         break;
      case 'Y':
         casafinal = 26;
         break;
      default:
         return ROD_CondRetPMoveErro;
   } /* switch */
   /* Verifica se a peça está perto de sua casafinal */
   if ( cs->casa <= casafinal )
   {
      /* Verifica se a peça mais o dado entram na lista final */
      if ( ( cs->casa + dado ) >= casafinal )
      {
         /* transferi peça da Lista Circular para Lista */
         CorrigeOffset( CaminhoNeutro( *tb ), cs->p );
         LCI_ObtemCorrente( CaminhoNeutro( *tb ), &ptr );
         aux = ( Casa * ) ptr;
         cont = ( cs->casa + dado ) - casafinal;
         if ( LIS_IrInicioLista ( CaminhoFinal( *tb, cor ) ) != LIS_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         if ( LIS_AvancarElementoCorrente( CaminhoFinal( *tb, cor ), cont ) != LIS_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         if ( LIS_ObterValor( CaminhoFinal( *tb, cor ), &ptr ) != LIS_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         alugada = ( Casa * ) ptr;
         alugada->p = aux->p;
         alugada->p->casa = alugada->casa;
         aux->p = NULL;
         if ( alugada->casa != -1 )
         {
            aux->p = NULL;
         } /* if */
         return ROD_CondRetOK;
      } else {
         return ROD_MoveCaminhoNeutroAuxiliar( *tb, cs, dado );
      } /* if */
   } else {
      return ROD_MoveCaminhoNeutroAuxiliar( *tb, cs, dado );
   } /* if */ 
} /* Fim MovePecaCaminhoNeutro */

/************* Função: ROD &MovePecaCaminhoFinal ******************/
static ROD_CondRet ROD_MovePecaCaminhoFinal( Tabuleiro **tb, short dado, char cor, int casapeca )
{
   int i = 0;
   void *ptr;
   Casa *aux;
   Casa *aux2;

   if ( *tb == NULL )
   {
      return ROD_CondRetPMoveErro;
   } else {
      if ( LIS_IrInicioLista( CaminhoFinal( *tb, cor ) ) != LIS_CondRetOK )
      {
         return ROD_CondRetPMoveErro;
      } /* if */
      while ( i < 6 )
      {
         ptr = NULL;
         if ( LIS_ObterValor( CaminhoFinal( *tb, cor ), &ptr ) != LIS_CondRetOK )
         {
            return ROD_CondRetPMoveErro;
         } /* if */
         aux = ( Casa * ) ptr;
         if ( aux->p && aux->p->casa == casapeca )
         { 
            if ( LIS_AvancarElementoCorrente( CaminhoFinal( *tb, cor ), dado ) != LIS_CondRetOK )
            {
               return ROD_CondRetPMoveErro;
            } /* if */
            if ( LIS_ObterValor( CaminhoFinal( *tb, cor ), &ptr ) != LIS_CondRetOK )
            {
               return ROD_CondRetPMoveErro;
            } /* if */
            aux2 = ( Casa * ) ptr;
            aux2->p = aux->p;
            aux->p = NULL;
            aux2->p->casa = aux2->casa;
            return ROD_CondRetOK;
         } /* if */
         LIS_AvancarElementoCorrente( CaminhoFinal( *tb, cor ), 1 );
         i++;
      } /* while */
   }/* if */

   return ROD_CondRetPMoveErro;
} /* Fim MovePecaCaminhoFinal */

static int DeterminaCasaFinal( char cor )
{
   /* retorna a primeira casa de uma cor que inicia o caminho final */
   switch ( cor )
   {
      case 'R':
         return 52;
         break;
      case 'G':
         return 39;
         break;
      case 'B':
         return 13;
         break;
      case 'Y':
         return 26;
         break;
      default:
         return 0;
   } /* switch */
}

/***********************************************************/
/**************** Função pública do módulo *****************/

/************* Função: ROD &RealizaRodada ******************/
ROD_CondRet ROD_RealizaRodada( Tabuleiro *tb, char *ordem, short score[], int qtdjogadores )
{
   char Jogador, success = 0, SemJogadas; /* "booleanos" de controle de usuário */
   int i, k, opcao; /* iteradores i e k, e opção para capturar opção de jogada do usuário */
   short dado;
   Peca *p = NULL;
   LCircular *lp; /* peças pertencentes a um jogador */
   void *ptr;
   char cmd[4] = { '\0', '\0', '\0', '\0' };
   Casa auxiliar;
   int opcaoativa[4] = { 0, 0, 0, 0 };
   short casasPecas[4] = { 0, 0, 0, 0 }; /* vetor para guardar cada casa valida para cada jogada */
   Peca *vetordepecas[4] = { NULL, NULL, NULL, NULL }; /* vetor para guardar cada peça que será usada por tal jogada */

   if ( tb == NULL )
   {
      TAB_RecuperaTabuleiro( &tb );
   } /* if */

   if ( TAB_VerificaIntegridadeTab( tb ) != TAB_CondRetOK )
   {
      TAB_RecuperaIntegridadeTab( tb );
   } /* if */

   for ( i = 0; i < 4; i++ )
   {
      Jogador = ordem[i];
      if ( Jogador != '\0' )
      {
         /* desenha no prompt */
         DES_LimpaPrompt();
         DES_DesenhaTabuleiro( tb );
         DES_DesenhaPlacar( score[0], score[1], score[2], score[3] );
         DES_DesenhaOrdem( ordem );
         DES_DesenhaAreaPecas( tb );
         printf(">>Quantidade de Jogadores Ativos: %d\n", qtdjogadores );
         printf( ">>COR: %c\n", ordem[i] );
         DES_PerguntaDado( &dado );
         /* itera sobre as peças e mostra na tela jogadas disponíveis */
         lp = ListaPeca( tb, Jogador );
         SemJogadas = 1;
         for ( k = 0; k < 4; k++ )
         {
            LCI_ObtemCorrente( lp, &ptr );
            p = ( Peca * ) ptr;
            if ( VerificaJogada( tb, p, dado, Jogador ) == ROD_CondRetJogadaValida )
            {
               SemJogadas = 0;
               opcaoativa[k] = 1;
               printf( "\n** %d) Mover peca da ", k+1 );
               if ( p->casa == 0 )
               {
                  cmd[k] = 'b';
                  printf( "base para casa " );
                  switch ( p->cor )
                  {
                     case 'R':
                        printf( " 1? \n" );
                        break;
                     case 'G':
                        printf( " 40? \n" );
                        break;
                     case 'B':
                        printf( " 14? \n" );
                        break;
                     case 'Y':
                        printf( " 27? \n" );
                        break;
                     default:
                        return ROD_CondRetErro;
                  } /* switch */
                  casasPecas[k] = p->casa;
                  vetordepecas[k] = p;
               } else if ( p->casa < 0 ) 
               {
                  cmd[k] = 'f';
                  printf( "casa %d para casa %d? ( Caminho Final ) \n", ( p->casa )*( -1 ), ( ( -1 )*( p->casa ) ) + dado );
                  casasPecas[k] = p->casa;
                  vetordepecas[k] = p;
               } else {
                  cmd[k] = 'n';
                  printf( " casa %d para casa ", p->casa );
                  if( p->casa + dado > 52 )
                  {
                     printf( "%d ? \n", (p->casa + dado) - 52 );
                  } else {
                     if ( p->casa < DeterminaCasaFinal( p->cor ) && p->casa + dado > DeterminaCasaFinal( p->cor ) )
                     {
                        printf( "%d ? ( Caminho Final ) \n", p->casa + dado - DeterminaCasaFinal( p->cor ) );  
                     } else {
                        printf( "%d ? \n", p->casa + dado );
                     }
                  } /* if */
                  casasPecas[k] = p->casa;
                  vetordepecas[k] = p;
               } /* if */
            } /* if */
            LCI_TrocarPeloProximo( lp );
         } /* for */

         do {
            if ( !SemJogadas )
            {
               scanf( "%d", &opcao );
            } else {
               break;
            } /* if */
            if( opcao <= 4 && opcao > 0 && opcaoativa[opcao-1] ) 
            {
               success = 1;
               switch( cmd[opcao-1] )
               {
                  case 'b':
                     ROD_PoeEmJogo( &tb, p->cor );
                     break;
                  case 'f':
                     if ( (casasPecas[opcao-1]*(-1)) + dado == 7 )
                     {
                        switch ( p->cor )
                        {
                           case 'R':
                              score[0] += 1;
                              if ( score[0] == 4 )
                              {
                                 DES_LimpaPrompt();
                                 printf( " Jogador Vermelho (RED) ganhou o JOGO! \n " ); 
                                 return ROD_CondRetVitoria;
                              }
                              break;
                           case 'G':
                              score[1] += 1;
                              if ( score[1] == 4 )
                              {
                                 DES_LimpaPrompt();
                                 printf( " Jogador Verde (GRE) ganhou o JOGO! \n " ); 
                                 return ROD_CondRetVitoria;
                              }
                              break;
                           case 'B':
                              score[2] += 1;
                              if ( score[2] == 4 )
                              {
                                 DES_LimpaPrompt();
                                 printf( " Jogador Azul (BLU) ganhou o JOGO! \n " ); 
                                 return ROD_CondRetVitoria;
                              }
                              break;
                           case 'Y':
                              score[3] += 1;
                              if ( score[3] == 4 )
                              {
                                 DES_LimpaPrompt();
                                 printf( " Jogador Amarelo (YEL) ganhou o JOGO! \n " ); 
                                 return ROD_CondRetVitoria;
                              }
                              break;
                           default:
                              return ROD_CondRetErro;
                        } /* switch */
                     } /* if */
                     ROD_MovePecaCaminhoFinal( &tb, dado, p->cor, casasPecas[opcao-1] );
                     break;
                  case 'n':
                     auxiliar.p = vetordepecas[opcao-1];
                     auxiliar.casa = casasPecas[opcao-1];
                     ROD_MovePecaCaminhoNeutro( &tb, dado, &auxiliar, p->cor );
                     break;
                  default:
                     return ROD_CondRetErro;
               } /* switch */
            } else {
               printf( " !!Digite uma opcao valida.!! \n " );
            } /* if */
         } while ( !success ); /* do */
      } /* if */
   } /* for */

   return ROD_CondRetOK;
} /* Fim RealizaRodada */

/************************************************************/

