@ECHO OFF
REM Cria .make e o .exe

pushd .

if ""=="%1" goto erro
set FILENAME="%1"
del %FILENAME%.exe"
del *.make
del *.err
del *.list
del *.build
echo Chamando vsvars32.bat
call vsvars32.bat
gmake /c%FILENAME%.comp"
call geraexe.bat %FILENAME%
echo Compilado com SUCESSO
goto sai

:erro
echo Falta nome do arquivo
echo Uso -> Compila.bat <NOME_SEM_EXTENSAO>
goto sai

:sai
popd


