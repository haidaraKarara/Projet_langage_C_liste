#include <stdio.h>
#include <stdlib.h>
#include "insererMembre.h"
#include <string.h>
//Ecrire dans le fichier au moyen d'une liste chainee
void save(pliste l,plisteFormation form)
{
		int i = 0;
		FILE * f;
		f = fopen("membre.txt","w");
		while(l!= NULL)
			{
				fprintf(f,"%d:%s:%s:%s",l->m.numero,l->m.nom,l->m.prenom,l->m.adresse);		 
				//form->f = l->m.formation;
				while(i < l->m.nformation)
				{
					fprintf(f,":%d:%s:%d",form->f.codeClasse,form->f.intitule,form->f.annee);
					form = form->suiv;
					i++;
				}
				i = 0;
				fprintf(f,"\n");
				l = l->suiv;
			}
			fclose(f);		
}//Fonction permettant de supprimer un membre
int supprimerMembre(pliste 	*l, int key)
{
	pliste tete = *l;
	pliste avant =*l;
	if((*l)->m.numero == key)
	{
		pliste k = *l;
		(*l) = (*l)->suiv;
		free(k);
		return 1;
	}
	while(tete->suiv != NULL && tete->m.numero != key)
	{
		/*if(tete->info == element)
		{
			avant->suiv = tete->suiv;
			tete->suiv = NULL;
			free(tete);
		}
		break;*/
		avant = tete;
		tete = tete->suiv;
	}
	if(key == tete->m.numero)
	{
		avant->suiv = tete->suiv;
		free(tete);
		return 1;
	}
	return 0;
}
//Fonction permttant de rechercher l'existance d'un numéro de membre.
int rechercherNumeroMembre()
{
	return 1;
}
/*Fonction permettant de charger la liste chainée (celle des membre et des formations)  au démarrage du programme.
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
char * strtok(const char * s, const char * separators);
 
int atoi(const char * s);
long atol(const char * s);
double atof(const char * s);
*/
Membre chargerListeChainee(FILE *f,char * chaineDeParcours)
{
	char separateur[] = ":";
	char *sousChaine;
	int i = 0;
	Membre unMembre;
	unMembre.nom = (char*)malloc(sizeof(char) * 30);
	unMembre.prenom = (char*)malloc(sizeof(char) * 30);
	unMembre.adresse = (char*)malloc(sizeof(char) * 20);
	unMembre.formation= (Formation*)malloc(sizeof(Formation) * 5);//supposoons qu'il a fait 5 formations aux max.
	sousChaine = strtok(chaineDeParcours,separateur);
	unMembre.numero = atoi(sousChaine);
	sousChaine = strtok(NULL, separateur);//pour pouvoir extraire le prochain souschaine de la mm ligne.
	unMembre.nom = sousChaine;
	sousChaine = strtok(NULL, separateur);
	unMembre.prenom = sousChaine;
	sousChaine = strtok(NULL, separateur);
	unMembre.adresse = sousChaine;
	sousChaine = strtok(NULL, separateur);
	do
	{
		unMembre.formation[i].codeClasse = atoi(sousChaine);
        sousChaine = strtok(NULL, separateur);
		unMembre.formation[i].intitule = (char*)malloc(sizeof(char) * 15);
        unMembre.formation[i].intitule = sousChaine;
        sousChaine = strtok(NULL, separateur);
        unMembre.formation[i].annee = atoi(sousChaine);
	    sousChaine = strtok(NULL, separateur);
        i = i + 1;//A la sortie nombreDeFormation = nombre de formation suivi par le membre.
    }while(sousChaine !=NULL);    		        
	//initialisation du champ nombre de formation suivi par un membre
	//*nombreDeFormation = i;
	unMembre.nformation = i;	    
	return unMembre;
}
//Créer une nouvelle liste  vide  de formation
plisteFormation creerListeVideFormation()
{
	plisteFormation f = (plisteFormation)malloc(sizeof(struct listeFormation) * 10);
	f = NULL;
	return f;
}
//Créer une nouvelle liste de formation
plisteFormation nouvelleListeFormation(Formation k,plisteFormation s)
{
	plisteFormation n = (plisteFormation)malloc(sizeof(struct listeFormation));
	n->f = k;
	n->suiv = s;
	return n;
}
//Ajout d'une formation dans la liste de formation: les valeur de m ont été déja saisi.
void insererEnQueue(Formation k, plisteFormation *f)
{  
    plisteFormation n =nouvelleListeFormation(k,NULL);
	if(*f==NULL) *f=n ;
	else {
		plisteFormation f1=*f;
		while(f1->suiv!=NULL)
		{
			f1=f1->suiv;
		}
		f1->suiv=n;
	}
}
//creation d'une liste vide
pliste creerListeVide()
{
	pliste l = (pliste)malloc(sizeof(struct liste));
	l = NULL;
	return l;
}
//Créer une nouvelle liste
pliste nouvelleListe(Membre k,pliste s)
{
	pliste n = (pliste)malloc(sizeof(struct liste));
	n->m = k;
	n->suiv = s;
	return n;
}
//Ajout d'un membre dans la liste
void insererDernier(Membre k, pliste *l)
{
	pliste n = nouvelleListe(k,NULL);
	if (*l == NULL)
	{
		*l = n;
	}
	else
	{
		pliste l1 = *l;
		while(l1->suiv != NULL) l1 = l1->suiv;
		l1->suiv = n;
	}
}
//FONCTION PERMETTANT DE CREER UN NOUVEAU MEMBRE
Membre creerMembre(int *nombreDeFormation)
{
	*nombreDeFormation = 0;
	Membre m; int i = 0;
	printf("\n\nIdentifiant membre :  ");
	scanf("%d",&m.numero);
	m.nom = (char*)malloc(sizeof(char) * 30);
	m.prenom = (char*)malloc(sizeof(char) * 30);
	m.adresse = (char*)malloc(sizeof(char) * 20);
	printf("\nNom :  ");
	scanf("%s",m.nom);
	printf("\nPrenom :  ");
	scanf("%s",m.prenom);
	printf("\nAdresse: ");
	scanf("%s",m.adresse);
	printf("\nDonner le nombre de formation suivies par ce membre : ");
	scanf("%d",nombreDeFormation);
	//Allocation de mémoire pour les variables : m.formation.codeClasse, m.formation.intitule, m.formation.anne
	m.formation= (Formation*)malloc(sizeof(Formation) * (*nombreDeFormation));
	//Fin allocation
	for (i=0; i < *nombreDeFormation; ++i)
	{
		printf("\nCode classe %d: ",i+1);
		scanf("%d",&m.formation[i].codeClasse);
		m.formation[i].intitule = (char*)malloc(sizeof(char) * 15);
		printf("\nIntitule : ");
		scanf("%s",m.formation[i].intitule);
		printf("\nAnnee : ");
		scanf("%d",&m.formation[i].annee);
	}
	m.nformation = *nombreDeFormation; // On stocke le nombre de formation du membre dans " nformation "
										// qui est une variable qui lui est propre.
	return m;
}
//Fonction permettant de modifier un membre
void ModifierMembre(pliste *l)   {
    pliste tmp=(*l);
    int identifiant;
    printf("\n------------La Modification--------------\n");
    printf("\nDonner l'identifiant' de l'etudiant pour modifier ses informations:");
    scanf("%d",&identifiant);
    while(tmp!=NULL){
                     if((*l)->m.numero==identifiant){
                                     printf("\nL'etudiant exist dans la liste....");
                                     printf("donner le nouveau identifiant:");
                                     scanf("%d",&((*l)->m.numero));
                                     printf("donner le nouveau nom:");
                                     scanf("%s",((*l)->m.nom));
                                     printf("donner le nouveau prenom:");
                                     scanf("%s",((*l)->m.prenom));
									 printf("donner le nouveau adresse:");
                                     scanf("%s",((*l)->m.adresse));
                                      }else printf("Membre inexistant");
					 
                     }
					tmp=tmp->suiv;

 		}

//Fonction permettant de faire une pause sous linux: that's cool !
void SystemPause()
{
   char magickey;
   fflush(stdin);
   printf("\t\tAppuyez sur une touche pour continuer...\n");
   scanf("%c", &magickey);
   magickey = getc(stdin);
   system("clear");
}
/*if (l != NULL && l->suiv == NULL)
		{
			fprintf(f,"%d:%s:%s:%s",l->m.numero,l->m.nom,l->m.prenom,l->m.adresse);		 
			while(i < l->m.nformation)
				{
					fprintf(f,":%d:%s:%d",form->f.codeClasse,form->f.intitule,form->f.annee);
					form = form->suiv;
					i++;
				}
				fprintf(f,"\n");
		}
		else if(l==NULL)
		{}
		else
		{
			while(l!= NULL)
			{
				fprintf(f,"%d:%s:%s:%s",l->m.numero,l->m.nom,l->m.prenom,l->m.adresse);		 
				//form->f = l->m.formation;
				while(i < l->m.nformation)
				{
					fprintf(f,":%d:%s:%d",form->f.codeClasse,form->f.intitule,form->f.annee);
					form = form->suiv;
					i++;
				}
				i = 0;
				fprintf(f,"\n");
				l = l->suiv;
			}
		}*/