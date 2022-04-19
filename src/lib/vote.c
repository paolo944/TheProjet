#include "vote.h"


void submit_vote(Protected* p){
    FILE *F=foppen("Pending_votes.txt","a");
    char* pstr=protected_to_str(p);
    fprintf(F,"%s",pstr);
    fputc(F,'\n');
    fclose(F);
    free(pstr);    
}


void create_block(CellTree* tree, Key* author, int d) {
    Block* Pending_block=malloc(sizeof(Block));
    CellProtected* cpro=malloc(sizeof(CellProtected));
    cpro->data=read_protected("Pending_votes.txt");

    remove("Pending_votes.txt");
    Pending_block->author=author;
    Pending_block->previous_hash=last_node(tree)->block->hash;
    //peut-être il faut rajouter a la fin du tree
    Pending_block->hash="123";
    compute_proof_of_work(Pending_block,d);
    ecrire_block(Pending_block,"Pending_bloc.txt");
}

void add_block(int d, char* name){
    char* str;
    sprintf(str,"lib/Blockchain/%s",name);
    Block* b=lire_block("Pending_block.txt");
    if(verify_block(b,d)){
        ecrire_block(b,str);
    }
    remove("Pending_block.txt");
}

CellTree* read_tree(){
    CellTree** T=malloc(sizeof(CellTree*));
    DIR *rep =opendir("lib/Blockchain/");
    if(rep!=NULL){
        int i=0;
        struct dirent* dir;
        while ((dir=readdir(rep))){
            if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                T[i]=create_node(lire_block(dir->d_name));
                i+=1;
            }
        }
        closedir(rep);
    }
    int j=0;
    while (T[j]){
        int k=0;
        while(T[k]){
            if(T[k]->block->previous_hash==T[j]->block->hash){
                add_child(T[j],T[k]);
            }
            k+=1;
        }
        j+=1;
    }
    j=0;
    while (T[j]){
        if(T[j]->father==NULL){
            return T[j];
        }
    }       
    printf("Erreur: Pas de racine");
    return NULL;
}

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
    //ListeVote extraire les votes
    verification_fraude(listeVote); 
    return compute_winner(listeVote,candidates,voters,sizeC,sizeV);
}
