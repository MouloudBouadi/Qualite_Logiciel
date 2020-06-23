#pragma once
//#include "CArbre.h"
#include "CBatterie.h"
#include "CCapteur.h"
#include "CCommande.h"
#include "CCompas.h"
#include "CControleur.h"
#include "CDijsktra.h"
#include "CMesure.h"
#include "CMoteur.h"
#include "CDijsktra.h"

/**************************************************************
 * 
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615  
 * Reproduction et diffusion interdites. 
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 * 
 * SOUS-SYSTEME : ROBIOT SIMU
 * 
 * SOURCE       : CControleur.h
 * PRESENTATION : fichier entête de définition du controleur
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CControleur
{
private:
	

public:
	CControleur();
	~CControleur();
	void controle(int Map[V][V]);
};
