/***************************************************************************
 *  $MCI Módulo de implementação: TPEC Teste Peca
 *
 *  Arquivo gerado:              TestaPeca.c
 *  Letras identificadoras:      TPEC
 *
 *  Nome da base de software: Testa Peca
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: mr, pct, gb
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor    Data     Observações
 *     2.0     pct 14/out/2016  adição da funcionalidade de criar várias peças.
 *     1.0     mr  11/out/2016  início desenvolvimento.
 *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>

/* header do modulo */
#include "PECA.H"

/* arcabouco */
#include "TST_Espc.h"
#include "GENERICO.h"
#include "LERPARM.h"

/***********************************************************************
 *
 *  $ED Comandos disponíveis:
 *
 *     =criar                 peca	cor   casa      CondRetEsp
 *     =dest                  peca	                CondRetEsp
 *
 ***********************************************************************/

#define CRIARP_LC_CMD "=criar"
#define DESTROIP_LC_CMD "=dest"

/*****************************************************************
 ******
 *
 *  $FC Função: Efetuar operações de teste específicas para Peca
 *      Podem ser criadas ate 4 pecas por vez, sendo uma de cada cor.
 *  $EP Parâmetros
 *     $P ComandoTeste - String contendo o comando
 *
 ******************************************************************
 *****/

/* peca a ser testada */
Peca *peca[4] = { NULL, NULL, NULL, NULL };

TST_tpCondRet TST_EfetuarComando( char *ComandoTeste )
{

   PEC_CondRet RetEsperado;
   char cor;
   short casa;
   int NumLidos = -1;
   char p[50];


   if ( strcmp( ComandoTeste, CRIARP_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "scii", p, &cor, &casa, &RetEsperado );

      if ( NumLidos != 4 )
      {
         return TST_CondRetParm;
      } else {
         if ( cor == 'r' )
         {
            return TST_CompararInt( RetEsperado, PEC_Cria( &peca[0], cor, casa ),
                  "Retorno inesperado ao criar Peca." );
         } /* if */
         if ( cor == 'g' )
         {
            return TST_CompararInt( RetEsperado, PEC_Cria( &peca[1], cor, casa ),
                  "Retorno inesperado ao criar Peca." );
         } /* if */
         if ( cor == 'b' )
         {
            return TST_CompararInt( RetEsperado, PEC_Cria( &peca[2], cor, casa ),
                  "Retorno inesperado ao criar Peca." );
         } /* if */
         if ( cor == 'y' )
         {
            return TST_CompararInt( RetEsperado, PEC_Cria( &peca[3], cor, casa ),
                  "Retorno inesperado ao criar Peca." );
         } /* if */
      }
   } else if ( strcmp( ComandoTeste, DESTROIP_LC_CMD ) == 0 )
   {
      NumLidos = LER_LerParametros( "sci", p, &cor, &RetEsperado );
      if ( NumLidos != 3 )
      {
         return TST_CondRetParm;
      } else {
         if ( cor == 'r' )
         {
            return TST_CompararInt( RetEsperado,
                  PEC_Destroi( &peca[0] ),
                  "Retorno inesperado ao destruir Peca" );
         } /* if */
         if ( cor == 'g' )
         {

            return TST_CompararInt( RetEsperado,
                  PEC_Destroi( &peca[1] ),
                  "Retorno inesperado ao destruir Peca" );
         } /* if */
         if ( cor == 'b' )
         {

            return TST_CompararInt( RetEsperado,
                  PEC_Destroi( &peca[2] ),
                  "Retorno inesperado ao destruir Peca" );
         } /* if */
         if ( cor == 'y' )
         {

            return TST_CompararInt( RetEsperado,
                  PEC_Destroi( &peca[3] ),
                  "Retorno inesperado ao destruir Peca" );
         } /* if */
      } /* if */
   }
   return TST_CondRetParm;
} /* Fim TST_EfetuarComando */
