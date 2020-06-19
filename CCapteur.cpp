#include "CCapteur.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CCapteur.cpp
 * PRESENTATION : fichier source de définition du capteur de signaux balise
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/

/**************************************************************
* METHODE : CCapteur::CCapteur()
* PRESENTATION : Contructeur de la classe CCapteur
*
* **************************************************************/

CCapteur::CCapteur()
{
	iEtatCapteur = 0;
}

/**************************************************************
* METHODE : CCapteur::CCapteur(int _iEtatCapteur)
* PRESENTATION : Contructeur de la classe CCapteur avec initialisation de l'état du capteur
*
* **************************************************************/

CCapteur::CCapteur(int _iEtatCapteur)
{
	iEtatCapteur = _iEtatCapteur;
}

/**************************************************************
* METHODE : CCapteur::GetEtatCapteur()
* PRESENTATION : Donne l'état du capteur
*
* SORTIE :
*	int iEtatCapteur
* **************************************************************/

int CCapteur::GetEtatCapteur()
{
	return iEtatCapteur;
}

/**************************************************************
* METHODE : CCapteur::SetEtatCapteur(int _iEtatCapteur)
* PRESENTATION : définie l'état du capteur
*
* **************************************************************/

void CCapteur::SetEtatCapteur(int _iEtatCapteur)
{
	iEtatCapteur = _iEtatCapteur;
}