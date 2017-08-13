#if (!defined DESENHA_MOD)
#define DESENHA_MOD

/***************************************************************************
 *
 *  $MCD Módulo de definição: DES  Desenha a interface do jogo
 *
 *  Arquivo gerado:              DESENHA.H
 *  Letras identificadoras:      DES
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: pct, gb, mr
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data          Observações
 *      3.0    mr      04/dez/2016     Inspeção do código
 *      2.0    gb      03/dez/2016     Especificação do módulo
 *      1.0    pct     01/dez/2016     Implementação inicial
 *
 *  $ED Descrição do módulo
 *     Desenha a inteface do jogo de ludo.
 *     Apenas uma instância do jogo pode estar desenhado no console.
 *     
 *     O desenho da interface é baseado no módulo rodada, que gerencia o jogo,
 *     além das estruturas implementadas em outros módulos.
 *     
 *     A interface será redesenhada a cada rodada, afim de atualizar a tela para
 *     o jogador, contextualidada nas possibilidades da jogada.
 * 
 *     A função ObterOrdem determina, no início da partida, qual será a ordem dos
 *     jogadores. Os jogadores, em sentido horário, jogam os dados e essa ordem é
 *     definida.
 *     
 *     A função LimpaPrompt reseta o console, possibilitando um redesenho nesse
 *     console, utilizada em diversas funções desse módulo.
 *     
 *     A função DesenhaPlacar, ao ser chamada, atualiza o placar, redesenhando-o
 *     no console.
 *     
 *     A função DesenhaTabuleiro desenha as casas e as peças que estão envolvidas
 *     no jogo.
 *
 *     A função PerguntaDado indica para o jogador que o dado será jogado, obtém
 *     o valor que o jogador tirou no dado e o coloca no ponteiro passado à função.
 *     
 *     A função DesenhaOrdem exibe a ordem dos jogadores nessa partida.
 *     
 *     A função DesenhaAreaPecas exibe no console quais são as peças que estão em
 *     jogo para que o jogador tome uma decisão.
 *
 ***************************************************************************/

#if defined( DESENHA_OWN )
        #define DESENHA_EXT
#else
        #define DESENHA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

#include "TABULEIRO.H"

/****************************************************************************
 *  $FC Função: DES  &DES_ObterOrdem
 *
 *  $ED Descrição da Função:
 *     Essa função joga o dado para cada jogador, no sentido horário, e depois
 *     determina a ordem dos jogadores à partir dos resultados obtidos.  
 *
 *  $EP Parâmetros:
 *     ordem - Vetor de caracteres indicando a ordem dos jogadores.
 *     qtdjogadores - Número inteiro indicando quantos jogadores estão ativos na 
 *     partida.
 *
 ****************************************************************************/

void DES_ObterOrdem( char ordem[], int qtdjogadores );

/****************************************************************************
 *  $FC Função: DES  &DES_LimpaPrompt
 *
 *  $ED Descrição da Função:
 *     Essa função limpa a tela, permitindo que a interface seja desenhada no seu
 *     próximo estado.
 *
 ****************************************************************************/

void DES_LimpaPrompt( void );

/****************************************************************************
 *  $FC Função: DES  &DES_DesenhaPlacar
 *
 *  $ED Descrição da Função:
 *     Essa função exibe o placar atual da partida.
 *
 *  $EP Parâmetros:
 *     ScoreRed - Indica o placar do jogador vermelho na partida.
 *     ScoreGreen - Indica o placar do jogador verde na partida.
 *     ScoreBlue - Indica o placar do jogador azul na partida.
 *     ScoreYellow - Indica o placar do jogador amarelo na partida.
 *
 ****************************************************************************/

void DES_DesenhaPlacar( short ScoreRed, short ScoreGreen, short ScoreBlue, short ScoreYellow );

/****************************************************************************
 *  $FC Função: DES  &DES_DesenhaTabuleiro
 *
 *  $ED Descrição da Função:
 *     Essa função exibe o tabuleiro e as peças em jogo, nas suas respectivas
 *     posições.
 *
 *  $EP Parâmetros:
 *     tb - Tabuleiro da partida, administrado por outros módulos.
 *
 ****************************************************************************/

void DES_DesenhaTabuleiro( Tabuleiro *tb );

/****************************************************************************
 *  $FC Função: DES  &DES_PerguntaDado
 *
 *  $ED Descrição da Função:
 *     Essa função pega o resultado obtido no dado jogado, administrado por outro
 *     módulo. 
 *
 *  $EP Parâmetros:
 *     resultado - É o ponteiro no qual será colocado o resultado obtido no dado.
 *
 ****************************************************************************/

void DES_PerguntaDado( short *resultado );

/****************************************************************************
 *  $FC Função: DES  &DES_DesenhaOrdem
 *
 *  $ED Descrição da Função:
 *     Essa função exibe a ordem dos jogadores na partida, estabelecido pela função
 *     ObterOrdem. 
 *
 *  $EP Parâmetros:
 *     ordem - Vetor de caracteres indicando a ordem dos jogadores, a qual será
 *             exibida por esta função.
 *
 ****************************************************************************/

void DES_DesenhaOrdem( char ordem[] );

/****************************************************************************
 *  $FC Função: DES  &DES_DesenhaAreaPecas
 *
 *  $ED Descrição da Função:
 *     Desenha em uma área específica da interface tadas as peças e suas
 *     respectivas casas no momento da partida. 
 *
 *  $EP Parâmetros:
 *     ordem - Vetor de caracteres indicando a ordem dos jogadores.
 *     qtdjogadores - Número inteiro indicando quantos jogadores estão ativos na
 *     partida.
 *
 ****************************************************************************/

void DES_DesenhaAreaPecas( Tabuleiro *tab );

#undef DESENHA_EXT

#endif
