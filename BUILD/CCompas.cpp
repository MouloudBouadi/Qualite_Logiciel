#include "CCompas.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CCompas.cpp
 * PRESENTATION : fichier source de définition du compas. Géolocalisation du robiot
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

 /**************************************************************
 * METHODE : CCompas::CCompas()
 * PRESENTATION : Contructeur de la classe CCompas
 * Initialisation des coordonnées du ROBIOT dans l'angle superieur gauche du terrain forestier
 *
 * **************************************************************/

CCompas::CCompas()
{
	iCoordX = 0;
	iCoordY = 0;
}


/**************************************************************
* METHODE : CCompas::CCompas()
* PRESENTATION : Contructeur de la classe CCompas
*
* **************************************************************/

CCompas::CCompas(int i_CoordX, int i_CoordY)
{
	iCoordX = i_CoordX;
	iCoordY = i_CoordY;
}

/**************************************************************
* METHODE : CCompas::GetCompasX()
* PRESENTATION : Fonction permettant de retourner la coordonnée en X du ROBIOT
*
* SORTIE
*	int iCoordX : La coordonnée en X du ROBIOT
* **************************************************************/

int CCompas::GetCompasX()
{
	return iCoordX;
}

/**************************************************************
* METHODE : CCompas::GetCompasY()
* PRESENTATION : Fonction permettant de retourner la coordonnée en Y du ROBIOT
*
* SORTIE
*	int iCoordY : La coordonnée en Y du ROBIOT
* **************************************************************/

int CCompas::GetCompasY()
{
	return iCoordY;
}

/**************************************************************
* METHODE : CCompas::SetCompasX(int _iCoordX)
* PRESENTATION : Fonction permettant de fixer la coordonnée en X du ROBIOT
*
* ENTREE :
*	int _iCoordX : La coordonnée en X souhaitée pour le ROBIOT
* **************************************************************/

void CCompas::SetCompasX(int _iCoordX)
{
	iCoordX = _iCoordX;
}

/**************************************************************
* METHODE : CCompas::SetCompasY(int _iCoordY)
* PRESENTATION : Fonction permettant de fixer la coordonnée en Y du ROBIOT
*
* ENTREE :
*	int _iCoordY : La coordonnée en Y souhaitée pour le ROBIOT
* **************************************************************/

void CCompas::SetCompasY(int _iCoordY)
{
	iCoordY = _iCoordY;
}

/**************************************************************
* METHODE : CCompas::~CCompas()
* PRESENTATION : Destructeur de la classe CCompas
*
* **************************************************************/

CCompas::~CCompas()
{

}