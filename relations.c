// relations.c�: d�finit le point d'entr�e pour l'application .
//

typedef int bool;
#define false 0
#define true -1

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"

/**
 * @enum rtype
 * Définit un type relationnel.
 */
typedef enum
{
    FRERE = 2,    ///<  Frere
    COUSIN,       ///<  Cousin
    PARENT,       ///<  Parent
    ONCLE,        ///<  Oncle
    EPOUX,        ///<  Epoux
    AMI,          ///<  Ami
    VIT,          ///<  Vit
    CONNAIT,      ///<  Connait
    CHEF,         ///<  Chef
    COLLEGUE,     ///<  Collegue
    LOCATAIRE,    ///<  Locataire
    TRAVAILLE,    ///<  Travaille
    PROPRIETAIRE, ///<  Proprietaire
    SITUE,        ///<  Situe
    DECOUVERT     ///<  Decouvert
} rtype;

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien de parenté sinon faux.
 */
bool est_lien_parente(rtype id)
{
    return id >= FRERE && id <= EPOUX;
}

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien professionel sinon faux.
 */
bool est_lien_professionel(rtype id)
{
    return id >= CHEF && id <= COLLEGUE;
}

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien de connaissance sinon faux.
 */
bool est_lien_connaissance(rtype id)
{
    return id >= AMI && id <= CONNAIT;
}

/**
 * @param id : un type relationnel.
 * @return la chaine de caractère associée au type relationnel id.
 */
char *toString(rtype id)
{
    //* id = 0 => omega : NULL
    //* id = 1 => INCONNUE
    char *relations[] = {NULL, "INCONNUE", "FRERE", "COUSIN", "PARENT",
                         "ONCLE", "EPOUX", "AMI", "VIT",
                         "CONNAIT", "CHEF",
                         "COLLEGUE", "LOCATAIRE", "TRAVAILLE",
                         "PROPRIETAIRE", "SITUE", "DECOUVERT"};

    return relations[id];
}

////////////////////////////////////////
// Exercice 2: Liste de pointeurs
/**
 * @struct s_node
 * @brief Cette structure permet de définir un noeud.
 */
typedef struct s_node
{
    void *val; // pointeur vers objet quelconque
    struct s_node *suiv;
} *listeg;

/**
 * @param Aucun.
 * @brief Création d'une nouvelle liste.
 * @return Un pointeur NULL.
 */
listeg listegnouv() { return NULL; }

/**
 * @param lst : Une liste.
 * @param x : Un pointeur générique.
 * @brief Adjonction d'un élément en tête dans la liste.
 * @return Une nouvelle liste.
 */
listeg adjtete(listeg lst, void *x)
{
    //* Création du nouveau noeud
    listeg newNode = (listeg)malloc(sizeof(struct s_node));

    //* On vérifie que le malloc a bien eu lieu.
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur : allocation échouée.\n");
        exit(EXIT_FAILURE);
    }

    newNode->suiv = lst;
    newNode->val = x;

    return newNode;
}

/**
 * @param lst : Une liste.
 * @param x : Un pointeur générique.
 * @brief Adjonction d'un élément en queue dans la liste.
 * @return Une nouvelle liste.
 */
listeg adjqueue(listeg lst, void *x)
{
    //* Création du nouveau noeud
    listeg newNode = (listeg)malloc(sizeof(struct s_node));

    //* On vérifie le malloc
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur : allocation échouée.\n");
        exit(EXIT_FAILURE);
    }

    newNode->val = x;

    //* Cas de la liste vide
    if (lst == NULL)
    {
        newNode->suiv = NULL;
        return newNode;
    }

    //* Cas où la liste a au moins un élément.
    //* On se positionne sur la queue.
    listeg temp = lst;
    while (temp->suiv != NULL)
    {
        temp = temp->suiv;
    }
    //* On est sur la queue.
    //* On place le noeud à la queue.
    temp->suiv = newNode;
    newNode->suiv = NULL;

    return lst;
}

/**
 * @param lst : Une liste.
 * @brief Suppression en tête.
 * @return Une nouvelle liste.
 */
listeg suptete(listeg lst)
{
    if (lst == NULL)
    {
        return NULL;
    }

    listeg nodeToDestroy = lst;
    //* On recupère le noeud suivant
    lst = lst->suiv;

    //* Destruction du noeud
    free(nodeToDestroy);

    return lst;
}

/**
 * @param lst : Une liste.
 * @brief L'élement en tête de la liste.
 * @return Le pointeur générique en tête de la liste.
 */
void *tete(listeg lst)
{
    return lst != NULL ? lst->val : NULL;
}

/**
 * @param lst : Une liste.
 * @brief Est-ce que la liste est vide?
 * @return true si oui sinon false.
 */
bool estVide(listeg lst)
{
    return lst == NULL;
}

/**
 * @param lst : Une liste.
 * @brief La longueur de la liste.
 * @return Un entier representant la longeur.
 */
int longueur(listeg lst)
{
    return estVide(lst) ? 0 : 1 + longueur(lst->suiv);
}

/**
 * @param lst : Une liste.
 * @brief Destruction de la liste.
 * @return rien.
 */
void detruire(listeg lst)
{
    listeg temp = lst;
    while (temp != NULL)
    {
        temp = suptete(temp);
    }
}

/**
 * @param objet1 : Un pointeur générique.
 * @param objet2 : Un pointeur générique.
 * @brief Comparaison lexicographique des deux objets.
 * @return Un entier representant la longeur.
 */
int cmp(void *objet1, void *objet2)
{
    return strcmp((char *)objet1, (char *)objet2);
}

listeg rech(listeg lst, void *x, int (*comp)(void *, void *))
{
    //* objectsFound : contiendra tous les noeuds trouvés.
    listeg objectsFound = NULL;

    while (!estVide(lst))
    {
        if (!comp(lst->val, x))
        {
            //* L'ordre dans lequel les éléments sont placés dans
            //* la listeg n'a pas d'importance
            objectsFound = adjtete(objectsFound, lst->val);
        }
        lst = lst->suiv;
    }

    return objectsFound;
}

////////////////////////////////////////
// Exercice 3: Construction du graphe

#define LONG_NOM_MAX 64
typedef enum
{
    PERSONNE = 1,
    OBJET,
    ADRESSE,
    VILLE
} etype;

typedef struct s_entite
{
    char nom[LONG_NOM_MAX]; // le nom de l�entit� p.ex � Peugeot 106 �
    etype ident;            // l�identifiant associ�, p.ex OBJET
} *Entite;
// 3.1 les structures de donn�es
typedef struct s_sommet
{
    // A DEFINIR
    listeg larcs;
    Entite x;
} *Sommet;

typedef struct s_arc
{
    // A DEFINIR
    rtype t;
    Entite x;
} *Arc;

typedef struct s_relations
{
    // A DEFINIR
    listeg liste;
} *Relations;

void checkMalloc(void *objet)
{
    if (objet == NULL)
    {
        fprintf(stderr, "Erreur : allocation echouée.\n");
        exit(EXIT_FAILURE);
    }
}

// 3.2 les constructeurs
Entite creerEntite(char *s, etype e)
{
    Entite newEntity = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc((Entite)newEntity);

    strncpy(newEntity->nom, s, LONG_NOM_MAX);
    newEntity->ident = e;

    return newEntity;
}

Sommet nouvSommet(Entite e)
{
    Sommet newSommet = (Sommet)malloc(sizeof(struct s_sommet));

    checkMalloc((Sommet)newSommet);

    newSommet->x = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc(newSommet->x);

    newSommet->larcs = listegnouv();

    memcpy(newSommet->x, e, sizeof(struct s_entite));

    return newSommet;
}

Arc nouvArc(Entite e, rtype type)
{
    Arc newArc = (Arc)malloc(sizeof(struct s_arc));

    checkMalloc((Arc)newArc);

    newArc->x = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc(newArc->x);

    newArc->t = type;
    memcpy(newArc->x, e, sizeof(struct s_entite));

    return newArc;
}

void relationInit(Relations *g)
{
    *g = (Relations)malloc(sizeof(struct s_relations));

    checkMalloc((Relations)*g);

    (*g)->liste = listegnouv();
}

void freeLarcs(listeg *ptrlisteOfArcs)
{
    if (estVide(*ptrlisteOfArcs))
    {
        return;
    }
    // listeg curr = *ptrlisteOfArcs;

    //* Destruction : mais avant on a bésoin de supprimer l'entité
    //* Dans l'arc, c'est pourquoi on ne peut pas utiliser la fonction
    //* detruire() ici.
    while ((*ptrlisteOfArcs) != NULL)
    {
        //* On nettoie l'entite dans l'arc.
        free(((Arc)(*ptrlisteOfArcs)->val)->x);

        //* On nettoie l'arc lui-même.
        free((Arc)(*ptrlisteOfArcs)->val);

        //* Après on supprime la tête courrante.
        (*ptrlisteOfArcs) = suptete(*ptrlisteOfArcs);
    }
}

void freeSommet(Sommet *ptrSommet)
{
    if (*ptrSommet == NULL)
    {
        return;
    }

    //* On efface l'entite dans le sommet.
    free((*ptrSommet)->x);

    //* On efface le sommet lui-même.
    free(*ptrSommet);
}

void relationFree(Relations *g)
{
    if (*g == NULL)
    {
        return;
    }

    // listeg curr = (*g)->liste;
    while ((*g)->liste != NULL)
    {
        //* On recupère le sommet courrant.
        Sommet som = ((Sommet)((*g)->liste)->val);
        // listeg listeConnaissance = som->larcs;

        //* On efface la liste des rélations.
        freeLarcs(&((Sommet)((*g)->liste)->val)->larcs);

        //* On efface le sommet.
        freeSommet((Sommet *)&((*g)->liste->val));

        // freeSommet(&((Sommet)((*g)->liste)->val));

        //* On efface la tête.
        (*g)->liste = suptete((*g)->liste);
    }

    free(*g);
    *g = NULL;
    return;
}

// 3.3 les comparaisons
int compEntite(void *e, void *string)
{
    Entite entity = (Entite)e;

    return strcmp(entity->nom, (char *)string);
}

/**
 * s : est un sommet.
 * string : est un nom.
 */
int compSommet(void *s, void *string)
{
    Sommet som = (Sommet)s;

    return strcmp(som->x->nom, (char *)string);
}

int compArc(void *a, void *string)
{
    Arc arc = (Arc)a;

    return strcmp(arc->x->nom, (char *)string);
}

listeg searchSommet(listeg liste, char *nom)
{
    //* Tanque la liste n'est pas vide et que les deux sommets sont pas les mêmes
    //* on part au suivant.
    listeg listetemp = liste;
    while (listetemp != NULL && compSommet((Sommet)listetemp->val, (char *)nom) != 0)
    {
        listetemp = listetemp->suiv;
    }

    return listetemp;
}
// 3.4 ajout d'entites et de relations
void adjEntite(Relations g, char *nom, etype t)
{
    Entite entityToAdd = creerEntite(nom, t);
    Sommet sommetToAdd = nouvSommet(entityToAdd);

    if (estVide(g->liste))
    {
        g->liste = adjtete(g->liste, (Sommet)sommetToAdd);
    }
    else
    {
        //* le nom est unique. (Pas de doublons).
        //* On parcours g->liste et on cherche à savoir s'il y a déjà une entité
        //* du même nom
        //* si non, on l'ajoute.
        //* si oui, on l'ajoute pas.
        // if (!searchSommet(g, nom))
        // {
        //     //* On a pas trouvé l'entité, on l'ajoute.
        //     g->liste = adjqueue(g->liste, (Sommet)sommetToAdd);
        // }
        if (rech(g->liste, (char *)nom, compSommet) == NULL)
        {
            g->liste = adjqueue(g->liste, (Sommet)sommetToAdd);
        }
        //* Sinon on fait rien.
    }

    //* ça été copié, nous en avons plus bésoin.
    free(entityToAdd);
}

void afficheEntites(Relations g)
{
    if (g == NULL)
    {
        return;
    }

    listeg curr = g->liste;
    if (curr == NULL)
    {
        printf("Graphe Vide.\n");
        return;
    }

    int i = 0;
    while (curr != NULL)
    {
        // printf("%d => %p\n", i, curr);
        Sommet som = (Sommet)curr->val;
        Entite entity = (Entite)som->x;
        printf("%s\n", entity->nom);
        printf("En rélation avec : \n");
        listeg listeConnaissance = som->larcs;
        printf("%p\n", listeConnaissance);
        while (listeConnaissance != NULL)
        {
            Arc arc = (Arc)listeConnaissance->val;
            Entite entity = (Entite)(arc->x);
            printf("   %s\n", toString(arc->t));
            printf("   %s\n", entity->nom);
            printf("   %p\n", entity);
            printf("--------------------\n");
            listeConnaissance = listeConnaissance->suiv;
        }
        curr = curr->suiv;
        i++;
    }
}

/**
 * listeArcs : liste des arcs du sommet.
 * nom : clé.
 * Return NULL ou l'arc trouvé.
 */
listeg searchArc(listeg listeArcs, char *nom)
{
    while (listeArcs != NULL && compArc(listeArcs->val, nom) != 0)
    {
        listeArcs = listeArcs->suiv;
    }

    return listeArcs;
}

// PRE CONDITION: id doit �tre coh�rent avec les types des sommets correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0
void adjRelation(Relations g, char *nom1, char *nom2, rtype id)
{
    //* Les sommets sont déjà ajoutés, ici on ajoute juste les arcs (relations).

    //* On cherche le sommet portant le nom : nom1
    listeg curr = g->liste;
    Sommet s1 = NULL;
    while (curr != NULL && s1 == NULL)
    {
        Sommet som = (Sommet)curr->val;
        if (compSommet(som, nom1) == 0)
        {
            s1 = som;
        }
        curr = curr->suiv;
    }

    //* On cherche le sommet 2 portant le nom : nom2
    curr = g->liste;
    Sommet s2 = NULL;
    while (curr != NULL && s2 == NULL)
    {
        Sommet som = (Sommet)curr->val;
        if (compSommet(som, nom2) == 0)
        {
            s2 = som;
        }
        curr = curr->suiv;
    }

    listeg nodeArc1 = searchArc(s1->larcs, nom2);
    if (nodeArc1 != NULL)
    {
        //* L'arc existe déjà, on met à jour l'id.
        Arc arcFound = (Arc)nodeArc1->val;
        arcFound->t = id;
    }
    else
    {
        //* Ajout du premier arc de nom1 à nom2
        Arc newArc = nouvArc(s2->x, id);
        s1->larcs = adjtete(s1->larcs, (Arc)newArc);
    }

    listeg nodeArc2 = searchArc(s2->larcs, nom1);
    if (nodeArc2 != NULL)
    {
        //* L'arc existe déjà, on met à jour l'id.
        Arc arcFound = (Arc)nodeArc2->val;
        arcFound->t = id;
    }
    else
    {
        //* Ajout du second arc de nom2 à nom1
        Arc newArc = nouvArc(s1->x, id);
        s2->larcs = adjtete(s2->larcs, (Arc)newArc);
    }

    return;
}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
listeg en_relation(Relations g, char *x)
{
    listeg listSommet = g->liste;
    listeg listeOfArcs = NULL;

    listeg sommetFound = rech(listSommet, (char *)x, compSommet);

    if (sommetFound != NULL)
    {
        //* Le sommet de nom x a été trouvé.
        Sommet som = (Sommet)sommetFound->val;
        listeOfArcs = som->larcs;

        //* On n'oublie pas de detruire la liste.
        detruire(sommetFound);
    }

    return listeOfArcs;
}

listeg chemin2(Relations g, char *x, char *y)
{
    listeg listOfArcsX = en_relation(g, x);
    listeg listOfArcsY = en_relation(g, y);
    listeg cheminList = listegnouv();

    //* On parcourt listOfArcsX
    while (listOfArcsX != NULL)
    {
        //* On recupère le premier arc.
        Arc currArcX = (Arc)listOfArcsX->val;

        //* On recupère l'entité.
        Entite entity = currArcX->x;

        listeg arcFound = searchArc(listOfArcsY, entity->nom);

        if (arcFound != NULL)
        {
            Arc arc = (Arc)arcFound->val;
            cheminList = adjtete(cheminList, (Entite)arc->x);
            // printf("found : %s\n", arc->x->nom);
        }

        listOfArcsX = listOfArcsX->suiv;
    }
    return cheminList;
}

// 4.2 verifier un lien de parente
// PRE CONDITION: strcmp(x,y)!=0
bool ont_lien_parente(Relations g, char *x, char *y)
{
    listeg listOfArcs = en_relation(g, x);
    bool isFamily = false;
    listeg arcNodeFound = searchArc(listOfArcs, y);

    if (arcNodeFound != NULL)
    {
        Arc arc = (Arc)arcNodeFound->val;
        isFamily = est_lien_parente(arc->t);
    }

    return isFamily;
}
// 4.3 tester connaissances
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent(Relations g, char *x, char *y)
{
    //* On recupère la liste des rélations de x.
    listeg listOfArcsX = en_relation(g, x);
    bool isRelationship = false;

    listeg arcNodeFound = searchArc(listOfArcsX, y);

    if (arcNodeFound != NULL)
    {
        //* On l'a trouvé parmis ses voisins.
        Arc arc = (Arc)arcNodeFound->val;
        rtype type = arc->t;
        bool estParenteOk = est_lien_parente(type);
        bool estConaissanceOk = est_lien_connaissance(type);
        bool estProfessionelOk = est_lien_professionel(type);
        isRelationship = estParenteOk || estConaissanceOk || estProfessionelOk;
    }
    else
    {
        //* Sinon, on regarde parmis les voisins communs.
        listeg commonNeighbours = chemin2(g, x, y);
        listeg temp = commonNeighbours;
        while (temp != NULL)
        {
            Entite entity = (Entite)temp->val;
            char *z = entity->nom;
            if (ont_lien_parente(g, x, z) && ont_lien_parente(g, z, y))
            {
                isRelationship = true;
            }
            temp = temp->suiv;
        }
        detruire(commonNeighbours);
    }

    return isRelationship;
}

bool _isRelationDirecte(Relations g, char *x, char *y)
{
    listeg listOfArcsX = en_relation(g, x);
    bool isDirectRelationship = false;

    listeg arcNodeFound = searchArc(listOfArcsX, y);

    if (arcNodeFound != NULL)
    {
        //* On l'a trouvé parmis ses voisins. Donc  c'est une relation directe.
        isDirectRelationship = true;
    }

    return isDirectRelationship;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_proba(Relations g, char *x, char *y)
{
    bool probablyRelation = false;
    if (_isRelationDirecte(g, x, y))
    {
        probablyRelation = false;
    }
    else
    {
        listeg commonNeighbours = chemin2(g, x, y);
        listeg temp = commonNeighbours;
        while (temp != NULL)
        {
            Entite entity = (Entite)temp->val;
            char *z = entity->nom;
            if ((ont_lien_parente(g, x, z) && !ont_lien_parente(g, y, z)) || (!ont_lien_parente(g, x, z) && ont_lien_parente(g, y, z)))
            {
                probablyRelation = true;
            }
            temp = temp->suiv;
        }
        detruire(commonNeighbours);
    }

    return probablyRelation;
}

// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_peutetre(Relations g, char *x, char *y)
{
    if (_isRelationDirecte(g, x, y))
    {
        return false;
    }
    else if (se_connaissent_proba(g, x, y))
    {
        return false;
    }
    else
    {
        listeg commonNeighbours = chemin2(g, x, y);
        if (commonNeighbours != NULL)
        {
            detruire(commonNeighbours);
            return true;
        }
        else
        {
            return false;
        }
    }
}
////////////////////////////////////////
// Exercice 5: Affichages
void affiche(void *objet)
{
    //* Dans notre cas, on affiche une chaine
    printf("%s\n", (char *)objet);

    return;
}

void affichelg(listeg l, void (*aff)(void *))
{
    while (!estVide(l))
    {
        aff(l->val);
        l = l->suiv;
    }
}

void afficheEntite(void *x)
{
    Entite entity = (Entite)x;
    printf("%s : ", entity->nom);
    switch (entity->ident)
    {
    case PERSONNE:
        printf("PERSONNE");
        break;
    case OBJET:
        printf("OBJET");
        break;
    case ADRESSE:
        printf("ADRESSE");
        break;
    case VILLE:
        printf("VILLE");
        break;
    default:
        printf("Type d'entité inconnu");
    }
    printf("\n");
}

void afficheArc(void *x)
{
    Arc arc = (Arc)x;
    printf("-- %s -->", toString(arc->t));
    void *entity = arc->x;
    afficheEntite(entity);
}

////////////////////////////////////////
// Exercice 6: Parcours
void affiche_degre_relations(Relations r, char *x)
{
    listeg listeVisites = listegnouv();
    listeg fileSuivants = listegnouv();
    listeg fileSuivants2 = listegnouv();
    listeg relations = en_relation(r, x);
    listeg sommetX = rech(r->liste, x, compSommet);
    listeVisites = adjtete(listeVisites, ((Sommet)sommetX->val)->x);
    detruire(sommetX);
    for (; !estVide(relations); relations = relations->suiv)
    {
        fileSuivants = adjqueue(fileSuivants, ((Arc)relations->val)->x);
    }
    printf("%s\n", x);
    int degre = 1;
    while (!estVide(fileSuivants))
    {
        printf("-- %d\n", degre++);
        listeg fileSuivantsIter = fileSuivants;
        for (; !estVide(fileSuivantsIter); fileSuivantsIter = fileSuivantsIter->suiv)
        {
            printf("%s\n", ((Entite)fileSuivantsIter->val)->nom);
        }
        while (!estVide(fileSuivants))
        {
            char *suivant = ((Entite)tete(fileSuivants))->nom;
            fileSuivants = suptete(fileSuivants);
            listeg relations = en_relation(r, suivant);
            for (; !estVide(relations); relations = relations->suiv)
            {
                listeg comparaisonVisites = rech(listeVisites, ((Arc)relations->val)->x->nom, compEntite);
                listeg comparaisonFile = rech(fileSuivants, ((Arc)relations->val)->x->nom, compEntite);
                listeg comparaisonFile2 = rech(fileSuivants2, ((Arc)relations->val)->x->nom, compEntite);
                if (estVide(comparaisonVisites) && estVide(comparaisonFile) && estVide(comparaisonFile2))
                {
                    listeg sommetFils = rech(r->liste, ((Arc)relations->val)->x->nom, compSommet);
                    fileSuivants2 = adjqueue(fileSuivants2, ((Sommet)sommetFils->val)->x);
                    detruire(sommetFils);
                }
                detruire(comparaisonVisites);
                detruire(comparaisonFile);
            }
            listeg sommetSuivant = rech(r->liste, suivant, compSommet);
            listeVisites = adjtete(listeVisites, ((Sommet)sommetSuivant->val)->x);
            detruire(sommetSuivant);
        }
        fileSuivants = fileSuivants2;
        fileSuivants2 = listegnouv();
    }
    detruire(listeVisites);
}

int main()
{

    // return 1;
    int i, j;
    Relations r;
    relationInit(&r);

    // ajouter les entites de l'exemple
    char *tabe[] = {"KARL", "LUDOVIC", "CELINE", "CHLOE", "GILDAS", "CEDRIC", "SEVERINE",
                    "PEUGEOT 106", "1, RUE DE LA RUE", "STRASBOURG"};
    //* On ajoute les personnes.
    for (i = 0; i < 7; i++)
        adjEntite(r, tabe[i], PERSONNE);

    //* On ajoute les objets.
    adjEntite(r, tabe[7], OBJET);
    adjEntite(r, tabe[8], ADRESSE);
    adjEntite(r, tabe[9], VILLE);

    // ajouter les relations de l'exemple
    adjRelation(r, tabe[0], tabe[1], FRERE);
    adjRelation(r, tabe[0], tabe[2], AMI);
    adjRelation(r, tabe[0], tabe[3], CONNAIT);
    adjRelation(r, tabe[0], tabe[5], COUSIN);
    adjRelation(r, tabe[0], tabe[7], PROPRIETAIRE);
    adjRelation(r, tabe[0], tabe[8], PROPRIETAIRE);
    adjRelation(r, tabe[3], tabe[4], VIT);
    adjRelation(r, tabe[5], tabe[6], EPOUX);
    adjRelation(r, tabe[5], tabe[8], LOCATAIRE);
    adjRelation(r, tabe[7], tabe[8], DECOUVERT);
    adjRelation(r, tabe[8], tabe[9], SITUE);

    // afficheEntites(r);

    // explorer les relations
    printf("%s est en relation avec:\n", tabe[0]);
    affichelg(en_relation(r, tabe[0]), afficheArc);
    printf("\n");

    for (i = 0; i < 7; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont les relations communes:\n", tabe[i], tabe[j]);
            listeg ch = chemin2(r, tabe[i], tabe[j]);
            affichelg(ch, afficheEntite);
            printf("\n");
            detruire(ch);
        }
    printf("\n\n");

    for (i = 0; i < 10; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont lien de parente: %s\n",
                   tabe[i], tabe[j], ont_lien_parente(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }

    printf("\n");
    for (i = 0; i < 7; i++)
    {
        for (j = i + 1; j < 7; j++)
        {
            printf("<%s> et <%s> se connaissent: %s\n",
                   tabe[i], tabe[j], se_connaissent(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent tres probablement: %s\n",
                   tabe[i], tabe[j], se_connaissent_proba(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent peut etre: %s\n",
                   tabe[i], tabe[j], se_connaissent_peutetre(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
        printf("\n");
    }

    affiche_degre_relations(r, tabe[3]);
    relationFree(&r);
    return 0;
    printf("\nPRESS RETURN\n");
    char buff[64];
    fscanf(stdin, "%s", buff);
    return 0;
}
