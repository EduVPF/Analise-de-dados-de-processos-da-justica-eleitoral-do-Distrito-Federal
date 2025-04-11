🧾 TP01 - Processamento de Processos Judiciais em C
Este projeto foi desenvolvido com o objetivo de manipular e analisar dados de processos judiciais utilizando a linguagem C. Ele realiza a leitura de um arquivo .csv com informações de processos e permite uma série de operações úteis via menu interativo.

📌 Funcionalidades
📥 Carregamento de processos a partir de um arquivo CSV

🔢 Ordenação por ID (crescente)

📅 Ordenação por Data de Ajuizamento (decrescente)

📊 Contagem de processos por ID de Classe

🧠 Contagem de assuntos únicos

📋 Listagem de processos com múltiplos assuntos

⏱️ Cálculo de dias em tramitação

💾 Salvamento dos dados ordenados em novos arquivos CSV

📂 Estrutura de Arquivos
bash
Copiar
Editar
.
├── main.c               # Menu principal com interação do usuário
├── processo.c           # Lógica de leitura, ordenação e manipulação dos dados
├── processo.h           # Header com a estrutura do Processo e protótipos
├── entrada.csv          # Arquivo com os processos a serem carregados
├── README.md            # Este documento
⚙️ Como Compilar e Executar
Compile os arquivos:

bash
Copiar
Editar
gcc main.c processo.c -o tp01
Execute:

bash
Copiar
Editar
./tp01
📄 Formato esperado do arquivo entrada.csv
csv
Copiar
Editar
id,"numero",data_ajuizamento,{id_classe},{id_assunto1},{id_assunto2},...,ano_eleicao
📌 Exemplo:

csv
Copiar
Editar
405278031,"00000781820176070091",2017-08-16 17:40:56.000,{12559},{11778},0
🖥️ Interface de Menu
markdown
Copiar
Editar
--- MENU ---
1. Ordenar por ID (crescente) e salvar em CSV
2. Ordenar por Data (decrescente) e salvar em CSV
3. Contar processos por ID de Classe
4. Contar assuntos únicos
5. Listar processos com múltiplos assuntos
6. Mostrar dias em tramitacao para cada processo
0. Sair
📌 Detalhes Técnicos
Leitura de arquivos com fgets() e strtok()

Uso de structs e arrays dinâmicos para armazenar dados

Manipulação de datas com struct tm, mktime() e difftime()

Escrita de arquivos com fprintf() no formato .csv
