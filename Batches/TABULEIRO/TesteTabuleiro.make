##################################################
###
### Diretivas de MAKE para o construto: TesteTabuleiro
### Gerado a partir de: TesteTabuleiro.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteTabuleiro


### Nomes de paths

Pobj                 = .
Perr                 = ..\..\Produto
Ph                   = ..\..\Fontes
PDEFAULT             = ..\..\Fontes
Pc                   = ..\..\Fontes

### Nomes de diretórios para geração

Fobj                 = .
Ferr                 = ..\..\Produto
Fh                   = ..\..\Fontes
FDEFAULT             = ..\..\Fontes
Fc                   = ..\..\Fontes

### Macros da plataforma


O       = /D_CRT_SECURE_NO_DEPRECATE
OD      = /Zi /Od /D_CRT_SECURE_NO_DEPRECATE
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox /D_CRT_SECURE_NO_DEPRECATE
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de geração

all : limpa \
   $(Fobj)\LCIRCULAR.obj   $(Fobj)\LISTA.obj   $(Fobj)\PECA.obj \
   $(Fobj)\TABULEIRO.obj   $(Fobj)\TESTATABULEIRO.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\LCIRCULAR.obj :  {$(Pc)}\LCIRCULAR.c \
    {$(PDEFAULT)}../Tabelas/IdTiposEspaco.def {$(PDEFAULT)}CESPDIN.H            {$(PDEFAULT)}CONTA.H              \
    {$(PDEFAULT)}LCIRCULAR.H         
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\LISTA.obj :  {$(Pc)}\LISTA.c \
    {$(PDEFAULT)}LISTA.H             
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\PECA.obj :  {$(Pc)}\PECA.c \
    {$(PDEFAULT)}PECA.H              
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\TABULEIRO.obj :  {$(Pc)}\TABULEIRO.c \
    {$(PDEFAULT)}LCIRCULAR.H          {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}PECA.H               \
    {$(PDEFAULT)}TABAUXILIAR.H        {$(PDEFAULT)}TABULEIRO.H         
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\TESTATABULEIRO.obj :  {$(Pc)}\TESTATABULEIRO.c \
    {$(PDEFAULT)}GENERICO.H           {$(PDEFAULT)}LCIRCULAR.H          {$(PDEFAULT)}LERPARM.H            \
    {$(PDEFAULT)}LISTA.H              {$(PDEFAULT)}PECA.H               {$(PDEFAULT)}TABULEIRO.H          \
    {$(PDEFAULT)}TST_ESPC.H           {$(Ph)}TST_Espc.h          
   cl /D_DEBUG $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\LCIRCULAR.obj   $(Fobj)\LISTA.obj   $(Fobj)\PECA.obj \
   $(Fobj)\TABULEIRO.obj   $(Fobj)\TESTATABULEIRO.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteTabuleiro
###
##################################################

