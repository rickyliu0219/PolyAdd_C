#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ITEMS 10

struct term {
    float coef; // 係數
    int exp;    // 指數
};

void parsePolynomial(char *input, struct term poly[], int *size) {
    *size = 0;
    char *token = strtok(input, "+");
    while (token != NULL && *size < NUM_ITEMS) {
        float coef = 1;
        int exp = 0;
        if (strchr(token, 'x')) {
            sscanf(token, "%fx^%d", &coef, &exp);
        } else {
            sscanf(token, "%f", &coef);
            exp = 0;
        }
        poly[*size].coef = coef;
        poly[*size].exp = exp;
        (*size)++;
        token = strtok(NULL, "+");
    }
}

void addPolynomials(struct term polyA[], int sizeA, struct term polyB[], int sizeB, struct term polyR[], int *sizeR) {
    int indexA = 0, indexB = 0, indexR = 0;
    
    while (indexA < sizeA && indexB < sizeB) {
        if (polyA[indexA].exp == polyB[indexB].exp) {
            polyR[indexR].exp = polyA[indexA].exp;
            polyR[indexR].coef = polyA[indexA].coef + polyB[indexB].coef;
            indexA++;
            indexB++;
        } else if (polyA[indexA].exp < polyB[indexB].exp) {
            polyR[indexR] = polyB[indexB];
            indexB++;
        } else {
            polyR[indexR] = polyA[indexA];
            indexA++;
        }
        indexR++;
    }
    
    while (indexA < sizeA) {
        polyR[indexR++] = polyA[indexA++];
    }
    
    while (indexB < sizeB) {
        polyR[indexR++] = polyB[indexB++];
    }
    
    *sizeR = indexR;
}

void printPolynomial(struct term poly[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2fx^%d", poly[i].coef, poly[i].exp);
        if (i < size - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    struct term PolyA[NUM_ITEMS], PolyB[NUM_ITEMS], PolyR[NUM_ITEMS];
    int sizeA, sizeB, sizeR;
    char inputA[100], inputB[100];
    
    printf("\n本程式由 劉禹寬 設計\n\n");
    
    printf("請輸入第一個多項式 A(x) (格式範例: 7x^4+3x^2+4): ");
    scanf("%s", inputA);
    parsePolynomial(inputA, PolyA, &sizeA);
    
    printf("請輸入第二個多項式 B(x) (格式範例: 6x^5+5x^4+x^2+7x+9): ");
    scanf("%s", inputB);
    parsePolynomial(inputB, PolyB, &sizeB);
    
    addPolynomials(PolyA, sizeA, PolyB, sizeB, PolyR, &sizeR);
    
    printf("\n多項式 A(x): ");
    printPolynomial(PolyA, sizeA);
    printf("多項式 B(x): ");
    printPolynomial(PolyB, sizeB);
    printf("\n相加後的結果 R(x): \n");
    printPolynomial(PolyR, sizeR);
    
    system("pause");
    return 0;
}
