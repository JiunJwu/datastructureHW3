#include <iostream>
#include <string.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Host{
	int HP;
	int EXP;
	int LV;
};
bool surviveOrNot(Host *host, char object, int hurt=0 ){
	switch (object){
		case 'K':
			if(host->HP/2>0){
				return true;
			}
			break;		
		case 'M':
			hurt = hurt-host->LV>0? hurt:1;
			if(host->HP-(hurt-host->LV)>0){
				return true;
			}
			break;			
		case 'B':
			hurt = hurt-host->LV>0? hurt:1;
			if(host->HP-(hurt-host->LV)>0){
				return true;
			}			
			break;		
	}
	return false;
	
}

Host mCalcutate(Host *host, int hurt ,int maxEXP){

	hurt = hurt-host->LV>0? hurt:1;
	host->HP=host->HP-(hurt-host->LV);
	host->EXP++;
	if(host->EXP >= maxEXP){
		host->EXP=0;
		host->LV++;	
	}
  	return *host;
};

Host hCalcutate(Host *host, int recover,int maxHP){
	host->HP = host->HP + host->LV * recover < maxHP? host->HP + host->LV * recover : maxHP;
	return *host;
};

Host kCalcutate(Host *host){
	host->HP=host->HP/2;
  	return *host;
};

Host bCalcutate(Host *host, int hurt,int maxEXP){
	hurt = hurt-host->LV>0? hurt:1;
	host->HP=host->HP-(hurt-host->LV);
	host->EXP=host->EXP+2;
	if(host->EXP >= maxEXP){
		host->EXP=0;
		host->LV++;	
	}
  	return *host;
};


int main(int argc, char** argv) {
	int maxHP,maxEXP,elementCount;
	printf("life and experience input:");
	scanf("%d %d",&maxHP,&maxEXP);
	printf("elements count input:");
	scanf("%d",&elementCount);
	scanf("%*[^\n]"); scanf("%*c"); //清空緩衝區

	struct ElementType{
		char object;
		int value;
	};

	struct Host *host = (struct Host*)malloc(sizeof(struct Host));
	host->HP = maxHP;
	host->EXP = 0;
	host->LV = 1;
	
	ElementType *element[elementCount];
	
	bool history[elementCount]={false};
	const char k = 'K';
	const char m = 'M';
	const char b = 'B';
	const char h = 'H';
	
	char tmpObject;
	for(int i=0;i<elementCount;i++){
		struct ElementType* new_node = (struct ElementType*)malloc(sizeof(struct ElementType));
  		element[i] = new_node;		
		printf("element%d:",i);
		
		scanf("%c",&tmpObject);
		element[i]->object=tmpObject;		
		if(tmpObject== k){
			element[i]->value=0;
			scanf("%*[^\n]"); scanf("%*c"); //清空緩衝區
			continue;
		}  
		int tmpVal;
		scanf("%d",&tmpVal);
		scanf("%*[^\n]"); scanf("%*c"); //清空緩衝區
		element[i]->value=tmpVal;
	}
	int stack[elementCount]={0};
	Host *hostStack[elementCount];
	for(int i=0;i<elementCount;i++){
		struct Host* new_node = (struct Host*)malloc(sizeof(struct Host));
  		hostStack[i] = new_node;		
	}	
	int stackCount=0;//堆疊了多少項
	int i=0;
	bool goNext = true;
	bool nofound=false;
	while(stackCount<elementCount && stackCount>-1){
		
		if(goNext!=true) {
			if(stackCount==0){
				nofound=true;
				break;
			} 
			i=stack[stackCount-1];
			history[i]=false;			
			host->EXP=hostStack[stackCount-1]->EXP;
			host->LV=hostStack[stackCount-1]->LV;
			host->HP=hostStack[stackCount-1]->HP;
			stackCount--;	
			
			i++;
		}else{
			i=0;
		}

		goNext=false;
		for(;i<elementCount;i++){
			char object= element[i]->object;

			if(object==k && history[i]==false ){
				
				if(surviveOrNot(host, object, element[i]->value)==true){
					history[i]=true;
					stack[stackCount]=i;
					hostStack[stackCount]->EXP=host->EXP;
					hostStack[stackCount]->LV=host->LV;
					hostStack[stackCount]->HP=host->HP;
					stackCount++;
					*host= kCalcutate(host);
					goNext=true;
					element[i]->value=1; 
					break;
				}
				if(element[i]->value!=1){
					break;			
				}
				
			}else if(object==m  && history[i]==false ){

				if(surviveOrNot(host, object, element[i]->value)==true){
					history[i]=true;
					stack[stackCount]=i;
					hostStack[stackCount]->EXP=host->EXP;
					hostStack[stackCount]->LV=host->LV;
					hostStack[stackCount]->HP=host->HP;
					stackCount++;
					*host = mCalcutate(host,element[i]->value,maxEXP);
					goNext=true;
					break;
				}
				
			}else if(object==b  && history[i]==false ){
				
				if(surviveOrNot(host, object, element[i]->value)==true){
					history[i]=true;
					stack[stackCount]=i;
					hostStack[stackCount]->EXP=host->EXP;
					hostStack[stackCount]->LV=host->LV;
					hostStack[stackCount]->HP=host->HP;
					stackCount++;
					*host=bCalcutate(host,element[i]->value,maxEXP);
					goNext=true;
					break;
				}
				
			}else if(object==h && history[i]==false ){
				
				if(host->HP<maxHP){
					hostStack[stackCount]->EXP=host->EXP;
					hostStack[stackCount]->LV=host->LV;
					hostStack[stackCount]->HP=host->HP;
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

	if(nofound==true){
		printf("no answer");
	}else{
		for(i=0;i<elementCount;i++){
			printf("ouput:%d ",stack[i]+1);
		}
		printf("LV:%d ",host->LV);
		printf("EXP:%d ",host->EXP);
	}
	free(host);
	system("pause");
	return 0;
}
