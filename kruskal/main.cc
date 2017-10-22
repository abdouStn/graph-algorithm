#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
//#include "triRapide.h"

using namespace std;

// ################## compilation  #####################
//	g++ main.cc Affichage.cc -o kruskal
//	kruskal && convert Arbre.ps Arbre.pdf
// ################## exo 1  #####################

void pointRandom(int n,int point[][2]) {

int val1 = 0, val2 = 0;
  for(int i =0; i<n; i++){
    val1 = rand()%613;
    val2 = rand()%793;
    point[i][0]=val1; point[i][1]=val2;
  }
}


// ################## exo 2  #####################

void distances (int n,int m,int point[][2], int edge[][3] ){
	int k = 0;
	for(int i = 0;i<m; i++){
		for(int j=i+1; j<n; j++ ){
		edge[k][0] = i;
		edge[k][1] = j;
		edge[k][2] = ((point[i][0] - point[j][0] ) * (point[i][0] - point[j][0] )) + ((point[i][1] - point[j][1] ) * (point[i][1] - point[j][1] )) ;
		k++;
	}

}
}

// ################## exo 3  #####################

void tri(int m,int edge[][3])      // principe du triBulle
{
    bool tab_en_ordre = false;

    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(int i=0 ; i < m -1 ; i++)
        {
            if(edge[i][2] > edge[i+1][2])
            {
                swap(edge[i][0],edge[i+1][0]);  // echange
                swap(edge[i][1],edge[i+1][1]);
                swap(edge[i][2],edge[i+1][2]);
                tab_en_ordre = false;
            }
        }
       // m--;
    }
}


// faire un triRapide aussi (voir triRapide.cc )


// ################## exo 4  #####################

/* Principe:
Un graphe composé de N sommets est donné par la liste de ses arêtes dans l'ordre de leur poids croissant.
Soit T l’arbre recherché.
	La liste des arêtes est lue en commençant par l'arête de plus faible poids, notée u1.
Au départ T = {u1}.
A l'étape k l'arête uk est lue. Si elle ne forme pas de cycle avec les arêtes de T alors elle est retenue.
L’algorithme s’arrête quand le nombre d’arêtes de T est égal à N-1.

*/



void kruskal(int n,int edge[][3], int arbre[][2] ) {
	int comp[n];
	int k = 0;
	for(int x= 0; x<n; x++ ) comp[x] = x;
	for(int i=0; i<(n*(n-1)/2); i++ )
    	{
      		int x = edge[i][0];
     		 int y = edge[i][1];
     		 int aux = 0;
      		if (comp[x] != comp[y]){
			aux = comp[x];
			arbre[k][0] = x;
			arbre[k][1] = y;
			k++;
		for(int z = 0; z< n; z++)
	  		if(comp[z] == aux ) comp[z]= comp[y];
      		}

   	 }
	cout<< "\n Kruskal ok"<<endl;
}

// ################## PRINT  #####################

void afficher(int m, int edge[][3])
{

  cout<<endl<<"Affichage de edge"<<endl;
  for (int i= 0; i<m; i++) {
	  cout<<edge[i][0]<<" "<<edge[i][1]<<" "<<edge[i][2];
	  cout<<endl;
}
}

void AffichageGraphique(int n, int point[][2], int arbre[][2]);       // Cree le fichier Arbre.ps qui affiche
/*                                                                     // les points et l'arbre de Kruskal.
{ofstream output;
 output.open("Arbre.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;
 for(int i=0;i<n;i++)
   {output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
   output << "0 setgray" <<endl;
   output << "fill" <<endl;
   output << "stroke"<<endl;
   output << endl;
   }
 output << endl;
 for(int i=0;i<n-1;i++)
   {output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1]
	   << " moveto" << endl;
   output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1]
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
}*/

// ################## MAIN  #####################

int main(){
  int n;             //Le nombre de points.
  cout << "Entrer le nombre de points: ";
  cin >> n;
  int m=n*(n-1)/2;   // Le nombre de paires de points.
  int point[n][2];   // Les coordonnees des points dans le plan.
  int edge[m][3];    // Les paires de points et le carre de leur longueur.
  int arbre[n-1][2]; // Les aretes de l’arbre de Kruskal.

  pointRandom(n,point);
  distances(n,m,point,edge);
  tri(m,edge);
  //tri_rapide(edge, m)
  kruskal(n,edge,arbre);
  AffichageGraphique(n,point,arbre);
  //afficher(m,edge);


  return 0;
}
