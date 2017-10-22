#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// ################## exo 1  #####################
void voisinstrandom(int n, int m, vector<int> voisins[]){
	int x = 0, y= 0;
	bool appartient = true;
	x = rand()%n;
	y = rand()%n;
	
	for(int i= 0;i<m;i++){
		appartient = true;
		
		while(appartient){
			appartient = false;
			x = rand()%n;
			y = rand()%n;
			if(x==y) {
				appartient = true;
				//x = rand()%n;
				}
			for(int i = 0;i<voisins[y].size();i++){
				if(x == voisins[y][i] ){ 
					appartient = true; 
				}
			}
		}
			
			voisins[y].push_back(x);
			voisins[x].push_back(y);				
	}
	
cout<<"voisinage aleatoire ok"<<endl<<endl;
}


void afficherVect(int n, vector<int> voisins[]){
	for(int i = 0;i<n;i++){
		if(!voisins[i].empty() ){
			cout<<"voisins de "<<i<<" : ";
			for(int j = 0;j<voisins[i].size();j++)
				cout<<voisins[i][j]<<" |";
				cout<<endl;
		}
	}
}

void afficherTab(int n, int tab[]){
	for(int i=0; i<n; i++){
	if(tab[i] != -1)
		cout<<i<<" : [ "<<tab[i]<<" ]"<<endl;
	}

}

// ################## exo 2  #####################

void parcoursLargeur(int n,vector<int> voisins[],int niveau[],int ordre[],int pere[] ) {
	
	for(int i=0; i<n; i++) {
		niveau[i]  = -1; ordre[i]  = -1; pere[i]  = -1;
		}
		
	int dv[n];       // deja vu ( tableau qui indique si le sommet a été visité ou pas )
	int r = 0; 	  // racine
	vector<int> at ;  //la file 
	int t = 0;	   // le temps
	
	for(int i=0;i<n;i++)  dv[i] = 0;
	
	dv[r] = 1; ordre[r] = 1; pere[r] = r; niveau[r] = 0;
	at.push_back(r);
	t = 2;
	while(!at.empty() ){
		int v = at[0];
		at.erase(at.begin());
		for(int x=0; x<voisins[v].size(); x++){
			if(dv[voisins[v][x]] == 0){
				dv[voisins[v][x]] = 1;
				at.push_back(voisins[v][x]);
				ordre[voisins[v][x]] = t; t = t+1;
				pere[voisins[v][x]] = v;
				niveau[voisins[v][x]] = niveau[v]+1;
				
			}
		} 
	}
	cout<<"\n\tParcours Largeur ok"<<endl;
}

//############## exo3 ##########################

void ecritureTaille(int n, int niveau[]){
	int niveauTries[n];
	int pasMemeComp = 0;
	for(int i=0; i<n; i++) niveauTries[i]  = 0;
	for(int i=0; i<n; i++){
		int t = niveau[i];
		if(t >= 0) niveauTries[t]++;
		else pasMemeComp++;
	}
	
	for(int i=0; i<n; i++){
		if(niveauTries[i] != 0){
			cout<<"Il y'a "<< niveauTries[i] <<" sommets au niveau "<<i<<endl;
		}
	}
	cout<<"Il y'a "<< pasMemeComp <<" sommets qui ne sont pas dans la composante de 0"<<endl;

}

//################# exo 4 #######################"

void parcoursProfondeur(int n,vector<int> voisins[],int niveau[],int pere[],int debut[], int fin[] ) {
	
	int nmax = 0;
	int dv[n];       // deja vu ( tableau qui indique si le sommet a été visité ou pas )
	int r = 0; 	  // racine
	vector<int> at ;  //la pile
	int t = 0;	   // le temps
	
	for(int x=0; x<n; x++) dv[x] = 0;
	dv[r] = 1;
	at.push_back(r);
	for(int i=0; i<n; i++) {
		niveau[i]  = -1; debut[i]  = -1; fin[i] = -1; pere[i]  = -1;  
		}
	 debut[r] = 1; pere[r] = r; niveau[r] = 0;
	t = 2;
	while(!at.empty() ){
		int x = at[at.size()-1];
		//at.erase(at.begin());
		if(voisins[x].empty()){
			at.pop_back();
			fin[x] = t; t = t+1;
		}
		else{
			int y = voisins[x][voisins[x].size()-1];
			voisins[x].pop_back();
			if(dv[y] == 0){
				dv[y] = 1;
				at.push_back(y);
				debut[y] = t; t++;
				pere[y] = x;
				niveau[y] = niveau[x] +1;
				nmax = (niveau[y]>nmax) ? niveau[y] : nmax;
			}
		}

		} 
	cout<<"\n\tParcours profondeur ok \t nmax = "<<nmax<<endl;
	}

//############## main ##########################

int main(){
int n;             //Le nombre de sommets.
int m;             // Le nombre d'aretes.
cout << "Entrer le nombre de sommets: ";
cin >> n;
cout << "Entrer le nombre d'aretes: ";
cin >> m;
vector<int> voisins[n];	// Les listes des voisins. 
int pere[n];            // L'arbre en largeur.
int ordre[n];           // L'ordre de parcours.
int niveau[n];          // Le niveau du point.

int debut[n];
int fin[n];

srand(time(NULL));

voisinstrandom(n,m,voisins);

parcoursLargeur(n,voisins, niveau,ordre, pere); 
afficherVect(n, voisins);
cout<<"niveau:"<<endl;
afficherTab(n,niveau);
cout<<"pere:"<<endl;
afficherTab(n,pere);
cout<<"ordre:"<<endl;
afficherTab(n,ordre);


ecritureTaille(n,niveau);
cout<<"\n============================================"<<endl;
//voisinstrandom(n,m,voisins);
parcoursProfondeur(n,voisins,niveau,pere, debut,fin) ;
afficherVect(n, voisins);
cout<<"niveau:"<<endl;
afficherTab(n,niveau);
cout<<"pere:"<<endl;
afficherTab(n,pere);
cout<<"debut:"<<endl;
afficherTab(n,debut);
cout<<"fin:"<<endl;
afficherTab(n,fin);


ecritureTaille(n,niveau);
return 0;
}
