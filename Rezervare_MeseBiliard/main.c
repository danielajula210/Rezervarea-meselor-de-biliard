/**Sistem de rezervare mese biliard
Afacerea dispune de 6 mese de biliard. Aplicația oferă utilizatorului posibilitatea rezervării unei mese
de biliard oricând în intervalul orar limita_ora 15 :00 - 21:00 pe o durată aleasă de acesta (inclusiv minute).
Utilizatorul poate vizualiza disponibilitatea unei mese într-o anumită zi. Utilizatorul poate vizualiza
statistici despre fiecare masă în parte (cât de mult a fost utilzată în ultima lună ca număr de ore și minute,
numărul total de rezervări din ultima lună etc.).
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
///#include<conio.h>

void iesire() {
    printf("La revedere!\n");
    exit(0);
}

///FUNCTIE DE BACK
 void back(){
     system("cls");
     main();
}

struct masa{
    char nr[50];
    char disponibilitate[100];
} mese[100];

int limita_ora=15;
void rezervare(numarmasa){
    FILE* fp = fopen("mesebiliard.txt", "a");
    int ora, minut,durata;
    char zi[9];
    printf("Introduceti ziua rezervarii: ");
    scanf("%s",zi);
    printf("Introduceti ora(format 24 de ore, orele 15-21): ");
    scanf("%d", &ora);
    if (ora < limita_ora || ora >= 21) {
        printf("Ne pare rau, rezervarile sunt disponibile intre orele %d:00 si 21:00.\n", limita_ora);
        return;
    }
    printf("Introduceti minutul: ");
    scanf("%d", &minut);
    printf("Introduceti durata rezervarii(in minute): ");
    scanf("%d", &durata);
    if (ora + (minut + durata) / 60 >= 21) {
        printf("Ne pare rau, nu putem accepta rezervari care se termina dupa ora 21:00.\n");
        return;
    }
     else{
        printf("\n");
        printf(" Masa a fost rezervata cu succes!\n");
        printf("\n");
        fprintf(fp,"In ziua de %s, masa de biliard cu nr %d este disponibila pentru rezervare incepand cu ora %d:%02d, pentru o durata de %d minute.\n",zi, numarmasa, ora, minut, durata);
    }
    fclose(fp);
}

int nrmese;
void citire(){
    FILE* fp = fopen("mesebiliard.txt", "r");
    fscanf(fp, "%d", &nrmese);
    fgetc(fp);
    for (int i = 0; i < nrmese; i++) {
        fgets(mese[i].nr, 50, fp);
        mese[i].nr[strlen(mese[i].nr) - 1] = '\0';
        fgets(mese[i].disponibilitate, 100, fp);
        mese[i].disponibilitate[strlen(mese[i].disponibilitate) - 1] = '\0';
    }
    fclose(fp);
}

void afisare_detalii(int i){
    FILE* fp = fopen("mesebiliard.txt", "r");
    char line[256];
    int count=0;
    char aux[10] = "nr ";
    char nr_masa[2];
    sprintf(nr_masa, "%d", i+1);
    strcat(aux, nr_masa);
    int durata=0,ore=0, minute=0;
    while (fgets(line, sizeof(line), fp)){
        if (strstr(line,aux)!= NULL){
            count++;
            int durata;
            sscanf(line, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d minute", &durata);
            minute=minute+durata;
        }
    }
    fclose(fp);
    ore=minute/60;
    minute=minute%60;
    printf("Detalii legate de masa cu nr %d\n",i+1);
    printf("\n");
    printf("- Disponibilitate: %s\n- Durata utilizare in ultima luna: %d ore si %d minute\n- Numar total de rezervari din ultima luna: %d\n",
        mese[i].disponibilitate,ore, minute, count);
}



int main(){
    while (1 == 1) {
        system("cls");
        printf("    -= MENIU =-\n");
        printf("\n");
        printf("1. Rezervare mese biliard\n");
        printf("2. Iesire\n");
        printf("\n");
        int choice;
        do {
            printf("Introduceti optiunea dorita: ");
            scanf("%d", &choice);
        } while (choice < 1 || choice > 2);
        system("cls");
        lista:
        if (choice == 1) {
            citire();
            printf("  -= MESE BILIARD =-\n");
            printf("\n");
            printf("Mese de biliard disponibile:\n");
            printf("- Masa numarul 1\n");
            printf("- Masa numarul 2\n");
            printf("- Masa numarul 3\n");
            printf("- Masa numarul 4\n");
            printf("- Masa numarul 5\n");
            printf("- Masa numarul 6\n");
            printf(" Pentru a reveni la meniul principal apasati numarul 7!\n");
            printf("\n");
            int masa;
            do {
                printf("Introduceti numarul mesei pe care doriti sa o rezervati: ");
                scanf("%d", &masa);
            } while (masa < 1 || masa > 7);
            system("cls");
            ///MASA 1
            if(masa==1){
                masa1:
                printf("Ati selectat masa cu nr 1.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati tasta 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("-Pentru a merge inapoi apasati tasta 1!\n");
                    printf("-Pentru a rezerva masa apasati tasta 2!\n");
                    printf("\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa1;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///MASA 2
            else if(masa==2){
                masa2:
                printf("Ati selectat masa cu nr 2.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("Pentru a merge inapoi apasati tasta 1!\n");
                    printf("Pentru a rezerva masa apasati tasta 2!\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa2;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///MASA 3
            else if(masa==3){
                masa3:
                printf("Ati selectat masa cu nr 3.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("Pentru a merge inapoi apasati tasta 1!\n");
                    printf("Pentru a rezerva masa apasati tasta 2!\n");
                    printf("\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa3;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///MASA 4
            else if(masa==4){
                masa4:
                printf("Ati selectat masa cu nr 4.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("Pentru a merge inapoi apasati tasta 1!\n");
                    printf("Pentru a rezerva masa apasati tasta 2!\n");
                    printf("\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa4;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///MASA 5
            else if(masa==5){
                masa5:
                printf("Ati selectat masa cu nr 5.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("Pentru a merge inapoi apasati tasta 1!\n");
                    printf("Pentru a rezerva masa apasati tasta 2!\n");
                    printf("\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa5;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    printf("\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///MASA 6
            else if(masa==6){
                masa6:
                printf("Ati selectat masa cu nr 6.\n");
                printf("\n");
                printf("1. Vezi detalii\n");
                printf("2. Rezerva masa\n");
                printf("- Pentru a accesa din nou lista de mese apasati tasta 3!\n");
                printf("- Pentru a reveni la meniul principal apasati 4!\n");
                printf("\n");
                int opt;
                do {
                    printf(" Introduceti optiunea dorita: ");
                    scanf("%d", &opt);
                } while (opt < 1 || opt > 4);
                system("cls");
                if(opt==1){
                    afisare_detalii(masa-1);
                    ///system("pause");
                    printf("Pentru a merge inapoi apasati tasta 1!\n");
                    printf("Pentru a rezerva masa apasati tasta 2!\n");
                    printf("\n");
                    int alegere;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &alegere);
                    } while (alegere < 1 || alegere > 2);
                    system("cls");
                    if(alegere==1){
                        goto masa6;
                        system("cls");
                    }
                    else if(alegere==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                    }
                }
                else if(opt==2){
                    rezervare(masa);
                   /// _getch();
                    printf("- Daca doriti sa rezervati alta masa apasati tasta 1!\n");
                    printf("- Daca ati terminat apasati tasta 2!\n");
                    int op;
                    do {
                       printf(" Introduceti optiunea dorita: ");
                       scanf("%d", &op);
                    } while (op < 1 || op > 2);
                    system("cls");
                    if(op==1) goto lista;
                    else if(op=2) iesire();
                }
                else if(opt==3){
                    goto lista;
                    system("cls");
                }

                else if(opt==4)
                    back();
            }
            ///PENTRU BACK
            else if(masa==7)
                back();

        }
        else if(choice==2)
            iesire();
    }
}
