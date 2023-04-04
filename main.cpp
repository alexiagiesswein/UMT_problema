#include<stdio.h>
#include<stdlib.h>

bool splitArray(int A[30], int n)
{
    int suma=0;  //declaram si initializam suma elementelor vectorului cu 0, pe care o calculam ulterior
    int ok=0;    //tinem un contor pentru a putea returna false daca e imposibil sa impartim vectorul in 2 liste cu media egala si true daca este posibil
    for(int i=0; i<n; i++)  //aici am calculat suma tuturor elementelor din vector
    {
        suma += A[i];
    }

    for(int i=1; i<n/2 && ok==0; i++) //aici verificam daca vectorul poate sau nu sa fie impartit in 2 liste care sa aiba aceeasi medie si sa nu fie vide
    {
        if((suma*i)%n == 0)
        {
            ok=1;
        }
    }
    /* Verificarea de mai sus se face astfel:
     Avem un vector A si vrem sa il impartim in doua liste nevide B, C, care sa aiba media egala => suma elementelor din B e egala cu suma elementelor din C, care e egala cu (suma elementelor din A)/2
     sumaB + sumaC =sumaA, sumaB= sumaC= sumaA/2
     Avand n elemente in A, le vom imparti astfel: vom pune i elemente in B si (n-i) elemente in C
     Asta inseamna ca sumaA= sumaB * i/n + sumaC * (n-i)/n
     Vrem sa gasim o valoare a lui i, astfel incat sa putem imparti vectorul A, in 2 liste B,C de lungime i si (n-i), iar sumaB si sumaC sa fie intregi
     Astfel, calculand (sumaA*i)%n, verificam daca exista un astfel de i ca sa putem imparti vectorul
     Daca nu exista o astfel de valoare, impartirea sigur nu poate fi facuta si returnam false
     Daca exista o posibila impartire, trebuie sa verificam incontinuare daca putem imparti in 2 liste cu media egala
     Pentru asta am folosit programare dinamica.*/

    if(ok==0) return false;

    int mat[suma+1][(n/2)+1]={0};
    /*Declaram o matrice in care tinem cont daca o anumita suma poate fi obtinuta cu un anumit numar de elemente i din vectorul A, incercand toate cazurile.
    Dimensiunea matricii este (sumaA+1)*((n/2)+1) deoarece suma maxima pe care o putem obtine este suma elementelor din vectorul A,
    iar numarul maxim de elemente pe care il putem pune intr una din liste este de n/2
    Vom pune in matrice mat[j][k] 1 daca este posibil sa obtinem suma j cu k elemente si 0 daca nu este posibil */
    mat[0][0]=1; //primul element din matrice este 1, deoarece putem obtine o suma=0 folosind 0 elemente

    for(int i=0; i<n; i++) //luam pe rand fiecare element din vector
    {
        int element=A[i]; //il retinem intr-un auxiliar

        for(int j=suma; j>=element; j--) //punem in matrice toate sumele posibile pornind de la suma maxima pana la elementul curent
        {
            for(int k=1; k<=n/2; k++)  //pentru fiecare suma punem in matrice 1 daca se poate obtine din k elemente si 0 daca nu se poate, numarul maxim de elemente este k=n/2 care poate fi pus intr-una din liste
            {
                mat[j][k]=mat[j][k] | mat[j-element][k-1];
                /*Facem "sau" astfel:
                Daca putem obtine suma de j-elementulCurent folosind k-1 elemente, atunci putem
                obtine suma j folosind k elemente, adaugand elementulCurent
                Calculam toate combinatiile posibile si le retinem in matrice, daca sunt posibile sau nu.*/
            }
        }
    }

    /*La final in matricea va reprezenta daca este posibil sa obtinem orice suma j (pana la suma maxima sumaA)
    folosind oricate k elemente (pana la numarul maxim de elemente n/2)*/

    for(int i=1; i<=n/2; i++)
    {
        if(mat[(suma*i)/n][i]) return true;
    }
    /*La final, luam pe rand fiecare numar posibil de elemente i pe care il putem adauga intr-o lista
    si verificam daca suma (sumaA*i/n) poate fi obtinuta din i elemente si returnam true daca in matrice se gaseste valoarea 1,
    adica daca mat[(suma*i)/n][i]=1 suma (suma*i)/n se poate obtine din i elemente si returnam true, daca este 0 returnam false,
    deoarece nu se poate imparti vectorul A in 2 liste cu media egala */

    return false;

}

int main()
{

    int v[]={1,2,3,4,5,6,7,8};
    int a[]{2,7};
    if(splitArray(v,8)==1) printf("True\n");
    else printf("False\n");

    if(splitArray(a,2)==1) printf("True\n");
    else printf("False\n");

    return 0;

}
