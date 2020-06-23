#include "pch.h"

/**************************************************************
 *
 * Copyright (c) ecotree - contrat n° TNK/DEV/CCTP-20200615
 * Reproduction et diffusion interdites.
 * Developpe par CDTI G2 Corp
 * Projet ROBIOT
 *
 * SOUS-SYSTEME : ROBIOT SIMU
 *
 * SOURCE       : test.cpp
 * PRESENTATION : fichier source de test du projet ROBIOT
 *
 * AUTEUR       : Mouloud Jean-Mathieu Etienne
 * VERSION CVS  : V1
 * DATE         : 18/06/2020
 *
 ***************************************************************/


 /*======================
 =======Unit tests=======
 ========================*/

 /*====CArbre tests====*/

//Test de la création d'un arbre avec paramètres d'initialisation
TEST(CArbreTest, CreationArbreTest)
{
    CArbre* pArbre1 = new CArbre(5, 2, 0);

    ASSERT_EQ(pArbre1->getArbreX(), 5);
    ASSERT_EQ(pArbre1->getArbreY(), 2);
    ASSERT_EQ(pArbre1->getStatut(), 0);
}

//test du changement de statut d'un arbre
TEST(CArbreTest, ChgtStatutArbreTest)
{
    CArbre* pArbre1 = new CArbre(5, 2, 0);
    pArbre1->setStatut(1);

    ASSERT_EQ(pArbre1->getStatut(), 1);
}

 /*====CMesure tests====*/

//Test du changement d'état de l'arbre après l'avoir mesuré
TEST(CMesureTest, NouvelleMesureTest)
{
    CArbre* pArbre = new CArbre(5, 2, 0);
    CMesure maMesure;
    maMesure.NouvelleMesure(pArbre);

    ASSERT_EQ(pArbre->getStatut(), CArbre::MESURE);
}


//Test de la consomation d'une mesure
TEST(CMesureTest, ConsoMesureTest)
{
    CArbre* pArbre = new CArbre(5, 2, 0);
    CMesure maMesure;
    maMesure.NouvelleMesure(pArbre);

    ASSERT_EQ(maMesure.getConsoMesure(), 30);
}

//Test de la consomation de 2 mesures
TEST(CMesureTest, Conso2MesureTest)
{
    CArbre* pArbre1 = new CArbre(5, 2, 0);
    CArbre* pArbre2 = new CArbre(3, 6, 0);
    CMesure maMesure;
    maMesure.NouvelleMesure(pArbre1);
    maMesure.NouvelleMesure(pArbre2);

    ASSERT_EQ(maMesure.getConsoMesure(), 60);
}

//Test du temps d'une mesure
TEST(CMesureTest, TempsMesureTest)
{
    CArbre* pArbre = new CArbre(5, 2, 0);
    CMesure maMesure;
    maMesure.NouvelleMesure(pArbre);

    ASSERT_EQ(maMesure.getTempsMesure(), 5);
}

//Test du temps de 2 mesures
TEST(CMesureTest, Temps2MesureTest)
{
    CArbre* pArbre1 = new CArbre(5, 2, 0);
    CArbre* pArbre2 = new CArbre(3, 6, 0);
    CMesure maMesure;
    maMesure.NouvelleMesure(pArbre1);
    maMesure.NouvelleMesure(pArbre2);

    ASSERT_EQ(maMesure.getTempsMesure(), 10);
}

/*====CCapteur tests====*/

//test de la création du capteur
TEST(CCapteurTest, CreationCapteurTest)
{
    CCapteur monCapteur = CCapteur(0);

    ASSERT_EQ(monCapteur.GetEtatCapteur(), 0);
}

//Test du changement d'état du capteur
TEST(CCapteurTest, ChgtEtatCapteurTest)
{
    CCapteur monCapteur = CCapteur(CCapteur::LIBRE);
    monCapteur.SetEtatCapteur(CCapteur::OBSTACLE);

    ASSERT_EQ(monCapteur.GetEtatCapteur(), CCapteur::OBSTACLE);
}

/*====CBatterie tests====*/

//test de la création d'une batterie avec initialisation de son niveau de charge
TEST(CBatterieTest, CréationBatterie)
{
    CBatterie maBatterie = CBatterie(80);

    ASSERT_EQ(maBatterie.GetNiveauBatterie(), 80);
}

//test du changement de niveau de chage batterie
TEST(CBatterieTest, ChgtNiveauBatterie)
{
    CBatterie maBatterie = CBatterie(80);
    maBatterie.SetNiveauBatterie(30);

    ASSERT_EQ(maBatterie.GetNiveauBatterie(), 30);
}

/*====CCompas tests====*/

//Test de la création d'un compas avec initialisation de la position
TEST(CCompasTest, CreationCompasTest)
{
    CCompas monCompas = CCompas(12, 4);

    ASSERT_EQ(monCompas.GetCompasX(), 12);
    ASSERT_EQ(monCompas.GetCompasY(), 4);
}

//Test de la modification de la position du compas
TEST(CCompasTest, ChgtPositionCompasTest)
{
    CCompas monCompas = CCompas(12, 4);
    monCompas.SetCompasX(2);
    monCompas.SetCompasY(6);

    ASSERT_EQ(monCompas.GetCompasX(), 2);
    ASSERT_EQ(monCompas.GetCompasY(), 6);
}

/*====CMoteur tests====*/

//Test de création des moteur du robiot création 
TEST(CMoteurTest, CreationMoteurTest)
{
    CMoteur mesMoteur = CMoteur();

    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurGauche"), 0);
    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurDroit"), 0);
}

//Test de la methode Avancer()
TEST(CMoteurTest, AvanceMoteurTest)
{
    CMoteur mesMoteur = CMoteur();
    mesMoteur.Avancer();

    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurGauche"), 1);
    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurDroit"), 1);
}
//Test de la methode Reculer()
TEST(CMoteurTest, ReculeMoteurTest)
{
    CMoteur mesMoteur = CMoteur();
    mesMoteur.Reculer();

    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurGauche"), -1);
    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurDroit"), -1);
}
//Test de la methode Gauche()
TEST(CMoteurTest, GaucheMoteurTest)
{
    CMoteur mesMoteur = CMoteur();
    mesMoteur.Gauche();

    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurGauche"), -1);
    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurDroit"), 1);
}
//Test de la methode Droite()
TEST(CMoteurTest, DroiteMoteurTest)
{
    CMoteur mesMoteur = CMoteur();
    mesMoteur.Droite();

    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurGauche"), 1);
    ASSERT_EQ(mesMoteur.GetEtatMoteur("MoteurDroit"), -1);
}
