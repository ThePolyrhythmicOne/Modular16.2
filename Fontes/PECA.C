/***************************************************************************
 *  $MCI Módulo de implementação: PEC Peça
 *
 *  Arquivo gerado:              PECA.C
 *  Letras identificadoras:      PEC
 *
 *  Projeto: Ludo - INF1301
 *  Autores: pct, mr, gb
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor      Data        Observações
 *    5.0      mr       11/out/2016    Mudança da função MovePeca do módulo Peca para o módulo Rodada
 *    4.0      pct      10/out/2016    Finalização das Funções MovePeca.
 *    3.0      pct,mr   07/out/2016    Implementação das Funções MovePeca e 
 *                                     Padronização do Código.
 *    2.0      mr       01/out/2016    Padronização do código inicial
 *	                                    Mudança da estrutura Casa, do módulo peça
 *	                                    para o módulo Tabuleiro.
 *    1.0	   pct      28/set/2016    Início do desenvolvimento.
 *
 ***************************************************************************/

#include <stdlib.h>
#define  PECA_OWN
#include "PECA.H"
#undef   PECA_OWN

/************* Função: PEC &Criar Peca ******************/
PEC_CondRet PEC_Cria( Peca **p, char cor, short casa )
{

   if(*p != NULL)
   {
      return PEC_CondRetPJaExiste;
   } else {
      *p = ( Peca * ) malloc( sizeof( Peca ) );
      if(*p == NULL)
         return PEC_CondRetFaltouMemoria;
      (*p)->casa = casa;
      (*p)->cor = cor;
      return PEC_CondRetOK;
   } /* if */

} /* Fim PEC_Cria */


/************* Função: PEC &Destroi Peca ******************/
PEC_CondRet PEC_Destroi( Peca **p )
{

   if( *p == NULL )
   {
      return PEC_CondRetPNaoExiste;
   } /* if */
   free( *p );
   *p = NULL;
   return PEC_CondRetOK;

} /* Fim PEC_Destroi */
