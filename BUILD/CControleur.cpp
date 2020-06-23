#include "CControleur.h"
//#include "cncc.cpp"

CControleur::CControleur()
{

}

CControleur::~CControleur()
{

}


/**************************************************************
* METHODE : CControleur::controle()
* PRESENTATION : La fonction transforme la map(.txt) en un tableau d'entiers'
*
* ENTREE : fichier "cartoTerrain.txt"
* SORTIE : Tableau d'entiers'
* **************************************************************/
void CControleur::controle(int Map[V][V])
{	
	ifstream monFlux("cartoTerrain.txt");

	if(monFlux)
	{
		/*while(! monFlux.eof())
		{
			//Récupération des données de la map dans un tableau à 2 dimensions	
		}*/
	}
	else
	{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
}

int main(int argc, char* argv[]) 
{
	CCommande *myControleur = new CCommande(); 
	//int Map[];
	//controle(Map[][]); //remplissage de 'Map' du "cartoTerrain.txt"
	//dijkstra(int Map[V][V], int src) //Calcul final de la distance la plus courte pour atteindre un arbre selectionner
	
	
	return 0;
}