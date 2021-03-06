/***************************************************************************
 *  $MCI M�dulo de implementa��o: PEC Pe�a
 *
 *  Arquivo gerado:              PECA.C
 *  Letras identificadoras:      PEC
 *
 *  Projeto: Ludo - INF1301
 *  Autores: pct, mr, gb
 *
 *  $HA Hist�rico de evolu��o:
 *    Vers�o  Autor      Data        Observa��es
 *    5.0      mr       11/out/2016    Mudan�a da fun��o MovePeca do m�dulo Peca para o m�dulo Rodada
 *    4.0      pct      10/out/2016    Finaliza��o das Fun��es MovePeca.
 *    3.0      pct,mr   07/out/2016    Implementa��o das Fun��es MovePeca e 
 *                                     Padroniza��o do C�digo.
 *    2.0      mr       01/out/2016    Padroniza��o do c�digo inicial
 *	                                    Mudan�a da estrutura Casa, do m�dulo pe�a
 *	                                    para o m�dulo Tabuleiro.
 *    1.0	   pct      28/set/2016    In�cio do desenvolvimento.
 *
 ***************************************************************************/

#include <stdlib.h>
#define  PECA_OWN
#include "PECA.H"
#undef   PECA_OWN

/************* Fun��o: PEC &Criar Peca ******************/
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


/************* Fun��o: PEC &Destroi Peca ******************/
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
