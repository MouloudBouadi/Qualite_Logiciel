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
 * PRESENTATION : fichier source de définition du compas
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

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

int CCompas::GetCompasX()
{
	return iCoordX;
}

int CCompas::GetCompasY()
{
	return iCoordY;
}

void CCompas::SetCompasX(int _iCoordX)
{
	iCoordX = _iCoordX;
}

void CCompas::SetCompasY(int _iCoordY)
{
	iCoordY = _iCoordY;
}
