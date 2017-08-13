/***************************************************************************
 *  $MCI Módulo de implementação: LCI  Lista Circular
 *
 *  Arquivo gerado:              LCIRCULAR.C
 *  Letras identificadoras:      LCI
 *
 *  Projeto: Ludo - INF1301
 *  Autores: pct, mr, gb
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *      7.0   pct,mr 16/dez/2016   Finalização das assertivas, tratadores, deturpação.
 *      6.0   gb     14/dez/2016   Introdução dos marcadores de contagem.
 *      5.0   mr     23/nov/2016   Criação e implementação da função verificadora do módulo.
 *      4.0   pct    11/nov/2016   Padronização do código conforme aula
 *      3.0   pct    04/out/2016   Atualização do estilo de código conforme livro.
 *      2.0   pct    29/set/2016   Correções devido a massa de teste
 *      1.0   pct    21/set/2016   Implementação inicial do código; Pré Teste;
 *
 ***************************************************************************/

#include   <stdlib.h>
#include   <string.h>
#include   <stdio.h>
#define    LCIRCULAR_OWN
#include   "LCIRCULAR.H"
#undef     LCIRCULAR_OWN

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#include "../Tabelas/IdTiposEspaco.def"
#endif

#ifdef _DEBUG
/* Espaço de dados lixo usado ao testar */
static char EspacoLixo[ 256 ] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
#endif

#ifdef _DEBUG
LCI_CondRet LCI_VerificaLista( LCircular *lc ); /* forward declaration */
#endif

/***********************************************************************
 *
 *  $TC Tipo de dados: LC Nó da Lista
 *
 ***********************************************************************/

typedef struct No No;

struct No {
   void *valor;
   No *anterior;
   No *posterior;
};

/***********************************************************************
 *
 *  $TC Tipo de dados: LC Descritor da cabeça de lista circular
 *
 *
 ***********************************************************************/

struct LCircular {
   No *corrente;
   No *inicial;
   No *final;
   int NumElementos;
   void *Hidra[3]; /* Indices correspondem a inicial, final e corrente respectivamente */
   void ( *ExcluiDado ) ( void *ptrdado );
};

/************* Função: LCI &Criar Lista ******************/
LCI_CondRet LCI_Cria( LCircular **lc, void ( *ExcluiDado ) ( void *ptrdado ) )
{

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_CriaLC" ) ;
   #endif   

   if ( *lc != NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_CriaLCJaExiste" ) ;
      #endif   
      return LCI_CondRetLJaExiste;
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_CriaLCPonteiroVazio" ) ;
      #endif
      *lc = ( LCircular * ) malloc( sizeof( LCircular ) );
      if ( *lc == NULL ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_CriaLCFaltouEspaco" ) ;
         #endif
         return LCI_CondRetFaltouMemoria;
      }
      (*lc)->inicial = NULL;
      (*lc)->corrente = NULL;
      (*lc)->final = NULL;
      (*lc)->NumElementos = 0;
      (*lc)->ExcluiDado = ExcluiDado;

      #ifdef _DEBUG
      CED_DefinirTipoEspaco( lc , LCI_TipoEspacoCabeca );
      #endif

      return LCI_CondRetOK;
   } /* if */

} /* Fim LCI_Cria */

/************* Função: LCI &Destroi Lista ***************/
LCI_CondRet LCI_Destroi( LCircular **lc )
{

   LCircular *aux;
   No *noaux;

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_DestroiLC" );
   #endif

   if ( *lc == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_DestroiLCInexistente" ) ;
      #endif 
      return LCI_CondRetLNaoExiste;
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_DestroiLCExistente" ) ;
      #endif 
      if ( (*lc)->inicial == (*lc)->final ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_DestroiLCSo1No" ) ;
         #endif 
         if( (*lc)->inicial != NULL )
         {
            free( (*lc)->inicial );
         }
         aux = *lc;
         *lc = NULL;
         free( aux );
         return LCI_CondRetOK;
      } else {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_DestroiLCMultNos" ) ;
         #endif
         noaux = (*lc)->final;
         //if ( noaux != NULL )
         //{
         (*lc)->final = noaux->anterior;
         //} /* if */
         free( noaux );
         return LCI_Destroi( lc );
      } /* if */
   } /* if */

} /* Fim LCI_Destroi */

/************** Função: LC &Cria Nó ****************/
static No *CriaNo( No *anterior, No *posterior, void *valor )
{

   No *a = ( No * ) malloc( sizeof( No ) );

   #ifdef _DEBUG
   CED_DefinirTipoEspaco( a , LCI_TipoEspacoNo );
   CNT_CONTAR( "LCI_CriaNo" );
   #endif

   if ( a != NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_CriaNoSucesso" ) ;
      #endif 
      a->anterior = anterior;
      a->posterior = posterior;
      a->valor = valor;
      return a;
   } /* if */
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_CriaNoFaltaMemoria" ) ;
   #endif 
   return NULL;

} /* Fim CriaNo */

/************** Função: LC &Insere Elemento *****************/
LCI_CondRet LCI_Insere( LCircular *lc, void *valor )
{
   No *a;
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_Insere" );
   #endif

   if ( lc == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_InsereLCInexistente" );
      #endif
      return LCI_CondRetLNaoExiste;
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_InsereLCExistente" );
      #endif
      /* primeira insercao */
      if ( lc->inicial == NULL ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_InsereLCVazia" );
         #endif
         a = CriaNo( NULL, NULL, valor );
         if ( a == NULL ) 
         {
            #ifdef _DEBUG 
            CNT_CONTAR( "LCI_InsereLCFaltaMemoria0Elementos" );
            #endif
            return LCI_CondRetFaltouMemoria;
         } /* if */
         lc->inicial = a;
         lc->final = a;
         lc->corrente = lc->final;
         lc->inicial->posterior = a;
         lc->inicial->anterior = a;
         lc->final->anterior = a;
         lc->final->posterior = a;
         lc->NumElementos += 1;
         lc->Hidra[0] = lc->inicial;
         lc->Hidra[1] = lc->final;
         lc->Hidra[2] = lc->corrente;
         return LCI_CondRetOK;
      } else {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_InsereLCNaoVazia" );
         #endif
         /* segunda insercao */
         if (lc->inicial == lc->final) 
         {
           #ifdef _DEBUG
            CNT_CONTAR( "LCI_InsereLCSo1No" );
            #endif
            a = CriaNo( lc->final, lc->inicial, valor );
            if ( a == NULL ) 
            {
               #ifdef _DEBUG
               CNT_CONTAR( "LCI_InsereLCFaltaMemoria1Elemento" );
               #endif
               return LCI_CondRetFaltouMemoria;
            } /* if */
            lc->corrente = a;
            lc->final = a;
            lc->Hidra[1] = lc->final;
            lc->Hidra[2] = lc->corrente;
            lc->inicial->anterior = a;
            lc->inicial->posterior = a;
            lc->NumElementos += 1;
            return LCI_CondRetOK;
         } else {
            #ifdef _DEBUG
            CNT_CONTAR( "LCI_InsereLCMultNo" );
            #endif
            /* insercao generica */
            a = CriaNo( lc->final, lc->inicial, valor );
            if ( a == NULL ) 
            {
               #ifdef _DEBUG
               CNT_CONTAR( "LCI_InsereLCFaltaMemoria2+Elemento" );
               #endif
               return LCI_CondRetFaltouMemoria;
            } /* if */
            lc->final->posterior = a;
            lc->inicial->anterior = a;
            lc->corrente = a;
            lc->final = a;
            lc->Hidra[1] = lc->final;
            lc->Hidra[2] = lc->corrente;
            lc->NumElementos += 1;
            return LCI_CondRetOK;
         } /* if */
      } /* if */
   } /* if */

} /* Fim LCI_Insere */

/****** Função: LCI &Busca ( recebe um ponteiro para o final e busca contra-relogio ) *******/
static No *BuscaNo( LCircular *lc, No *no, void *valor )
{

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_BuscaNo" );
   #endif

   if ( no == lc->inicial ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_BuscaNoLCSo1No" );
      #endif
      /* compara byte por byte o valor do nó e o ponteiro opaco valor */
      if ( no->valor == valor )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_BuscaNoLCUnicoDaListaeoProcurado" );
         #endif
         return no;
      } else {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_BuscaNoLCUnicoDaListaNaoeoProcurado" );
         #endif
         return NULL;
      } /* if */
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_BuscaNoLC+2Nos" );
      #endif
      /* compara byte por byte o valor do nó e o ponteiro opaco valor */
      if ( no->valor == valor ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_BuscaNoLCElemProcuradoNoNoPassado" );
         #endif
         return no;
      } else {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_BuscaNoLCElemProcuradoNaoNoPassado" );
         #endif
         return BuscaNo( lc, no->anterior, valor );
      } /* if */
   } /* if */

} /* Fim BuscaNo */

/********************* Função: LCI &Procurar Elemento *************************/
LCI_CondRet LCI_ProcurarElem( LCircular *lc, void **ptr, void *valor )
{
   No *aux;

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_ProcuraElem" );
   #endif

   if ( lc == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ProcuraElemLCNaoExiste" );
      #endif
      return LCI_CondRetLNaoExiste;
   } /* if */
   if ( lc->inicial == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ProcuraElemLCVazia" );
      #endif
      return LCI_CondRetLVazia;
   } /* if */
   /* Busca Nó idêntico a valor */
   if ( ( aux = BuscaNo( lc, lc->final, valor ) ) == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ProcuraElemLCElemNaoEncontrado" );
      #endif
      return LCI_CondRetNaoAchou;
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ProcuraElemLCElemEncontrado" );
      #endif
      lc->corrente = aux;
      lc->Hidra[2] = lc->corrente;
      *ptr = aux->valor;
      return LCI_CondRetOK;
   } /* if */

} /* Fim LCI_Pega */

/*************** Função: LCI &RemoveElemento ******************/
LCI_CondRet LCI_RemoveElemento( LCircular *lc, void *valor )
{
   No *aux;

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_RemoveElem" );
   #endif

   if ( lc == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemLCInexistente" );
      #endif
      return LCI_CondRetLNaoExiste;
   } /* if */
   if ( lc->inicial == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemLCVazia" );
      #endif
      return LCI_CondRetLVazia;
   } /* if */
   /* Busca Nó idêntico a valor */
   if ( ( aux = BuscaNo( lc, lc->final, valor ) ) == NULL ) 
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemLCElemNaoEncontrado" );
      #endif
      return LCI_CondRetNaoAchou;
   } else {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemLCElemEncontrado" );
      #endif
      /* remocao de uma lista com um unico elemento */
      if ( aux == lc->inicial && aux == lc->final ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_RemoveElemLCRemoveUnicoDaLista" );
         #endif
         lc->inicial = NULL;
         lc->final = NULL;
         lc->corrente = NULL;
         lc->Hidra[0] = lc->inicial;
         lc->Hidra[1] = lc->final;
         lc->Hidra[2] = lc->corrente;
         free( aux );
         return LCI_CondRetOK;
      }
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemLC+2Elemento" );
      #endif
      /* remocao generica */
      aux->anterior->posterior = aux->posterior;
      aux->posterior->anterior = aux->anterior;
      if ( aux == lc->inicial )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_RemoveElemLCElemePrimeiro" );
         #endif
         lc->inicial = aux->posterior;
         lc->corrente = aux->posterior;
      } else if ( aux == lc->final ) 
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_RemoveElemLCElemeUltimo" );
         #endif
         lc->final = aux->anterior;
         lc->corrente = aux->anterior;
      } else {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_RemoveElemLCElemNoMeio" );
         #endif
         lc->corrente = aux->anterior;
      } /* if */
      if ( lc->ExcluiDado != NULL )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_RemoveElemLCExcluiDadoNaoNulo" );
         #endif
         lc->ExcluiDado( aux );
      } /* if */
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_RemoveElemlCExecucaoCorreta" );
      #endif
      lc->Hidra[0] = lc->inicial;
      lc->Hidra[1] = lc->final;
      lc->Hidra[2] = lc->corrente;
      return LCI_CondRetOK;
   } /* if */

} /* Fim LCI_Remove */

/********** Função: LCI &Trocar Corrente pelo Próximo ****************/
LCI_CondRet LCI_TrocarPeloProximo( LCircular *lc )
{

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_TrocaPeloProx" );
   #endif

   if ( lc == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_TrocaPeloProxLCNaoExiste" );
      #endif
      return LCI_CondRetLNaoExiste;
   } /* if */
   if ( lc->corrente == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_TrocaPeloProxLCVazia" );
      #endif
      return LCI_CondRetLVazia;
   } /* if */
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_TrocaPeloProxLCNaoVazia" );
   #endif
   lc->corrente = lc->corrente->posterior;
   lc->Hidra[2] = lc->corrente;
   return LCI_CondRetOK;

} /* Fim LCI_Proximo */

/************* Função: LCI &Trocar Corrente pelo Anterior ***************/
LCI_CondRet LCI_TrocarPeloAnterior( LCircular *lc )
{

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_TrocaPeloAnt" );
   #endif

   if ( lc == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_TrocaPeloAntLCInexistente" );
      #endif
      return LCI_CondRetLNaoExiste;
   } /* if */
   if ( lc->corrente == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_TrocaPeloAntLCVazia" );
      #endif
      return LCI_CondRetLVazia;
   } /* if */
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_TrocaPeloAntLCNaoVazia" );
   #endif
   lc->corrente = lc->corrente->anterior;
   lc->Hidra[2] = lc->corrente;
   return LCI_CondRetOK;

} /* Fim LCI_Anterior */

/************ Função: LCI &Nó Corrente ************/
LCI_CondRet LCI_ObtemCorrente( LCircular *lc, void **ptr )
{

   #ifdef _DEBUG
   CNT_CONTAR( "LCI_ObtemCorrente" );
   #endif

   if ( lc == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ObtemCorrenteLCInexistente" );
      #endif
      return LCI_CondRetLNaoExiste;
   } /* if */
   if ( lc->corrente == NULL )
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_ObtemCorrenteLCVazia");
      #endif
      return LCI_CondRetLVazia;
   } /* if */
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_ObtemCorrenteLCNaoVazia" );
   #endif
   *ptr = lc->corrente->valor;
   return LCI_CondRetOK;
} /* Fim LCI_ObtemCorrente */

/************ Função: LCI &RecuperaLista ************/
int LCI_RecuperaLista( LCircular *lc )
{
   int modificacoes = 0;
   LCI_CondRet retorno;
   #ifdef _DEBUG
      CNT_CONTAR( "LCI_Recupera" );
   #endif
   do {
      /* Verifica se inicial é NULL ou é lixo */
      if ( lc->inicial == NULL || lc->inicial != lc->Hidra[0] )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LCI_RecuperaIniNuloOuLixo" );
         #endif
         lc->inicial = ( No * ) lc->Hidra[0];
         modificacoes += 1;
      } /* if */
      /* Verifica se final é NULL ou é lixo */
      if ( lc->final == NULL || lc->final != lc->Hidra[1] )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LCI_RecuperaFimNuloOuLixo" );
         #endif
         lc->final = ( No * ) lc->Hidra[1];
         modificacoes += 1;
      } /* if */
      /* Verifica se corrente é NULL ou é lixo */
      if ( lc->corrente == NULL || lc->corrente != lc->Hidra[2] )
      {
         #ifdef _DEBUG
            CNT_CONTAR( "LCI_RecuperaCurrNuloOuLixo" );
         #endif
         lc->corrente = ( No * ) lc->Hidra[2];
         modificacoes += 1;
      } /* if */
      #ifdef _DEBUG
	  if ( LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->inicial ) || LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->final )
		  || LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->corrente ) )
	  {
        CNT_CONTAR( "LCI_RecuperaTipoErrado" );
		  CED_DefinirTipoEspaco( lc->inicial, LCI_TipoEspacoNo );
		  CED_DefinirTipoEspaco( lc->final, LCI_TipoEspacoNo );
		  CED_DefinirTipoEspaco( lc->corrente, LCI_TipoEspacoNo );
		  modificacoes += 1;
	  } /* if */
      #endif
   } while ( ( retorno = LCI_VerificaLista( lc ) ) == LCI_CondRetErroEstruturalReparavel ); /* while */

   return modificacoes;

} /* LCI_RecuperaLista */

/************ Função: LCI &VerificaLista ************/
LCI_CondRet LCI_VerificaLista( LCircular *lc )
{
   int totalElem = 0;
   No *aux;
   #ifdef _DEBUG
   CNT_CONTAR( "LCI_VerificaLC" );
   #endif
   if ( lc == NULL ) /* Verifica se a cabeça existe */
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_VerificaLCInexistente" );
      #endif
      printf( "\nTentou verificar cabeca inexistente." );
      return LCI_CondRetLNaoExiste;
   } /* if */

   #ifdef _DEBUG
   if ( LCI_TipoEspacoCabeca != CED_ObterTipoEspaco( lc ) ) /* Checa se o tipo do espaço controlado pelo cespdin bate com o tipo passado */
   {
      CNT_CONTAR( "LCI_VerificaLCTipoCabecaErrado" );
      printf( "\nTipo do espaço de dados nao eh cabeca de lista circular." );
      return LCI_CondRetErroEstrutural;
   } /* if */
   #endif
   #ifdef _DEBUG
   if ( !CED_VerificarEspaco( lc , NULL ) ) /* verifica se o espaco usado pela cabeca esta ok */
   {
      CNT_CONTAR( "LCI_VerificaLCErroNoEspacoDaCabeca" );
      printf( "\nControle do espaco acusou erro.\n" );
      return LCI_CondRetErroEstrutural;
   } /* if */
   #endif
   if ( lc->NumElementos == 0 ) /* Lista vazia */
   {
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_VerificaLCVazia" );
      #endif
      if ( lc->corrente != NULL ) /* Lista vazia tem no corrente nao nulo */
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCVaziaCorrenteNaoNulo" );
         #endif
         printf( "\nLista vazia tem no corrente nao nulo." );
         return LCI_CondRetErroEstrutural;
      } /* if */
      if ( lc->final != NULL ) /* Verifica se a lista vazia tem no final nao nulo */
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCVaziaFinalNaoNulo" );
         #endif
         printf( "\nLista vazia tem no final nao nulo." );
         return LCI_CondRetErroEstrutural;
      } /* if */
      if ( lc->inicial != NULL ) /* Verifica se a lista vazia tem no inicial nao nulo */
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCVaziaInicioNaoNulo" );
         #endif
         printf( "\nLista vazia tem no inicial nao nulo." );
         return LCI_CondRetErroEstrutural;
      } /* if */
   } else { /* Lista não vazia */ 
      #ifdef _DEBUG
      CNT_CONTAR( "LCI_VerificaLCNaoVazia" );
      #endif
	  
	  #ifdef _DEBUG
	  if ( LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->inicial ) )
	  {
		 CNT_CONTAR( "LCI_VerificaLCInicioNulo" );
		 printf("\nControle do espaco acusou erro.");
         return LCI_CondRetErroEstruturalReparavel;
	  } /* if */
	  #endif
	  if ( lc->inicial == NULL || lc->inicial != lc->Hidra[0] )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCInicioNulo" );
         #endif
		 printf("\nControle do espaco acusou erro.");
         return LCI_CondRetErroEstruturalReparavel;
      } /* if */
	  
	  #ifdef _DEBUG
	  if ( LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->corrente ) )
	  {
		 CNT_CONTAR( "LCI_VerificaLCErroCorrenteNulo" );
         printf("\nControle do espaco acusou erro.");
         return LCI_CondRetErroEstruturalReparavel;
	  } /* if */
	  #endif
      if ( lc->corrente == NULL || lc->corrente != lc->Hidra[2] )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCErroCorrenteNulo" );
         #endif
         printf("\nControle do espaco acusou erro.");
         return LCI_CondRetErroEstruturalReparavel;
      } /* if */
	  #ifdef _DEBUG
	  if ( LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->corrente ) )
	  {
		 CNT_CONTAR( "LCI_VerificaLCErroFimNulo" );
		 printf("\nControle do espaco acusou erro.");
         return LCI_CondRetErroEstruturalReparavel;
	  } /* if */
	  #endif
      if ( lc->final == NULL || lc->final != lc->Hidra[1] )
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaLCErroFimNulo" );
         #endif
         return LCI_CondRetErroEstruturalReparavel;
      } /* if */
      totalElem++;
      lc->corrente = lc->inicial;
      while ( lc->corrente != lc->final )
      {
         LCI_TrocarPeloProximo( lc );
         aux = ( No * ) lc->Hidra[2];
         
         #ifdef _DEBUG
         if ( LCI_TipoEspacoNo != CED_ObterTipoEspaco( lc->corrente ) ) /* Verifica se o tipo de dado do no corrente e de lista circular */
         {
            CNT_CONTAR( "LCI_VerificaLCEspacoDadosNaoEhNo" );
            printf( "\nTipo do espaco de dados nao eh no de lista circular." );
            return LCI_CondRetErroEstrutural;
         } /* if */
         #endif
         if ( lc->corrente != lc->Hidra[2] ) /* Checa o espaço do nó */
         {
            #ifdef _DEBUG
            CNT_CONTAR( "LCI_VerificaLCErroCorrenteNulo" );
            #endif
            printf("\nControle do espaco acusou erro.");
            return LCI_CondRetErroEstruturalReparavel;
         } /* if */
         totalElem++;
      } /* while */

      if ( ( totalElem ) < lc->NumElementos ) /* Checa se o número de nos percorrido é igual ao guardado na cabeca da lista */
      {
         #ifdef _DEBUG
         CNT_CONTAR( "LCI_VerificaListaLCErroNumElementos" );
         #endif
         printf( "\nNumero de elementos percorridos nao condiz com o numero esperado." );
         return LCI_CondRetErroEstrutural;
      } /* if */
   } /* if */
   return LCI_CondRetOK;
} /* Fim LCI_VerificaLista */

#ifdef _DEBUG
/********** Função: LCI  &Deturpar Lista Circular ************/
void LCI_Deturpar( LCircular *lc , LCI_tpModosDeturpacao ModoDeturpar )
{
   CNT_CONTAR( "LCI_Deturpar" );
   if ( lc == NULL )
   {
      CNT_CONTAR( "LCI_DeturparLCInexistente" );
      return;
   } /* if */

   switch ( ModoDeturpar ) {

      /* Anula ponteiro corrente */
      case DeturpaCorrenteNulo :
         {
            CNT_CONTAR( "LCI_DeturparCorrenteNulo" );
            lc->corrente = NULL ;
            break ;
         } /* fim ativa: Anula ponteiro corrente */

         /* Anula ponteiro inicial */
      case DeturpaInicialNulo :
         {
            CNT_CONTAR( "LCI_DeturparInicioNulo" );
            lc->inicial = NULL ;
            break ;
         } /* fim ativa: Anula ponteiro Inicial */

         /* Anula ponteiro final */
      case DeturpaFinalNulo :
         {
            CNT_CONTAR( "LCI_DeturparFinalNulo" );
            lc->final = NULL ;
            break ;
         } /* fim ativa: Anula ponteiro final */

         /* Faz corrente apontar para lixo */
      case DeturpaCorrenteLixo :
         {
            CNT_CONTAR( "LCI_DeturparCorrenteLixo" );
            lc->corrente = ( No * )( EspacoLixo ) ;
            break ;
         } /* fim ativa: Faz corrente apontar para lixo */

         /* Faz inicial apontar para lixo */
      case DeturpaInicialLixo :
         {
            CNT_CONTAR( "LCI_DeturparInicioLixo" );
            lc->inicial = ( No * )( EspacoLixo ) ;
            break ;
         } /* fim ativa: Faz incial apontar para lixo */

         /* Faz final apontar para lixo */
      case DeturpaFinalLixo :
         {
            CNT_CONTAR( "LCI_DeturparFinalLixo" );
            lc->final = ( No * )( EspacoLixo ) ;
            break ;

         } /* fim ativa: Faz final apontar para lixo */

      default :
         if ( lc->corrente != NULL )
         {
            CNT_CONTAR( "LCI_DeturparCorrenteNaoNulo" );
            switch ( ModoDeturpar ) 
			{
               /* Modifica tipo nó corrente */
               case DeturpaTipoNo :
                  {
                     CNT_CONTAR( "LCI_DeturparTipoNo" );
                     CED_DefinirTipoEspaco( lc->corrente , CED_ID_TIPO_VALOR_NULO ) ;
                     break ;
                  } /* fim ativa: Modifica tipo nó corrente */
                  /* Modifica tipo nó inicial */
               case DeturpaTipoInicial :
                  {
                     CNT_CONTAR( "LCI_DetuparTipoInicial" );
                     CED_DefinirTipoEspaco( lc->inicial , CED_ID_TIPO_VALOR_NULO ) ;
                     break ;
                  } /* fim ativa: Modifica tipo nó inicial */

                  /* Modifica tipo nó final */
               case DeturpaTipoFinal :
                  {
                     CNT_CONTAR( "LCI_DeturparTipoFinal" );
                     CED_DefinirTipoEspaco( lc->final , CED_ID_TIPO_VALOR_NULO ) ;
                     break ;
                  } /* fim ativa: Modifica tipo nó final */
			} /* switch */
		 } /* if */
   }
} /* Fim LCI_Deturpar */
#endif
