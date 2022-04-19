#include "protected.h"
#include "cellProtected.h"
#include "block.h"
#include "Cellkey.h"
#include "cellTree.h"
#include <dirent.h>
#include <stdio.h>
#include "hashCell.h"

#ifndef VOTE_H
#define VOTE_H


void submit_vote(Protected* p);
void create_block(CellTree* tree, Key* author, int d);
void add_block(int d, char* name);
CellTree* read_tree();

#endif //VOTE_H