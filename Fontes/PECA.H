#if !defined PECA_MOD
#define PECA_MOD

/***************************************************************************
*
*  $MCD Módulo de definição: PEC  Peça para jogo Ludo
*
*  Arquivo gerado:              Peca.h
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Ludo
*
*  Projeto: INF 1301 - Ludo
*  Autores: pct, mr, gb
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data       Observações
*      5.0    mr     11/out/2016  Mudança da função MovePeca do módulo Peca para o módulo Rodada (T4).
*      4.0    pct    10/out/2016  Especificação da Função MovePeca.
*      3.0    pct,mr 07/out/2016  Inclusão da Função MovePeca e de funções auxiliares; Padronização do Código.
*      2.0    mr     01/out/2016  Padronização do código inicial. Mudança da estrutura Casa,
*                                 do módulo peça para o módulo Tabuleiro.
*      1.0    pct    23/set/2016  Início desenvolvimento.
*
*  $ED Descrição do módulo
*     Implementa uma peça especificamente para o jogo Ludo.
*     Podem existir múltiplas peças ativas simultaneamente.
*     
*     Uma peça pode ser armazenada em qualquer estrutura de dados.
*     
*     Uma peça só será criada caso o ponteiro referenciado pelo parâmetro p seja nulo.
*     A criação de uma peça implica que ela se encontra fora de jogo, portanto,
*     sua casa está fora do tabuleiro.
* 
*     A destruição de uma peça libera o a área de memória referenciada
*     por p, e em caso de sucesso, p referencia NULL.
*
***************************************************************************/

#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

/***** Tipo de dados exportados pelo módulo *****/

typedef struct Peca Peca;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Peca
*
***********************************************************************/

struct Peca {
	short casa; /* casa corrente */
	char cor;
};

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de Peca
*
***********************************************************************/

typedef enum {
    
  PEC_CondRetOK,
  /* Concluiu corretamente */
  
  PEC_CondRetFaltouMemoria,
  /* Não existe memória disponível */
  
  PEC_CondRetPNaoExiste,
  /* A peça não existe */
  
  PEC_CondRetPJaExiste
  /* A peça já existe */

}PEC_CondRet;

/***********************************************************************
*
*  $FC Função: PEC  &Criar peça
*
*  $ED Descrição da função
*     Cria uma peça para o jogo ludo.
*
*  $EP Parâmetros
*            p        - Referência para um ponteiro do tipo Peca
*                       onde será criado a nova peça via malloc.
*                       A criação só ocorre caso a referência inicial
*                       seja NULL.
*            cor      - Caracter que representa a cor de uma peça.
*            casa     - Número da casa corrente.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
* 
*     Se ocorreu algum erro, por exemplo falta de memória,
*     a função retornará PEC_CondRetFaltouMemoria ou PEC_CondRetPJaExiste.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_CondRet PEC_Cria( Peca **p, char cor, short casaesp );

/***********************************************************************
*
*  $FC Função: P  &Destruir peça
*
*  $ED Descrição da função
*     Destroi uma peça.
*
*  $EP Parâmetros
*            p        - Referência para um ponteiro do tipo Peca
*                       onde será criado a destruido a peça via free.
*                       A destruição só ocorre caso a referência inicial
*                       não seja NULL e a área de memória seja compatível
*                       com free.
*
*  $FV Valor retornado
*     Se executou corretamente retorna PEC_CondRetOK.
* 
*     Se ocorreu algum erro, por exemplo peça inexistente,
*     a função retornará PEC_CondRetPNaoExiste.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

PEC_CondRet PEC_Destroi( Peca **p );

#undef PECA_EXT
#endif
