#if !defined( TABULEIRO_MOD )
#define TABULEIRO_MOD

/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: TAB  Tabuleiro Ludo
 *
 *  Arquivo gerado:              Tabuleiro.h
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: mr, pct, gb
 *
 *  $HA Hist�rico de evolu��o:
 *    Vers�o  Autor    Data      Observa��es
 *     6.0     mr    13/dez/2016  Implementa��o da assertiva de recupera��o por avan�o (hidra).
 *     5.0     pct   17/out/2016  Ajuste da estrutura Tabuleiro.
 *     4.0     pct   08/out/2016  Implementa��o da fun��o DestroiTab.
 *     3.0     pct   05/out/2016  Padroniza��o do c�digo conforme o Livro.
 *     2.0     mr    01/out/2016  Inclus�o de novas condi��es de retorno.
 *     1.0     mr    30/set/2016  In�cio desenvolvimento.
 *
 *  $ED Descri��o do m�dulo
 *     Implementa o tabuleiro do jogo de ludo cl�ssico.
 *     Pode apenas existir um �nico tabuleiro por vez.
 *
 *     A cria��o de uma tabuleiro s� acontece caso a refer�ncia de tab seja NULL.
 *     A nova refer�ncia ser� o tabuleiro.
 *
 *     A fun��o Cria apenas aloca a mem�ria necess�ria para a inicializa��o do tabuleiro.
 *
 ***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Constantes exportadas pelo m�dulo *****/

#define CAMINHO_NEUTRO 8
#define CAMINHO_FINAL_Y 7
#define CAMINHO_FINAL_B 6
#define CAMINHO_FINAL_G 5
#define CAMINHO_FINAL_R 4
#define PGREEN 3
#define PYELLOW 2
#define PBLUE 1
#define PRED 0

/***** Declara��es exportadas pelo m�dulo *****/

#include "LCIRCULAR.H"
#include "LISTA.H"
#include "PECA.H"

/***** Tipo de dados exportados pelo m�dulo *****/

typedef struct Tabuleiro Tabuleiro;
typedef struct Casa Casa;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Tabuleiro
*
***********************************************************************/

struct Tabuleiro{
   LIS_tppLista tblr;
   void *hidra[9];
   Tabuleiro *secundario;
};

/***********************************************************************
*
*  $TC Tipo de dados: TAB Casa
*
***********************************************************************/

struct Casa {
   short casa;
   Peca *p;
};

/***********************************************************************
 *
 *  $TC Tipo de dados: TAB Condi��es de retorno
 *
 *
 *  $ED Descri��o do tipo
 *     Condi��es de retorno das fun��es do Tabuleiro
 *
 ***********************************************************************/

typedef enum {

   TAB_CondRetOK,
    /* Concluiu corretamente */

   TAB_CondRetTNaoExiste,
    /* O Tabuleiro n�o existe */

   TAB_CondRetFalhaInicializacao,
    /* Houve uma falha na fun��o de inicializa��o */

   TAB_CondRetFalhaCriacao,
    /* Houve uma falha na fun��o de cria��o */

   TAB_CondRetTJaExiste,
    /* Tabuleiro j� existe */

   TAB_CondRetFaltouMemoria,
    /* Mem�ria n�o foi suficiente para a aloca��o */

   TAB_CondRetCNaoExiste,
    /* Casa n�o existe */

   TAB_CondRetCJaExiste,
    /* Casa j� existe */

   TAB_CondRetFalhaDestruicao,
   /* Houve uma falha na destruicao */
   
   TAB_CondRetTJaInicializado,
   /* Tabuleiro j� inicializado */
   
   TAB_CondRetErro
   /* Erro ao realizar um a��o no tabuleiro */

} TAB_CondRet;

#ifdef _DEBUG
typedef enum {

   DeturparTabuleiroNulo,
   /* Destroi o Tabuleiro */
   
   DeturparUmaCabeca,
   /* Destroi apenas uma cabeca */
   
   DeturparDuasCabecas,
   /* Destroi duas cabecas */
   
   DeturparCabecasListas
   /* Destroi as cabecas da lista guardadas na estrutura do tabuleiro */

} TAB_tpModosDeturpacao;
#endif
/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Criar Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Cria o tabuleiro para o jogo de ludo.
 *
 *  $EP Par�metros
 *            tab         - Refer�ncia para um ponteiro do tipo Tabuleiro
 *                          onde ser� criado o novo tabuleiro via malloc.
 *                          A cria��o s� ocorre caso a refer�ncia inicial
 *                          seja NULL.
 *            ordem       - String que representa a ordem dos jogadores.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *
 *     Se ocorreu algum erro, por exemplo falta de mem�ria,
 *     a fun��o retornar� TAB_CondRetFalhaCriacao ou TAB_CondRetTJaExiste.
 *     N�o ser� dada mais informa��o quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_criaTabuleiro( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Inicializar Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Inicializa o tabuleiro para o jogo de ludo, construido todas as 
 *     52 casas do caminho neutro e as 24 dos caminhos finais, alem das
 *	    pe�as inicialmente fora de jogo.
 *
 *  $EP Par�metros
 *            tab       - Refer�ncia para um ponteiro do tipo Tabuleiro
 *                        onde ser� incializado o novo tabuleiro.
 *                        A inicialia��o s� ocorre caso a refer�ncia inicial
 *                        n�o seja NULL.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *
 *     Se ocorreu algum erro, por exemplo falta de mem�ria,
 *     a fun��o retornar� TAB_CondRetFalhaInicializacao.
 *     N�o ser� dada mais informa��o quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_inicializaTabuleiro( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Destroi Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Destroi o Tabuleiro criado com TAB_criaTabuleiro
 *
 *  $EP Par�metros
 *            tb       -  Refer�ncia para um ponteiro do tipo Tabuleiro
 *                        onde ser� destruido o tabuleiro.
 *                        A destrui��o s� ocorre caso a refer�ncia inicial
 *                        n�o seja NULL.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *     A referencia para o Tabuleiro � alterada para NULL em caso de Sucesso.
 *     Se ocorreu algum erro, a fun��o retornar� TAB_CondRetFalhaDestruicao 
 *     ou TAB_CondRetTNaoExiste.
 *     N�o ser� dada mais informa��o quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_DestroiTab( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Retorna Lista Do Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Retorna um ponteiro opaco para o elemento idxLista da lista de
 *     de cabe�as do tabuleiro.
 *
 *  $EP Par�metros
 *            tab       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                         tabuleiro da partida, cuja refer�ncia na estru-
 *                         tura adicional ser� retornada.
 *            idxLista  -  Inteiro que indica qual elemento retornar.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna um ponteiro ptr para o elemento na
 *     lista.
 *     Caso haja algum erro na execu��o da fun��o, � retornado NULL.
 *
 ***********************************************************************/
 
void* TAB_RetornaListaDoTabuleiro ( Tabuleiro *tab, int idxLista );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Recupera Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Conserta o Tabuleiro caso a refer�ncia seja NULL.
 *
 *  $EP Par�metros
 *            tb       -  Ponteiro para ponteiro de tipo tabuleiro, que 
 *                        aponta para o tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execu��o da fun��o, � retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_RecuperaTabuleiro( Tabuleiro **tb );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Recupera Integridade Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Conserta o Tabuleiro caso haja erros que violem a integridade estrutural
 *     do tabuleiro referenciado.
 *
 *  $EP Par�metros
 *            tb       -  Ponteiro de tipo tabuleiro, que 
 *                        aponta para o tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execu��o da fun��o, � retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_RecuperaIntegridadeTab( Tabuleiro *tb );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Verifica Integridade Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Verifica se h� erros que violem a integridade estrutural do tabuleiro
 *     referenciado.
 *
 *  $EP Par�metros
 *            tb       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                        tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execu��o da fun��o, � retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_VerificaIntegridadeTab( Tabuleiro *tb );

/***********************************************************************
 *
 *  $FC Fun��o: TAB  &Deturpa Tabuleiro
 *
 *  $ED Descri��o da fun��o
 *     Induz erros na estrutura tabuleiro referenciada, afim de testar a fun��o
 *     verificadora e a fun��o de recupera��o.
 *
 *  $EP Par�metros
 *            tb       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                        tabuleiro da partida, alvo da deturpa��o.
 *            modo     -  Determina qual o tipo de deturpa��o que ser� realizada
 *                        no tabuleiro referenciado.
 *
 ***********************************************************************/

#ifdef _DEBUG
void TAB_Deturpa( Tabuleiro *tb, TAB_tpModosDeturpacao modo );
#endif

#undef TABULEIRO_EXT

#endif
