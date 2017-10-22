
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

// ################## exo 1  #####################

void pointRandom(int n,int point[][2]) {

int val1 = 0, val2 = 0;
  for(int i =0; i<n; i++){
    val1 = rand()%613;
    val2 = rand()%793;
    point[i][0]=val1; point[i][1]=val2;
  }
}

int distance(int point[][2],int x, int y){   // distance au carré
	return (((point[x][0] - point[y][0] ) * (point[x][0] - point[y][0] )) + ((point[x][1] - point[y][1] ) * (point[x][1] - point[y][1] ))) ; // distance au carré
	}


void voisins(int n, int dmax, int point[][2], vector<int> voisin[] ){
	
	for(int i= 0;i<n;i++){
		for(int j = i+1;j<n;j++){
			int d = distance(point, i,j);
			if (d<= (dmax*dmax)){
				voisin[i].push_back(j);
				voisin[j].push_back(i);
			}
		}
	}
	cout<<"voisinage par distance ok!"<<endl<<endl;
}


//######################  exo2 #################################

void AffichageGraphe(int n, int point[][2], vector<int> voisin[]){
 ofstream output;                           
 output.open("Graphe.ps",ios::out);
 output << "%!PS-Adobe-3.0" << endl;  // ???
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
   for(int j=0;j<voisin[i].size();j++)
   {//output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] 
   output << point[i][0] << " " << point[i][1] 
	   << " moveto" << endl;
   //output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] 
   output << point[voisin[i][j]][0] << " " << point[voisin[i][j]][1] 
	  << " lineto" << endl;
   output << "stroke" << endl;
   output << endl;
   }
}


//######################  exo3 ###################################
int triMin(int n, int traite[],int d[]){
	int imin =-1; int ref=-1;
	for(int i= 0; i<n;i++){
			
		if(traite[i]==0) {
			ref=i;
			break;
		}
	}
	for(int i= 0; i<n;i++){
			
		if(traite[i]==0 && d[i]<=d[ref]) {
			imin = i;
			//return imin;
		}
	}
	return imin;
}

void dijkstra(int n, vector<int> voisin[], int point[][2], int pere[]){
	
	int cpt=1;
	int d[n], traite[n];   // distance a la racine / traité 

	bool fini = false;
	
	for(int i=0;i<n;i++){
		d[i] = 100000000;  // infini  
		traite[i] = 0;
		pere[i] = -1;
	}
	
	int dmin = d[0], x=0;
	int r = 0; pere[r] = r; d[r] = 0;
	
	
	while(fini==false){
		fini=true;
		
		x=triMin(n,traite,d);
		if(x != -1 ){
			fini = false;
			cout<< ">>> x = "<<x<<endl;
			traite[x] = 1;
		}
		else{
			//exit(2);
			return;
		}
		for(int i = 0;i<voisin[x].size();i++){
			//fini = true;

			int y = voisin[x][i];
			if((traite[y] == 0) && (d[y] > (d[x]+(distance(point, x,y)*distance(point, x,y))))){ 
				fini = false;
				d[y] = (d[x]+(distance(point, x,y)*distance(point, x,y)));
				//dmin = (d[y]<dmin) ? d[y]+1 : dmin+1; // le minimum
				pere[y] = x;
				cout<<"y= "<<y<<" d[y]= "<<d[y]<<endl;
				
			}
		}
	}
}
	


//######################  exo4 ###################################

int construitArbre(int n, int arbre[][2], int pere[]){
	int cpt=0;
	for(int i=0; i<n; i++){
		if(pere[i]!=-1){
			arbre[i][0]=i;
			arbre[i][1]=pere[i];		
			cpt++;
		}
	
	}
	return cpt;

}


void AffichageGraphique(int n, int point[][2], int arbre[][2]){
	 ofstream output;                           
	 output.open("Dijkstra.ps",ios::out);
	 output << "%!PS-Adobe-3.0" << endl;
	 output << "%%BoundingBox: 0 0 612 792" << endl;
	 output << endl;  
	 for(int i=0;i<n;i++)
	   {
		   output << point[i][0] << " " << point[i][1] << " 3 0 360 arc" <<endl;
		   output << "0 setgray" <<endl;
		   output << "fill" <<endl;
		   output << "stroke"<<endl;
		   output << endl;
	   }
	 output << endl;
	 for(int i=0;i<n-1;i++)
	   {
		   output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] 
			   << " moveto" << endl;
		   output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] 
			  << " lineto" << endl;
		   output << "stroke" << endl;
		   output << endl;
	   }
}

//#####################   PRINTING  #############################

void afficherVect(int n, vector<int> voisins[]){
	for(int i = 0;i<n;i++){
		if(!voisins[i].empty() ){
			cout<<"voisins de "<<i<<" : ";
			for(unsigned int j = 0;j<voisins[i].size();j++)
				cout<<voisins[i][j]<<" |";
				cout<<endl;
		}
	}
	//cout<<"fin\n";
}

void afficherTab(int n, int tab[]){
	for(int i=0; i<n; i++){
	if(tab[i] != -1)
		cout<<i<<" : [ "<<tab[i]<<" ]"<<endl;
	}
}



//############## main ##########################

int main(){
	srand(time(NULL));
	int n;                   //Le nombre de points.
	int m;                   //Le nombre d aretes.
	cout << "Entrer le nombre de points: ";
	cin >> n;

	int dmax=50;             // La distance jusqu'a laquelle on relie deux points.

	vector<int> voisin[n];   // Les listes de voisins.          
	int point[n][2];         // Les coordonnees des points.

	int d[n];                // La distance a la racine.
	int arbre[n-1][2];       // Les aretes de l'arbre de Dijkstra.
	int pere[n];             // La relation de filiation de l'arbre de Dijkstra.
	//int l[n]; for(int i= 0; i<n;i++){ l[n] = 12000;} // distance a la racine

	pointRandom(n,point);
	voisins(n, dmax,point,voisin);
	
	afficherVect(n,voisin);
	AffichageGraphe(n,point,voisin);	// affichage du graphe entier generé
	dijkstra(n,voisin,point,pere);
	afficherTab(n,pere);
	construitArbre(n, arbre, pere);	  
	AffichageGraphique(n,point,arbre);	
	
return 0;
}
