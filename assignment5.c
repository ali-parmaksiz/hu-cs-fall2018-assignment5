#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int start_control(char *s){
    char start_codon[4] = "AUG";
    int i,j=0;
    for (i=0;i<3;i++)
        if (s[i] == start_codon[i])
            j++;
    if (j == 3)
        return 1;
    else
        return 0;
}

int stop_contol(char *s){
    char stop_codon_1[4] = "UAA";
    char stop_codon_2[4] = "UAG";
    char stop_codon_3[4] = "UGA";

    int i,j,c1=0,c2=0,c3=0;
    int length = (int) strlen(s);
    for (i=0,j=3; i < 3, 0 < j; i++,j--) {
        if (s[length - j] == stop_codon_1[i]) c1++;

        if (s[length - j] == stop_codon_2[i]) c2++;

        if (s[length - j] == stop_codon_3[i]) c3++;
    }

    if (c1 ==3)
        return 1;
    else if (c2==3)
        return 1;
    else if (c3 ==3)
        return 1;
    else
        return 0;

}

char alphabet(char *s){
    char codon_table[4][4][4] = {{{'F','F','L','L'},{'S','S','S','S'},{'Y','Y',' ',' '},{'G','C',' ','W'}}
                                ,{{'L','L','L','L'},{'P','P','P','P'},{'H','H','Q','Q'},{'R','R','R','R'}}
                                ,{{'I','I','I','M'},{'T','T','T','T'},{'N','N','K','K'},{'S','S','R','R'}}
                                ,{{'V','V','V','V'},{'A','A','A','A'},{'D','D','E','E'},{'G','G','G','G'}}};
    int i;
    int x[3];
    for (i=0;i<3;i++){
        switch (s[i]){
            case 'U':
                x[i] = 0;
                break;
            case 'C':
                x[i] = 1;
                break;
            case 'A':
                x[i] = 2;
                break;
            case 'G':
                x[i] = 3;
                break;
            default:
                break;
        }

    }

    return codon_table[x[0]][x[1]][x[2]] ;

}

char getting_triple(char *s, int start_point){
    char triple[3];
    int i,j=0;
    for (i=start_point;i<start_point+3;i++){
        triple[j] = s[i];
        j++;
    }
    return alphabet(triple);
}

void printing_amino_acid(char *s){
    int i;
    for (i=0;i<8;i++){
        if (s[i] == ' ')
            break;
        printf("%c-",s[i]);
    }
    printf("%c",s[i]);
}

int controlling_middle_stop_codon(char *s){
    int i,j=0;
    for (i=0;i<9;i++){
        if (s[i] == ' ')
            j++;
    }
    if (j > 0)
        return 0;
    else
        return 1;
}

int main(int argc, char* argv[]) {

    char myProteinA[31] = "AUGGUGGCGGAGGGGACGAAGAGGAUCUAA";
    char myProteinB[31] = "AUGGGAGAAGCAGUAAGAAAAACAAUAUAG";
    char myProteinC[31] = "AUGUUUUCCUAUUGCCUGCCACAACGCUGA";
    char myProteinD[31] = "AUGUUCUUGGUCCCUACUUACGAUCAUUAA";
    char myProteinE[31] = "AUGUUUUCCUAUUGCCUGCCAAAACGCUGA";

    FILE *fp;
    fp =fopen(argv[1],"r");
    char input[30];

    int j;
    for (j=0; j<30;j++){
        fscanf(fp,"%c",&input[j]);

    }
    printf("fname: %s File content: %s\n\n", argv[1], input);

    char protein_sequence_A[10];
    char protein_sequence_B[10];
    char protein_sequence_C[10];
    char protein_sequence_D[10];
    char protein_sequence_E[10];
    char protein_sequence_input[10];

    int i;
    for (i=0;i<9;i++){
        protein_sequence_A[i] = getting_triple(myProteinA,i*3);
        protein_sequence_B[i] = getting_triple(myProteinB,i*3);
        protein_sequence_C[i] = getting_triple(myProteinC,i*3);
        protein_sequence_D[i] = getting_triple(myProteinD,i*3);
        protein_sequence_E[i] = getting_triple(myProteinE,i*3);
    }


    if (start_control(input) == stop_contol(input)){
        int i;
        for (i=0;i<9;i++)
            protein_sequence_input[i] = getting_triple(input,i*3);
        if (controlling_middle_stop_codon(protein_sequence_input) == 0){
            printf("It is not a known protein.\n");
            printf("It is probably new protein. ");
            printing_amino_acid(protein_sequence_input); printf("\n");
        }
        else if(strcmp(protein_sequence_input,protein_sequence_A) == 0){
            printf("MyProteinA is identified in sequence.\n");
            printf("The amino acids of MyProteinA: "); printing_amino_acid(protein_sequence_input); printf("\n");
            printf("proteinA: "); printing_amino_acid(protein_sequence_A); printf("\n");
        }
        else if(strcmp(protein_sequence_input,protein_sequence_B) == 0){
            printf("MyProteinB is identified in sequence.\n");
            printf("The amino acids of MyProteinB: "); printing_amino_acid(protein_sequence_input); printf("\n");
            printf("proteinB: "); printing_amino_acid(protein_sequence_B); printf("\n");
        }
        else if(strcmp(protein_sequence_input,protein_sequence_C) == 0){
            printf("MyProteinA is identified in sequence.\n");
            printf("The amino acids of MyProteinC: "); printing_amino_acid(protein_sequence_input); printf("\n");
            printf("proteinC: "); printing_amino_acid(protein_sequence_C); printf("\n");
        }
        else if(strcmp(protein_sequence_input,protein_sequence_D) == 0){
            printf("MyProteinA is identified in sequence.\n");
            printf("The amino acids of MyProteinD: "); printing_amino_acid(protein_sequence_input); printf("\n");
            printf("proteinD: "); printing_amino_acid(protein_sequence_D); printf("\n");
        }
        else if(strcmp(protein_sequence_input,protein_sequence_E) == 0){
            printf("MyProteinA is identified in sequence.\n");
            printf("The amino acids of MyProteinE: "); printing_amino_acid(protein_sequence_input);
            printf("proteinE: "); printing_amino_acid(protein_sequence_E); printf("\n");
        }
    }
    else{
        if (start_control(input) != 1){
            printf("Not start with AUG! It is not a protein."); printf("\n");
        }
        else if (stop_contol(input) != 1){
            printf("It is not a protein! No stop code."); printf("\n");
        }
    }

    fclose(fp);
    return 0;
}


