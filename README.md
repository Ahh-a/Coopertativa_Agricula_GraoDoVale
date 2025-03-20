Trabalho final de IP 

                              Descrição do Problema Hipotético
                              
  Uma cooperativa agrícola recebe regularmente carregamentos de grãos para armazenagem e
posterior comercialização provenientes de diferentes origens. As cargas, identificadas por origem e número
de protocolo, são avaliadas na recepção, através de várias amostras tomadas por sondas em pontos
aleatórios, para classificação, registro e destinação do produto.
Além de registrar a informação de peso bruto do produto obtido na balança, a empresa precisa
classificar cada carga de acordo com informações obtidas pela análise imediata das amostras, para
determinar a presença de produto transgênico, a porcentagem de impurezas a deduzir e o grau de umidade
do produto, e gerar estatísticas globais (cumulativas) periódicas.

                              Método

  As medidas disponíveis após a análise de amostras são: o peso bruto (p), o peso de impurezas (q) e
o grau de umidade (u), individuais por amostra, e o tipo de produto (tp), global para a carga. O percentual
médio de impurezas da carga (pic) e o percentual médio de umidade da carga (guc) são determinados a
partir das amostras, de forma ponderada (considerando valores expressos na mesma unidade) por:

![image](https://github.com/user-attachments/assets/76762acb-d591-4cdf-bac7-72bf2b525c37)

![image](https://github.com/user-attachments/assets/23dd78c3-9844-4684-ad2c-78d707bcac15)

                              Entradas

  A entrada de dados é feita via teclado e arquivos de dados em texto (um para cada carregamento). O
teclado deve ser usado para informar o "nome do arquivo" preparado na recepção (incluindo a análise de
amostras) e a "data de recebimento" da carga, bem como os dados complementares que forem
necessários. Os arquivos de entrada possuem as seguintes informações:
- um registro inicial com
- identificação da origem da carga [ número inteiro de 1 a 999 ] ,
- número de protocolo da carga [ número inteiro de 1 a 1000 ] ,
- peso bruto do produto (carga) [ número real, em t ],
- número (n) de amostras da carga [ máximo de 20 ] e
- tipo de produto [ número inteiro, 0 ou 1, correspondendo a "sem" e "com" transgênicos ]
- n registros, um para cada amostra, com
- a identificação da amostra (número de ordem) [ número inteiro ] e
- as medidas da amostra
- peso bruto da amostra [ número real, em Kg ],- peso das impurezas [ número inteiro, em g ] e
- grau de umidade [ número real, em % com 1 casa decimal ].

                              Arquivo de banco de dados

  O banco de dados é formado por um único arquivo binário (para um determinado ano) composto por
registros com as seguintes informações e estrutura:
- Um registro para cada carga recebida (considerando todos os carregamentos recebidos no ano);
- Campos do registro (com tipos de dados):
- Origem [ inteiro de 1 a 999 ];
- Carga [ inteiro de 1 a 1000 ];
- Mês de recebimento da carga [ inteiro de 1 a 12 ];
- Dia de recebimento da carga [ inteiro de 1 a 31 ];
- Tipo de produto [ inteiro; valores válidos são 0 (sem transgênico), 1 (com transgênico) ];
- Peso bruto do produto [ real; valores em toneladas ];
- Perc. de impurezas [ real ];
- Perc. de umidade [ real ].




