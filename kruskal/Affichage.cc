#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


          
void AffichageGraphique(int n, int point[][2], int arbre[][2])       // Cree le fichier Exemple.ps qui affiche
                                                                     // les points et l'arbre de Kruskal.
{ofstream output;                           
 output.open("Arbre.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;
 output << "%%BoundingBox: 0 0 612 792" << endl;
 output << endl;  
 for(int i=0;i<n;i++)
 	
   {
   point[i][0]=10*i; point[i][1]=(int)25*((i/10)*(i/10)*(i/10) - 9*(i/10)*(i/10) + 22*(i/10));
   output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
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
}
