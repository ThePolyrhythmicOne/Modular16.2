/***************************************************************************
 *  $MCI M�dulo de implementac�o: TAB Tabuleiro
 *
 *  Arquivo gerado:              Tabuleiro.c
 *  Letras identificadoras:      TAB
 *
 *  Projeto: Ludo - INF1301
 *  Autores: mr, pct, gb
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o  Autor   Data
 *        8.0 mr,pct,gb 19/dez/2016 Finaliza��es.
 *        7.0    mr   13/dez/2016   Implementa��o da assertiva de recupera��o por avan�o (hidra).
 *        6.0    pct  17/out/2016   Ajuste da estrutura Tabuleiro conforme enunciado no T2.
 *        5.0    pct  15/out/2016   Mudan�a de nome de fun��es do m�dulo LCIircular. 
 *        4.0    pct  08/out/2016   Implementa��o TAB_Destroi.
 *        3.0    pct  05/out/2016   Padroniza��o do c�digo conforme o Livro.
 *        2.0    mr   01/set/2016   Padroniza��o do c�digo inicial; inclus�o da fun��o inicializa;
 *                                  Mudan�a da estrutura Casa, do m�dulo Peca, para o m�dulo
 *                                  Tabuleiro, junto da fun��o criar Casa.
 *        1.0    mr   30/set/2016   In�cio do desenvolvimento.
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define  TABULEIRO_OWN
#include "TABULEIRO.H"
#undef   TABULEIRO_OWN
#include "PECA.H"
#include "TABAUXILIAR.H"

#define NMAX 52 /* Numero m�ximo de casas neutras */

TAB_CondRet TAB_VerificaIntegridadeTab( Tabuleiro *tb ); /* forward declaration */

/*******************************************/
/******* Fun��es auxiliares p�blicas *******/

/*********** Fun��o: TAB &PreencheVetorNeutro ***********/
void TAB_PreencheVetorNeutro( Tabuleiro *tb, int Neutro[] )
{
   /* Preenche Neutro com o n�mero da casa correspondente ao �ndice */
   /* Se uma pe�a est� na casa, preenche com -1 */

   LCircular* auxiliar;
   LIS_tppLista auxiliar2;
   Casa* aux1 = NULL;
   void* ptr;
   int i;

   auxiliar = ( LCircular * ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_NEUTRO );

   for ( i = 0; i < NMAX; i++ )
   {
      LCI_ObtemCorrente( auxiliar, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p == NULL )
      {
         Neutro[(aux1->casa)-1] = aux1->casa;
      } else {
         Neutro[(aux1->casa)-1] = -1;
      } /* if */
      LCI_TrocarPeloProximo( auxiliar );
   } /* for */

   for ( i = 0; i < 4; i++ )
   {
      auxiliar2 = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_FINAL_R + i );
      LIS_IrInicioLista( auxiliar2 );
      LIS_ObterValor( auxiliar2, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p )
      {
         switch ( CAMINHO_FINAL_R + i )
         {
            case CAMINHO_FINAL_R:
               Neutro[51] = -1;
               break;
            case CAMINHO_FINAL_G:
               Neutro[38] = -1;
               break;
            case CAMINHO_FINAL_B:
               Neutro[12] = -1;
               break;
            case CAMINHO_FINAL_Y:
               Neutro[25] = -1;
               break;
            default:
               break;
         } /* switch */
      } /* if */
   } /* for */
} /* Fim PreencheVetorNeutro */

/*********** Fun��o: TAB &PreencheVetorPecas ***********/
void TAB_PreencheVetorPecas( Tabuleiro* tb, int Red[], int Blue[], int Green[], int Yellow[], int flag )
{
   /* Preenche os vetores Red, Blue, Green, Yellow com os respectivos c�digos caso */
   /* haja pe�a dispon�vel ou com o char 254 caso n�o tenha pe�a dispon�vel */
   /* Se flag for 1, ent�o preenche o vetor com as casas ou inv�s da cor */

   LCircular *auxiliar;
   Peca *aux1;
   void *ptr;
   int i;

   auxiliar = ( LCircular * ) TAB_RetornaListaDoTabuleiro( tb, PRED );

   for( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( auxiliar, &ptr );
      aux1 = ( Peca * ) ptr;
      if ( flag == 1 )
      {
         Red[i] = aux1->casa;
      } else {
         if ( aux1->casa == 0 )
         {
            Red[i] = 'R';
         } else {
            Red[i] = 254;
         }
      } /* if */
      LCI_TrocarPeloProximo( auxiliar );
   } /* for */

   auxiliar = ( LCircular * ) TAB_RetornaListaDoTabuleiro (tb, PBLUE );

   for( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( auxiliar, &ptr );
      aux1 = ( Peca * ) ptr;
      if ( flag == 1 )
      {
         Blue[i] = aux1->casa;
      } else {
         if ( aux1->casa == 0 )
         {
            Blue[i] = 'B';
         } else {
            Blue[i] = 254;
         }
      } /* if */
      LCI_TrocarPeloProximo( auxiliar );
   } /* for */

   auxiliar = ( LCircular * ) TAB_RetornaListaDoTabuleiro( tb, PGREEN );

   for( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( auxiliar, &ptr );
      aux1 = ( Peca * ) ptr;
      if ( flag == 1 )
      {
         Green[i] = aux1->casa;
      } else {
         if ( aux1->casa == 0 )
         {
            Green[i] = 'G';
         } else {
            Green[i] = 254;
         }
      } /* if */
      LCI_TrocarPeloProximo( auxiliar );
   } /* for */

   auxiliar = ( LCircular * ) TAB_RetornaListaDoTabuleiro( tb, PYELLOW );

   for( i = 0; i < 4; i++ )
   {
      LCI_ObtemCorrente( auxiliar, &ptr );
      aux1 = ( Peca * ) ptr;
      if ( flag == 1 )
      {
         Yellow[i] = aux1->casa;
      } else {
         if ( aux1->casa == 0 )
         {
            Yellow[i] = 'Y';
         } else {
            Yellow[i] = 254;
         }
      } /* if */
      LCI_TrocarPeloProximo( auxiliar );
   } /* for */
} /* Fim PreencheVetorPecas */

/*********** Fun��o: TAB &PreencheVetorFinal ***********/
void TAB_PreencheVetorFinal( Tabuleiro* tb, int Red[], int Blue[], int Green[], int Yellow[] )
{
   int i;
   void *ptr;
   Casa *aux1;
   LIS_tppLista auxiliar;

   auxiliar = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_FINAL_R );

   LIS_IrInicioLista( auxiliar );

   for( i = 0; i < 6; i++ )
   {
      LIS_ObterValor( auxiliar, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p == NULL )
      {
         Red[i] = i;
      } else {
         Red[i] = -1;
      } /* if */
      LIS_AvancarElementoCorrente( auxiliar, 1 );
   } /* for */

   auxiliar = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_FINAL_G );

   LIS_IrInicioLista( auxiliar );

   for( i = 0; i < 6; i++ )
   {
      LIS_ObterValor( auxiliar, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p == NULL )
      {
         Green[i] = i;
      } else {
         Green[i] = -1;
      } /* if */
      LIS_AvancarElementoCorrente( auxiliar, 1 );
   } /* for */

   auxiliar = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_FINAL_B );

   LIS_IrInicioLista( auxiliar );

   for( i = 0; i < 6; i++ )
   {
      LIS_ObterValor( auxiliar, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p == NULL )
      {
         Blue[i] = i;
      } else {
         Blue[i] = -1;
      } /* if */
      LIS_AvancarElementoCorrente( auxiliar, 1 );
   } /* for */

   auxiliar = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( tb, CAMINHO_FINAL_Y );

   LIS_IrInicioLista( auxiliar );

   for( i = 0; i < 6; i++ )
   {
      LIS_ObterValor( auxiliar, &ptr );
      aux1 = ( Casa * ) ptr;
      if ( aux1->p == NULL )
      {
         Yellow[i] = i;
      } else {
         Yellow[i] = -1;
      } /* if */
      LIS_AvancarElementoCorrente( auxiliar, 1 );
   } /* for */

} /* Fim PreencheVetorFinal */

/**************************************/

/**************************************/
/********** Fun��es p�blicas **********/

/************* Fun��o: TAB &Retorna Lista do Tabuleiro ******************/
void* TAB_RetornaListaDoTabuleiro ( Tabuleiro *tab, int idxLista )
{
   /* Retorna refer�ncia para estrutura de dados no Indice idxLista */
   void *ptr;
   if ( LIS_IrInicioLista( tab->tblr ) != LIS_CondRetOK )
   {
      return NULL;
   } /* if */
   if ( LIS_AvancarElementoCorrente( tab->tblr, idxLista ) != LIS_CondRetOK )
   {
      return NULL;
   } /* if */
   if ( LIS_ObterValor( tab->tblr, &ptr ) != LIS_CondRetOK )
   {
      return NULL;
   } /* if */
   return ptr;  
} /* Fim TAB_RetornaListaDoTabuleiro */

/************* Fun��o: TAB &Criar Tabuleiro ******************/
TAB_CondRet TAB_criaTabuleiro( Tabuleiro **tab )
{

   LCircular *PRed;             /* pe�as vermelhas */
   LCircular *PBlue;            /* pe�as azuis */
   LCircular *PYellow;          /* pe�as amarelas */
   LCircular *PGreen;           /* pe�as verdes */
   LIS_tppLista CaminhoFinalR;  /* Caminho */
   LIS_tppLista CaminhoFinalG;  /* Caminho */
   LIS_tppLista CaminhoFinalB;  /* Caminho */
   LIS_tppLista CaminhoFinalY;  /* Caminho */
   LCircular *Caminho;          /* Caminho Neutro */
   int i;

   /* Checar se tabuleiro j� existe */
   if ( *tab != NULL ) 
   {
      return TAB_CondRetTJaExiste;
   } /* if */
   /* Cria��o do Tabuleiro */
   *tab = ( Tabuleiro * )malloc( sizeof( Tabuleiro ) );
   if ( *tab == NULL ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */

   /* inicializando ponteiros */
   PRed = NULL;
   PBlue = NULL;
   PYellow = NULL;
   PGreen = NULL;
   CaminhoFinalR = NULL;
   CaminhoFinalG = NULL;
   CaminhoFinalB = NULL;
   CaminhoFinalY = NULL;
   Caminho = NULL;

   /* Cria��o do caminho neutro */
   if ( LCI_Cria( &Caminho, NULL ) != LCI_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */

   /**************************************/
   /* Cria��o das listas de pe�as fora de jogo */
   if ( LCI_Cria( &PBlue, NULL ) != LCI_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LCI_Cria( &PRed, NULL ) != LCI_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LCI_Cria( &PGreen, NULL ) != LCI_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LCI_Cria( &PYellow, NULL ) != LCI_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   /**************************************/

   /**************************************/
   /* Cria�ao dos caminhos finais */
   if ( LIS_CriarLista( NULL, &CaminhoFinalB ) != LIS_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_CriarLista( NULL, &CaminhoFinalG ) != LIS_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */ 
   if ( LIS_CriarLista( NULL, &CaminhoFinalR ) != LIS_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_CriarLista( NULL, &CaminhoFinalY ) != LIS_CondRetOK ) 
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_CriarLista( NULL, &(*tab)->tblr ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, PRed ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, PGreen ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, PBlue ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, PYellow ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, CaminhoFinalR ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, CaminhoFinalG ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, CaminhoFinalB ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, CaminhoFinalY ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   if ( LIS_InserirElementoApos( (*tab)->tblr, Caminho ) != LIS_CondRetOK )
   {
      return TAB_CondRetFalhaCriacao;
   } /* if */
   /**************************************/

   /*Assertiva de recupera��o por avan�o*/
   LIS_IrInicioLista( (*tab)->tblr );
   for ( i = 0; i < 9; i++ )
   {
      LIS_ObterValor( (*tab)->tblr, &(*tab)->hidra[i] );
      LIS_AvancarElementoCorrente( (*tab)->tblr,1 );
   } /* for */

   return TAB_CondRetOK;
} /* Fim TAB_criaTabuleiro */

/************* Fun��o: TAB &Criar Casa ******************/
static TAB_CondRet TAB_CriaCasa( Casa **c, short pos, Peca *peca )
{
   if ( *c != NULL ) 
   {
      return TAB_CondRetCJaExiste;
   } else {
      *c = ( Casa * )malloc( sizeof( Casa ) );
      if ( *c == NULL )
      {
         return TAB_CondRetFaltouMemoria;
      } /* if */
      (*c)->casa = pos;
      (*c)->p = peca;
      return TAB_CondRetOK;
   } /* if */
} /* Fim criaCasa */

/************* Fun��o: TAB &inicializa Tabuleiro Secundario ******************/
static Tabuleiro* TAB_inicializaSecundario( Tabuleiro *primario )
{
	/* Inicializa a redund�ncia para a recupera��o por avan�o */
	/* Copia todo o Tabuleiro primario e retorna um ponteiro para */
	/* a c�pia ( secundario ) */
	Tabuleiro *ptr;
	int i;
	
	ptr = ( Tabuleiro * ) malloc( sizeof( Tabuleiro ) );
	LIS_CriarLista( NULL, &ptr->tblr );
	if ( ptr == NULL )
	{
		return NULL;
	} /* if */
	for ( i = 0; i < 9; i++ )
	{
		LIS_InserirElementoApos( ptr->tblr, primario->hidra[i] );
		ptr->hidra[i] = primario->hidra[i];
	} /* for */
	ptr->secundario = NULL;
	return ptr;
} /* Fim TAB_inicializaSecundario */

/************* Fun��o: TAB &Inicializar Tabuleiro ******************/
TAB_CondRet TAB_inicializaTabuleiro( Tabuleiro **tab )
{
   short contneutro, contfinal, contfora;
   Casa *casa = NULL;
   Peca *peca = NULL;
   LCircular *neutro, *p;
   LIS_tppLista final;
   void *ptr;

   if ( *tab == NULL || (*tab)->tblr == NULL )
   {
      return TAB_CondRetFalhaInicializacao;
   } /* if */
   neutro = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_NEUTRO );
   if ( !neutro )
   {
      return TAB_CondRetFalhaInicializacao;
   } /* if */
   if ( LCI_ObtemCorrente( neutro, &ptr ) != LCI_CondRetLVazia )
   {
      return TAB_CondRetTJaInicializado;
   } /* if */
   for ( contneutro = 1; contneutro < 53; contneutro++ ) 
   {
      /* Criando a casa que sera referenciada pela lista circular do caminho neutro */
      if ( TAB_CriaCasa( &casa, contneutro, NULL ) != TAB_CondRetOK )
      {
         return TAB_CondRetFalhaInicializacao;
      } /* if */
      /* Fazendo a referencia citada acima */
      if ( LCI_Insere( neutro, casa ) != LCI_CondRetOK ) 
      {
         return TAB_CondRetFalhaInicializacao;
      } /* if */
      casa = NULL;

      /* Casa de numero 13 inicia o caminho final de cor Azul */
      if ( contneutro == 13 ) 
      {
         final = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_B );
         if ( !final )
         {
            return TAB_CondRetFalhaInicializacao;
         }
         for ( contfinal = 0; contfinal < 7; contfinal++ ) 
         {
            /* Criando a casa que sera apontada pela lista do caminho final */
            if ( TAB_CriaCasa( &casa, (contfinal+1)*(-1), NULL ) != TAB_CondRetOK )
            {
               return TAB_CondRetFalhaInicializacao;
            }
            /* Fazendo a referencia citada acima */
            if ( LIS_InserirElementoApos( final, casa ) != LIS_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            casa = NULL;
         } /* for */
         p = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PBLUE );
         if ( !p )
         {
            return TAB_CondRetFalhaInicializacao;
         } /* if */
         for ( contfora = 0; contfora < 4; contfora++ ) 
         {
            /* Criando a peca que sera referenciada pela lista circular de pe�as fora do jogo */
            if ( PEC_Cria( &peca, 'B', 0 ) != PEC_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            /* fazendo a referencia citada acima */
            if ( LCI_Insere( p, peca) != LCI_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            peca = NULL;
         } /* for */
      } /* if */
      /* Casa de numero 26 inicia o caminho final de cor Amarela */
      if ( contneutro == 26 ) 
      {
         final = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_Y );
         if ( !final )
         {
            return TAB_CondRetFalhaInicializacao;
         }
         for ( contfinal = 0; contfinal < 7; contfinal++ ) 
         {
            if ( TAB_CriaCasa( &casa, (contfinal+1)*(-1), NULL ) != TAB_CondRetOK )
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            if ( LIS_InserirElementoApos( final, casa ) != LIS_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            casa = NULL;
         } /* for */
         p = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PYELLOW );
         if ( !p )
         {
            return TAB_CondRetFalhaInicializacao;
         } /* if */
         for ( contfora = 0; contfora < 4; contfora++ ) 
         {
            if ( PEC_Cria( &peca, 'Y', 0 ) != PEC_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            if ( LCI_Insere( p, peca ) != LCI_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            peca = NULL;
         } /* for */
      } /* if */

      /* Casa de numero 39 inicia o caminho final de cor Verde */ 
      if ( contneutro == 39 ) 
      {
         final = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_G );
         if ( !final )
         {
            return TAB_CondRetFalhaInicializacao;
         }
         for ( contfinal = 0; contfinal < 7; contfinal++ ) 
         {
            if ( TAB_CriaCasa( &casa, (contfinal+1)*(-1), NULL ) != TAB_CondRetOK )
            {
               return TAB_CondRetFalhaInicializacao;
            }
            if ( LIS_InserirElementoApos( final, casa ) != LIS_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            casa = NULL;
         } /* for */
         p = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PGREEN );
         if ( !p )
         {
            return TAB_CondRetFalhaInicializacao;
         } /* if */
         for ( contfora = 0; contfora < 4; contfora++ ) 
         {
            if ( PEC_Cria( &peca, 'G', 0 ) != PEC_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            if ( LCI_Insere( p, peca ) != LCI_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            peca = NULL;
         } /* for */
      } /* if */
      /* Casa de numero 52 inicia o caminho final de cor Vermelha */
      if ( contneutro == 52 ) 
      {
         final = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_R );
         if ( !final )
         {
            return TAB_CondRetFalhaInicializacao;
         }
         for ( contfinal = 0; contfinal < 7; contfinal++ ) 
         {
            if ( TAB_CriaCasa( &casa, (contfinal+1)*(-1), NULL ) != TAB_CondRetOK )
            {
               return TAB_CondRetFalhaInicializacao;
            }
            if ( LIS_InserirElementoApos( final, casa ) != LIS_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            casa = NULL;
         } /* for */
         p = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PRED );
         if ( !p )
         {
            return TAB_CondRetFalhaInicializacao;
         } /* if */
         for ( contfora = 0; contfora < 4; contfora++ ) 
         {
            if ( PEC_Cria( &peca, 'R', 0 ) != PEC_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            if ( LCI_Insere( p, peca ) != LCI_CondRetOK ) 
            {
               return TAB_CondRetFalhaInicializacao;
            } /* if */
            peca = NULL;
         } /* for */
      } /* if */
      peca = NULL;
   } /* for */
   
   (*tab)->secundario = TAB_inicializaSecundario( (*tab) );
   
   return TAB_CondRetOK; 
} /* Fim TAB_inicializaTabuleiro */

/************* Fun��o: TAB &Destroi Casa ******************/
static TAB_CondRet TAB_DestroiCasa( Casa **c )
{
   if ( *c == NULL ) 
   {
      return TAB_CondRetCNaoExiste;
   } else {
      free( *c );
      *c = NULL;
      return TAB_CondRetOK;
   } /* if */
} /* Fim TAB_DestroiCasa */

TAB_CondRet TAB_DestroiTab( Tabuleiro **tab )
{
   int i;
   void *ptr;
   Peca *aux;
   Casa *aux2;
   LCircular *red, *green, *blue, *yellow, *caminho;
   LIS_tppLista finalR, finalG, finalB, finalY;

   if ( (*tab) == NULL || (*tab)->tblr == NULL )
   {
      return TAB_CondRetTNaoExiste;
   } else {
      /**************************************/
      /* referencia ponteiros red green blue yellow */
      red = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PRED );
      green = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PGREEN );
      blue = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PBLUE );
      yellow = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), PYELLOW );
      if ( !red || !green || !blue || !yellow )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */

      /* destroi listas circulares de pe�as */
      for ( i = 0; i < 4; i++ )
      {
         if ( LCI_ObtemCorrente( red, &ptr ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux = ( Peca * ) ptr;
         if ( PEC_Destroi( &aux ) != PEC_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_ObtemCorrente( green, &ptr ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux = ( Peca * ) ptr;
         if ( PEC_Destroi( &aux ) != PEC_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_ObtemCorrente( blue, &ptr ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux = ( Peca * ) ptr;
         if ( PEC_Destroi( &aux ) != PEC_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_ObtemCorrente( yellow, &ptr ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux = ( Peca * ) ptr;
         if ( PEC_Destroi( &aux ) != PEC_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_TrocarPeloProximo( red ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_TrocarPeloProximo( green ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_TrocarPeloProximo( blue ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_TrocarPeloProximo( yellow ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
      }
      if ( LCI_Destroi( &red ) != LCI_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LCI_Destroi( &green ) != LCI_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LCI_Destroi( &blue ) != LCI_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LCI_Destroi( &yellow ) != LCI_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      /**************************************/

      /**************************************/
      /* referencia ponteiros finalR, finalG, finalB, finalY */
      finalR = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_R );
      finalG = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_G );
      finalB = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_B );
      finalY = ( LIS_tppLista ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_FINAL_Y );
      if ( !finalR || !finalG || !finalB || !finalY )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      /* Ajusta corrente para in�cio das listas */
      if ( LIS_IrInicioLista( finalR ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_IrInicioLista( finalG ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_IrInicioLista( finalB ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_IrInicioLista( finalY ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */

      /* destroi listas de caminhos finais */
      for ( i = 0; i < 6; i++ )
      {
         if ( LIS_ObterValor( finalR, &ptr ) != LIS_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux2 = ( Casa * ) ptr;
         if ( TAB_DestroiCasa( &aux2 ) != TAB_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LIS_ObterValor( finalG, &ptr ) != LIS_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux2 = ( Casa * ) ptr;
         if ( TAB_DestroiCasa( &aux2 ) != TAB_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LIS_ObterValor( finalB, &ptr ) != LIS_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux2 = ( Casa * ) ptr;
         if ( TAB_DestroiCasa( &aux2 ) != TAB_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LIS_ObterValor( finalY, &ptr ) != LIS_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux2 = ( Casa * ) ptr;
         if ( TAB_DestroiCasa( &aux2 ) != TAB_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( i < 5 )
         {
            if ( LIS_AvancarElementoCorrente( finalR, 1) != LIS_CondRetOK )
            {
               return TAB_CondRetFalhaDestruicao;
            } /* if */
            if ( LIS_AvancarElementoCorrente( finalG, 1) != LIS_CondRetOK )
            {
               return TAB_CondRetFalhaDestruicao;
            } /* if */
            if ( LIS_AvancarElementoCorrente( finalB, 1) != LIS_CondRetOK )
            {
               return TAB_CondRetFalhaDestruicao;
            } /* if */
            if ( LIS_AvancarElementoCorrente( finalY, 1) != LIS_CondRetOK )
            {
               return TAB_CondRetFalhaDestruicao;
            } /* if */
         } /* if */
      }
      if ( LIS_EsvaziarLista( finalR ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_EsvaziarLista( finalG ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_EsvaziarLista( finalB ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      if ( LIS_EsvaziarLista( finalY ) != LIS_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      /**************************************/

      /**************************************/
      /* referencia ponteiro caminho */
      caminho = ( LCircular * ) TAB_RetornaListaDoTabuleiro( (*tab), CAMINHO_NEUTRO );
      if ( !caminho )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
      /* destroi caminho neutro */
      for ( i = 0; i < 52; i++ )
      {
         if ( LCI_ObtemCorrente( caminho, &ptr ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         aux2 = ( Casa * ) ptr;
         if ( TAB_DestroiCasa( &aux2 ) != TAB_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
         if ( LCI_TrocarPeloProximo( caminho ) != LCI_CondRetOK )
         {
            return TAB_CondRetFalhaDestruicao;
         } /* if */
      } /* for */
      if ( LCI_Destroi( &caminho ) != LCI_CondRetOK )
      {
         return TAB_CondRetFalhaDestruicao;
      } /* if */
   } /* if */
   /**************************************/

   free( *tab );
   *tab = NULL;
   return TAB_CondRetOK;

} /* Fim TAB_Destroi */

/*********** Fun��o: TAB &RecuperaIntegridadeTab ***********/
TAB_CondRet TAB_RecuperaIntegridadeTab( Tabuleiro *tb )
{
   /*** Recupera��o por avan�o ***/
   TAB_CondRet retorno;
   int idx = 0;

   do {
      if ( LIS_InserirElementoAntes( tb->tblr, tb->hidra[idx] ) != LIS_CondRetOK )
      {
         return TAB_CondRetErro;
      } /* if */
      if ( LIS_AvancarElementoCorrente( tb->tblr, 1 ) != LIS_CondRetOK )
      {
         return TAB_CondRetErro;
      } /* if */
      if ( LIS_ExcluirElemento( tb->tblr ) != LIS_CondRetOK )
      {
         return TAB_CondRetErro;
      } /* if */
      idx += 1;
   }  while ( ( retorno = TAB_VerificaIntegridadeTab( tb ) ) != TAB_CondRetOK ); /* while */

   return TAB_CondRetOK;
} /* Fim TAB_RecuperaIntegridadeTab */

/*********** Fun��o: TAB &VerificaIntegridadeTab ***********/
TAB_CondRet TAB_VerificaIntegridadeTab( Tabuleiro *tb )
{
   int i;
   void *ptr;

   if ( tb == NULL )
   {
      return TAB_RecuperaTabuleiro( &tb );
   } /* if */
   if ( tb->tblr == NULL )
   {
	   return TAB_CondRetErro;
   }
   LIS_IrInicioLista( tb->tblr );
   for ( i = 0 ; i < 9 ; i++ )
   {
      LIS_ObterValor( tb->tblr, &ptr );
      if ( ptr == NULL || ptr != tb->hidra[i] )
      {
         return TAB_CondRetErro;
      } /* if */
      LIS_AvancarElementoCorrente( tb->tblr, 1 );
   } /* for */
   return TAB_CondRetOK;
} /* Fim TAB_VerificaIntegridadeTab */

/*********** Fun��o: TAB &RecuperaTabuleiro ***********/
TAB_CondRet TAB_RecuperaTabuleiro( Tabuleiro **tb )
{
   /*** Recupera��o por avan�o ***/
   if ( (*tb)->tblr == NULL )
   {
	   (*tb)->tblr = (*tb)->secundario->tblr;
	   return TAB_CondRetOK;
   } /* if */
   if ( TAB_criaTabuleiro( tb ) != TAB_CondRetOK )
   {
      return TAB_CondRetErro;
   } /* if */
   if ( TAB_inicializaTabuleiro( tb ) != TAB_CondRetOK )
   {
      return TAB_CondRetErro;
   } /* if */

   return TAB_CondRetOK;
} /* Fim TAB_RecuperaTabuleiro */

#ifdef _DEBUG
void TAB_Deturpa( Tabuleiro *tb, TAB_tpModosDeturpacao modo )
{
   int i;

   switch ( modo )
   {
      case DeturparTabuleiroNulo:
      {
	     tb->tblr = NULL;
         break;
      }
      case DeturparUmaCabeca:
      {
         LIS_IrInicioLista( tb->tblr );
         LIS_InserirElementoAntes( tb->tblr, NULL );
         LIS_AvancarElementoCorrente( tb->tblr, 1 );
         LIS_ExcluirElemento( tb->tblr );
         LIS_AvancarElementoCorrente( tb->tblr, 1 );
         break;
      }
      case DeturparDuasCabecas:
      {
         LIS_IrInicioLista( tb->tblr );
         for ( i = 0; i < 2; i++ )
         {
            LIS_InserirElementoAntes( tb->tblr, NULL );
            LIS_AvancarElementoCorrente( tb->tblr, 1 );
            LIS_ExcluirElemento( tb->tblr );
            LIS_AvancarElementoCorrente( tb->tblr, 1 );
         } /* for */
      }
      case DeturparCabecasListas:
      {
         LIS_IrInicioLista( tb->tblr );
         for ( i = 0; i < 9; i++ )
         {
            LIS_InserirElementoAntes( tb->tblr, NULL );
            LIS_AvancarElementoCorrente( tb->tblr, 1 );
            LIS_ExcluirElemento( tb->tblr );
            LIS_AvancarElementoCorrente( tb->tblr, 1 );
         } /* for */
        break;
      }
      default:
      {
         break;
      }
   } /* switch */
}
#endif 

