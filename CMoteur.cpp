#include "CMoteur.h"
/**************************************************************
* METHODE : CMoteur::CMoteur()
* PRESENTATION : Contructeur de la classe CMoteur
*
* **************************************************************/
CMoteur::CMoteur()
{
	iEtatMoteurGauche = 0; //Moteur a l'arret. Mettre 1 pour etat de fonctionnement
	iEtatMoteurDroite = 0; //Moteur a l'arret. Mettre 1 pour etat de fonctionnement
}

/**************************************************************
* METHODE : CMoteur::GetEtatMoteur()
* PRESENTATION : Fonction permettant de retourner l'etat du moteur entré en paramètre
*
* ENTREE
	string IDmoteur : choix du moteur gauche ou droit
* SORTIE
*	int iEtatMoteurGauche : etat du moteur gauche
*	int iEtatMoteurDroite : etat du moteur droit
*	0 : arret | 1 : marche avant | -1 : marche arrière | -2 : moteur non reconnu'

* **************************************************************/
int CMoteur::GetEtatMoteur(string IDmoteur)
{
	if (IDmoteur == "MoteurGauche")
	{
		return iEtatMoteurGauche;
    }
	else if(IDmoteur == "MoteurDroit")
	{
        return iEtatMoteurDroite;
    }
	else 
	{
        return -2; //moteur non reconnu
	}
}
/**************************************************************
* METHODE : CCapteur::SetEtatCapteur(int _iEtatCapteur)
* PRESENTATION : définie l'état des moteurs
*
* ENTREE
*	int i_EtatMoteurGauche : definition de l'etat du moteur gauche'
*	int i_EtatMoteurdroite : definition de l'etat du moteur droit'
* **************************************************************/
void CMoteur::SetEtatMoteur(int _iEtatMoteurGauche, int _iEtatMoteurDroite)
{
	iEtatMoteurGauche = _iEtatMoteurGauche;
	iEtatMoteurDroite = _iEtatMoteurDroite;
}

/**************************************************************
* METHODE : CMoteur::Avancer()
* PRESENTATION : Contructeur de la classe CMoteur
*
* SORTIE
*	retourne un entier : 0 si OK sinon -1 pour erreur
* **************************************************************/
int CMoteur::Avancer()
{
	SetEtatMoteur(1,1); //On avance les 2 moteurs
	if(GetEtatMoteur("MoteurGauche") == 1 && GetEtatMoteur("MoteurDroite") == 1)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/**************************************************************
* METHODE : CMoteur::Reculer()
* PRESENTATION : Contructeur de la classe CMoteur
*
* SORTIE
*	retourne un entier : 0 si OK sinon -1 pour erreur
* **************************************************************/
int CMoteur::Reculer()
{
	SetEtatMoteur(-1,-1); //On recule les 2 moteurs
	if(GetEtatMoteur("MoteurGauche") == -1 && GetEtatMoteur("MoteurDroite") == -1)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/**************************************************************
* METHODE : CMoteur::Gauche()
* PRESENTATION : Contructeur de la classe CMoteur
*
* SORTIE
*	retourne un entier : 0 si OK sinon -1 pour erreur
* **************************************************************/
int CMoteur::Gauche()
{
	SetEtatMoteur(-1,1);//moteur gauche recule et moteur droit avance pour tourner à gauche
	if(GetEtatMoteur("MoteurGauche") == -1 && GetEtatMoteur("MoteurDroite") == 1)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

/**************************************************************
* METHODE : CMoteur::Droite()
* PRESENTATION : Contructeur de la classe CMoteur
*
* SORTIE
*	retourne un entier : 0 si OK sinon -1 pour erreur
* **************************************************************/
int CMoteur::Droite()
{
	SetEtatMoteur(1,-1);//moteur gauche avance et moteur droit recule pour tourner à droite
	if(GetEtatMoteur("MoteurGauche") == 1 && GetEtatMoteur("MoteurDroite") == -1)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
