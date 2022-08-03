# DESCRIÇÃO DO PROJETO

Este programa foi desenvolvido para analisar e validar um banco de dados, enquanto realiza o monitoramento das URLs informadas entre estes dados.

Ou seja, o programa lê os dados inseridos em monitoring.db e inicia o monitoramento de acordo com estes dados, que se baseiam em três protocolos: HTTP, PING e DNS.

As informações obtidas pelo programa monitoring devem ser exibidas no terminal de forma simplificada, enquanto informações complementares devem estar armazenadas num arquivo monitoring.log.


## OBJETIVOS DO PROJETO 

De forma detalhada e por passo-a-passo, os objetivos deste projeto seriam:

- Ler os dados do arquivo monitoring.db;
- Analisar estes dados por protocolo;
- Monitorar as URLs informadas;
- Monitorar de acordo com o intervalo informado;
- Armazenar informações no arquivo monitoring.log; e
-	Utilizar o argumento --simplify para adquirir informações sucintas a partir do arquivo monitoring.log.

O arquivo monitoring.db possui as seguintes configurações para cada protocolo:

| Protocolo   | Configurações                                                           |
|-------------|-------------------------------------------------------------------------|
| HTTP        | nome, protocolo, endereço, método HTTP, código HTTP esperado, intervalo |
| PING        | nome, protocolo, endereço, intervalo                                    |
| DNS         | nome, protocolo, endereço, intervalo, servidor DNS                      |


## OBJETIVOS ALCANÇADOS

As funcionalidades que implementei foram:

- Leitura dos dados de monitoring.db;
-	Monitoramento das URLs informadas ao executar o programa ./monitoring;
- Análise dos dados durante o monitoramento: 
  -	Se as requisições foram bem sucedidas; e
  -	Informações complementares sobre as URLs.
 
  No caso do `protocolo HTTP/HTTPS`:
     -	Requisição realizada através do método HTTP especificado no monitoring.db;
     -	Verificação se o protocolo utilizado foi o de acordo com o monitoring.db; e
     -	Verificação se o código HTTP foi o esperado.


### Contextualização: Protocolos e Libcurl

HTTP é um protocolo de transferência que possibilita ver conteúdos e dados de sites. A sigla vem do inglês Hypertext Transfer Protocol. Qualquer servidor que hospede um site, tem um programa projetado para receber solicitações HTTP. Uma `solicitação HTTP` é o que a API Libcurl envia ao servidor quando o informa o que fazer. 

Cada solicitação HTTP contém um método, exemplos deles são os GET, POST, HEAD e DELETE. Os dois primeiros são os principais. O método GET é utilizado para consulta, ou seja, para requisição de informação. Já o POST, é um método para inserção de informações, como para inserir ou atualizar valores. 

Curl é a abreviação para `Client URL`, seus comandos são uma forma do `client` verificar a conectividade da `URL`. Pode-se utilizar os comandos do Curl no terminal, mas também há a biblioteca. No caso deste projeto, foi utilizada a Libcurl para monitorar os serviços. 

Um dos importantes monitoramentos realizados pela Curl é para identificar o `código HTTP`. Obtendo este código, podemos interpretar se a requisição HTTP foi corretamente concluída. As `respostas HTTP em forma de código` são agrupadas em cinco classes:

- Respostas de informação (100-199);
- Respostas de sucesso (200-299);
- Redirecionamentos (300-399);
- Erros do cliente (400-499); e
- Erros do servidor (500-599).

No projeto não foi verificado o valor de PING e do DNS, mas para conhecimento, estas são as definições e funcionalidades:

- Ping é um utilitário que usa o protocolo ICMP (um protocolo de rede) para testar a conectividade entre equipamentos. Seu funcionamento consiste no envio de pacotes para o equipamento de destino e na "escuta" das respostas. Ping  é o tempo que leva para um pacote de dados ser transmitido de seu dispositivo para um servidor na Internet e retornar ao dispositivo, sendo medido em milissegundos (ms). Quanto maior o valor do ping, mais lenta é a conectividade do dispositivo.

- O DNS converte nomes de domínio legíveis por humanos (por exemplo, www.amazon.com) em endereços IP legíveis por máquina (por exemplo, 192.0.2.44).

### Planejamento do projeto

Para a elaboração do projeto, foram definidas etapas como na imagem abaixo:

![PLANEJAMENTO](https://user-images.githubusercontent.com/98241492/182670108-3fda450d-660e-41c6-b758-74a58abc51d9.png)


### Funções e ferramentas utilizadas

Para leitura dos dados, foram usadas principalmente as seguintes funções:

- `Get next line:` A função deve retornar a linha que foi lida incluindo o caractere \n, exceto se o final do arquivo foi atingido e não termine com um caractere \n.

- `Ft_split:` Esta função foi essencial para armazenar os dados em um array, de forma que os dados podem ser analisados e utilizados ao acessar sua variável correspondente.

- `Strstr:` A função strstr retorna nulo se não encontrar a string que deseja ser encontrada (no caso do projeto: HTTP, PING e DNS) na string de origem (cada linha de monitoring.db). 

Para o monitoramento:

- `Libcurl:` As funções `curl_easy_setopt` são para definir as opções de requisição, já a função `curl_easy_perform` para executar toda a solicitação, de forma que retorne `CURLE_OK`, caso a solicitação seja bem sucedida, ou uma `mensagem de erro` caso não seja possível atender a solicitação. Para obter as informações, foram usadas as funções `curl_easy_getinfo`.

Para informar dados de forma sucinta:

- curl_easy_setopt(curl, `CURLOPT_WRITEFUNCTION`, write_data): Com a libcurl, utilizei o argumento WRITEFUNCTION para conseguir armazenar os dados do site em uma estrutura chamada chunck. 

## USO

Para utilizar o programa, deve estar instalada a biblioteca LIBCURL.

Deve-se executar `make` para compilar, e iniciar o programa digitando no terminal `./monitoring`.

Caso o programa tenha tido sucesso ao encontrar o site definido pelo monitoring.db, irá retornar a mensagem "Successful request” e algumas análises do site. Se não tiver acesso à URL, informará “"Download problem is:” com as informações de erro.
