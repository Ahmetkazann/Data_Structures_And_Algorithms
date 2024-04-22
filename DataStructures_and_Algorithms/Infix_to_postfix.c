#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//19010011039 AHMET EMÝN KAZAN

// example: a+((b-c)+(d*f)/g)
// a*((((b-c)+d)/e)-f)
// a+(b*(c-(d/(f+g)-h*j)-k)+l)
// a*b-c/d+h*j/k/l


typedef struct n
{
    char c;
    struct n* next;
} nn;

typedef struct d
{
    int deger;
    struct d *next;
}dd;

dd* degerler;
dd* iter3;
dd* ifade;

nn* posfix;
nn* stack;

nn* iter;
nn* top;

nn* pushchar(nn * root,char cc)
{
    if(root->c == 0)
    {
        root->c = cc;
        root->next = NULL;
    }
    else
    {
        iter = root;
        nn*temp = (nn*)calloc(1,sizeof(nn));
        temp->c = cc;
        while(iter->next != NULL){
            iter = iter->next;
        }
        iter->next = temp;
        iter = iter->next;
        iter->next = NULL;

    }

    return root;
}

void pop()
{
    iter = stack;
    if(stack->next == NULL)
    {
        if(stack->c != '(')pushchar(posfix,stack->c);
        free(stack);
        stack = (nn*)calloc(1,sizeof(nn));

    }
    else
    {
        while(iter->next != NULL){

            iter = iter->next;
        }
        if(iter->c != '(')pushchar(posfix,iter->c);


        iter = stack;
        while(iter->next->next != NULL){
            iter = iter->next;
        }
        free(iter->next);
        iter->next = NULL;

    }

}

char findtop()
{
    if(stack->c == 0){
        return '1';
    }
    if(stack->next == NULL)
    {
        return stack->c;
    }
    else
    {
        iter = stack;
        while(iter->next->next != NULL)
        {
            iter= iter->next;
        }
        return(iter->next->c);

    }

}

nn* iter2;

void printstep(){
    iter = posfix;
    while(iter != NULL){
        printf("%c",iter->c);
        iter = iter->next;
    }
    printf("      ");
    iter2 = stack;
    while(iter2 != NULL){
        printf("%c",iter2->c);
        iter2 = iter2->next;
    }
    printf("\n");

}

dd* pushint(dd * root,int d)
{
    if(root->deger == 0)
    {
        //root->deger = d;
        //root->next = NULL;
        root->deger = d;
    }
    else
    {
        iter3 = root;
        dd*temp = (dd*)malloc(sizeof(dd));
        temp->deger = d;
        while(iter3->next != NULL){
            iter3 = iter3->next;
        }
        iter3->next = temp;
        //ifade = iter3;
        iter3 = iter3->next;
        iter3->next = NULL;

    }

    return root;
}

void calculate(char operat)
{
    ifade = degerler;
    iter3 = degerler;
    while(iter3->next != NULL){
        ifade = iter3;
        iter3 = iter3->next;
    }

    if(operat == '+')
    {
        printf("The addition operation was performed");
        ifade->deger = ifade->deger + iter3->deger;
        free(ifade->next);
        ifade->next = NULL;
    }
    else if(operat == '-')
    {
            printf("The subtraction operation was performed");
            ifade->deger = ifade->deger - iter3->deger;
            free(ifade->next);
            ifade->next = NULL;
    }
    else if(operat == '*')
    {
            printf("The multiplication operation was performed");
            ifade->deger = ifade->deger * iter3->deger;
            free(ifade->next);
            ifade->next = NULL;
            //ifade = degerler;
            //iter3 = ifade->next;
    }
    else if(operat == '/')
    {
            printf("The division operation was performed");
            ifade->deger = ifade->deger / iter3->deger;
            free(ifade->next);
            ifade->next = NULL;
            //ifade = degerler;
            //iter3 = ifade->next;
    }



}

int main()
{
    char dizi[50];
    char tepe;
    printf("The operation should be entered using the alphabet first: ");
    scanf("%s",dizi);
    int i = 0;
    posfix = (nn*)calloc(1,sizeof(nn));
    stack = (nn*)calloc(1,sizeof(nn));

    while(dizi[i] != 0)
    {
        tepe = findtop();
        if(dizi[i] == '+' || dizi[i] == '-' || dizi[i] == '*' || dizi[i] == '/' || dizi[i] == '(' || dizi[i] == ')')
        {
            if(dizi[i] == '(')
            {
                pushchar(stack,dizi[i++]);
            }
            else if (dizi[i] == '*' || dizi[i] == '/') {
                    tepe = findtop();
                if(tepe == '+' || tepe == '-' || tepe == '1' || tepe == '(') {

                    pushchar(stack,dizi[i++]);
                }
                else {
                    pop();
                    pushchar(stack,dizi[i++]);
                }

            }
            else if (dizi[i] == '+' || dizi[i] == '-') {
                    tepe = findtop();
                    if(tepe == '1' || tepe == '('){
                        pushchar(stack,dizi[i++]);
                        tepe = findtop();
                    }
                    else if(tepe == '+' || tepe == '-' || tepe == '*' || tepe == '/'){
                        pop();
                        tepe = findtop();
                        while(tepe != NULL) {
                            if(tepe == '+' || tepe == '-' || tepe == '*' || tepe == '/') {
                            pop();
                            tepe = findtop();
                        }
                        else break;
                        }
                    pushchar(stack,dizi[i++]);
                }
            }
            else if(dizi[i] == ')')
            {
                i++;
                while(tepe != '(')
                {
                    pop();
                    tepe = findtop();
                }
                pop();
                tepe = findtop();
            }
        }

        else
        {
            pushchar(posfix,dizi[i++]);
        }
        printstep();
    }
    while(tepe != '1')
    {
        pop();
        tepe = findtop();
        printstep();
    }

    degerler = (dd*)calloc(1,sizeof(dd));
    iter = posfix;
    iter2 = degerler;

    int sayi;
    while(iter != NULL)
    {
        if(iter->c == '+' || iter->c == '-' || iter->c == '*' || iter->c == '/'){
            iter3 = degerler;;
            while(iter3->next != NULL){
                ifade=iter3;
                iter3 = iter3->next;
            }
            printf("%d and ",ifade->deger);
            printf("%d",iter3->deger);


            calculate(iter->c);
            printf("\n");
            iter3 = degerler;
            while(iter3 != NULL)
            {
                iter3 = iter3->next;
            }





            iter = iter->next;
            continue;
        }

            printf("%c value: ",iter->c);
            scanf("%d",&sayi);
            pushint(degerler,sayi);

        iter = iter->next;

    }

    iter3 = degerler;
   /* while(iter3 != NULL) {
        printf("sonuc: %d\n",iter3->deger);
        iter3 = iter3->next;
    }*/

    printf("\n conclusion :%d",iter3->deger);






    return 0;
}
