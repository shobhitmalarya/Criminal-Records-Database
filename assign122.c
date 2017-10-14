/*SOUMIK MANDAL*/
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef struct date {
  char day[3];
	char month[3];
  char year[5];

}DATE;

typedef struct info{
 char pid[10];
 char name[33];
 char offence[100];
 char region[20];
 char prisonname[20];
 struct date adate;
 struct date rdate;
 struct info *next;
}INFO;
INFO *insertItem(INFO *t){

  INFO *I=(INFO *)malloc(sizeof(INFO));
	while(t->next!=NULL){
		t=t->next;
	}
	I->next=NULL;
	t->next=I;
	return I;
}
INFO *genDataset(FILE *fp){
	INFO *head=NULL;
	char listp[9999],buffer[5];
	head=(INFO*)malloc(sizeof(INFO));
	head->next=NULL;
	while(fgets(listp,sizeof(listp),fp)!= NULL){
		INFO *I;
		int i,j=0,k=0;
		char type[100][100]={"\0"};
		I=insertItem(head);
		for(i=0;i<strlen(listp);i++){
			if(listp[i]=='#'){
				type[j][k++]='\0';
				k=0;
				j++;
			}
			else
				type[j][k++]=listp[i];
		}
	strcpy(I->pid,type[0]);
  //printf("%s\t",I->pid);
	strcpy(I->name,type[1]);
  //printf("%s\n",type[1]);
	strcpy(I->offence,type[2]);
	strcpy(I->region,type[3]);
  //printf("%s\n",I->region);
	strcpy(I->prisonname,type[4]);
  //printf("%s_____\n",type[4]);
	buffer[0]=type[5][0];
	buffer[1]=type[5][1];
	buffer[2]='\0';
  //printf("****************%s\n",buffer);
    strcpy(I->adate.day,buffer);
    buffer[0]=type[5][3];
    buffer[1]=type[5][4];
    buffer[2]='\0';
    strcpy(I->adate.month,buffer);
    //printf("##########%s\n",I->adate.month);
    buffer[0]=type[5][6];
    buffer[1]=type[5][7];
    buffer[2]=type[5][8];
    buffer[3]=type[5][9];
    buffer[4]='\0';
    strcpy(I->adate.year,buffer);

	buffer[0]=type[6][0];
	buffer[1]=type[6][1];
	buffer[2]='\0';
    strcpy(I->rdate.day,buffer);
    buffer[0]=type[6][3];
    buffer[1]=type[6][4];
    buffer[2]='\0';
    strcpy(I->rdate.month,buffer);
    buffer[0]=type[6][6];
    buffer[1]=type[6][7];
    buffer[2]=type[6][8];
    buffer[3]=type[6][9];
    buffer[4]='\0';
    strcpy(I->rdate.year,buffer);

	}
return head;
}
//Print the details of a specific node.

void print_detail(INFO *f){
	printf("___________________________________________________________________________________________________________\n");

	printf(" |PID: %s \n |NAME: %s \n |OFFENCE: %s\n |REGION: %s\n |PRISON NAME: %s\n |ARREST-DATE: %s/%s/%s\n |RELEASE-DATE: %s/%s/%s\n",f->pid,f->name,f->offence,f->region,f->prisonname,f->adate.day,f->adate.month,f->adate.year,f->rdate.day,f->rdate.month,f->rdate.year);
	printf("___________________________________________________________________________________________________________\n");
}

void print_node(INFO *f){

   printf("|%s \t\t |%s \t\t |%s \t\t |%s\t\t |%s \t\t |%s/%s/%s\t|%s/%s/%s\n",f->pid,f->name,f->offence,f->region,f->prisonname,f->adate.day,f->adate.month,f->adate.year,f->rdate.day,f->rdate.month,f->rdate.year);
 printf("___________________________________________________________________________________________________________\n");

  }
//Print all the details in the database.
void print(INFO *f){
  if (f == NULL){
 	 printf("___________________________________________________________________________________________________________\n");

    return;}
    else {
      printf("|%s \t\t --- \t%s \n",f->pid,f->name);
      print(f->next);
    }
}
//Utility functions by the type or field of search.
/*---------------------------------------------------------------------------------------*/
void searchByPID(INFO *f, char *pi,int flag){//Function to search by pid.

  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}


  if (strcmp(f->pid,pi)==0 ){
	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}	print_detail(f);

  } searchByPID(f->next,pi,flag);
}
void searchByNAME( INFO *head,char *str,int flag){//Function to search by NAME.

    int length = strlen(str),count=0,i;
    INFO *node = head;
    printf("%s - RESULTS : \n",str);
    while (node != NULL){

        if (length <= strlen(node->name)){
            flag = 0;
            for(i=0; i<length; i++){
                if (str[i] != node->name[i]){
                    flag = 1;
                    break;
                }
            } if (flag == 0) {
		if(count==0)
                print_detail(node);
                count++;
            }
        }
        node=node->next;
    }

    if (count == 0){
        printf("SORRY ! NO MATCHES FOUND \n");
    }
}


void searchByOFFENCE(INFO *f,char *off,int flag){//Function to search by OFFENCE.

  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}


  if (strcmp(f->offence,off)==0 ){
	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}
	print_detail(f);
   }
   searchByOFFENCE(f->next,off,flag);
}
void searchByREGION(INFO *f,char *reg,int flag){//Function to search by REGION.
  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}


  if (strcmp(f->region,reg)==0 ){
    	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}print_detail(f);

 } searchByREGION(f->next,reg,flag);

}
void searchByPRISONNM(INFO *f,char *pnm,int flag){//Function to search by PRISON NAME.
  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}



  if (strcmp(f->prisonname,pnm)==0 ){
	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}
	print_detail(f);

  }  searchByPRISONNM(f->next,pnm,flag);

}
void searchByADATE(INFO *f,char *d,int flag){//Function to search by ARRESTED DATE.
int dd=atoi(d);
int mm=atoi(d+3);
int yy=atoi(d+6);

  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}

//printf("The date to search is ::%d/%d/%d",dd,mm,yy);
if((atoi(f->adate.day)==dd && atoi(f->adate.month)==mm && atoi(f->adate.year)==yy )){

	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}
	print_detail(f);

}searchByADATE(f->next,d,flag);
}
void searchByRDATE(INFO *f,char *d,int flag){//Function to search by RELEASE DATE.
  int dd=atoi(d);
  int mm=atoi(d+3);
  int yy=atoi(d+6);

  if( f == NULL)
	{
	if(flag==0)
		printf("Their is no such prisoner\n");
	return;
	}

  //printf("The date to search is ::%d/%d/%d",dd,mm,yy);
  if((atoi(f->rdate.day)==dd && atoi(f->rdate.month)==mm && atoi(f->rdate.year)==yy)||f==NULL){
	if(flag==0)    {
	printf("Person found\n");
	flag=1;
	}
	print_detail(f);

  }  searchByRDATE(f->next,d,flag);
}


int main(){



  return 0;
}
