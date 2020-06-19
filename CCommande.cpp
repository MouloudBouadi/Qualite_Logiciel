#include "CCommande.h"

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
	//rempli le vecteur d'arbre en lisant les coordonnées dans le fichier de simu
	//initialisation des arbres au statut NONMESURE
	//Utilise la méthode addArbre'
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
* METHODE : CCommande::MoveToNextArbre()
* PRESENTATION : Passe d'un arbre au suivant dans le vecteur d'arbre vArbres
*
* **************************************************************/

void CCommande::MoveToNextArbre()
{

}