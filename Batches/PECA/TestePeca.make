##################################################
###
### Diretivas de MAKE para o construto: TestePeca
### Gerado a partir de: TestePeca.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TestePeca


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
   $(Fobj)\PECA.obj   $(Fobj)\TESTAPECA.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\PECA.obj :  {$(Pc)}\PECA.c \
    {$(PDEFAULT)}PECA.H              
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\TESTAPECA.obj :  {$(Pc)}\TESTAPECA.c \
    {$(Ph)}GENERICO.h           {$(Ph)}LERPARM.h            {$(PDEFAULT)}PECA.H               \
    {$(Ph)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\PECA.obj   $(Fobj)\TESTAPECA.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TestePeca
###
##################################################

