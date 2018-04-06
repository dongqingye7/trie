#include <stdio.h>
#include "trie.h"
#include <stdlib.h>
struct trie {
	struct trie **children;
	bool exist;
};

  struct trie *
trie_new(void)
{
    struct trie * const tempNode = malloc(sizeof(*tempNode));
    if (tempNode== NULL) return NULL;
    tempNode->children = malloc(sizeof(struct trie *) * 256);
    if (tempNode->children ==NULL){
    	free(tempNode);
    	return NULL;
    }
    tempNode->exist=false;
    return tempNode;
}

  bool
trie_set(struct trie * trie, u32 len, u8 * key)
{  
    struct trie *temp = trie;
    for (u32 i=0; i<len;i++){
    
    	if(!temp->children[key[i]]){
	  	temp->children[key[i]]=trie_new();
	}
	temp=temp->children[key[i]];
    }
    temp->exist=true;
    return true;
}

  bool
trie_get(struct trie * trie, u32 len, u8 * key)
{
    struct trie *temp = trie;
    for (u32 i=0; i<len;i++){
	if(!temp->children[key[i]]){
	  	return false;
	}
	temp=temp->children[key[i]];
    }
    return temp->exist; 
}

bool isFreeNode(struct trie * trie){
   int i;
   for(i=0; i<256;i++){
	if(trie->children[i])
		return false;
   }
   return true;
}

void freeNode(struct trie * trie){
   free(trie);
   trie=NULL;
}

bool del_word(struct trie * trie, u8 * key, int count, u32 len){
    struct trie *temp = trie;
    if(temp){
    	if(count==len) {
		if(temp->exist){
			temp->exist=false;	
			if(isFreeNode(temp)){
				return true;
			}
			return false;
		}    
	}else{
		u32 k=key[count];
		if(del_word(temp->children[k],key,count+1,len)){
			freeNode(temp->children[k]);
		
			return isFreeNode(temp)&&(temp->exist==false);
		}
    	}
    }
    return false;
}

  bool
trie_del(struct trie * trie, u32 len, u8 * key)
{
    if(!len) return false;
    del_word(trie,key, 0,len);
    return true;
}
