#if !defined( TABULEIROAUX_H )
#define TABULEIROAUX_H

/***************************************************************************
 *
 *  $MCD Módulo de definição: TAB  Tabuleiro Ludo
 *
 *  Arquivo gerado:              TABAUXILIAR.H
 *  Letras identificadoras:      TAB
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: pct, gb, mr
 *
 *  $HA Histórico de evolução:
 *    Versão  Autor    Data      Observações
 *
 *  $ED Descrição do módulo
 *     Funções usadas no módulo DESENHA, porém definidas no módulo tabuleiro para evitar
 *     que o módulo DESENHA precise usar os módulos LCIRCULAR e LISTA.
 *
 *     A função PreenheVetorNeutro preenche o caminho neutro com os números correspondentes às suas
 *     posições no vetor. Caso uma peça esteja na casa, ela é preenchida com -1.
 *
 *     A função PreencheVetorPecas atribui às posições nos vetores Red, Blue, Green, Yellow com os
 *     códigos caso a peça esteja disponível ou com char 254 caso a peça não esteja disponível. Se
 *     flag for 1, as peças estão no tabuleiro, e a posição será preenchida com sua posição no caminho
 *     neutro.
 *
 *     A função PreencheVetorFinal atribui às posições dos vetores de caminhos finais com os números
 *     de seus trajetos e -1 caso haja uma peça nessa posição.
 *
 ***************************************************************************/

/***** Declarações exportadas pelo header *****/

#include "TABULEIRO.H"

 /***********************************************************************
 *
 *  $FC Função: TAB  &Preenche Vetor Neutro
 *
 *  $ED Descrição da função
 *     Essa função preenche o vetor do caminho neutro com as suas posições no trajeto, e -1 caso
 *     haja uma peça nessa casa.
 *
 *  $EP Parâmetros
 *            tb          - É um ponteiro para o tabuleiro da partida. 
 *            Neutro      - É o vetor de inteiros que indica o caminho neutro.
 *
 ***********************************************************************/
 
void TAB_PreencheVetorNeutro( Tabuleiro *tb, int Neutro[] );

/***********************************************************************
 *
 *  $FC Função: TAB  &Preenche Vetor Peças
 *
 *  $ED Descrição da função
 *     Essa função preenche os vetores das peças (Red, Blue, Green, Yellow) com a letra
 *     de cada peça e char 254 caso a peça não esteja em movimento. Caso flag seja 1 
 *     a função preenche o vetor com a casa em que cada peça está ao invés da cor. 
 *
 *  $EP Parâmetros
 *            tb          - Ponteiro para o tabuleiro da partida.
 *            Red         - Vetor de inteiros correspondente às peças vermelhas.
 *            Blue        - Vetor de inteiros correspondente às peças azuis.
 *            Green       - Vetor de inteiros correspondente às peças verdes.
 *            Yellow      - Vetor de inteiros correspondente às peças amarelas.
 *            flag        - Indica se as peças estão no tabuleiro ou não.
 *
 ***********************************************************************/

void TAB_PreencheVetorPecas( Tabuleiro* tb, int Red[], int Blue[], int Green[], int Yellow[], int flag );

/***********************************************************************
 *
 *  $FC Função: TAB  &Preenche Vetor Final
 *
 *  $ED Descrição da função
 *     Essa função preenche os vetores dos caminhos finais (Red, Blue, Green, Yellow) com os números
 *     das casas e -1 caso haja uma peça nessa casa.
 *
 *  $EP Parâmetros
 *            tb          - Ponteiro para o tabuleiro da partida.
 *            Red         - Vetor de inteiros correspondente ao caminho final vermelho.
 *            Blue        - Vetor de inteiros correspondente ao caminho final azul.
 *            Green       - Vetor de inteiros correspondente ao caminho final verde.
 *            Yellow      - Vetor de inteiros correspondente ao caminho final amarelo.
 *
 ***********************************************************************/

void TAB_PreencheVetorFinal( Tabuleiro* tb, int Red[], int Blue[], int Green[], int Yellow[] );

#endif
