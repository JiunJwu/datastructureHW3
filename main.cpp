#include <iostream>
#include <string.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Host{
	int HP;
	int EXP;
	int LV;
};

Host mCalcutate(Host *host, int hurt ,int maxEXP){
	Host *newHost = (struct Host*)malloc(sizeof(struct Host));
	*newHost = *host;
	hurt = hurt-newHost->LV>0? hurt:1;
	newHost->HP=host->HP-(hurt-newHost->LV);
	newHost->EXP++;
	newHost->EXP = newHost->EXP > maxEXP?  maxEXP: newHost->EXP;
  	return *newHost;
};

Host hCalcutate(Host *host, int recover,int maxHP){
	host->HP = host->HP + recover < maxHP? host->HP + recover : maxHP;
	return *host;
};

Host kCalcutate(Host *host){
	Host *newHost = (struct Host*)malloc(sizeof(struct Host));
	*newHost = *host;
	newHost->HP=newHost->HP/2;
  	return *host;
};

Host bCalcutate(Host *host, int hurt,int maxEXP){
	Host *newHost = (struct Host*)malloc(sizeof(struct Host));
	*newHost = *host;
	hurt = hurt-newHost->LV>0? hurt:1;
	newHost->HP=newHost->HP-(hurt-newHost->LV);
	newHost->EXP=newHost->EXP+2;
	newHost->EXP = newHost->EXP > maxEXP?  maxEXP: newHost->EXP;
  	return *newHost;
};


int main(int argc, char** argv) {
	int maxHP,maxEXP,*elementCount;
	printf("life and experience input:");
	scanf("%d %d",&maxHP,&maxEXP);
	printf("elements count input:");
	scanf("%d",elementCount);
	
	struct ElementType{
		char object;
		int value;
	};

	Host *host = (struct Host*)malloc(sizeof(struct Host));
	host->HP = maxHP;
	host->EXP = 0;
	host->LV = 1;
	ElementType *element[*elementCount]={};
	bool history[*elementCount]={false};
	const char *k = "K";
	const char *m = "M";
	const char *b = "B";
	const char *h = "H";
	int stack[*elementCount]={0};
	
	for(int i=0;i<*elementCount;i++){
		char tmpObject;
		printf("element%d:",i);
		scanf("%s",&tmpObject);
		struct ElementType* new_element = (struct ElementType*)malloc(sizeof(struct ElementType));
		element[i]=new_element;
		element[i]->object=tmpObject;
		if(strcmp(&tmpObject, k) == 0){
			continue;
		}
		int tmpVal;
		scanf("%d",&tmpVal);
		element[i]->value=tmpVal;
	}
	

	int stackCount=0;//堆疊了多少項
	int i=0;
	Host *newHost = (struct Host*)malloc(sizeof(struct Host));
	bool goNext = true;
	while(stackCount<*elementCount && stackCount>-1){
		
		if(goNext!=true) {
			i=stack[stackCount];
			stackCount--;
		}else{
			i=0;
		}
		goNext=false;
		for(;i<*elementCount;i++){
			char object= element[i]->object;
			if(object==*k && history[i]==false ){
				*newHost = kCalcutate(host);
				if(newHost->HP>0){
					history[i]=true;
					stack[stackCount]=i;
					stackCount++;
					*host=*newHost;
					goNext=true;
				}else{
					break;			
				}

			}else if(object==*m  && history[i]==false ){
				*newHost = mCalcutate(host,element[i]->value,maxEXP);
				
				if(newHost->HP>0){
					history[i]=true;
					stack[stackCount]=i;
					stackCount++;
					*host=*newHost;
					goNext=true;
					break;
				}
			}else if(object==*b  && history[i]==false ){
				*newHost = bCalcutate(host,element[i]->value,maxEXP);

				if(newHost->HP>0){
					history[i]=true;
					stack[stackCount]=i;
					stackCount++;
					*host=*newHost;
					goNext=true;
					break;
				}
			}else if(object==*h && history[i]==false ){
				if(host->HP<maxHP){
					hCalcutate(host, element[i]->value, maxHP);
					stack[stackCount]=i;
					history[i]=true;
					stackCount++;
					goNext=true;
					break;
				}
			}

		}
	}
	free(newHost);
	free(host);
	for(i=0;i<*elementCount;i++){
		printf("ouput:%d ",stack[i]+1);
	}
	system("pause");
	return 0;
}
