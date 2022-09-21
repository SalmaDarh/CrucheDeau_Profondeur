#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//RECHERCHE EN PROFONDEUR //
typedef struct//generalement ces structures resteront les memes.
{
     int x,y;
}etat;

typedef struct Noeud
{
    struct Noeud *suivant;
    etat Etat;
}noeud;

typedef struct//dans la recharche en profondeur on travaillera avec une pile ainsi on aura besoin que d'un sommet
{
    noeud *sommet;
}liste;

liste listeNoeuds;

int n;

void Inserer(etat e,liste *L)//la fonction sert a inserer l etat e au sommet de la pile
{
    noeud *ne;
    ne=(noeud*)malloc(sizeof(noeud));
    ne->Etat = e;
    ne->suivant=L->sommet;//le suivant de ne pointera vers le sommet actuel
    L->sommet=ne;//le sommet pointera maintenant vers le noeud qu'on vient d'inserer

}

int Vide(liste L)
{
    if (L.sommet) return 0;
    return 1;
}


etat Extraire(liste *L0) //cette fonction retourne le premier etat de la liste et le supprime de la pile
{
    etat e;
    noeud *p;
    liste L;
    L=*L0;
    p=L.sommet;
    e=p->Etat;//prends l etat du premier noeud
    L.sommet=p->suivant;//le sommet pointe vers le deuxieme noeud qui deviendra maintenant sommet meme s'il est NULL
    free(p);
    *L0=L;
    return e;
}


int Appartient(etat e, liste L)
{
    noeud *p;

    for(p=L.sommet;p!=NULL;p=p->suivant)
        if((p->Etat.x==e.x)&& (p->Etat.y==e.y))  return 1;
    return 0;
}

int etatSolution(etat e)
{
    if (e.x==2)
        return 1;
    return 0;
}

void genereSuccesseurs(etat et)
{
	int m=0,x0,y0;
	x0=et.x;
	y0=et.y;
	etat e;
	if(x0<4)
	{
		e.x=4;
		e.y=y0;

		Inserer(e,&listeNoeuds);
	}
	if(x0>0)
	{
		e.x=0;
		e.y=y0;

		Inserer(e,&listeNoeuds);
	}
	if(y0<3)
	{

		e.y=3;
		e.x=x0;
		Inserer(e,&listeNoeuds);
	}
	if(y0>0)
	{
		e.y=0;
		e.x=x0;

		Inserer(e,&listeNoeuds);
	}

	if((x0>0)&&(y0<3))
	{
		m=fmin(x0,3-y0);
		e.x=x0-m;
		e.y=y0+m;
		Inserer(e,&listeNoeuds);
	}
	if((y0>0)&&(x0<4))
	{
		m=fmin(4-x0,y0);
		e.x=x0+m;
		e.y=y0-m;
		Inserer(e,&listeNoeuds);
	}
}

void RechercheProfondeur(etat etatInitial, etat etatFinal, void genereSuccesseurs())
{
    liste NoeudsDejaTraites;
    etat etatCourant;
    listeNoeuds.sommet = NULL;
    Inserer(etatInitial,&listeNoeuds);
    NoeudsDejaTraites.sommet=NULL;
    while(!Vide(listeNoeuds))
    {

        etatCourant=Extraire(&listeNoeuds);
        n++;


        if(etatSolution(etatCourant))
        {

            printf("\nSucces ! Arret sur le noeud : (%d,%d)\n\n Nombre de noeuds explores : %d\n",etatCourant.x, etatCourant.y, n);
            exit(0);
        }
        else if (!Appartient(etatCourant,NoeudsDejaTraites))
        {

            genereSuccesseurs( etatCourant);
            Inserer(etatCourant, &NoeudsDejaTraites);

        }
    }
    puts("\nPas de Solution");
}


int main()
{
    etat etatInitial={0,0},etatFinal={2,3};
    RechercheProfondeur(etatInitial,etatFinal,genereSuccesseurs);

    return 0;
}
