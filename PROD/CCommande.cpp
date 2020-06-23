#include "CCommande.h"

using namespace std; 
/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CCommande.cpp
 * PRESENTATION : fichier source de définition de la commande
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/

/**************************************************************
* METHODE : CCommande::CCommande()
* PRESENTATION : Contructeur de la classe CCommande
*
* **************************************************************/

CCommande::CCommande()
{
	int iX;
	int iY;

	ifstream monFlux("listeDeControle.txt");

	if(monFlux)
	{
		while(! monFlux.eof())
		{
			monFlux >> iX;
			//cout << "iX :" << iX <<endl;
			monFlux >> iY;
			//cout << "iY :" << iY <<endl;
			CArbre* pArbre = new CArbre(iX, iY, CArbre::NONMESURE);  //création d'un arbre avec les données lues'
			addArbre(pArbre); //ajout de l'arbre au vecteur d'arbres
		}
	}
	else
	{
    cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
}

/**************************************************************
* METHODE : CCommande::addArbre(CArbre* p_arbre)
* PRESENTATION : La fonction ajoute un arbre au vecteur vArbres 
*
* ENTREE : p_arbre : pointeur sur un arbre
* **************************************************************/

void CCommande::addArbre(CArbre* p_arbre)
{
	vArbres.push_back(p_arbre);
}

/**************************************************************
* METHODE : CCommande::~CCommande()
* PRESENTATION : Destructeur de la classe CCommande
*
* **************************************************************/

CCommande::~CCommande()
{
	//Destructeur de la classe CCommande
}

