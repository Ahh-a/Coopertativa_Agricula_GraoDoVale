#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define tam 100
#define ARQUIVO_BINARIO "database/2024.dat"

typedef struct 
{
    int origem;
    int protocolo;
    float pesoBrutoTotal;
    int numeroAmostras;
    int transgenico;
    int idAmostra[tam];
    float pesoBruto[tam];
    float pesoImpureza[tam];
    float grauUmindade[tam];
    int faixa[tam];
}cargas;

typedef struct 
{
    int mes;
    int origem;
    int protocolo;
    int dia;
    int transgenico;
    float pesoBrutoTotal;
    float pesoLimpo;
    float guc;
    float pic;

} dados;

void cabecalho_comum(char *funcaoNome);
void relatorioQuantitativoMensal(int mes, int origem, int protocolo, float guc);
void rodape_comum();
void leitura();
void leitura2();
void recebimentoCarga();
float calcularGuc(float *p, float *q, float *u, int n);
float calcular_pic(int n, float p[], float q[]);
void relatorioCarregamento(int origem, int numeroAmostra, int dia, int mes, int ano,
                           float guc, float pesoLimpo, int transgenico, int faixa[],
                           int id[], int faixa1, int faixa2, int faixa3);
void salvar(int origem, int protocolo, int dia, int mes, int ano, int transgenico, 
            float pesoBrutoTotal, float pesoLimpo, float guc, float pic, int faixa1, int faixa2, int faixa3 );
void interface();
void menu();

int main ()
{
    menu();
    return 0;
}
void cabecalho_comum(char *funcaoNome)
{
    printf("\nUFG-BSI-IP (COOPERATIVA AGRÍCOLA GRÃO_DO_VALE V1.0)");
    printf("\nANO: 2024 <%s>", funcaoNome);
    printf("\n--------------------------------------------------------------------\n");
}

void rodape_comum() 
{
    printf("\n--------------------------------------------------------------------\n");
    printf("Programa desenvolvido pelos alunos. \n");
    printf("- Vitor Vitorette Serafim de Pina\n");
    printf("- Humberto Henry Gontijo Braga\n");
    printf("- Yuri Salatiel de Lima\n");
    printf("- Gabriel Augusto Ramos Detofol\n");
    printf("- Leo Faris Monteiro de Paula\n");
}

void relatorioQuantitativoMensal(int mes, int origem, int protocolo, float guc)
{
    char meses[12][20] = 
    {
        "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };

    printf("=>> Mês: %s\n", meses[mes - 1]);
    printf("Origem   Protocolo   GU Faixa 1   GU Faixa 2   GU Faixa 3   GU Extra\n");
    printf("-------+-----------+------------+------------+------------+------------\n");
    printf("%5d   %5d", origem, protocolo);
    
    if (guc <= 8.5)
    {
        printf("           X");
    }
    else if (guc <= 15.0)
    {
        printf("                      X");
    }
    else if (guc <= 25.0)
    {
        printf("                                 X");
    }
    else
    {
        printf("                                         X");
    }
    printf("\n");
}
float calcular_pic(int n, float p[], float q[]) {
    float soma_q = 0, soma_p = 0;
    for (int i = 0; i < n; i++) {
        soma_q += q[i];
        soma_p += p[i];
    }
    if (soma_p > 0) {
        return (soma_q / soma_p) * 100.0;
    } else {
        return 0.0;
    }
}

float calcularGuc(float *p, float *q, float *u, int n){
    float numerador = 0, denominador = 0, guc = 0;
 
    for(int i = 1; i <= n; i++)
    {
        numerador += u[i] * (p[i] - q[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        denominador += p[i] - q[i];
    }
    
    guc = numerador / denominador;

    return guc;
}

void leitura()
{
    dados dado;
    FILE *file = fopen(ARQUIVO_BINARIO, "rb");
    
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    printf("\nDeseja o relatório para um mês específico?\n"
           "1- Sim          2- Não\n");
    int decisao;
    scanf("%d", &decisao);

    if (decisao == 2)
    {
        cabecalho_comum("Estatísticas Mensais");
        while (fread(&dado, sizeof(dados), 1, file) == 1)
        {
            relatorioQuantitativoMensal(dado.mes, dado.origem, dado.protocolo, dado.guc);
        }
        rodape_comum();
    }
    else if (decisao == 1)
    {
        printf("Digite o mês desejado:\n"
               "1- Janeiro   2- Fevereiro  ...  12 - Dezembro\n");
        int mes;
        scanf("%d", &mes);
        if (mes < 1 || mes > 12) {
            printf("Mês inválido. Deve estar entre 1 e 12.\n");
            fclose(file);
            return;
        }
        cabecalho_comum("Estatísticas Mensais");
        while (fread(&dado, sizeof(dados), 1, file) == 1)
        {
            if (dado.mes == mes)
            {
                relatorioQuantitativoMensal(dado.mes, dado.origem, dado.protocolo, dado.guc);
            }
        }
        rodape_comum();
    }
    else
    {
        printf("Opção inválida.\n");
    }

    fclose(file);
}


void interface()
{
  printf("\n  código  | ação"
         "\n     1    | Recepção de carregamento"
         "\n     2    | Gerar relatório mensal"
         "\n     3    | Gerar relatório estatísticas"
         "\n     4    | Sair"
         "\n"
         "\nDigite o código: ");
}

void menu()
{ 
  interface();
  int codigo;
  do
  {
    scanf("%d", &codigo);
    switch (codigo)
    {
      case 1:  //Recepção de carregamento
        recebimentoCarga();
        interface();
        break;
      case 2:  //Gerar relatório mensal
        leitura();
        interface();
        break;
      case 3: //Gerar relatório estatísticas
        leitura2();
        interface();
        break;
      case 4: //Sair

        printf("\nFinalizando o programa...\n\n");

        break;
      default:

        printf("\nCódigo não encontrado...\n");

        break;
    }
  } while ( codigo != 4);
}
void cabecalhoRelatorioGeral()
{

    printf("             | Faixa 1   (umid.) | Faixa 2   (umid.) |Faixa 3    (umid.)\n");
    printf("Ori-   Peso  | Peso      Tipo(%%) | Peso      Tipo(%%) | Peso      Tipo(%%)\n");
    printf("Gem    Total | Limpo  Trans  Nao | Limpo  Trans  Nao | Limpo  Trans  Nao \n");
    printf("----+--------+------+------+------+------+------+------+------+------+----------\n");

}
void dadosRelatororioGeral(int origem, float pesoBrutoTotal, float pesoLimpo, int transgenico, float guc)
{
    if (guc <= 8.5)
    {
        printf("%3d    %3.2f   %3.2f", origem, pesoBrutoTotal, pesoLimpo);
        if (transgenico)
        {
            printf("    X");
        }
        else
            printf("        X");
        
    
    }
    else if (guc <= 15.0)
    {
        printf("%3d    %3.2f                        %3.2f", origem, pesoBrutoTotal, pesoLimpo);
        if (transgenico)
        {
            printf("    X");
        }
        else
            printf("        X");
        
    }
    else if (guc <= 25.0)
    {
        printf("%3d     %3.2f                                         %3.2f", origem, pesoBrutoTotal, pesoLimpo);
        if (transgenico)
        {
            printf("    X");
        }
        else
            printf("        X");
    }

    printf("\n");

}



void leitura2()
{
    dados dado;
    FILE *file = fopen(ARQUIVO_BINARIO, "rb");
    
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo");
        exit(EXIT_FAILURE);
    }


    cabecalho_comum("Resumo Geral");
    cabecalhoRelatorioGeral();
    while (fread(&dado, sizeof(dados), 1, file) == 1)
    {
        dadosRelatororioGeral(dado.origem,dado.pesoBrutoTotal,dado.pesoLimpo, dado.transgenico, dado.guc);
    }
    rodape_comum();


    fclose(file);
}

void recebimentoCarga()
{
    FILE *file;
    
    char arquivo[tam];
    char caminho[tam] = "cargasRecebidas/";
    cargas carga;

    printf("\nDigite o nome do arquivo da carga: ");
    scanf("%s", arquivo);
    strcat(caminho,arquivo);

    file = fopen(caminho, "r");

    if (file == NULL)
    {
        printf("Erro 420...\n");
        return;
    }
    
    int dia, mes, ano;
    printf("\nDigite o dia do recebimento:\n");
    scanf("%d", &dia);
    printf("\nDigite o mes do recebimento:\n");
    scanf("%d", &mes);
    printf("\nDigite o ano do recebimento:\n");
    scanf("%d", &ano);

    fscanf(file,"%d %d %f %d %d", &carga.origem, &carga.protocolo, &carga.pesoBrutoTotal, &carga.numeroAmostras, &carga.transgenico);
    
    float pic, guc;
    int faixa1 = 0, faixa2 = 0, faixa3 = 0;
    float pesoImpurezaTotal = 0;

    for (int i = 0; i < carga.numeroAmostras; i++)
    {
        fscanf(file,"%d %f %f %f", &carga.idAmostra[i], &carga.pesoBruto[i], &carga.pesoImpureza[i], &carga.grauUmindade[i]);

        pesoImpurezaTotal += carga.pesoImpureza[i];

        if (carga.grauUmindade[i] <= 8.5)
        {
            carga.faixa[carga.idAmostra[i]] = 1; 
            faixa1++;
        }
        else if ( carga.grauUmindade[i] >= 8.6 && carga.grauUmindade[i] <= 15)
        {
            carga.faixa[carga.idAmostra[i]] = 2; 
            faixa2++;
        }
        else if (carga.grauUmindade[i] >= 15.1 && carga.grauUmindade[i] <= 25)
        {
            carga.faixa[carga.idAmostra[i]] = 3; 
            faixa3++;
        }

        

    }
    
    pic = calcular_pic(carga.numeroAmostras, carga.pesoBruto, carga.pesoImpureza);
    guc = calcularGuc(carga.pesoBruto, carga.pesoImpureza, carga.grauUmindade, carga.numeroAmostras);

    float pesoLimpo = carga.pesoBrutoTotal - pesoImpurezaTotal/1000;
    fclose(file);

    relatorioCarregamento(carga.origem, carga.numeroAmostras, dia, mes, ano,
                          guc, pesoLimpo, carga.transgenico, carga.faixa,
                          carga.idAmostra, faixa1, faixa2, faixa3 );

    salvar(carga.origem, carga.protocolo, dia, mes, ano, carga.transgenico
            , carga.pesoBrutoTotal, pesoLimpo, guc, pic, 
                faixa1, faixa2, faixa3 );



}

void relatorioCarregamento(int origem, int numeroAmostra, int dia, int mes, int ano,
                           float guc, float pesoLimpo, int transgenico, int faixa[],
                           int id[], int faixa1, int faixa2, int faixa3)
{

    cabecalho_comum("carregamento");

    printf("\nRelatorio da funcao Carregamento - Descricao de Carregamento \n\n");

    printf("Origem: %d \t  Num. de amostras: %d   \t Data: %d/%d/%d \n", origem, numeroAmostra, dia, mes, ano);
    printf("Umidade: %.2f%% \t  Peso limpo: %.2fkg       \t Transgenico: %s \n\n",guc, pesoLimpo, (transgenico == 1) ? "Sim" : "Nao");


    
    printf("Umidade: GU Faixa 1 \t   Quant.: %d  \n", faixa1);  
    printf("Ident. das Amostras: ");
    for (int i = 0; i < numeroAmostra; i++)
    {
        if (faixa[id[i]] == 1)
        {
            printf("%d ", id[i]);
        }       
    }
    printf("\n\n");

    printf("Umidade: GU Faixa 2 \t   Quant.: %d  \n", faixa2);  
    printf("Ident. das Amostras: ");
    for (int i = 0; i < numeroAmostra; i++)
    {
        if (faixa[id[i]] == 2)
        {
            printf("%d ", id[i]);
        }       
    }
    printf("\n\n");

    printf("Umidade: GU Faixa 3 \t   Quant.: %d  \n", faixa3);  
    printf("Ident. das Amostras: ");
    for (int i = 0; i < numeroAmostra; i++)
    {
        if (faixa[id[i]] == 3)
        {
            printf("%d ", id[i]);
        }       
    }
    printf("\n\n");

    rodape_comum();
}

void salvar(int origem, int protocolo, int diaa, int mees, int anoo, int transgenico
            , float pesoBrutoTotal, float pesoLimpo, float guc, float pic, 
                int faixa1, int faixa2, int faixa3 )
{

    FILE *file;
    char arquivo[] = "database/2024.dat";
    file = fopen(arquivo, "ab+");
    int buffer;
    int found = 0;

    if (file == NULL)
    {
        printf("\nErro 401...\n");
        return;
    }
    

    while (fread(&buffer, sizeof(int), 1, file)) 
    {
        if (buffer == protocolo) 
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("\nCARGA JA ESTA NO BANCO DE DADOS\n");
        fclose(file);
        return;
    }
    

    fwrite(&mees, sizeof(int), 1, file);
    fwrite(&origem, sizeof(int), 1, file);
    fwrite(&protocolo, sizeof(int), 1, file);
    fwrite(&diaa, sizeof(int), 1, file);
    fwrite(&transgenico, sizeof(int), 1, file);
    fwrite(&pesoBrutoTotal, sizeof(float), 1, file);
    fwrite(&pesoLimpo, sizeof(float), 1, file);
    fwrite(&guc, sizeof(float), 1, file);
    fwrite(&pic, sizeof(float), 1, file);

    fclose(file);
    printf("\nCARGA SALVA NO BANCO DE DADOS\n");
}
