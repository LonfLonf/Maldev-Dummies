#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct Aluno
{
    char nome[100];
    int idade;
    float nota;
    struct Aluno *proximo;
} Aluno;

// Função para adicionar um aluno à lista
void adicionarAluno(Aluno **inicio, char nome[], int idade, float nota)
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    strcpy(novoAluno->nome, nome);
    novoAluno->idade = idade;
    novoAluno->nota = nota;
    novoAluno->proximo = *inicio;
    *inicio = novoAluno;
    printf("Aluno %s adicionado com sucesso!\n", nome);
}

// Função para remover um aluno da lista
void removerAluno(Aluno **inicio, char nome[])
{
    Aluno *atual = *inicio;
    Aluno *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Aluno %s não encontrado!\n", nome);
        return;
    }

    if (anterior == NULL)
    {
        *inicio = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Aluno %s removido com sucesso!\n", nome);
}

// Função para listar todos os alunos
void listarAlunos(Aluno *inicio)
{
    if (inicio == NULL)
    {
        printf("Nenhum aluno registrado.\n");
        return;
    }

    Aluno *atual = inicio;
    while (atual != NULL)
    {
        printf("Nome: %s, Idade: %d, Nota: %.2f\n", atual->nome, atual->idade, atual->nota);
        atual = atual->proximo;
    }
}

// Função para liberar a memória alocada para a lista
void liberarLista(Aluno *inicio)
{
    Aluno *atual = inicio;
    Aluno *proximo;

    while (atual != NULL)
    {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

void calculos_basicos()
{
    double a = 10.5, b = 4.2, result;

    // Soma
    result = a + b;
    printf("\nSoma: %.2f + %.2f = %.2f\n", a, b, result);

    // Subtração
    result = a - b;
    printf("Subtração: %.2f - %.2f = %.2f\n", a, b, result);

    // Multiplicação
    result = a * b;
    printf("Multiplicação: %.2f * %.2f = %.2f\n", a, b, result);

    // Divisão
    result = a / b;
    printf("Divisão: %.2f / %.2f = %.2f\n", a, b, result);
}


// Função para cálculo de potências e raízes
void potencias_raizes()
{
    double a = 9.0, result;

    // Potência
    result = pow(a, 2); // a^2
    printf("\nPotência: %.2f^2 = %.2f\n", a, result);

    // Raiz quadrada
    result = sqrt(a); // √a
    printf("Raiz quadrada de %.2f = %.2f\n", a, result);

    // Raiz cúbica
    result = cbrt(a); // ∛a
    printf("Raiz cúbica de %.2f = %.2f\n", a, result);
}

// Função para cálculos trigonométricos
void trigonometria()
{
    double angle = 45.0, radian;

    // Convertendo ângulo para radiano
    radian = angle * (2 / 180.0);

    // Seno
    printf("\nSeno de %.2f graus = %.2f\n", angle, sin(radian));

    // Cosseno
    printf("Cosseno de %.2f graus = %.2f\n", angle, cos(radian));

    // Tangente
    printf("Tangente de %.2f graus = %.2f\n", angle, tan(radian));
}

// Função para cálculo de determinante de uma matriz 2x2
void determinante_matriz()
{
    double a = 2.0, b = 3.0, c = 1.0, d = 4.0;

    // Determinante de uma matriz 2x2: |a b| = ad - bc
    //                                 |c d|
    double det = a * d - b * c;

    printf("\nDeterminante da matriz 2x2:\n");
    printf("| %.2f %.2f |\n", a, b);
    printf("| %.2f %.2f | = %.2f\n", c, d, det);
}

// Função para operações com números complexos
void numeros_complexos()
{
    double real1 = 3.0, imag1 = 2.0; // Primeiro número complexo
    double real2 = 1.0, imag2 = 4.0; // Segundo número complexo

    // Soma de números complexos
    double soma_real = real1 + real2;
    double soma_imag = imag1 + imag2;
    printf("\nSoma de números complexos: (%.2f + %.2fi) + (%.2f + %.2fi) = %.2f + %.2fi\n",
           real1, imag1, real2, imag2, soma_real, soma_imag);

    // Subtração de números complexos
    double sub_real = real1 - real2;
    double sub_imag = imag1 - imag2;
    printf("Subtração de números complexos: (%.2f + %.2fi) - (%.2f + %.2fi) = %.2f + %.2fi\n",
           real1, imag1, real2, imag2, sub_real, sub_imag);

    // Multiplicação de números complexos
    double mul_real = real1 * real2 - imag1 * imag2;
    double mul_imag = real1 * imag2 + imag1 * real2;
    printf("Multiplicação de números complexos: (%.2f + %.2fi) * (%.2f + %.2fi) = %.2f + %.2fi\n",
           real1, imag1, real2, imag2, mul_real, mul_imag);
}

// Função para cálculo de médias e desvio padrão
void media_desvio_padrao()
{
    double numeros[] = {5.0, 8.0, 7.0, 10.0, 6.0};
    double soma = 0.0, media, soma_quadrados = 0.0, desvio_padrao;
    int n = sizeof(numeros) / sizeof(numeros[0]);

    // Cálculo da soma
    for (int i = 0; i < n; i++)
    {
        soma += numeros[i];
    }
    media = soma / n;

    // Cálculo do desvio padrão
    for (int i = 0; i < n; i++)
    {
        soma_quadrados += pow(numeros[i] - media, 2);
    }
    desvio_padrao = sqrt(soma_quadrados / n);

    printf("\nMédia dos números: %.2f\n", media);
    printf("Desvio padrão dos números: %.2f\n", desvio_padrao);
}

// Função para corrigir erros de concordância
void corrigir_concordancia()
{
    printf("\nCorreção de concordância:\n");
    printf("A frase correta é: \"As crianças gostam de brincar no parque.\"\n");
}

// Função para classificar palavras
void classificar_palavras()
{
    printf("\nClassificação de palavras:\n");
    printf("Na frase: 'O cachorro preto corre rapidamente no jardim'\n");
    printf("Classificação:\n");
    printf("O - artigo definido\n");
    printf("cachorro - substantivo\n");
    printf("preto - adjetivo\n");
    printf("corre - verbo\n");
    printf("rapidamente - advérbio\n");
    printf("no - preposição + artigo definido\n");
    printf("jardim - substantivo\n");
}

// Função para conjugar o verbo "falar" no presente do indicativo
void conjugar_verbo()
{
    printf("\nConjugação do verbo 'falar' no presente do indicativo:\n");
    printf("Eu falo\n");
    printf("Tu falas\n");
    printf("Ele/ela fala\n");
    printf("Nós falamos\n");
    printf("Vós falais\n");
    printf("Eles/elas falam\n");
}

// Função para verificar o uso de crase
void verificar_crase()
{
    printf("\nUso de crase:\n");
    printf("1. 'Vou à escola de manhã' - Crase correta (escola é feminino e exige a preposição 'a')\n");
    printf("2. 'Ela foi à casa de sua amiga' - Crase correta (casa é feminino e exige a preposição 'a')\n");
    printf("3. 'Eu vou a pé até a padaria' - Sem crase (não se usa crase com a expressão 'a pé')\n");
}

// Função para substituir sujeitos por pronomes pessoais
void substituir_pronomes()
{
    printf("\nSubstituição de sujeitos por pronomes pessoais:\n");
    printf("Maria e João foram ao mercado. -> Eles foram ao mercado.\n");
    printf("O professor ensina a matéria todos os dias. -> Ele ensina a matéria todos os dias.\n");
    printf("Meu pai e eu fomos ao cinema. -> Nós fomos ao cinema.\n");
}

// Função para derivação de palavras
void derivar_palavras()
{
    printf("\nDerivação de palavras:\n");
    printf("Feliz -> felicidade\n");
    printf("Amor -> amoroso\n");
    printf("Beleza -> belo\n");
}

// Função para verificar o uso de advérbios
void verificar_adverbios()
{
    printf("\nFrase com advérbios de tempo, lugar e modo:\n");
    printf("Ontem, eu estudei na biblioteca calmamente.\n");
    printf("Advérbio de tempo: Ontem\n");
    printf("Advérbio de lugar: na biblioteca\n");
    printf("Advérbio de modo: calmamente\n");
}

typedef int (*math)(int, int);

int main(void)
{
    printf("Let's go make a math");

    // Variáveis para cálculos
    double a = 10.5, b = 4.2, result;

    // Soma
    result = a + b;
    printf("Soma: %.2f + %.2f = %.2f\n", a, b, result);

    // Subtração
    result = a - b;
    printf("Subtração: %.2f - %.2f = %.2f\n", a, b, result);

    // Multiplicação
    result = a * b;
    printf("Multiplicação: %.2f * %.2f = %.2f\n", a, b, result);

    // Divisão
    result = a / b;
    printf("Divisão: %.2f / %.2f = %.2f\n", a, b, result);

    // Potência
    result = pow(a, b);
    printf("Potência: %.2f^%.2f = %.2f\n", a, b, result);

    // Raiz quadrada
    result = sqrt(a);
    printf("Raiz quadrada de %.2f = %.2f\n", a, result);
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    // Logaritmo natural (ln)
    result = log(a);
    printf("Logaritmo natural de %.2f = %.2f\n", a, result);

    // Logaritmo base 10
    result = log10(a);
    printf("Logaritmo base 10 de %.2f = %.2f\n", a, result);
    // Fatorial (usando loop)
    int n = 5, fatorial = 1;
    for (int i = 1; i <= n; i++)
    {
        fatorial *= i;
    }
    printf("Fatorial de %d = %d\n", n, fatorial);

    // Seno
    result = sin(a);
    printf("Seno de %.2f radianos = %.2f\n", a, result);

    // Cosseno
    result = cos(a);
    printf("Cosseno de %.2f radianos = %.2f\n", a, result);

    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();

    HMODULE hDll = LoadLibrary("mommy.dll");

    if (hDll == NULL) {
        // Exibe o erro se a DLL não puder ser carregada
        printf("Erro ao carregar a DLL. Código do erro: %d\n", GetLastError());
        return 1;
    }

    // Tangente
    result = tan(a);
    printf("Tangente de %.2f radianos = %.2f\n", a, result);

    // Cálculo de área do círculo (π * r^2)
    double r = 3.0;
    result = 3.14 * r * r;
    printf("Área de um círculo de raio %.2f = %.2f\n", r, result);
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    char pao[] = "mommy";

    char numsei[100];

    trigonometria();
    determinante_matriz();


    // Copia a primeira string para numsei
    strcpy(numsei, pao);

    // Concatenando dequeijo à string numsei

    numeros_complexos();
    media_desvio_padrao();
    printf("Let's go make a math");

    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    conjugar_verbo();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();
    calculos_basicos();
    potencias_raizes();
    trigonometria();
    determinante_matriz();
    numeros_complexos();
    media_desvio_padrao();

    HMODULE hModule = LoadLibrary("mommy.dll");

    conjugar_verbo();
    verificar_crase();

    // Cálculo de perímetro do círculo (2 * π * r)
    result = 2 * 3.14 * r;
    printf("Perímetro de um círculo de raio %.2f = %.2f\n", r, result);

    // Equação quadrática: ax^2 + bx + c = 0
    double a2 = 1.0, b2 = -3.0, c2 = 2.0;
    double discriminante = b2 * b2 - 4 * a2 * c2;
    if (discriminante >= 0)
    {
        double x1 = (-b2 + sqrt(discriminante)) / (2 * a2);
        double x2 = (-b2 - sqrt(discriminante)) / (2 * a2);
        printf("Raízes da equação quadrática %.2fx^2 + %.2fx + %.2f = 0: x1 = %.2f, x2 = %.2f\n", a2, b2, c2, x1, x2);
    }
    else
    {
        printf("A equação quadrática %.2fx^2 + %.2fx + %.2f = 0 não tem raízes reais\n", a2, b2, c2);
    }

    // Cálculo de média de uma lista de números
    double numeros[] = {2.5, 3.5, 4.5, 5.5, 6.5};
    double soma = 0;
    int n_elementos = sizeof(numeros) / sizeof(numeros[0]);
    for (int i = 0; i < n_elementos; i++)
    {
        soma += numeros[i];
    }
    double media = soma / n_elementos;
    printf("Média dos números: %.2f\n", media);

    // Cálculo de desvio padrão
    double soma_quadrados = 0;
    for (int i = 0; i < n_elementos; i++)
    {
        soma_quadrados += pow(numeros[i] - media, 2);
    }
    double desvio_padrao = sqrt(soma_quadrados / n_elementos);
    printf("Desvio padrão dos números: %.2f\n", desvio_padrao);

    corrigir_concordancia();
    classificar_palavras();
    substituir_pronomes();
    derivar_palavras();
    verificar_adverbios();

    return 0;
}