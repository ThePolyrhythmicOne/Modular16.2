#if (!defined RODADA_MOD)
#define RODADA_MOD

/***************************************************************************
 *
 *  $MCD Módulo de definição: ROD  Rodada
 *
 *  Arquivo gerado:              RODADA.H
 *  Letras identificadoras:      ROD
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: pct, gb, mr
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor     Data           Observações
 *       3.0   mr,gb,pct  02/dez/2016     Inspeção do código
 *       2.0   gb         24/nov/2016     Especificação do módulo
 *       1.0   pct        22/nov/2016     Implementação inicial
 *
 *  $ED Descrição do módulo
 *     Administra o andamento de cada rodada, cuidando da ordem dos jogadores, da movimentação
 *     das peças e de quais jogadas são possíveis.
 *     
 *     A função RealizaRodada lida com cada jogada da partida, controlando a ordem e oferecendo
 *     as opções de ação para cada jogador. É a única função desse módulo.
 *
 ***************************************************************************/

#if defined( RODADA_OWN )
        #define RODADA_EXT
#else
        #define RODADA_EXT extern
#endif

/***********************************************************************
 *
 *  $TC Tipo de dados: ROD Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções do Rodada
 *
 ***********************************************************************/

typedef enum {

   ROD_CondRetOK,
   /* Concluiu corretamente */

   ROD_CondRetJogadaInvalida,
   /* A Jogada não é Valida. ( Usada internamente no módulo ) */

   ROD_CondRetJogadaValida,
   /* A Jogada é Valida. ( Usada internamente no módulo */

   ROD_CondRetTNaoExiste,
   /* O Tabuleiro não existe */

   ROD_CondRetPMoveErro,
   /* Erro ao tentar mover peça ( Usada internamente no módulo ) */

   ROD_CondRetErro,
   /* Detectado um erro */

   ROD_CondRetVitoria
   /* Um determinado jogador foi declarado vitorioso */

} ROD_CondRet;

/***** Declarações exportadas pelo módulo *****/

#include "TABULEIRO.H"

/****************************************************************************
 *  $FC Função: ROD  &ROD_RealizaRodada
 *
 *  $ED Descrição da Função:
 *     Essa função recebe o tabuleiro da partida, a ordem dos jogadores, o placar e a quantidade
 *     de jogadores, sendo então responsável por cada jogada da partida. Deve oferecer aos
 *     participantes as opções de cada jogada para que eles tomem as decisões cabíveis.
 *
 *  $EP Parâmetros:
 *     tb - Ponteiro para o tabuleiro da partida.
 *     ordem - Vetor de char indicando a ordem dos jogadores na partida.
 *     score - Vetor de short indicando a pontuação de cada jogador na partida.
 *     qtdjogadores - Número inteiro que indica quantos jogadores estão participando da partida.
 *  
 *  $FV Valor Retornado:
 *     ROD_CondRetOK - Condição de retorno que indica que a rodada foi realizada com sucesso.
 *     ROD_CondRetErro - Condição de retorno que indica que houve algum erro na execução da 
 *                       rodada.
 *     ROD_CondRetVitoria - Condição de retorno que indica que algum dos jogadores ganhou a
 *                          partida em questão.
 *
 ****************************************************************************/

ROD_CondRet ROD_RealizaRodada( Tabuleiro *tb, char *ordem, short score[], int qtdjogadores );

#undef RODADA_EXT

#endif
