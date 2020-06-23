#include "CArbre.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n� TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CArbre.cpp
 * PRESENTATION : fichier source de d�finition d'arbres
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
	iStatut = 0; //Arbre non mesur�
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
* PRESENTATION : Change le statut de l'abre pour mesur�
*
* **************************************************************/

void CArbre::setStatut(int _iStatut)
{
	iStatut = _iStatut;
}

/**************************************************************
* METHODE : CArbre::getArbreX()
* PRESENTATION : Donne la coordonn� X de l'arbre
*
* RETOURNE: int iArbreX
* **************************************************************/

int CArbre::getArbreX()
{
	return iArbreX;
}

/**************************************************************
* METHODE : CArbre::getArbreY()
* PRESENTATION : Donne la coordonn� Y de l'arbre
*
* RETOURNE: int iArbreY
* **************************************************************/

int CArbre::getArbreY()
{
	return iArbreY;
}


int CArbre::getStatut()
{
	return iStatut;
}

/**************************************************************
* METHODE : CArbre::~CArbre()
* PRESENTATION : Destructeur de la classe CArbre
*
* **************************************************************/

CArbre::~CArbre()
{
	
}