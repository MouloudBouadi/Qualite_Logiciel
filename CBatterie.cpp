#include "CBatterie.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CBatterie.cpp
 * PRESENTATION : fichier source de définition de la batterie
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

/**************************************************************
* METHODE : CBatterie::CBatterie()
* PRESENTATION : Contructeur de la classe CBatterie
*
* **************************************************************/

CBatterie::CBatterie()
{
	iNiveauBatterie = 0;
}

/**************************************************************
* METHODE : CBatterie::CBatterie(int i_niveauBatterie)
* PRESENTATION : Contructeur de la classe CBatterie avec intitialisation du niveau de batterie
*
* **************************************************************/

CBatterie::CBatterie(int i_niveauBatterie)
{
	iNiveauBatterie = i_niveauBatterie;
}

/**************************************************************
* METHODE : CDoor::getStatus()
* PRESENTATION : RETOURNE LE POURCENTAGE DE BATTERIE RESTANT 
*
* SORTIE :
*	int : % DE BATTERIE
* **************************************************************/

int CBatterie::GetNiveauBatterie()
{
	return iNiveauBatterie;
}

/**************************************************************
* METHODE : CBatterie::SetNiveauBatterie(int i_niveauBatterie)
* PRESENTATION : définie le niveau de batterie restant
*
* ENTREE : 
*	int i_niveauBatterie : le % de batterie du robiot
*
* **************************************************************/

void CBatterie::SetNiveauBatterie(int i_niveauBatterie)
{
	iNiveauBatterie = i_niveauBatterie;
}