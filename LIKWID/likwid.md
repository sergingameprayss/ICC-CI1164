===== GUIA DE CONFIGURAÇÃO DO LINUX PARA USO DO LIKWID NO DINF ===============

1. Em uma janela shell, editar o arquivo '${HOME}/.bashrc' e acrescentar
   linhas abaixo:

       export LIKWID_HOME="/home/soft/likwid"
 
       if [ -d "${LIKWID_HOME}" ] ; then
	   PATH="$PATH:${LIKWID_HOME}/bin:${LIKWID_HOME}/sbin"
	   export LIKWID_LIB="${LIKWID_HOME}/lib"
	   export LIKWID_INCLUDE="${LIKWID_HOME}/include"
	   export LIKWID_MAN="${LIKWID_HOME}/man"
	   export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${LIKWID_LIB}"
	   export MANPATH="$MANPATH:${LIKWID_MAN}"
       fi

2. Na mesma janela shell, após a edição acima, executar o comando abaixo:

       source ${HOME}/.bashrc
       
3. Fazer download dos arquivos abaixo:

   https://www.inf.ufpr.br/nicolui/grad/ci164/Docs/exemplos/teste.c
   https://www.inf.ufpr.br/nicolui/grad/ci164/Docs/exemplos/teste.sh

4. Executar o comando abaixo:

      bash ./teste.sh

   Caso  a  configuração esteja  correta,  serão  criados dois  arquivos:
   (FLOPS_DP_Otimiz.log e FLOPS_DP_SemOtimiz.log) contendo os resultados
   gerados pelo LIKWID.

5. Opções para compilação de programas:

   gcc -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -c <prog.c>
   gcc -o <prog> <prog.o> -L${LIKWID_LIB} -llikwid


   * Nos códigos-fonte deve-se colocar

        #include <likwid.h>


===== GUIA DE CONFIGURAÇÃO DE FREQUENCIA DE RELÓGIO EM LINUX ===============

1. Para  aumentar a frequência de  relógio, execute a seguinte  linha de
   comando (onde  <CORE> é  a identificação  do core  do qual  se deseja
   alterar a frequência):

   echo "performance" > /sys/devices/system/cpu/cpufreq/policy<CORE>/scaling_governor

2. Para retornar à frequência original execute:

   echo "powersave" > /sys/devices/system/cpu/cpufreq/policy<CORE>/scaling_governor 


===== GUIA DE ACESSO REMOTO ÀS MÁQUINAS DOS LABORATÓRIOS DINF ===============

Nos acessos abaixo, sempre use seu login/senha nas máquinas do DINF

1. Copiar seus arquivos locais para a máquina 'macalan':

   scp -rp <sua_pasta_com_exercicio> <user_dinf>@macalan.c3sl.ufpr.br:.

2. Acessar 'macalan' com

   ssh <user_dinf>@macalan.c3sl.ufpr.br

3. Uma vez na 'macalan'

   ssh <maq_LAB_DINF>

   onde <maq_LAB_DINF> = máquinas  indicadas pelo professor no enunciado
                         de um trabalho.

4. ATENÇÃO: Lembre-se de RECOMPILAR SEUS PROGRAMAS em <maq_LAB_DINF>

