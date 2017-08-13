/***************************************************************************
 *  $MCI Módulo de implementação: TTB Teste Tabuleiro 
 *
 *  Arquivo gerado:              TestaTabuleiro.c
 *  Letras identificadoras:      TTB
 *
 *  Nome da base de software: Testa Tabuleiro
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: mr, pct, gb
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor    Data     Observações
 *     3.0     pct 17/dez/2016  implementação deturpação e recuperação.
 *     2.0     pct 13/out/2016  padronização do código.
 *     1.0     mr  10/out/2016  início desenvolvimento.
 *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>

/* header do modulo */
#include "TABULEIRO.H"

/* arcabouco */
#include "TST_ESPC.H"
#include "GENERICO.H"
#include "LERPARM.H"

/***********************************************************************
 *
 *  $ED Comandos disponíveis:
 *
 *     =criarTab                 tab	                CondRetEsp
 *     =init                     tab	                CondRetEsp
 *     =destTab                  tab	                CondRetEsp
 *     =deturpar                 tab                   Modo
 *     =verifica                 tab                   CondRetEsp
 *     =recovertab               tab                   CondRetEsp
 *     =recoverintegridade       tab                   CondRetEsp
 *
 ***********************************************************************/

#define CRIART_LC_CMD "=criar"
#define INIT_LC_CMD "=init"
#define DESTROIT_LC_CMD "=dest"
#define DETURPAR_LC_CMD "=deturpar"
#define VERIFICA_LC_CMD "=verifica"
#define RECUPERATAB_LC_CMD "=recovertab"
#define RECUPERAINT_LC_CMD "=recoverintegridade"

/*****************************************************************
 ******
 *
 *  $FC Função: Efetuar operações de teste específicas para Tabuleiro
 *      Pode ser criado apenas 1 Tabuleiro por vez.
 *  $EP Parâmetros
 *     $P ComandoTeste - String contendo o comando
 *
 ******************************************************************
 *****/

/* tabuleiro a ser testado */
Tabuleiro *tab = NULL;

TST_tpCondRet TST_EfetuarComando( char *ComandoTeste )
{

   TAB_CondRet RetEsperado;
   TAB_tpModosDeturpacao lido;
   char string[5];
   int NumLidos = -1;


   if ( strcmp( ComandoTeste, CRIART_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );

      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else 
      {
         return TST_CompararInt( RetEsperado, TAB_criaTabuleiro( &tab ),
               "Retorno inesperado ao criar Tabuleiro." );
      }
   } else if ( strcmp( ComandoTeste, INIT_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else {
         return TST_CompararInt( RetEsperado, TAB_inicializaTabuleiro( &tab ),
               "Retorno inesperado ao inicializar Tabuleiro" );
      }
   } else if ( strcmp( ComandoTeste, DESTROIT_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else
      {
         return TST_CompararInt( RetEsperado,
               TAB_DestroiTab( &tab ),
               "Retorno inesperado ao destruir Tabuleiro" );
      } /* if */
   } else if ( strcmp( ComandoTeste, DETURPAR_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "i", &lido );
      if ( NumLidos != 1 )
      {
         return TST_CondRetParm;
      } else
      {
         TAB_Deturpa( tab, lido );
         return TST_CondRetOK;
      } /* if */
   } else if ( strcmp( ComandoTeste, VERIFICA_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else
      {
         return TST_CompararInt( RetEsperado,
               TAB_VerificaIntegridadeTab( tab ),
               "Retorno inesperado ao verificar Tabuleiro" );
      } /* if */

   } else if ( strcmp( ComandoTeste, RECUPERATAB_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else
      {
         return TST_CompararInt( RetEsperado,
               TAB_RecuperaTabuleiro( &tab ),
               "Retorno inesperado ao recuperar Tabuleiro" );
      } /* if */

   } else if ( strcmp( ComandoTeste, RECUPERAINT_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "si", string, &RetEsperado );
      if ( NumLidos != 2 )
      {
         return TST_CondRetParm;
      } else
      {
         return TST_CompararInt( RetEsperado,
               TAB_RecuperaIntegridadeTab( tab ),
               "Retorno inesperado ao recuperar integridade do Tabuleiro" );
      } /* if */
   } /* if */

   return TST_CondRetParm;
} /* Fim TST_EfetuarComando */
