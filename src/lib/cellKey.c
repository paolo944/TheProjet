#include "headers/cellKey.h"

CellKey *create_cell_key(Key *key){         //Cr'eation d'une cellule de clé
    CellKey *cell = (CellKey*)malloc(sizeof(CellKey));
    if(!cell){
        return NULL;
    }
    else{
        cell->data = key;
        cell->next = NULL;
    }
    return cell;
}

void ajout_en_tete(CellKey *key, CellKey **liste){      //Ajout d'une cl'e en tete de cellule
    if(*liste == NULL){
        *liste = key;
        return;
    }
    key->next = *liste;
    *liste = key;
}

CellKey *read_public_keys(char *nomFic){      //Cr'eation d'une liste de cl'e a partir d'un fichier
    FILE *file = fopen(nomFic, "r");
    if(!file){
        return NULL;
    }
    char buffer[256];
    Key *key = NULL;
    CellKey *liste = NULL;
    while(fgets(buffer, 256, file)){
        key = str_to_key(buffer);
        ajout_en_tete(create_cell_key(key), &liste);
    }
    return liste;
}

void print_list_keys(CellKey *LCK){      //Affichage d'une liste de cl'e
    CellKey *tmp = LCK;
    while(tmp){
        printf("%s\n", key_to_str(tmp->data));
        tmp = tmp->next;
    }
}

void delete_cell_key(CellKey *c){       //Suppression d'une cellule de cl'e
    free(c->data);
    free(c);
}

void delete_liste_key(CellKey *c){       //Suppression d'une liste de cl'e
    CellKey *tmp = NULL;
    while(c){
        tmp = c->next;
        delete_cell_key(c);
        c = tmp;
    }
    free(c);
}
