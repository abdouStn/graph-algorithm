#include <iostream>
using namespace std;


/* PRINCIPE: La méthode consiste à placer un élément du tableau (appelé PIVOT) à sa place définitive, en permutant tous les éléments de telle sorte que tous ceux qui lui sont inférieurs soient à sa gauche et que tous ceux qui lui sont supérieurs soient à sa droite. Cette opération s'appelle le partitionnement.Pour chacun des sous-tableaux, on définit un nouveau pivot et on répète l'opération de partitionnement. Ce processus est répété récursivement, jusqu'à ce que l'ensemble des éléments soit trié

VERSION AVEC LE NB COMPARAISON ET NB ECHANGE

*/




bool Less(int a, int b)
{	
	return (a<b);
}





 void echanger(int *t, int i,int j)
 { 
	int tmp;
	tmp=t[i];
	t[i]=t[j];
	t[j]=tmp;
	
	}

void partition(int *t, int deb,int fin)
{
 
int compt=deb; 
//nbComp = 0; nbEch = 0;
int pivot=t[deb]; 
int i; 

for(i=deb+1;i<=fin;i++)
	{if (Less(t[i],pivot))   //if (t[i]<pivot)
		{
		
		echanger(t,compt,i);
		}
		}
echanger(t,compt,deb); 
return ;
}

void tri_rapide_bis(int *t, int debut,int fin)
{ 

if(debut<fin){ 
	int pivot = partition(t,debut,fin);
	tri_rapide_bis(t,debut,pivot-1);
	tri_rapide_bis(t,pivot+1,fin);
	}
}

void tri_rapide(int *t, int n)
{

tri_rapide_bis(t,0,n-1); 

}




// source: http://fr.scribd.com/doc/26076235/Langage-C-Les-Differents-Algorithmes-de-Tri

