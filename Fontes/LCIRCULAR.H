#if !defined( LCIRCULAR_MOD )
#define LCIRCULAR_MOD

/***************************************************************************
 *
 *  $MCD Módulo de definição: LCI  Lista Circular genérica
 *
 *  Arquivo gerado:              LCIRCULAR.H
 *  Letras identificadoras:      LCI
 *
 *  Nome da base de software:    Ludo
 *
 *  Projeto: INF 1301 - Ludo
 *  Autores: pct, gb, mr
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data          Observações
 *     7.0     mr       23/nov/2016    Criação e implementação da função verificadora do módulo.
 *     6.0     pct      11/nov/2016    Padronização do código conforme aulas.
 *     5.0     gb       07/out/2016    Especificação final do módulo.
 *     4.0     pct      04/out/2016    Atualização do estilo de código conforme Livro.
 *     3.0     pct      28/set/2016    Correções devido a massa de teste.
 *     2.0     pct      21/set/2016    Criação do arquivo.
 *     1.5     mr       19/set/2016    Correções devido a erros de implementação.
 *     1.0     mr       14/set/2016    Início do desenvolvimento.
 *
 *  $ED Descrição do módulo
 *     Implementa uma lista circular genérica.
 *     Podem existir n listas circulares ativas simultaneamente.
 *     
 *     Uma lista referencia qualquer dado.
 *     
 *     Devido a natureza opaca da lista circular, é de inteira
 *     responsabilidade do programador liberar a memória heap
 *     do dado referenciado pela lista.
 * 
 *     A criação de uma lista só acontece caso a referência de lc seja NULL.
 *     A nova referência será a lista circular.
 *     
 *     A função Pega realiza uma busca na lista circular e referencia ptr
 *     ao valor na lista caso encontrado, se não ptr não sofre mudança. O
 *     parâmetro bytes deve ser passado como o tamanho em bytes do valor
 *     a ser pego.
 * 
 *     A função Remove realiza uma busca na lista circular e remove o elemento
 *     caso o encontre. O parâmetro bytes deve ser passado como o tamanho em bytes
 *     do valor a ser removido.
 *     
 *     A função Proximo mexe o nó corrente da cabeça da lista para o próximo nó.
 * 
 *     A função Anterior mexe o nó corrente da cabeça da lista para o nó anterior.
 * 
 *     A função ObtemCorrente referencia ptr ao valor do nó corrente.
 * 
 *     A destruição de uma lista libera da memória heap apenas as
 *     estruturas internas.
 *
 ***************************************************************************/

#if defined( LCIRCULAR_OWN )
#define LCIRCULAR_EXT
#else
#define LCIRCULAR_EXT extern
#endif


/****************************************************************************
 *  $TC Tipo de Dados: LCI Condições de Retorno
 *
 *  $ED Descrição do Tipo:
 *     Condições de retorno das funções da Lista Circular
 ****************************************************************************/

typedef enum {

   LCI_CondRetOK,                                 
   /*Condicao retornada quando a funcao e executada corretamente*/
   
   LCI_CondRetLNaoExiste,                         
   /*Condicao retornada quando a lista ainda nao foi iniciada*/
   
   LCI_CondRetFaltouMemoria,                      
   /*Condicao retornada quando nao ha espaco para alocacao na memoria*/
   
   LCI_CondRetLVazia,                             
   /*Condicao retornada quando nao ha nenhum valor na lista circular*/
   
   LCI_CondRetNaoAchou,                           
   /*Condicao retornada quando nao se achou o valor procurado na lista*/
   
   LCI_CondRetLJaExiste,                          
   /*Condicao retornada quando tenta se criar uma lista onde outra ja existe*/
   
   LCI_CondRetErroEstrutural,                     
   /*Condicao retornada quando a funcao verificadora detecta um erro irreparavel na estrutura de dados*/
   
   LCI_CondRetErroEstruturalReparavel             
   /*Condicao retornada quando a funcao verificadora detecta um erro reparavel na estrutura de dados*/

} LCI_CondRet;

#ifdef _DEBUG
typedef enum {

   LCI_TipoEspacoCabeca,
   /* Tipo Espaco Cabeca */

   LCI_TipoEspacoNo
   /* Tipo Espaco No */

} LCI_TipoEspaco;
#endif

/***********************************************************************
 *
 *  $TC Tipo de dados: LCI Modos de deturpar
 *
 *
 ***********************************************************************/

#ifdef _DEBUG
typedef enum {

   DeturpaCorrenteNulo,
   /* Anula ponteiro corrente */

   DeturpaInicialNulo,
   /* Anula ponteiro incial */

   DeturpaFinalNulo,
   /* Anula ponterior final */

   DeturpaCorrenteLixo,
   /* Faz corrente apontar para lixo */

   DeturpaInicialLixo,
   /* Faz inicial apontar para lixo */

   DeturpaFinalLixo,
   /* Faz final apontar para lixo */  

   DeturpaTipoNo,
   /* Modifica o tipo do corrente */

   DeturpaTipoInicial,
   /* Modifica o tipo do inicial */

   DeturpaTipoFinal
   /* Modifica o tipo do final */
  
} LCI_tpModosDeturpacao ;
#endif

typedef struct LCircular LCircular;

/****************************************************************************
 *  $FC Função: LCI  &LCI_Cria
 *
 *  $ED Descrição da Função:
 *     Essa função recebe o endereço de um ponteiro onde se deseja criar uma lista
 *     circular duplamente encadeada.
 *
 *  $EP Parâmetros:
 *     lc - Endereço do ponteiro cabeça da LCI.
 *     ExcluiDado - Ponteiro para função de exclusão do dado inserido.
 *  
 *  $FV Valor Retornado:
 *     LCI_CondRetOK - Lista Circular foi criada com sucesso.
 *     LCI_CondRetFaltouMemoria - Não há memória suficiente para a alocação.
 *     LCI_CondRetLJaExiste - Já existe uma lista no endereço recebido.
 *
 ****************************************************************************/

LCI_CondRet LCI_Cria( LCircular **lc, void ( *ExcluiDado ) ( void *ptrdado ) );

/****************************************************************************
 *
 *  $FC Função: LCI  &LCI_Destroi
 *
 *  $ED Descrição da Função:
 *     Destrói a lista circular fornecida, caso exista.
 *
 *  $EP Parâmetros:
 *     lc - Endereço do ponteiro cabeça da LCI.
 *
 *  $FV Valor Retornado:
 *     LCI_CondRetOK - Destruição foi sucedida.
 *     LCI_CondRetLNaoExiste - Não há ponteiro no endereço recebido.
 *
 ****************************************************************************/

LCI_CondRet LCI_Destroi( LCircular **lc );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_ProcurarElem
 *
 *  $ED Descrição da Função:
 *     Realiza uma busca pelo valor recebido como parâmetro na lista e preenche
 *     o segundo parâmetro com o valor encontrado, ou, caso o valor não seja
 *     encontrado, com NULL. Corrente referencia valor adquirido.
 *
 *  $EP Parâmetros:
 *     lc     - É o parâmetro que receberá a cabeça da lista. Este parâmetro é
 *              passado por referência.
 *     ptr    - É o parâmetro que será referenciado com o resultado da busca, 
 *              ou seja, receberá um endereço. Este parâmetro é passado por 
 *              referência.
 *     valor  - É o parâmetro que receberá o valor a ser buscado. Este parâmetro
 *              é passado por referência.
 *
 *  $FV Valor Retornado:
 *     LCI_CondRetLVazia       - A LCI que foi passada está vazia.
 *     LCI_CondRetLNaoExiste   - Não há LCI no endereço recebido.
 *     LCI_CondRetNaoAchou     - O valor procurado não está na lista.
 *     LCI_CondRetOK           - A busca foi um sucesso. Valor está na referência.
 *
 ****************************************************************************/

LCI_CondRet LCI_ProcurarElem( LCircular *lc, void **ptr, void *valor );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_Insere
 *
 *  $ED Descrição da Função:
 *     Cria um novo nó com o valor recebido como parâmetro e insere-o na LCI, imediatamente 
 *     após o ultimo nó inserido.
 *
 *  $EP Parâmetros:
 *     lc      - É o parâmetro que receberá a cabeça da lista. Este parâmetro é passado 
 *               por referência.
 *     valor   - É o parâmetro que receberá o valor a ser inserido. Este parâmetro
 *               é passado por referência.
 *     
 *  $FV Valor Retornado:
 *     LCI_CondRetLNaoExiste      - Não existe LCI no endereço recebido.
 *     LCI_CondRetFaltouMemoria   - Faltou memória para a alocação do nó.
 *     LCI_CondRetOK              - A inserção foi feita com sucesso.
 *
 ****************************************************************************/

LCI_CondRet LCI_Insere( LCircular *lc, void *valor );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_RemoveElemento
 *
 *  $ED Descrição da Função:
 *     Realiza uma busca pelo valor recebido como parâmetro e remove o nó em que
 *     este foi encontrado.
 *
 *  $EP Parâmetros:
 *     lc      - É o parâmetro que receberá a cabeça da lista. Este parâmetro é 
 *               passado por referência.
 *     valor   - É o parâmetro que receberá o valor a ser procurado. Este parâmetro
 *               é passado por referência.
 *     
 *  $FV Valor Retornado:
 *     LCI_CondRetLNaoExiste      - Não existe LCI no endereço recebido.
 *     LCI_CondRetNaoAchou        - O valor a ser retirado não está contido na LCI.
 *     LCI_CondRetOK              - A remoção foi feita com sucesso.
 *     LCI_CondRetVazia           - A LCI está vazia.
 *
 ****************************************************************************/

LCI_CondRet LCI_RemoveElemento( LCircular *lc, void *valor );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_TrocarPeloPróximo
 *
 *  $ED Descrição da Função:
 *     Troca o nó apontado como cabeça da LCI por seu sucessor.
 *
 *  $EP Parâmetros:
 *     lc      - É o parâmetro que receberá a cabeça da lista. Este parâmetro é passado 
 *               por referência.
 *     
 *  $FV Valor Retornado:
 *     LCI_CondRetLNaoExiste      - Não existe LCI no endereço recebido.
 *     LCI_CondRetOK              - A troca foi feita com sucesso.
 *     LCI_CondRetLVazia          - A lista está vazia.
 *
 ****************************************************************************/

LCI_CondRet LCI_TrocarPeloProximo( LCircular *lc );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_TrocarPeloAnterior
 *
 *  $ED Descrição da Função:
 *     Troca o nó apontado como cabeça da LCI por seu antecessor.
 *
 *  $EP Parâmetros:
 *     lc      - É o parâmetro que receberá a cabeça da lista. Este parâmetro é passado 
 *               por referência.
 *
 *  $FV Valor Retornado:
 *     LCI_CondRetLNaoExiste      - Não existe LCI no endereço recebido.
 *     LCI_CondRetOK              - A troca foi feita com sucesso.
 *     LCI_CondRetLVazia          - A lista está vazia.
 *
 ****************************************************************************/

LCI_CondRet LCI_TrocarPeloAnterior( LCircular *lc );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_ObtemCorrente
 *
 *  $ED Descrição da Função:
 *     Referencia o parâmetro ptr com o valor do nó apontado pela cabeça da LCI.
 *
 *  $EP Parâmetros:
 *     lc     - É o parâmetro que receberá a cabeça da lista. Este parâmetro é
 *              passado por referência.
 *     ptr    - É o parâmetro que será referenciado com o valor do nó apontado
 *              pela cabeça da LCI.
 *
 *  $FV Valor Retornado:
 *     LCI_CondRetLVazia       - A LCI que foi passada está vazia.
 *     LCI_CondRetLNaoExiste   - Não há LCI no endereço recebido.
 *     LCI_CondRetOK           - Valor está na referência.
 *
 ****************************************************************************/

LCI_CondRet LCI_ObtemCorrente( LCircular *lc, void **ptr );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_VerificaLista
 *
 *  $ED Descrição da Função:
 *     Essa função instrumentada verifica se a lista circular 
 *     tem todas as suas propriedades corretas. Caso contrário, essa função
 *     avisa que há um erro.
 *
 *  $EP Parâmetros:
 *     lc     - É o parâmetro que receberá a cabeça da lista. Este parâmetro é
 *              passado por referência.
 *
 *  $FV Valor Retornado:
 *     LCI_CondRetErroEstrutural - A lista tem algum erro estrutural irreparavel.
 *     LCI_CondRetErroEstruturalReparavel - A lista tem algum erro estrutural reparavel.
 *     LCI_CondRetOK             - A lista está em estado correto.
 *
 ****************************************************************************/

LCI_CondRet LCI_VerificaLista( LCircular *lc );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_RecuperaLista
 *
 *  $ED Descrição da Função:
 *     Recebe a lista e conserta quaisquer erros estruturais que podem gerar
 *     erros no resto do programa e retirá-lo de seu estado de corretude.
 *
 *  $EP Parâmetros:
 *     lc     - É o parâmetro que receberá a cabeça da lista. Este parâmetro é
 *              passado por referência.
 *
 *  $FV Valor Retornado:
 *     Retorna o número de alterações que foram realizadas para consertar a
 *     estrutura da lista circular e fazê-la voltar para seu estado de corretude.
 *
 ****************************************************************************/

int LCI_RecuperaLista( LCircular *lc );

/****************************************************************************
 *
 *  $FC Função: LCI &LCI_Deturpar
 *
 *  $ED Descrição da Função:
 *     Recebe a lista e introduz erros controlados para que possamos testar as
 *     funções de recuperação por avanço.
 *
 *  $EP Parâmetros:
 *     lc           - É o parâmetro que receberá a cabeça da lista. Este parâmetro é
 *                    passado por referência.
 *     ModoDeturpar - É o parâmetro que indica qual deturpação será realizada na
 *                    Lista Circular passada para a função
 *
 ****************************************************************************/

#ifdef _DEBUG
void LCI_Deturpar( LCircular *lc , LCI_tpModosDeturpacao ModoDeturpar );
#endif

#undef LCIRCULAR_EXT
#endif
