#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

typedef struct Question
{
	char question[100];
	char reponse1[20];
	char reponse2[20];
	char reponse3[20];
	char caracteristique1[20];
	char caracteristique2[20];
	char caracteristique3[20];
	struct Questions *suiv;
} QUES;

typedef struct Liste_ques
{
	char question[100];
	QUES *Info_question;
	struct Liste_questions *suiv;
}INFO_Q;

QUES * Creer()
{	
	QUES *E;
	E=(QUES*)malloc(sizeof(QUES));
  	if (E == NULL)
  	{
  		printf("Erreur d'allocation memoire\n");
  	}
  	else
  	{
	printf("Question: \n"); 
  	scanf("%s", E->question); 
  	printf("Reponse 1: \n"); 
  	scanf("%s", E->reponse1);
	printf("Caracteristique de la reponse 1: \n"); 
  	scanf("%s", E->caracteristique1);
  	printf("Reponse 2: \n"); 
  	scanf("%s",E->reponse2); 
  	printf("Caracteristique de la reponse 2: \n"); 
  	scanf("%s", E->caracteristique2);
  	printf("Reponse 3: \n"); 
  	scanf("%s",E->reponse3); 
  	printf("Caracteristique de la reponse 3: \n"); 
  	scanf("%s", E->caracteristique3);
  	E->suiv = NULL;		
    }
	return E;
}


QUES* Inserer(QUES* Liste, QUES* E)
{
	if(E == NULL) // Cas liste vide
	{
		printf("Rien a inserer \n");
		return Liste;
	}
	if (Liste == NULL)
	{
		return E;
	}

	if(strcmp (E->question, Liste->question) <  0)  // Cas nouveau < premier maillon pas de else car return
	{
		E->suiv = Liste;
		return E;
	}

Liste->suiv = Inserer(Liste->suiv, E);						// Insertion dans le reste de la liste
return Liste;
}


void Afficher(QUES *Liste)
{
	int i=0;
	if(Liste == NULL)
		return;
	
	printf("\nQUESTION: %s\n", Liste->question);
	printf("REPONSE 1: %s\n", Liste->reponse1);
	printf("CARACTERISTIQUE 1: %s\n", Liste->caracteristique1);
	printf("REPONSE 2: %s\n", Liste->reponse2);
	printf("CARACTERISTIQUE 2: %s\n", Liste->caracteristique2);	
	printf("REPONSE 3: %s\n", Liste->reponse3);
	printf("CARACTERISTIQUE 3: %s\n", Liste->caracteristique3);	
	Afficher(Liste->suiv);
} 



void Sauvegarder(QUES * Liste)
{
	FILE *fic = NULL;
	char sNomFic[30];
	printf("\n *************************SAUVEGARDE *************************");
	printf("\nDonnez le nom du fichier a creer (attention son contenu sera effacer): ");
	scanf(" %s", sNomFic);
	
	if ((fic = fopen(sNomFic, "a")) == NULL)
		printf("\nErreur d'ouverture de fichier - Abandon");
	else
	{ 
		while(Liste != NULL)
		{
			if (fwrite(Liste, sizeof(QUES), 1, fic) != 1)
			{ 
				printf("\nErreur d'ecriture dans le fichier - Abandon");
				Liste = NULL;
			}
			else
				Liste = Liste->suiv;
		}
		if ((fic != NULL) && (fclose(fic) != 0))
			printf("\nProbleme de fermeture de fichier");
	}
} 



QUES* lireFicCreer(void)
{
	int lecture=0;
	FILE * fic = NULL;
	fic=fopen("base_ques.txt", "r");
	do
	{
	 lecture=fgetc(fic);
	 printf("%c",lecture);
	} while(lecture !=EOF);
	fclose(fic);
	}

int main(void)
{
	QUES *Liste=NULL;
	QUES *E=NULL;
	INFO_Q *film;
	INFO_Q *Liste1=NULL;
	INFO_Q * E1;
	QUES *filmRech;
	int save;
	char mot[30];

	int choix, nbre, i;

	while(1)
	{
		printf("MENU BASE DE QUESTIONS: \n");
		printf("0- Quitter: \n");
		printf("1 - Afficher \n");
		printf("2- Creer \n");
		printf("3- Sauvegarder \n");
		printf("4- Charger \n");
		scanf("%d",&choix);
		switch(choix)
		{
	
			case 0: return 0;
			
			case 1: Afficher(Liste);
					break;
			

			case 2: printf("combien voulez vous rajouter de questions ? \n");
					scanf("%d",&nbre);
					for(i=0;i<nbre;i++)
					{
					E=Creer();
					Liste = Inserer(Liste,E);
					} break;
	
					
			case 3: Sauvegarder(Liste);break;
			
			case 4: lireFicCreer();break;
			
		
			default : printf("Mauvais choix\n"); 
		}
	}
}
