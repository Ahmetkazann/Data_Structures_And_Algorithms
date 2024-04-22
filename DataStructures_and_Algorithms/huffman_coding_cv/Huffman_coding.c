#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARACTERS 30

typedef struct node {
    char character;
    int frekans;
    struct node* right;
    struct node* left;
} n;

typedef struct sifre {
    char c;
    int *s;
    struct sifre* next;
}sif;


n* root;

int is_character_exist_in_list(char dizi[], char c) {
    for (int i = 0; i < MAX_CHARACTERS; i++) {
        if (dizi[i] == c) {
            return 1;
        }
    }
    return 0;
}

void readCharacterFromFile(char *fileName, char grafa_eklenecek_karakterler[], int grafa_eklenecek_karakterlerin_frekanslar[]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        exit(1);
    }

    int character;
    int karakter_indis = 0;

    while ((character = fgetc(file)) != EOF) {
        printf("%c", character);
        int character_exist_control = is_character_exist_in_list(grafa_eklenecek_karakterler, character);
        if (character_exist_control == 0) {
            grafa_eklenecek_karakterler[karakter_indis] = character;
            grafa_eklenecek_karakterlerin_frekanslar[karakter_indis] = 1;
            karakter_indis += 1;
        } else if (character_exist_control == 1) {
            int find_character_indis = 0;
            while (grafa_eklenecek_karakterler[find_character_indis] != '\0') {
                if (character == grafa_eklenecek_karakterler[find_character_indis]) {
                    grafa_eklenecek_karakterlerin_frekanslar[find_character_indis] += 1;
                    break;
                }
                find_character_indis += 1;
            }
        }
    }

    fclose(file);
    printf("\n\nkarakterler ve frekanslar: \n");
    printf("\n%s\n", grafa_eklenecek_karakterler);

    for (int i = 0; i < karakter_indis; i++) {
        printf("-%d", grafa_eklenecek_karakterlerin_frekanslar[i]);
    }
}

void delete_from_list_char(char l[], char c) {
    int i, j;
    int removed = 0; // Bayrak: eğer 1 olursa bir kere silinmiş demektir.
    for (i = 0, j = 0; l[i] != '\0'; i++) {
        if (l[i] != c || removed) { // Silinecek elemanı bulduğunda ve bir kere silindiğinde geç.
            l[j] = l[i];
            j++;
        } else {
            removed = 1; // Bayrağı ayarla.
        }
    }
    l[j] = '\0'; // Yeni diziyi sonlandır
}
void delete_from_list_int(int l[], int n, int size) {
    int i, j;
    int removed = 0; // Bayrak: eğer 1 olursa bir kere silinmiş demektir.
    for (i = 0, j = 0; i < size; i++) {
        if (l[i] != n || removed) { // Silinecek elemanı bulduğunda ve bir kere silindiğinde geç.
            l[j] = l[i];
            j++;
        } else {
            removed = 1; // Bayrağı ayarla.
        }
    }
}

int add_to_graph(int a, char aa, int b, char bb, int silinecek_mi,n* f[]){
    int mevcut_indis;
    if(f[0]->frekans != 0){
            // 3 tane durum -> {a,b,f[i]} -> {a,f[i],b} -> {f[i],a,b} 1. durumda a ve b birbirine baglanýr ve f dizisine yaprak eklenir
            //                                                       2. durumda a ve f[i] baglanýr b listeden silinmez bir sonraki iterasyonda grafa eklenir
            //                                                       3. durumda f[i] ve a baglanýr b listeden silinmez bir sonkari iterasyonda grafa eklenir
            //                                                       2. ve 3. durumda silinmeyen b yani ikinci en kucuk deger bir sonraki iteraasyonda
            //                                                       fonksiyona a degeri olarak girer.
            //                                                       boylece tum harfler grafa eklenmis olur. f baglý dizisinin frekanslarý kucukten buyuge
            //                                                       sýralanmýstýr yani her seferinde f[0] ile baglama gerceklestirilmelidir.
        if(a < f[0]->frekans && b <= f[0]->frekans){
            n* node1 = (n*)malloc(sizeof(n));
            n* node2 = (n*)malloc(sizeof(n));
            node1->character = aa;
            node1->frekans = a;
            node1->left = NULL;
            node1->right = NULL;
            node2->character = bb;
            node2->frekans = b;
            node2->left = NULL;
            node2->right = NULL;

            n* temp = (n*)malloc(sizeof(n));
            temp->frekans = a + b;
            temp->character = NULL;
            temp->right = node2;
            temp->left = node1;
            mevcut_indis = 0;
            while(f[mevcut_indis]->frekans != 0){
                mevcut_indis+=1;
            }
            f[mevcut_indis] = temp;
            return 1;
        }
        else if(a <= f[0]->frekans && b > f[0]->frekans){

            n* temp2;
            temp2 = f[0];
            n* node1 = (n*)malloc(sizeof(n));
            node1->character = aa;
            node1->frekans = a;
            node1->left = NULL;
            node1->right = NULL;

            n* temp = (n*)malloc(sizeof(n));
            temp->frekans = a + f[0]->frekans;
            temp->character = NULL;
            temp->left = node1;
            temp->right = temp2;
            f[0] = temp;

            return 0;
        }
        else if(a >= f[0]->frekans && b > f[0]->frekans){
            n* temp3;
            temp3 = f[0];
            n* node1 = (n*)malloc(sizeof(n));
            node1->character = aa;
            node1->frekans = a;
            node1->left = NULL;
            node1->right = NULL;

            n* temp = (n*)malloc(sizeof(n));
            temp->frekans = a + f[0]->frekans;
            temp->character = NULL;
            temp->left = temp3;
            temp->right = node1;
            f[0] = temp;

            return 0;
        }
    }
    else{
        n* node1 = (n*)malloc(sizeof(n));
        n* node2 = (n*)malloc(sizeof(n));

        node1->character = aa;
        node1->frekans = a;
        node1->left = NULL;
        node1->right = NULL;

        node2->character = bb;
        node2->frekans = b;
        node2->left = NULL;
        node2->right = NULL;

        n* temp = (n*)malloc(sizeof(n));
        temp->frekans = a + b;
        temp->character = NULL;
        temp->left = node1;
        temp->right = node2;
        f[0] = temp;
        return 1;
    }

}

void inorder(n* node){
    if(node == NULL){
        return;
    }
    inorder(node->left);
    printf("%d",node->frekans);
    if(node->character != NULL){
        printf("-%c",node->character);
    }
    printf("   ");

    inorder(node->right);
}

void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

void printCodes(n* root, int arr[8], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (root->right == NULL & root->left == NULL) {
        printf("%c: ", root->character);
        printArr(arr, top);
    }
}

int main() {

    char *fileName = "Sifrelenecek.txt";
    char grafa_eklenecek_karakterler[MAX_CHARACTERS] = {0};
    int grafa_eklenecek_karakterlerin_frekanslar[MAX_CHARACTERS] = {0};

    readCharacterFromFile(fileName, grafa_eklenecek_karakterler, grafa_eklenecek_karakterlerin_frekanslar);

    printf("\n\ndiziler alindi\n--%s\n", grafa_eklenecek_karakterler);
    for (int i = 0; i < sizeof(grafa_eklenecek_karakterler) / sizeof(char); i++) {
        printf("-%d", grafa_eklenecek_karakterlerin_frekanslar[i]);
    }
    printf("\n");
    char en_kucuk_char;
    char ikinci_en_kucuk_char;
    int en_kucuk = 1000;
    int ikinci_en_kucuk = 1000;
    n* mevcut_frekanslar[MAX_CHARACTERS];
    for(int i = 0; i < MAX_CHARACTERS; i++){
        mevcut_frekanslar[i] = (n*)malloc(sizeof(n));
        mevcut_frekanslar[i]->frekans = 0;
    }


    int ikinci_en_kucugu_sil = 1;
    printf("\n\n\n\n\n****************NODE'LAR OLUSTURULUYOR*******************");
    for(int j = 0; j < sizeof(grafa_eklenecek_karakterler) / sizeof(char); j++){
        en_kucuk = 1000;
        ikinci_en_kucuk =1000;
        if(grafa_eklenecek_karakterlerin_frekanslar[0] == '\0'){
            break;
        }
        for(int i = 0; i < sizeof(grafa_eklenecek_karakterler) / sizeof(char); i++){
            if(grafa_eklenecek_karakterler[i] == '\0')
                {
                    break;
                }
            if(grafa_eklenecek_karakterlerin_frekanslar[i] < en_kucuk){
                ikinci_en_kucuk = en_kucuk;
                ikinci_en_kucuk_char = en_kucuk_char;
                en_kucuk = grafa_eklenecek_karakterlerin_frekanslar[i];
                en_kucuk_char = grafa_eklenecek_karakterler[i];
            }
            else if(grafa_eklenecek_karakterlerin_frekanslar[i] < ikinci_en_kucuk){
                ikinci_en_kucuk = grafa_eklenecek_karakterlerin_frekanslar[i];
                ikinci_en_kucuk_char = grafa_eklenecek_karakterler[i];
            }
        }
        printf("\n");
        for (int i = 0; i < sizeof(grafa_eklenecek_karakterler) / sizeof(char); i++) {
            printf("-%d", grafa_eklenecek_karakterlerin_frekanslar[i]);
        }
        ikinci_en_kucugu_sil = 1;
        printf("\nbaglanacak en kucuk harf ve frekans: %c-%d\n",en_kucuk_char,en_kucuk);



        ikinci_en_kucugu_sil = add_to_graph(en_kucuk, en_kucuk_char, ikinci_en_kucuk, ikinci_en_kucuk_char, ikinci_en_kucugu_sil,mevcut_frekanslar);
        //printf("\nsilecek mi ?%d,",ikinci_en_kucugu_sil);
        delete_from_list_char(grafa_eklenecek_karakterler, en_kucuk_char);
        delete_from_list_int(grafa_eklenecek_karakterlerin_frekanslar, en_kucuk, MAX_CHARACTERS);


        if(ikinci_en_kucugu_sil == 1){
            printf("\nbaglanacak ikinci en kucuk frekans ve harfi: %c-%d\n",ikinci_en_kucuk_char,ikinci_en_kucuk);
            delete_from_list_char(grafa_eklenecek_karakterler, ikinci_en_kucuk_char);
            delete_from_list_int(grafa_eklenecek_karakterlerin_frekanslar, ikinci_en_kucuk, MAX_CHARACTERS);
        }
        int k = 0;
        int kucuk_frekans = 10000;
        while(mevcut_frekanslar[k]->frekans != 0){
            int l = k;
            int kucuk_indis;
            kucuk_frekans = 10000;
            n* list_temp;
            while(mevcut_frekanslar[l]->frekans!=0){
                if(mevcut_frekanslar[l]->frekans < kucuk_frekans){
                    kucuk_frekans = mevcut_frekanslar[l]->frekans;
                    kucuk_indis = l;
                }
                l+=1;
            }
            list_temp = mevcut_frekanslar[k];
            mevcut_frekanslar[k] = mevcut_frekanslar[kucuk_indis];
            mevcut_frekanslar[kucuk_indis] = list_temp;
            k+=1;
        }
        k = 0;
        printf("\n");
        while(mevcut_frekanslar[k]->frekans != 0){
        printf("birlestirilecek ve dizide tutulan node'lar  -  %d\n",mevcut_frekanslar[k]->frekans);
        k+=1;
    }
        /*printf("\nkarakterleri baglanmis birlestirilecek dugumler : \n");
        k = 0;
        while(mevcut_frekanslar[k]->frekans != 0){
            printf("%d,",mevcut_frekanslar[k]->frekans);
            k+=1;
        }*/
       /* while(mevcut_frekanslar[k+1]->frekans != 0){
            printf("%d,",mevcut_frekanslar[k]->frekans);
            k+=1;
        }
        k = 0;*/
    }
    printf("\n\n*******************tum harfler node'a baglandi adreslerini tuttugumuz node'lar birlestiriliyor************\n\n");
    int k = 0;
    int kokun_frekans = 0;
    printf("adresler ve frekanslar\n");
    while(mevcut_frekanslar[k]->frekans != 0){
        printf("%d-%d\n",&mevcut_frekanslar[k],mevcut_frekanslar[k]->frekans);
        kokun_frekans += mevcut_frekanslar[k]->frekans;
        k+=1;
    }
    int son_indis;
    printf("\nTOPLAM KARAKTER SAYISI:%d\n\n",kokun_frekans);
    son_indis = k;
    k = 0;

    while(mevcut_frekanslar[son_indis]->frekans != kokun_frekans){

        int j = k;
        while(mevcut_frekanslar[j]->frekans != 0){
            printf("%d-%d\n",&mevcut_frekanslar[j],mevcut_frekanslar[j]->frekans);
            // += mevcut_frekanslar[j]->frekans;
            j+=1;

        }
        printf("TOPLAM KARAKTER SAYISI BIRLESTIRILEN NODE'A ESIT OLANA KADAR DEVAM EDER:%d-%d\n",kokun_frekans,mevcut_frekanslar[j-1]->frekans);
        if(kokun_frekans == mevcut_frekanslar[j-1]->frekans){
            son_indis = j-1;
            break;
        }
        n* temp = (n*)malloc(sizeof(n));
        temp->frekans = mevcut_frekanslar[k]->frekans + mevcut_frekanslar[k+1]->frekans;
        temp->left = mevcut_frekanslar[k];
        temp->right = mevcut_frekanslar[k+1];
        mevcut_frekanslar[son_indis] = temp;



        int kucuk_frekans = 10000; // kucukten buyuge sırala
        int m = 0;
        while(mevcut_frekanslar[m]->frekans != 0){
            int l = m;
            int kucuk_indis;
            kucuk_frekans = 10000;
            n* list_temp;
            while(mevcut_frekanslar[l]->frekans!=0){
                if(mevcut_frekanslar[l]->frekans < kucuk_frekans){
                    kucuk_frekans = mevcut_frekanslar[l]->frekans;
                    kucuk_indis = l;
                }
                l+=1;
            }
            list_temp = mevcut_frekanslar[m];
            mevcut_frekanslar[m] = mevcut_frekanslar[kucuk_indis];
            mevcut_frekanslar[kucuk_indis] = list_temp;
            m+=1;
        }


        son_indis +=1;
        k+=2;
    }

    printf("\n*******HUFFMAN AGACI YAZDIRMA(INORDER)********");

    k = 0;
    printf("\n");
    printf("inorder siralama:\n");

    inorder(mevcut_frekanslar[son_indis]);






    printf("\n\n\n\n****************SIFRELENIYOR****************\n\n");
    fileName = "Sifrelenecek.txt";
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        exit(1);
    }

    int character;
    int karakter_indis = 0;
    int sifre[8] = {};
    character = 'l';
    int top = 0;
    sif* root_sifre;
    root_sifre = NULL;

    printCodes(mevcut_frekanslar[son_indis], sifre, top);
/*
    while ((character = fgetc(file)) != EOF) {
        char sifre[8] = {};
        printf("%c", character);
        strcpy(sifre,(findcharacter_at_tree(mevcut_frekanslar[son_indis],character,sifre)));
    }*/
    printf("\n\nmanaging garbages");
    fclose(file);
    printf("-deallocation to memory...");
    for(int i = 0; i<MAX_CHARACTERS ;i++){
        free(mevcut_frekanslar[i]);
    }





    return 0;
}
