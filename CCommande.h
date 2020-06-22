#pragma once
#include "CArbre.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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
 * SOURCE       : CCommande.h
 * PRESENTATION : fichier entête de définition de la commande
 * 
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1 
 * DATE         : 18/06/2020
 * 
 ***************************************************************/ 

class CCommande
{
private:
	std::vector<CArbre*> vArbres;

public:
	CCommande();
	//CCommande(std::string s_monFichier);
	~CCommande();

	void addArbre(CArbre* p_arbre);
	void MoveToNextArbre();
};

