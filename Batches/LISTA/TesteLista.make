##################################################
###
### Diretivas de MAKE para o construto: TesteLista
### Gerado a partir de: TesteLista.comp
###
### ----- Arquivo gerado, NÃO EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TesteLista


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
   $(Fobj)\LISTA.obj   $(Fobj)\TESTLIS.obj \
   Construto

### Limpar arquivos

limpa :
   if exist $(Ferr)\$(NOME).err  del $(Ferr)\$(NOME).err


### Dependências de módulos objeto a compilar

$(Fobj)\LISTA.obj :  {$(Pc)}\LISTA.c \
    {$(PDEFAULT)}LISTA.H             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\TESTLIS.obj :  {$(Pc)}\TESTLIS.c \
    {$(Ph)}Generico.h           {$(Ph)}LerParm.h            {$(Ph)}Lista.h              \
    {$(Ph)}TST_Espc.h          
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Terminação

Construto : \
   $(Fobj)\LISTA.obj   $(Fobj)\TESTLIS.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TesteLista
###
##################################################

