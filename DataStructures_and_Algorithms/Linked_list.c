#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//Ahmet Emin Kazan 19010011039 ödev1
typedef struct kisi
{
    char ad[20];
    char soyad[20];
    int telno;
    struct kisi * sonraki;
} k;

k * ilk;
k * gezer;
k * gecici;
k * siralagecici;
k * aragecici;

void ekle(char  ad2[20],char soyad2[20],int telno2)
{
    if(ilk == NULL)
    {
        ilk = (k*)calloc(1,sizeof(k));

        strcpy((ilk->ad),ad2);
        strcpy((ilk->soyad),soyad2);
        ilk->telno = telno2;
        printf("%s->",ilk->ad);
        printf("%s->05",ilk->soyad);
        printf("%d\n",ilk->telno);
        ilk->sonraki = ilk;
    }
    else
    {
        gecici = (k*)calloc(1,sizeof(k));
        gezer=ilk;

        strcpy((gecici->ad),ad2);
        strcpy((gecici->soyad),soyad2);
        gecici->telno = telno2;
        printf("%s->",gecici->ad);
        printf("%s->05",gecici->soyad);
        printf("%d\n",gecici->telno);
        gezer = ilk;
        while(gezer->sonraki != ilk)
        {
            gezer = gezer->sonraki;
        }
        gezer->sonraki = gecici;
        gezer->sonraki->sonraki = ilk;
    }
    system("cls");
}

void listele()
{
    system("cls");
    printf("***************************************************************************************************************\n");
    gezer = ilk;
    if(ilk == NULL)
    {
        printf("eleman girilmedi...............\n\n");
    }
    else if(ilk->sonraki == ilk)    //1 eleman varsa
    {
        printf("%s->",gezer->ad);
        printf("%s->05",gezer->soyad);
        printf("%d\n",gezer->telno);
    }
    else
    {
        while(gezer->sonraki != ilk)
        {
            printf("%s->",gezer->ad);
            printf("%s->05",gezer->soyad);
            printf("%d\n",gezer->telno);
            gezer = gezer->sonraki;
        }
        if(gezer->sonraki == ilk)
        {
            printf("%s->",gezer->ad);
            printf("%s->05",gezer->soyad);
            printf("%d\n",gezer->telno);
        }
    }


}

void sil()
{
    int gecicitelno;
    printf("silinecek kisinin numarasini giriniz: 05");
    scanf("%d",&gecicitelno);
    gecici = ilk;
    if(ilk->telno == gecicitelno)
    {
        if(ilk->sonraki == ilk)
        {
            free(ilk);
            ilk = NULL;
        }
        else
        {
            while(gecici->sonraki != ilk)
                gecici = gecici->sonraki;
            gecici->sonraki = ilk->sonraki;
            ilk = ilk->sonraki;
        }

    }
    else
    {
        while(gecici->sonraki != ilk)
        {
            if(gecici->sonraki->telno == gecicitelno)
            {
                free(gecici->sonraki);
                gecici->sonraki = gecici->sonraki->sonraki;
            }
            gecici = gecici->sonraki;
        }
    }
    system("cls");
}

void siralasoyad()
{
//strcmp soldaki alfabede sonra geliyor ise 1 saðdaki sonra geliyor ise -1 döndürür

    int kisisayi = 1;
    gecici = ilk;
    if(ilk == NULL && ilk->sonraki == ilk)
    {
        printf("siralamak icin en az 2 eleman gerekli...");
    }
    else
    {

        while(gecici->sonraki != ilk)
        {
            gecici = gecici->sonraki;
            kisisayi++;
        }
        gecici = ilk;
        printf("kisi sayi : %d",kisisayi);
        for(int q = 0; q <= kisisayi; q++)
        {
            for(int j=0; j<kisisayi-1; j++)
            {
                int m;
                m = strcmp(gecici->soyad,gecici->sonraki->soyad);
                if(m==1)
                {
                    siralagecici = (k*)malloc(sizeof(k));
                    printf("if ici\n");
                    strcpy(siralagecici->ad,gecici->ad);
                    strcpy(siralagecici->soyad, gecici->soyad);
                    siralagecici->telno = gecici->telno;
                    strcpy(gecici->ad, gecici->sonraki->ad);
                    strcpy (gecici->soyad, gecici->sonraki->soyad);
                    gecici->telno = gecici->sonraki->telno;
                    strcpy(gecici->sonraki->ad, siralagecici->ad);
                    strcpy(gecici->sonraki->soyad, siralagecici->soyad);
                    gecici->sonraki->telno = siralagecici->telno;
                }
                gecici = gecici->sonraki;
            }
            gecici = ilk;
        }
    }
    listele();

}
void aramaad()
{
    aragecici = (k*)malloc(sizeof(k));

    int kontrol = 0;
    char ad[20];
    int k;
    printf("aradiginiz ad: ");

    scanf("%s",&ad);


    strcpy(aragecici->ad,ad);
    if(ilk->sonraki == ilk)
    {
        k = strcmp(ilk->ad,aragecici->ad);

        if(k == 0)
        {
            printf("aranan ad bulundu :\n");
            kontrol = 1;
            printf("%s->",ilk->ad);
            printf("%s->05",ilk->soyad);
            printf("%d\n",ilk->telno);
        }
    }
    else
    {
        gecici = ilk;
        while(gecici->sonraki != ilk)
        {
            k = strcmp(gecici->ad,aragecici->ad);

            if(k == 0)
            {
                printf("aranan ad bulundu :\n");
                kontrol = 1;
                printf("%s->",gecici->ad);
                printf("%s->05",gecici->soyad);
                printf("%d\n",gecici->telno);
            }
            gecici = gecici->sonraki;
        }
        k = strcmp(gecici->ad,aragecici->ad);

        if(k == 0)
        {
            printf("aranan ad bulundu :\n");
            kontrol = 1;
            printf("%s->",gecici->ad);
            printf("%s->05",gecici->soyad);
            printf("%d\n\n",gecici->telno);
        }
        else if (kontrol == 0)
            printf("bulunamadi...\n");


    }


}

void aramatel()
{
    gecici = ilk;
    int gecicitelno;
    printf("aranan tel no giriniz: 05");
    scanf("%d",&gecicitelno);

    if(ilk->sonraki == ilk)   //1 eleman varsa
    {
        printf("1 eleman var...");
        printf("%s",gecici->ad);
        printf("%s",gecici->soyad);
        printf("05%d\n",gecici->telno);
    }
    else
    {
        while(gecici->sonraki != ilk)
        {
            if(gecicitelno == gecici->telno)
            {
                printf("aranan no bulundu . \n");
                printf("%s->",gecici->ad);
                printf("%s->",gecici->soyad);
                printf("05%d\n",gecici->telno);
            }
                gecici = gecici->sonraki;
            }
            if(gecicitelno == gecici->telno) {
                printf("aranan no bulundu . \n");
                printf("%s->",gecici->ad);
                printf("%s->",gecici->soyad);
                printf("05%d\n",gecici->telno);
            }
        }
}
    int main()
    {
        char ad2[20],soyad2[20];
        int telno2;
        int menu;
        int i;
        int kisisayi = 0;
        gezer = ilk;
        gecici = ilk;
        while(menu != 7)
        {
            printf("eklemek icin 1, listelemek icin 2,silmek icin 3,soyada gore siralamak(soyad) icin 4\n,aramak(ad) icin 5,aramak(telno) icin 6\ncikis icin 7\n");
            scanf("%d",&menu);
            if(menu == 1)
            {
                i = 1;
                printf("ad: ");
                scanf("%s",&ad2);
                printf("soyad: ");
                scanf("%s",&soyad2);
                printf("telno: 05");
                scanf("%d",&telno2);
                gecici = ilk;
                if(telno2 < 100000000 || telno2 > 999999999)
                {
                    while(i == 1)
                    {
                        printf("telefon numarasini tekrar gir! :05");
                        scanf("%d",&telno2);
                        if(telno2 >= 100000000 && telno2 <= 999999999)
                        {
                           i = 0;
                        }
                    }
                }
                else if(kisisayi >= 1) {
                        if(ilk->telno == telno2)
                        {
                                while(ilk->telno == telno2) {
                                    printf("baska no gir:05");
                                    scanf("%d",&telno2);
                                }

                        }
                        while(gecici->sonraki != ilk)
                        {
                            gecici= gecici->sonraki;


                            if(gecici->telno == telno2 || ilk->telno == telno2){
                                printf("baska no gir:05");
                                gecici = ilk;
                                scanf("%d",&telno2);
                            }
                        }

                }
                kisisayi ++;
                ekle(ad2,soyad2,telno2);

            }
            else if(menu == 2)
            {
                listele();
            }
            if(menu == 3)
            {
                sil();
            }
            if(menu == 4)
            {
                siralasoyad();
            }
            if(menu == 5)
            {
                aramaad();
            }
            if (menu == 6)
            {
                aramatel();
            }
        }





        return 0;
    }
