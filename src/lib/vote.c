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
    Pending_block->votes=read_protected("Pending_votes.txt");
    remove("Pending_votes.txt");
    Pending_block->author=author;
    Pending_block->previous_hash=last_node(tree)->block->hash;
    //peut-être il faut rajouter a la fin du tree
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