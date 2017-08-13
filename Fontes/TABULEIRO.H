#if !defined( TABULEIRO_MOD )
#define TABULEIRO_MOD

/***************************************************************************
 *
 *  $MCD Módulo de definição: TAB  Tabuleiro Ludo
 *
 *  Arquivo gerado:              Tabuleiro.h
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: mr, pct, gb
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor    Data      Observações
 *     6.0     mr    13/dez/2016  Implementação da assertiva de recuperação por avanço (hidra).
 *     5.0     pct   17/out/2016  Ajuste da estrutura Tabuleiro.
 *     4.0     pct   08/out/2016  Implementação da função DestroiTab.
 *     3.0     pct   05/out/2016  Padronização do código conforme o Livro.
 *     2.0     mr    01/out/2016  Inclusão de novas condições de retorno.
 *     1.0     mr    30/set/2016  Início desenvolvimento.
 *
 *  $ED Descrição do módulo
 *     Implementa o tabuleiro do jogo de ludo clássico.
 *     Pode apenas existir um único tabuleiro por vez.
 *
 *     A criação de uma tabuleiro só acontece caso a referência de tab seja NULL.
 *     A nova referência será o tabuleiro.
 *
 *     A função Cria apenas aloca a memória necessária para a inicialização do tabuleiro.
 *
 ***************************************************************************/

#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Constantes exportadas pelo módulo *****/

#define CAMINHO_NEUTRO 8
#define CAMINHO_FINAL_Y 7
#define CAMINHO_FINAL_B 6
#define CAMINHO_FINAL_G 5
#define CAMINHO_FINAL_R 4
#define PGREEN 3
#define PYELLOW 2
#define PBLUE 1
#define PRED 0

/***** Declarações exportadas pelo módulo *****/

#include "LCIRCULAR.H"
#include "LISTA.H"
#include "PECA.H"

/***** Tipo de dados exportados pelo módulo *****/

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
 *  $TC Tipo de dados: TAB Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do Tabuleiro
 *
 ***********************************************************************/

typedef enum {

   TAB_CondRetOK,
    /* Concluiu corretamente */

   TAB_CondRetTNaoExiste,
    /* O Tabuleiro não existe */

   TAB_CondRetFalhaInicializacao,
    /* Houve uma falha na função de inicialização */

   TAB_CondRetFalhaCriacao,
    /* Houve uma falha na função de criação */

   TAB_CondRetTJaExiste,
    /* Tabuleiro já existe */

   TAB_CondRetFaltouMemoria,
    /* Memória não foi suficiente para a alocação */

   TAB_CondRetCNaoExiste,
    /* Casa não existe */

   TAB_CondRetCJaExiste,
    /* Casa já existe */

   TAB_CondRetFalhaDestruicao,
   /* Houve uma falha na destruicao */
   
   TAB_CondRetTJaInicializado,
   /* Tabuleiro já inicializado */
   
   TAB_CondRetErro
   /* Erro ao realizar um ação no tabuleiro */

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
 *  $FC Função: TAB  &Criar Tabuleiro
 *
 *  $ED Descrição da função
 *     Cria o tabuleiro para o jogo de ludo.
 *
 *  $EP Parâmetros
 *            tab         - Referência para um ponteiro do tipo Tabuleiro
 *                          onde será criado o novo tabuleiro via malloc.
 *                          A criação só ocorre caso a referência inicial
 *                          seja NULL.
 *            ordem       - String que representa a ordem dos jogadores.
 *
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *
 *     Se ocorreu algum erro, por exemplo falta de memória,
 *     a função retornará TAB_CondRetFalhaCriacao ou TAB_CondRetTJaExiste.
 *     Não será dada mais informação quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_criaTabuleiro( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Função: TAB  &Inicializar Tabuleiro
 *
 *  $ED Descrição da função
 *     Inicializa o tabuleiro para o jogo de ludo, construido todas as 
 *     52 casas do caminho neutro e as 24 dos caminhos finais, alem das
 *	    peças inicialmente fora de jogo.
 *
 *  $EP Parâmetros
 *            tab       - Referência para um ponteiro do tipo Tabuleiro
 *                        onde será incializado o novo tabuleiro.
 *                        A inicialiação só ocorre caso a referência inicial
 *                        não seja NULL.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *
 *     Se ocorreu algum erro, por exemplo falta de memória,
 *     a função retornará TAB_CondRetFalhaInicializacao.
 *     Não será dada mais informação quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_inicializaTabuleiro( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Função: TAB  &Destroi Tabuleiro
 *
 *  $ED Descrição da função
 *     Destroi o Tabuleiro criado com TAB_criaTabuleiro
 *
 *  $EP Parâmetros
 *            tb       -  Referência para um ponteiro do tipo Tabuleiro
 *                        onde será destruido o tabuleiro.
 *                        A destruição só ocorre caso a referência inicial
 *                        não seja NULL.
 *
 *  $FV Valor retornado
 *     Se executou corretamente retorna TAB_CondRetOK.
 *     A referencia para o Tabuleiro é alterada para NULL em caso de Sucesso.
 *     Se ocorreu algum erro, a função retornará TAB_CondRetFalhaDestruicao 
 *     ou TAB_CondRetTNaoExiste.
 *     Não será dada mais informação quanto ao problema ocorrido.
 *
 ***********************************************************************/

TAB_CondRet TAB_DestroiTab( Tabuleiro **tab );

/***********************************************************************
 *
 *  $FC Função: TAB  &Retorna Lista Do Tabuleiro
 *
 *  $ED Descrição da função
 *     Retorna um ponteiro opaco para o elemento idxLista da lista de
 *     de cabeças do tabuleiro.
 *
 *  $EP Parâmetros
 *            tab       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                         tabuleiro da partida, cuja referência na estru-
 *                         tura adicional será retornada.
 *            idxLista  -  Inteiro que indica qual elemento retornar.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna um ponteiro ptr para o elemento na
 *     lista.
 *     Caso haja algum erro na execução da função, é retornado NULL.
 *
 ***********************************************************************/
 
void* TAB_RetornaListaDoTabuleiro ( Tabuleiro *tab, int idxLista );

/***********************************************************************
 *
 *  $FC Função: TAB  &Recupera Tabuleiro
 *
 *  $ED Descrição da função
 *     Conserta o Tabuleiro caso a referência seja NULL.
 *
 *  $EP Parâmetros
 *            tb       -  Ponteiro para ponteiro de tipo tabuleiro, que 
 *                        aponta para o tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execução da função, é retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_RecuperaTabuleiro( Tabuleiro **tb );

/***********************************************************************
 *
 *  $FC Função: TAB  &Recupera Integridade Tabuleiro
 *
 *  $ED Descrição da função
 *     Conserta o Tabuleiro caso haja erros que violem a integridade estrutural
 *     do tabuleiro referenciado.
 *
 *  $EP Parâmetros
 *            tb       -  Ponteiro de tipo tabuleiro, que 
 *                        aponta para o tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execução da função, é retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_RecuperaIntegridadeTab( Tabuleiro *tb );

/***********************************************************************
 *
 *  $FC Função: TAB  &Verifica Integridade Tabuleiro
 *
 *  $ED Descrição da função
 *     Verifica se há erros que violem a integridade estrutural do tabuleiro
 *     referenciado.
 *
 *  $EP Parâmetros
 *            tb       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                        tabuleiro da partida.
 *
 *  $FV Valor retornado
 *     Se executou corretamente, retorna TAB_CondRetOK.
 *     Caso haja algum erro na execução da função, é retornado TAB_CondRetErro.
 *
 ***********************************************************************/

TAB_CondRet TAB_VerificaIntegridadeTab( Tabuleiro *tb );

/***********************************************************************
 *
 *  $FC Função: TAB  &Deturpa Tabuleiro
 *
 *  $ED Descrição da função
 *     Induz erros na estrutura tabuleiro referenciada, afim de testar a função
 *     verificadora e a função de recuperação.
 *
 *  $EP Parâmetros
 *            tb       -  Ponteiro de tipo tabuleiro, que aponta para o
 *                        tabuleiro da partida, alvo da deturpação.
 *            modo     -  Determina qual o tipo de deturpação que será realizada
 *                        no tabuleiro referenciado.
 *
 ***********************************************************************/

#ifdef _DEBUG
void TAB_Deturpa( Tabuleiro *tb, TAB_tpModosDeturpacao modo );
#endif

#undef TABULEIRO_EXT

#endif
