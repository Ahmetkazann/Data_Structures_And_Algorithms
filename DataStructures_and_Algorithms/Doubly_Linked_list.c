#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//19010011039 AHMET EMİN KAZAN
//ODEV 2 CİFT YÖNLÜ BAGLI LİSTE
//72, 94 VE 162. SATIRDAKİ AÇIKLAMA SATIRLARINI SİLEREK ÇİFT YÖNLÜ OLUP OLMADIĞINI KONTROL EDEBİLİRSİNİZ

typedef struct d{

int data;
struct d * next;
struct d * prev;
} dd;

int main()
{
    int sayi;
    srand(time(NULL));
    printf("size of list (less then 8): ");
    scanf("%d",&sayi);

    printf("size of struct : %d",sizeof(dd));

    dd *ilk1 = (dd*)malloc(sizeof(dd));
    dd *ilk2 = (dd*)malloc(sizeof(dd));
    dd* iter1 = ilk1;
    dd* iter2 = ilk2;
    dd* temp;
    dd* temp2;
    dd* son1; // 73. satır
    dd* son2; // 95. satır

    //dd* tempadres;

            iter1->data = rand() % 100;
            iter1->prev = NULL;
            iter2->data = rand() % 100;
            iter2->prev = NULL;

    for(int i = 1;i < sayi ; i ++) {

        temp = (dd*)malloc(sizeof(dd));
        temp2 = (dd*)malloc(sizeof(dd));
        temp->data = rand() % 100;
        temp2->data = rand() % 100;

        iter1->next = temp;
        temp->prev = iter1;
        iter2->next = temp2;
        temp2->prev = iter2;
        iter2->next->prev = iter2;

        iter1 = iter1->next;
        iter2 = iter2->next;

        son1 = iter1;
        son2 = iter2;
    }

    iter1 = ilk1;
    iter2 = ilk2;

    printf("\n ------------1.dizinin degerleri ve adresleri--------------\n");
    for(int j = 1 ; j < sayi + 1; j++)
    {

        printf("%d. eleman %d -> ",j,iter1->data);
        printf("%d.adres %d\n",j,iter1);
        iter1 = iter1->next;

    }
    //çift yönlü olup olmadýðýný kontrol
  /*  printf("\n ------------1.dizinin degerleri ve adresleri(CIFT YONLU KONTROL)--------------\n");
    iter1 = son1;
        for(int j = 1 ; j < sayi + 1; j++)
    {

        printf("%d. eleman %d -> ",j,iter1->data);
        printf("%d.adres %d\n",j,iter1);
        iter1 = iter1->prev;

    }
*/

    printf("------------2.dizinin degerleri ve adresleri--------------\n");
    for(int k = 1 ; k < sayi +1 ; k ++) {


        printf("%d. eleman %d -> ",k,iter2->data);
        printf("%d.adres %d\n",k,iter2);
        iter2 = iter2->next;
    }

     //çift yönlü olup olmadýðýný kontrol
 /*   printf("\n ------------2.dizinin degerleri ve adresleri(CIFT YONLU KONTROL)--------------\n");
    iter2 = son2;
        for(int k = 1 ; k < sayi +1 ; k ++) {


        printf("%d. eleman %d -> ",k,iter2->data);
        printf("%d.adres %d\n",k,iter2);
        iter2 = iter2->prev;
    }
*/


    iter1 = ilk1;
    iter2 = ilk2;


        for(int p = 0 ; p < sayi; p++) {

            temp = iter1->next;
            iter1->next = iter2;
            iter2->prev = iter1;
            temp2 = iter2->next;
            iter2->next = temp;
            temp->prev = iter2;
            iter2 = temp2;
            iter1 = temp;

    }
    iter1 = ilk1;
    printf("----------------birlestirilen dizinin elemanlari-----------\n");
    for(int h = 0; h < (sayi*2) ; h++) {
        printf("%d. eleman deger %d adres %d \t",h+1,iter1->data,iter1);
        if(h % 2 == 1) printf("\n");
        iter1 = iter1->next;
    }

    iter1 = ilk1;
    int s = 1;
    while(s != sayi * 2) {
        iter1 = iter1->next;
        // son eleman
        s++;
    }

        printf("----------------birlestirilen dizinin elemanlari(REVERSE)-----------\n");
    iter2 = ilk1;
    ilk1 = iter1;
    for(int i = 0;i < sayi * 2;i++) {   // büyük adres ilk adres yapan döngü
        temp = iter1->prev;
        iter1->next = temp;
        iter1 = iter1->prev;
    }
    iter1 = ilk1;

    for(int i = 0;i < sayi * 2 -1;i++) { // tek yönlü diziyi çift yönlü yapan döngü
        temp = iter1->next;
        temp->prev = iter1;
        iter1 = iter1->next;
    }

    iter1 = ilk1;
        for(int h = 0; h < (sayi*2) ; h++) {
        printf("%d. eleman deger %d adres %d \t",h+1,iter1->data,iter1);
        if(h % 2 == 1) printf("\n");
        iter1 = iter1->next;
    }

 /*   printf("----------------birlestirilen dizinin elemanlari(REVERSE(writing with prev))-----------\n");
    iter1 = iter2;
    for(int h = 0; h < (sayi*2) ; h++) {
        printf("%d. eleman deger %d adres %d \t",h+1,iter1->data,iter1);
        if(h % 2 == 1) printf("\n");
        iter1 = iter1->prev;
    }*/

    return 0;
}
