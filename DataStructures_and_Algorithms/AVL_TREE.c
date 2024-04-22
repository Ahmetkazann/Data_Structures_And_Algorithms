#include <stdio.h>
#include <stdlib.h>


struct agac{

  int veri;
  struct agac*sol;
  struct agac*sag;
  int yukseklik;

};

int max(int a, int b){  //her kokün yuksekliğini hesaplayan fonksiyondan sol sağ değerleri parametre olarak alıp
                        // büyük olanı döndüren  fonksiyon.
   if(a>b){

      return a;

   }

   else{

      return b;
   }

}

int yukseklik(struct agac*kok){

   if(kok==NULL){

      return 0;           // her bir kök değerinin mevcut yükseklik değerini geri döndüren fonksiyon

   }

   return kok->yukseklik;

}


struct agac*kokdugum(int deger){

 struct agac* kok =(struct agac*)malloc(sizeof(struct agac));

   kok->veri=deger;

   kok->sol=NULL;
   kok->sag=NULL;

   return kok;

}


struct agac*rightRotation(struct agac*kok)    // sagdan çevirme fonksiyonu
{
    struct agac*subkok = kok->sol;        //parametre olarak gelen kok adresine bir kok  pointer atar ve bu pointer'a kokün solunu işraet eder.
    struct  agac*subtree = subkok->sag;  //kokkten diğer alt ağaca erişmek için pointer tanımlanır bu da bir önceki pointer'in işaret etiiği
                                        //kokün sağını işaret eder.

    subkok->sag=kok;             //subkok'ün sağı kokü işaret eder
    kok->sol=subtree;            //kokün solu da diğer alt ağacı işaret eder     böylelikle subkök üste çıkmış olur

     kok->yukseklik=max(yukseklik(kok->sol), yukseklik(kok->sag)) + 1;  //düzenlemeden sonra her kok ve altkökün yükseklik değerleri
     subkok->yukseklik=max(yukseklik(kok->sol), yukseklik(kok->sag)) + 1; //hesaplanıp yükseklik verisine atanır

    return subkok;
}

struct agac*leftRotation(struct agac*subkok) //parametre olarak alt kökü alan solaçevirme
{
    struct agac*kok = subkok->sag;  //kok altkokün sağını işaret etti
    struct  agac*subtree = subkok->sol;  //alt ağaç subkokü işaret etmesi ayarlandı


     kok->sol=subkok;  //kokün solu subkokü işaret eder
     subkok->sag=subtree;  //alt ağaç subkoküe bağlandı

     subkok->yukseklik=max(yukseklik(kok->sol), yukseklik(kok->sag)) + 1;  //yapılan değişiklikten sonra yükseklik
     kok->yukseklik=max(yukseklik(kok->sol), yukseklik(kok->sag)) + 1;  //değeleri hesaplanıp köklerin veri değerlerine atandı.


    return kok;
}

int denge(struct agac*kok){    //sol yükseklikten sağ yüksekliği çıkarıp geri döndüren denge fonksiyonu.

  if(kok==NULL){

    return 0;
  }
  return (yukseklik(kok->sol))- (yukseklik(kok->sag));

}

struct agac*elemanekle(struct agac*kok,int deger){

   if(kok==NULL){    //ikili ağaç gibi ekleme işlemi yapılır.

     kok=kokdugum(deger);

   }

   else{
     if(deger<kok->veri){

        kok->sol=elemanekle(kok->sol,deger);

     }

     else if(deger>kok->veri){
        kok->sag=elemanekle(kok->sag,deger);

     }

     else{
        return kok;
     }

   }

   kok->yukseklik= 1+ max(yukseklik(kok->sol), yukseklik(kok->sag)); //kokün yeni yükseliği kokün sol
      //sağ yapraklarının yüksekliklerinden en fazla olanına 1 eklenmesi ile tekrar atanır.
   int dengesabit=denge(kok);  //üzeirnde bulunulan kök denge fonksiyonuna gönderilir ve geri dönen değer sabite atanır.

   if(dengesabit >1 && deger< (kok->sol->veri)){

      return rightRotation(kok);       //denge sabiti 1'den büyükse ve eklenecek değer kökteki değerden küçükse
             //Left-Left rotaiton yapılmalidır.

   }
   if(dengesabit < -1 && deger>(kok->sag->veri)){  //denge sabiti -1den küçükse ve değer  kökün sağ yaprağının sağına
                                                    //eklenecekse ;
       return leftRotation(kok);
       //righ-right rotaition yapılmalıdır.
   }

   if(dengesabit >1 && deger>(kok->sol->veri)){ //denge sabiti 1 den büyük ve değer kökün sol yağrağının sağına
                                                //eklecekse ;
     kok->sol=leftRotation(kok->sol);
             //Left-right rotaiton yapılmalıdır.  //kokün sol önce left rotaiton a gider çıkan sonuç
     return rightRotation(kok);                  //sol yaprağa atanır ve sonra right rotation'a gönderilir.

   }

   if(dengesabit <-1 && deger< (kok->sag->veri)){ //denge sabiti -1den küçük ve değer kökün sağ yağrağının soluna
                                                   //eklenecekse :
     kok->sag=rightRotation(kok->sag);//Right-left rotation yapılmalıdır. Önce kökün sağ yaprağı gönderilir.

     return leftRotation(kok); //daha sonra güncel kök left rotaition'a gönderilir.

   }

   return kok;

}

void preorder(struct agac*kok){


      if(kok!=NULL){

         printf("%d ", kok->veri);
         preorder(kok->sol);
         preorder(kok->sag);


      }

}



int enkucuk(struct agac*kok){ //silme icin sagda yaprakta en kucuk degere ihtiyac duyulduğunda çağrılır

    while(kok->sol!=NULL){

        kok=kok->sol;

    }

    return kok->veri;

}

int enbuyuk(struct agac*kok){     //silme icin sol yaprakta en buyuk degere ihtiyac duyulduğunda çağrılır

    while(kok->sag!=NULL){

        kok=kok->sag;

    }

    return kok->veri;

}

struct agac*elemansil(struct agac*kok, int deger){

       if(kok==NULL){

          return NULL;        //kok degeri null oldugu zaman
       }

       if(kok->veri==deger){   //silinecek degere ulasıldıgında

           if(kok->sol==NULL&&kok->sag==NULL){      //silinecek degerin child dugumu yoksa adres doner

               return NULL;

           }


           if(kok->sag!=NULL){   //silinecek degerin sagında veri varsa

               kok->veri=enkucuk(kok->sag); //sag yapraktaki en kucuk degeri bulup koke atama islemi
               kok->sag=elemansil(kok->sag, enkucuk(kok->sag)); //sag yaprakta bulunan en kucuk degeri recursive silme islemi
               return kok;


            }

            kok->veri=enbuyuk(kok->sol);
            kok->sol=elemansil(kok->sol,enbuyuk(kok->sol)); //ekstrem ihtimal durumu. sadece sol yaprakların uzandigi durum gibi.

            return kok;

            }



        if(kok->veri<deger){    //yukarıdakilerin calismamasi durumunda silincek deger child node'dur burada tekrar yukarı yollanir

             kok->sag=elemansil(kok->sag,deger);
            return kok;
        }

        else{

            kok->sol=elemansil(kok->sol,deger);

            return kok;

        }

       kok->yukseklik= 1+ max(yukseklik(kok->sol), yukseklik(kok->sag)); //kökün yükseklik değeri yapraklarının max değerlerine 1 eklenerek atanır.

       int dengesabit=denge(kok);  //mevcut adres denge fonksiyonuna gönderilir. ve değer sabite atanır.

       if(dengesabit>1 && (denge(kok->sol))>=0){ //denge sabiti 1den büyük ve kökün sol yaprağının geri dönüyü
                                                //0'a büyük veya eşitse
           return rightRotation(kok); //left-left rotation


       }

       if(dengesabit >1 && (denge(kok->sol))<0){ ////denge sabiti 1den büyük ve kökün sol yaprağının geri dönütü
                                                //0'dan küçükse
          kok->sol=leftRotation(kok->sol);  //left-right rotation yapılır. Kökün sol yaprağı left rotation'a gönderilirp atanır
          return rightRotation(kok);   //kokün right rotaitioa gönderilir ve döndürülür

       }

       if(dengesabit <-1 && denge(kok->sol)<=0){ //denge sabiti -1'den küçük kökün sol yağrağının geri dönütü 0'dan küçük
                                                  //veya eşitse
                                           //right-right rotation yapılır.
          return leftRotation(kok);

       }

       if(dengesabit <-1 && denge(kok->sol) >0){ //denge sabiti -1'den küçük kökün sol yağrağının geri dönütü 0'dan
                                                   //küçükse
          kok->sag=rightRotation(kok->sag);
          return leftRotation(kok);//right-left rotation yapılır.

       }

       return kok;




}






int main()
{
    int secim,sayi,yuksek,dugumsay,elemansay,dongu=0;
    struct agac*eleman=NULL;


  while(1){

          printf("<-------AVL Agac------->\n");
          printf("Yapmak Istediginiz Islemi Seciniz\n");
          printf("--->Ekleme Icin->1\n");
          printf("--->Silme Icin->2\n");
          printf("--->Listeleme(Inorder)Icin->3\n");
          scanf("%d",&secim);



          switch(secim)
          {

                case 1:

                          printf("Sayi Giriniz");
                          scanf("%d",&sayi);
                          eleman=elemanekle(eleman,sayi);
                          printf("\n\n");
                          break;


                case  2:


                         printf("Silinecek Sayi Giriniz");
                         scanf("%d",&sayi);
                         eleman=elemansil(eleman,sayi);
                         break;



                case 3:

                            printf("<------Inorder Liste------->\n");
                            preorder(eleman);
                            printf("\n\n\n");
                            break;


              }


    }

    return 0;
}
