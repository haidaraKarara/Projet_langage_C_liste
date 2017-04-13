#include <stdio.h>
#include <stdlib.h>
#include "insererMembre.h"

int main()
{
    FILE *f= fopen("membre.txt","r+");
    pliste l = creerListeVide();
    plisteFormation form = creerListeVideFormation();
    Membre unMembre;
    int i = 0,key;
    int  nombreDeFormation;
    //Chargement de la liste chainée
    char *chaineDeParcours;
    size_t nbrOctet = 400;
	chaineDeParcours = (char*)malloc(sizeof(char));
	if (f == NULL)
	{
        exit(EXIT_FAILURE);
	}
	if (getline(&chaineDeParcours,&nbrOctet,f) == -1)
	{
	 	goto label1;
	}
	else
	{

		do
		{
			unMembre =  chargerListeChainee(f,chaineDeParcours);
			//printf("%s\n",unMembre.formation[0].intitule);
			insererDernier(unMembre,&l);
			//printf("%s\n",l->m.formation[0].intitule);
			for (i = 0; i < unMembre.nformation; ++i)
			{
				//Ajour d'une formation dans la liste de formation d'un membre.
				insererEnQueue(unMembre.formation[i],&form);
			}
		}while(getline(&chaineDeParcours,&nbrOctet,f) != -1);
	}
	//fclose(f);

	//Fin chargement de la liste chainée
	int choix1 = 0;
	system("clear"); 
	printf("\n\n\t\t                     GESTION DES MEMBRE D'UNE ASSOCIATION\n\n");
	label1:
    printf("\n\t\t                      ++++++++++++++++++++++++++++++   ");
	printf("\n\t\t                      ------------------------------   ");
	printf("\n\t\t                              '''   '''  '''           ");
	printf("\n\t\t                      '''''''  MENU PRINCIPAL ''''''   ");
	printf("\n\t\t                              '''   '''  '''           ");
	printf("\n\n\t\t                                                     ");
	printf("\n\n\t\t                      1: Inserer un membre           ");
	printf("\n\n\t\t                      2: Modifier un membre     	 ");
	printf("\n\n\t\t                      3: Supprimer un membre 		 ");
	printf("\n\n\t\t                      4: Quitter                     ");
	printf("\n\n\t\t                      								 ");
	printf("\n\n\t\t                      +++++++++++++++++++++++++++++++");
	printf("\n\n");
	printf("\n      Votre choix ?  ");
	scanf("%d",&choix1);
	switch(choix1)
	{
		case 1  :
					unMembre = creerMembre(&nombreDeFormation);
					insererDernier(unMembre,&l);
					for (i = 0; i < nombreDeFormation; ++i)
					{
						//Ajour d'une formation dans la liste de formation d'un membre.
						insererEnQueue(unMembre.formation[i],&form);
					}
					SystemPause();
					system("clear");)
                    goto label1;
		case 2 :
				    ModifierMembre(&l) ;
					SystemPause();
					system("clear");
					goto label1;
		case 3 :
					printf("\nDonne le numéro du membre à supprimer : ");
					scanf("%d",&key);
					if ( 0 == supprimerMembre(&l,key))
					{
						printf("\nLe numéro de ce membre n'existe pas.\n");
					}
					else
					{
						printf("\nLe membre %d a ete supprimer avec succes ! \n",key);
					}
					SystemPause();
					system("clear");
					goto label1;
		case 4 :
					//remove("membre.txt");
					//fclose(f);
					//f = fopen("membre.txt","w");
					//fclose(f);
					save(l,form);//Enregistrement dans le fichier lors de la fermeture du programme.
					//fclose(f1);
					exit(0);
					//goto label1;
		default :
					printf("\n\t\tOUPS MAUVAIS CHOIX !!\n");
					SystemPause();
					system("clear");
					goto label1;
	}
    return 0;
}
/*if (f != NULL)
					{
						chargerListeChainee(f);

					}
					else
					{
						printf("\nERREURE D'OUVERTURE DE FICHIER ! ");
					}*/