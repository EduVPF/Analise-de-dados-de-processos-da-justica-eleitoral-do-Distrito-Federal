🧾 TP01 - Processamento de Processos Judiciais em C

Este projeto foi desenvolvido com o objetivo de manipular e analisar dados de processos judiciais utilizando a linguagem C. Ele realiza a leitura de um arquivo .csv com informações de processos e permite uma série de operações úteis via menu interativo.

📌 Funcionalidades

Carregamento de processos a partir de um arquivo CSV

Ordenação por ID (crescente)

Ordenação por Data de Ajuizamento (decrescente)

Contagem de processos por ID de Classe

Contagem de assuntos únicos

Listagem de processos com múltiplos assuntos

Cálculo de dias em tramitação

Salvamento dos dados ordenados em novos arquivos CSV

📂 Estrutura de Arquivos

main.c → Menu principal com interação do usuário

processo.c → Lógica de leitura, ordenação e manipulação dos dados

processo.h → Header com a estrutura do Processo e protótipos

entrada.csv → Arquivo com os processos a serem carregados

README.md → Este documento

⚙️ Como Compilar e Executar

Compile os arquivos usando um terminal ou prompt de comando:
gcc main.c processo.c -o tp01

Execute o programa:
./tp01 (Linux/macOS) ou tp01.exe (Windows)

📄 Formato Esperado do Arquivo entrada.csv

Cada linha do arquivo deve seguir o seguinte padrão:

ID do processo, número do processo (entre aspas), data de ajuizamento (AAAA-MM-DD HH:MM:SS.000), ID da classe, um ou mais assuntos entre chaves, e o ano da eleição.

Exemplo de linha válida:
405278031, "00000781820176070091", 2017-08-16 17:40:56.000, {12559}, {11778}, 0

🖥️ Interface de Menu (exibida no terminal)

--- MENU ---

Ordenar por ID (crescente) e salvar em CSV

Ordenar por Data (decrescente) e salvar em CSV

Contar processos por ID de Classe

Contar assuntos únicos

Listar processos com múltiplos assuntos

Mostrar dias em tramitacao para cada processo

Sair

📌 Detalhes Técnicos

Leitura de arquivos com funções como fgets e strtok

Uso de structs e arrays dinâmicos para armazenar os dados

Manipulação de datas com struct tm, mktime e difftime

Escrita de arquivos CSV com fprintf

