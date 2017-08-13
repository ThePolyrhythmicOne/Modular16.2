/***************************************************************************
 *  $MCI Módulo de implementação: TLC Teste lista circular genérica
 *
 *  Arquivo gerado:              TestaCircular.c
 *  Letras identificadoras:      TLC
 *
 *  Nome da base de software: Testa Lista Circular genérica
 *
 *  Projeto: INF 1301
 *  Autores: pct, gb, mr
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor    Data     Observações
 *     3     mr,pct,gb 19/dez/2016 deturpação e recuperação.
 *     2       pct   28/set/2016 correções devido a massa de teste
 *     1       pct   21/set/2016 início desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* header do modulo */
#include "LCIRCULAR.H"

/* arcabouco */
#include "TST_ESPC.H"
#include "GENERICO.H"
#include "LERPARM.H"
#include "CESPDIN.H"

/***********************************************************************
 *
 *  $ED Comandos disponíveis:
 * 
 *     =criar                    ptrLista            CondRetEsp
 *     =des                      ptrLista            CondRetEsp
 *     =ins                      ptrLista  int       CondRetEsp
 *     =curr                     ptrLista            CondRetEsp
 *     =rm                       ptrLista  int       CondRetEsp
 *     =nxt                      ptrLista            CondRetEsp
 *     =prv                      ptrLista            CondRetEsp
 *     =get                      ptrLista  int       CondRetEsp
 *     =deturpar                 ptrLista  int
 *     =verifica                 ptrLista
 *     =recupera                 ptrLista
 *
 ***********************************************************************/

#define CRIAR_LC_CMD "=criar"
#define INS_LC_CMD "=ins"
#define DESTROI_LC_CMD "=des"
#define REMOVE_LC_CMD "=rm"
#define GET_LC_CMD "=get"
#define NEXT_LC_CMD "=nxt"
#define PREV_LC_CMD "=prv"
#define CURR_LC_CMD "=curr"
#define DETURPAR_LC_CMD "=deturpar"
#define VERIFICA_LC_CMD "=verifica"
#define RECOVERY_LC_CMD "=recupera"

/*****************************************************************
 ******
 *
 *  $FC Função: Efetuar operações de teste específicas para Lista Circular
 *      Podem ser criadas até 2 listas, identificadas por ptrListaA ou ptrListaB.
 *  $EP Parâmetros
 *     $P ComandoTeste - String contendo o comando
 *
 ******************************************************************
 *****/

/* listas a serem testada */
LCircular *lc = NULL;
LCircular *lb = NULL;
/* variaveis para armazenar estado de teste */
int countLC = 0;
int countLB = 0;
int vInsereLC[256];
int vInsereLB[256];


/*************** Função: LC &ExcluiDado ******************/
void ExcluiDado ( void* ptr )
{
   free(ptr);
} /* Fim ExcluiDado */

int busca( int array[], int size, int valor )
{
   int i;
   for( i = 1; i < size; i++ )
   {
      if ( array[i] == valor )
      {
         return i;
      }
   }
   return -1;
}

TST_tpCondRet TST_EfetuarComando( char *ComandoTeste )
{

   LCI_CondRet RetEsperado;
   LCI_tpModosDeturpacao lido;
   int NumLidos = -1;
   char sLida[5];
   int iLido;
   int idx;
   void *ptr;

   if ( strcmp( ComandoTeste, CRIAR_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );

      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0 )
         {
            return TST_CompararInt( RetEsperado, LCI_Cria( &lc, &ExcluiDado ),
                  "Retorno inesperado ao criar Lista Circular." );
         } else if (strcmp(sLida, "lb") == 0)
         {
            return TST_CompararInt(RetEsperado, LCI_Cria( &lb, &ExcluiDado ),
                  "Retorno inesperado ao criar Lista Circular");
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste, INS_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "sii", sLida, &iLido, &RetEsperado );
      if ( NumLidos != 3 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0)
         {
            if ( RetEsperado == LCI_CondRetOK )
            {
               countLC++;
               vInsereLC[countLC] = iLido;
            }
            return TST_CompararInt( RetEsperado, LCI_Insere( lc, &vInsereLC[countLC] ),
                  "Retorno inesperado ao inserir na Lista Circular" );
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            if ( RetEsperado == LCI_CondRetOK )
            {
               countLB++;
               vInsereLB[countLB] = iLido;
            }
            return TST_CompararInt( RetEsperado, LCI_Insere( lb, &vInsereLB[countLB] ),
                  "Retorno inesperado ao inserir na Lista Circular" );
         } else {
            return TST_CondRetParm;
         }
      } /* if */
   } else if ( strcmp( ComandoTeste, DESTROI_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0 )
         {
            countLC = 0;
            return TST_CompararInt( RetEsperado, LCI_Destroi( &lc ),
                  "Retorno inesperado ao destruir a Lista Circular" );
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            countLB = 0;
            return TST_CompararInt( RetEsperado, LCI_Destroi( &lb ),
                  "Retorno inesperado ao destruir a Lista Circular" );
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste, REMOVE_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "sii", sLida, &iLido, &RetEsperado );
      if ( NumLidos != 3 )
      {
         return TST_CondRetParm;
      } else {

         if ( strcmp( sLida, "lc" ) == 0 )
         {
            idx = busca( vInsereLC, 256, iLido );
            if ( idx == -1 || RetEsperado != LCI_CondRetOK )
            {
               return TST_CompararInt( RetEsperado,
                     LCI_RemoveElemento( lc, &iLido ),
                     "Retorno inesperado ao remover na Lista Circular" );
            } else {
			   countLC--;
               return TST_CompararInt( RetEsperado,
                     LCI_RemoveElemento( lc, &vInsereLC[idx] ),
                     "Retorno inesperado ao remover na Lista Circular" );
            }
         }
         else if ( strcmp( sLida, "lb" ) == 0 )
         {
            idx = busca( vInsereLB, 256, iLido );
			if ( idx == -1 || RetEsperado != LCI_CondRetOK )
            {
               return TST_CompararInt( RetEsperado,
                     LCI_RemoveElemento( lb, &iLido ),
                     "Retorno inesperado ao remover na Lista Circular" );
            } else {
			   countLB--;
               return TST_CompararInt( RetEsperado,
                     LCI_RemoveElemento( lc, &vInsereLB[idx] ),
                     "Retorno inesperado ao remover na Lista Circular" );
            }
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste,  GET_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "sii", sLida, &iLido, &RetEsperado );
      if ( NumLidos != 3 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0 )
         {
            idx = busca( vInsereLC, 256, iLido );
            if ( idx == -1 )
            {
               return TST_CompararInt( RetEsperado,
                     LCI_ProcurarElem( lc, &ptr, &iLido ),
                     "Retorno inesperado ao pegar valor na Lista Circular" );
            } else {
               return TST_CompararInt( RetEsperado,
                     LCI_ProcurarElem( lc, &ptr, &vInsereLC[idx] ),
                     "Retorno inesperado ao pegar valor na Lista Circular" );
            }
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            idx = busca( vInsereLB, 256, iLido );
            if ( idx == -1 )
            {
               return TST_CompararInt( RetEsperado,
                     LCI_ProcurarElem( lc, &ptr, &iLido ),
                     "Retorno inesperado ao pegar valor na Lista Circular" );
            } else {
               return TST_CompararInt( RetEsperado,
                     LCI_ProcurarElem( lc, &ptr, &vInsereLB[idx] ),
                     "Retorno inesperado ao pegar valor na Lista Circular" );
            }
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */

   } else if ( strcmp( ComandoTeste, NEXT_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );
      if( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_TrocarPeloProximo( lc ),
                  "Retorno inesperado ao ir tentar pegar proximo no" );
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_TrocarPeloProximo( lb ),
                  "Retorno inesperado ao ir tentar pegar proximo no" );
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste, PREV_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp( sLida, "lc" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_TrocarPeloAnterior( lc ),
                  "Retorno inesperado ao ir tentar pegar no anterior" );
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_TrocarPeloAnterior( lb ),
                  "Retorno inesperado ao ir tentar pegar no anterior" );
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste, CURR_LC_CMD ) == 0 ) 
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         if ( strcmp ( sLida, "lc" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_ObtemCorrente( lc, &ptr ),
                  "Retorno inesperado ao ir tentar pegar proximo no" );
         } else if ( strcmp( sLida, "lb" ) == 0 )
         {
            return TST_CompararInt( RetEsperado,
                  LCI_ObtemCorrente( lb, &ptr ),
                  "Retorno inesperado ao ir tentar pegar proximo no" );
         } else {
            return TST_CondRetParm;
         } /* if */
      } /* if */
   } else if ( strcmp( ComandoTeste, DETURPAR_LC_CMD ) == 0 )
   {
	   NumLidos = LER_LerParametros( "si", sLida, &lido );
	   if ( NumLidos != 2 )
	   {
		   return TST_CondRetParm;
	   } else if ( strcmp( sLida, "lc" ) == 0 )
	   {
		   LCI_Deturpar( lc, lido );
		   return TST_CompararInt( 0, 0, "" );
	   } else if ( strcmp( sLida, "lb" ) == 0 )
	   {
		   LCI_Deturpar( lb, lido );
		   return TST_CompararInt( 0, 0, "" );
	   } /* if */
   } else if ( strcmp( ComandoTeste, VERIFICA_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", sLida, &RetEsperado );
	   if ( NumLidos != 2 )
	   {
		   return TST_CondRetParm;
	   } /* if */
	   if ( strcmp( sLida, "lc" ) == 0 )
	   {
		   return TST_CompararInt(  RetEsperado, 
                         LCI_VerificaLista( lc ), 
                         "Retorno inesperado ao Verificar Lista" );
	   } else if ( strcmp( sLida, "lb" ) == 0 )
	   {
		   return TST_CompararInt(  RetEsperado, 
                         LCI_VerificaLista( lb ), 
                         "Retorno inesperado ao Verificar Lista" );
	   } /* if */

   } else if ( strcmp( ComandoTeste, RECOVERY_LC_CMD ) == 0 )
   {
	   NumLidos = LER_LerParametros( "s", sLida );
	   if ( NumLidos != 1 )
	   {
		   return TST_CondRetParm;
	   } /* if */
	   if ( strcmp( sLida, "lc" ) == 0 )
	   {
		   if ( LCI_RecuperaLista( lc ) == 0 )
		   {
			   return TST_CondRetErro;
		   } /* if */
		   return TST_CondRetOK;
	   } else if ( strcmp( sLida, "lb" ) == 0 )
	   {
		   if ( LCI_RecuperaLista( lb ) == 0 )
		   {
			   return TST_CondRetErro;
		   } /* if */
		   return TST_CondRetOK;
	   } /* if */

   }
   return TST_CondRetParm;
} /* Fim TST_EfetuarComando */
