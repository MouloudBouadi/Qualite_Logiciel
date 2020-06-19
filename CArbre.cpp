#include "CArbre.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CArbre.cpp
 * PRESENTATION : fichier source de définition d'arbres
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/

/**************************************************************
* METHODE : CArbre::CArbre()
* PRESENTATION : Contructeur de la classe CArbre
*
* **************************************************************/

CArbre::CArbre()
{
	iArbreX = 0;
	iArbreY = 0;
	iStatut = 0; //Arbre non mesuré
}

/**************************************************************
* METHODE : CArbre::CArbre(int _iArbreX, int _iArbreY,int iStatus)
* PRESENTATION : Contructeur de la classe CArbre avec initialisation
*
* **************************************************************/

CArbre::CArbre(int _iArbreX, int _iArbreY, int _iStatut)
{
	iArbreX = _iArbreX;
	iArbreY = _iArbreY;
	iStatut = _iStatut;
}

/**************************************************************
* METHODE : Mesure()
* PRESENTATION : Change le statut de l'abre pour mesuré
*
* **************************************************************/

int CArbre::Mesure()
{
	if (iStatut == NONMESURE)
	{
		iStatut = MESURE;
		return 0;
	}
	if (iStatut == MESURE)
	{
		std::cout << "L'arbre a déjà été mesuré \n";
		return 0;
	}
	else
	{
		return -1;
	}

}

/**************************************************************
* METHODE : CArbre::getArbreX()
* PRESENTATION : Donne la coordonné X de l'arbre
*
* RETOURNE: int iArbreX
* **************************************************************/

int CArbre::getArbreX()
{
	return iArbreX;
}

/**************************************************************
* METHODE : CArbre::getArbreY()
* PRESENTATION : Donne la coordonné Y de l'arbre
*
* RETOURNE: int iArbreY
* **************************************************************/

int CArbre::getArbreY()
{
	return iArbreY;
}

/**************************************************************
* METHODE : CArbre::~CArbre()
* PRESENTATION : Destructeur de la classe CArbre
*
* **************************************************************/

CArbre::~CArbre()
{
	
}