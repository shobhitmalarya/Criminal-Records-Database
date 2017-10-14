//Criminal database
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>


//Defining Structures.
typedef struct date {
	char day[3];
	char month[3];
	char year[5];

}DATE;
//Composite structure with date.
typedef struct info{
	char pid[10];
	char name[33];
	char offence[100];
	char region[20];
	char prisonname[50];
	struct date adate;
	struct date rdate;
	struct info *next;
}INFO;
//Format for printing.

void  copy_to_file(INFO *f);
void print_detail(INFO *f);

void printd(){
	printf("___________________________________________________________________________________________________________\n");
	printf("|PID \t\t--- \t|NAME\n");//Spefied format.
	printf("___________________________________________________________________________________________________________\n");

}
//Function to read and create and insert item into a linked list.
INFO *insertItem(INFO *t){

	INFO *I=(INFO *)malloc(sizeof(INFO));//Allocating memory.
	while(t->next!=NULL){
		t=t->next;
	}
	I->next=NULL;
	t->next=I;
	return I;
	//returning generated temp node for linking.
}
INFO *genDataset(FILE *fp){
	INFO *head=NULL;//local head declaration.
	char listp[9999],buffer[5];//Dual dim array to break and store per line by "#" delimiter.
	head=(INFO*)malloc(sizeof(INFO));
	head->next=NULL;//Head is NULL.
	//Reading a line from file and breaking it.
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

//File creation and update of file.
//After creating of linked list file is written by extracting data from lnkd lst.
void fileupdate(INFO *node, char adate[], char rdate[]){

	FILE *fp;
	fp=fopen("file.txt","a");
	fprintf(fp,"%s",node->pid);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",node->name);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",node->offence);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",node->region);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",node->prisonname);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",adate);
	fprintf(fp,"%s","#");
	fprintf(fp,"%s",rdate);
	fprintf(fp,"%s","\n");

	fclose(fp);

}
int checkdate(char str[],char d[],char m[])
{
	int l;
	l=strlen(str);
	if(l==10&&str[2]=='/'&&str[5]=='/'&&atoi(d)<=31&&atoi(m)<=12)
		return 1;
	else
		return 0;	
}
int  rel_arr(int ad,int am,int ay,int rd,int rm,int ry)
{
	int a,r;
	a=ay*365+am*31+ad;
	r=ry*365+rm*31+rd;
	if(r>=a)
		return 1;
	else
		return 0;	
}

//Takes data from user to be inserted in database.
INFO *insert(INFO *root){
	INFO *tempnode = (INFO*)malloc(sizeof(INFO));
	printf("ENTER FOLLOWING DETAILS : \n");
	int d_check,r_check; 
	char pid[10],name[20],offence[100],region[20],prisonname[20],adate[15],rdate[15],day[4],month[4],year[6];


	while (1){
		int flag=0;//Checks if PID is already in database. if not flag==1.(Condition).
		INFO *node = root;//Copying head into node.
		printf("P-ID : ");
		scanf("%s",pid);
		getchar();
		//printf("");
		while(node!=NULL){
			if (strcmp(pid,node->pid)==0){
				flag=1;
				break;
			}
			node=node->next;
		}
		if ( flag == 1 ) {
			printf("INVALID or USED PID !! \n");
		} else {
			break;
		}
	}

	printf("OFFENCE : ");
	scanf("%[^'\n']s",offence);
	getchar();
	printf("REGION : ");
	scanf("%[^'\n']s",region);
	getchar();
	printf("NAME : ");
	scanf("%[^'\n']s",name);
	getchar();
	printf("PRISON NAME : ");
	scanf("%[^'\n']s",prisonname);
	getchar();

	printf("DATE OF ARREST (IN FORMAT DD/MM/YYYY) : ");

	scanf("%[^'\n']s",adate);
	getchar();

	while(1)
	{    //String formatting. BY FORMAT DD/MM/YYYY.
		day[0]=adate[0];
		day[1]=adate[1];
		day[2]='\0';
		month[0]=adate[3];
		month[1]=adate[4];
		month[2]='\0';
		year[0]=adate[6];
		year[1]=adate[7];
		year[2]=adate[8];
		year[3]=adate[9];
		year[4]='\0';		
		d_check=checkdate(adate,day,month);


		if(d_check==1){
			//Copying data into lnkd structure.
			strcpy(tempnode->adate.day ,day);
			strcpy(tempnode->adate.month ,month);
			strcpy(tempnode->adate.year ,year);
			break;
		}
		else{
			printf("Invalid date \nRetry\n");
			printf("DATE OF ARREST (IN FORMAT DD/MM/YYYY) : ");        
			scanf("%[^'\n']s",adate);
			getchar();
		}
	}
	printf("DATE OF RELEASE (IN FORMAT DD/MM/YYYY) : ");
	scanf("%[^'\n']s",rdate);
	getchar();

	while(1){

		day[0]=rdate[0];
		day[1]=rdate[1];
		day[2]='\0';
		month[0]=rdate[3];
		month[1]=rdate[4];
		month[2]='\0';
		year[0]=rdate[6];
		year[1]=rdate[7];
		year[2]=rdate[8];
		year[3]=rdate[9];
		year[4]='\0';

		d_check=checkdate(rdate,day,month);
		r_check=rel_arr(atoi(tempnode->adate.day),atoi(tempnode->adate.month),atoi(tempnode->adate.year),atoi(day),atoi(month),atoi(year));

		if(d_check==1 && r_check==1){
			strcpy(tempnode->rdate.day ,day);
			strcpy(tempnode->rdate.month ,month);
			strcpy(tempnode->rdate.year ,year);
			break;
		}
		else{
			printf("Invalid date \nRetry\n");
			printf("DATE OF Release (IN FORMAT DD/MM/YYYY) : ");        
			scanf("%[^'\n']s",rdate);
			getchar();
		}
	}
	strcpy(tempnode->pid,pid);
	strcpy(tempnode->name,name);
	strcpy(tempnode->offence,offence);
	strcpy(tempnode->region,region);
	strcpy(tempnode->prisonname,prisonname);


	tempnode->next = NULL;

	fileupdate(tempnode,adate,rdate);//Data read is updated into file.
	print_detail(tempnode);	

	return tempnode;
}

void newentry( INFO *root ){
	INFO *head = root;
	while(root->next != NULL){
		root=root->next;
	}
	root->next=insert(head);
	root->next->next=NULL;
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
			printf("Their is no such region registered\n");
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
			printf("Their is no such prison\n");
		return;
	}



	if (strcmp(f->prisonname,pnm)==0 ){
		if(flag==0)    {
			printf("Person found\n");
			flag=1;
			print_detail(f);return;
		}


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
/*---------------------------------------------------------------------------------------------------------------------*/
//Main function of search.
void search(INFO *f,int s){
	int flag=0;
	switch(s){
		char str[30];
		//Passing required data to specific utility function.
		//By swithing cases.
		case 1: printf("Enter the PID to be searched: ");getchar();scanf("%[^'\n']s",str);getchar();searchByPID(f,str,flag);printf("\n");break;
		case 2: printf("Enter the NAME to be searched: ");getchar();scanf("%[^'\n']s",str);getchar();searchByNAME(f,str,flag);printf("\n");break;
		case 3: printf("Enter the OFFENCE to be searched: ");getchar();scanf("%[^'\n']s",str);getchar();searchByOFFENCE(f,str,flag);printf("\n");break;
		case 4: printf("Enter the REGION to be searched: ");getchar();scanf("%[^'\n']s",str);getchar();searchByREGION(f,str,flag);printf("\n");break;
		case 5: printf("Enter the PRISON NAME to be searched: ");getchar();scanf("%[^'\n']s",str);getchar();searchByPRISONNM(f,str,flag);printf("\n");break;
		case 6: printf("Enter the ARREST DATE to be searched: ");scanf("%s",str);searchByADATE(f,str,flag);printf("\n");break;
		case 7: printf("Enter the RELEASE DATE to be searched: ");scanf("%s",str);searchByRDATE(f,str,flag);printf("\n");break;
		default: printf("Wrong Choice\n");
	}
}

/*-----------------------------------------MODIFY-----------------------------------------------------------------*/
//Utility functions for modify.

INFO *searchPID(INFO *f)       //FUNCTION TO SEARCH WHETHER THE GIVEN PID EXISTS IN THE RECORD 
{
	char id[10];
	printf("\nENTER THE PID:\t"); //ASKING FOR THE PID TO BE SEARCHED
	scanf("%s",id);

	while(f!=NULL){
		if(strcmp(id,f->pid)==0)  //SEARCHING WHETHER THE GIVEN PID EXISTS IN THE RECORD  
			return f;               //RETURNING THE NODE CONTAINING THE GIVEN PID
		f = f->next;  
	}
}

int IsPidAvailable(INFO *head,char nid[]) //FUNCTION TO CHECK WHETHER GIVEN PID IS ALREADY USED/SAME
{
	int fl = 0;
	while(head!=NULL)
	{
		if(strcmp(nid,head->pid)==0)
		{
			fl = 1;                             //SETTING FLAG TO 1
			printf("\n\n...ALREADY USED/SAME PID...\n\n");
			break;
		}
		head = head->next;
	}
	return fl;                     //RETURNING FLAG '0'-UNUSED '1'- USED/SAME
}

void modifyPID(INFO *f,INFO *head) //FUNCTION TO MODIFY PRISONER'S PID 
{
	char nid[10];
	int c = 0,u;

	while(c<3)                      //GIVING THE USER 3 CHANCES TO ENTER UNUSED PID
	{
		printf("\nENTER NEW PID:\t");
		scanf("%s",nid);
		u = IsPidAvailable(head,nid);   //CHECKING WHETHER THE PID ENTERED IS USED OR NOT
		if(u==0){
			printf("\n..............MODIFYING................\n");        sleep(2);  
			printf("\n--------------SUCCESS!!!---------------\n");        sleep(2);
			strcpy(f->pid,nid);
			break;
		}
		else
			c++;
	}
	if(c>=3)
		printf("...SORRY! WE CAN'T UNDERSTAND YOU...\n");
}

void modifyNAME(INFO *f)  //FUNCTION TO MODIFY PRISONER'S NAME 
{
	char nnam[100];

	printf("\nENTER NEW NAME:\t");
	getchar();
	scanf("%[^'\n']s",nnam);
	getchar();
	strcpy(f->name,nnam);
	printf("\n..............MODIFYING................\n");        sleep(2);  
	printf("\n---------------SUCCESS!!!---------------\n");       sleep(1);
}

void modifyOFFENCE(INFO *f) //FUNCTION TO MODIFY PRISONER'S OFFENCE 
{
	char noff[100];

	printf("\nENTER NEW OFFENCE:\t");
	getchar();
	scanf("%[^'\n']s",noff);
	getchar();
	strcpy(f->offence,noff);
	printf("\n..............MODIFYING................\n");        sleep(2);  
	printf("\n--------------SUCCESS!!!---------------\n");        sleep(1);
}

void modifyREGION(INFO *f)  //FUNCTION TO MODIFY REGION OF PRISONER
{
	char nreg[100];

	printf("\nENTER NEW REGION:\t");
	getchar();
	scanf("%[^'\n']s",nreg);
	getchar();
	strcpy(f->region,nreg);
	printf("\n..............MODIFYING................\n");        sleep(2);  
	printf("\n--------------SUCCESS!!!---------------\n");        sleep(1);
}

void modifyPRISONNM(INFO *f)  //FUNCTION TO MODIFY PRISON NAME 
{
	char npnm[100];

	printf("\nENTER NEW PRISONNAME:\t");
	getchar();
	scanf("%[^'\n']s",npnm);
	getchar();
	strcpy(f->prisonname,npnm);
	printf("\n..............MODIFYING................\n");        sleep(2);  
	printf("\n---------------SUCCESS!!!--------------\n");        sleep(1);
}

void modifyADATE(INFO *f) //FUNCTION TO MODIFY ARRIVAL DATE OF PRISONER
{
	int flag = 0,d_check;
	char adate[10],day[6],month[3],year[5];

	printf("\nENTER NEW ARREST DATE (IN FORMAT DD/MM/YYYY):\t");
	scanf("%s",adate);
	getchar();

	while(1)
	{    //String formatting. BY FORMAT DD/MM/YYYY.
		day[0]=adate[0];
		day[1]=adate[1];
		day[2]='\0';
		month[0]=adate[3];
		month[1]=adate[4];
		month[2]='\0';
		year[0]=adate[6];
		year[1]=adate[7];
		year[2]=adate[8];
		year[3]=adate[9];
		year[4]='\0';		
		d_check=checkdate(adate,day,month);	
		int rcheck = rel_arr(atoi(day),atoi(month),atoi(year),atoi(f->rdate.day),atoi(f->rdate.month),atoi(f->rdate.year));

		if(d_check==1 && rcheck==1)	//CHECKING WHETHER THE DATE ENTERED IS VALID OR NOT
		{
			//Copying data into lnkd structure.
			strcpy(f->adate.day ,day);
			strcpy(f->adate.month ,month);
			strcpy(f->adate.year ,year);
			break;
		}
		else
		{
			printf("Invalid date \nRetry\n");
			printf("DATE OF ARREST (IN FORMAT DD/MM/YYYY) : ");        
			scanf("%[^'\n']s",adate);
			getchar();
		}
	}
	printf("\n..............MODIFYING................\n");        sleep(1);  
	printf("\n--------------SUCCESS!!!---------------\n");        sleep(1);
}

void modify(INFO *f)  //DRIVER PROGRAM TO MODIFY RECORDS
{
	int ch,c,fl=0;
	INFO *status = NULL;  //TO STORE THE STATUS WHETHER A RECORD IS PRESENT OR NOT
	printf("\n1--> PRESS 1 TO ENTER THE PID OF THE PRISONER WHOSE DETAILS HAS TO BE MODIFIED\n\n\n");
	scanf("%d",&c);

	switch(c){
		case 1: status = searchPID(f);  //TO SEARCH WHETHER GIVEN PID EXISTS AND RETURN THE NODE
			break;
		default: printf("---------------WRONG ENTRY!!!------------\n");
			 fl = 1;
	}
	if(fl!=1)     //IF WRONG CHOICE IS NOT MADE
	{
		printf("\n....................SEARCHING..................\n");    sleep(2);

		if(status!=NULL)  //CHECKING IF THE ASKED RECORD EXISTS
		{
			printf("\n--------------------MATCH FOUND--------------------\n\n");    sleep(1);
			print_detail(status);   sleep(1);
			printf("\n---------------------------------------------\nENTER THE FIELD TO BE MODIFIED\n1>PID\n2>NAME\n3>OFFENCE\n4>REGION\n5>PRISONNAME\n6>ARRESTED DATE\n7>RELEASE DATE\n\n");
			scanf("%d",&ch);

			switch(ch){
				case 1: modifyPID(status,f);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
					print_detail(status);break;

				case 2: modifyNAME(status);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
					print_detail(status);break;

				case 3: modifyOFFENCE(status);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);  
					print_detail(status);break;

				case 4: modifyREGION(status);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);  
					print_detail(status);break;

				case 5: modifyPRISONNM(status);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);  
					print_detail(status);break;

				case 6: modifyADATE(status);
					printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);   
					print_detail(status);break;

				case 7: printf("\n-------------SORRY! NOT PERMITTED.--------------\n");  
					break;

				default: printf("\n---------Wrong Choice-------------\n\n");
			}
		}
		else
			printf("\n-------------NO SUCH RECORD FOUND------------\n");
	}
}

/*-------------------------------------------------------------------------------------------------------*/

//Function for maintainig archive.
//You will have choice what to archive.(Years //Release Date)
INFO* archive(INFO *t,INFO *arc){
	INFO *f,*temp;
	t->next=arc;
	arc=t;
	f=arc;
	if(strlen(t->pid)>2){
		printf("Ward Id:%s\tWard name\t%s----------------SEND TO ARCHIVE\n",t->pid,t->name);
		FILE *fp1=fopen("archive.txt","a");
		fprintf(fp1,"%s#%s#%s#%s#%s#%s/%s/%s#%s/%s/%s\n",f->pid,f->name,f->offence,f->region,f->prisonname,f->adate.day,f->adate.month,f->adate.year,f->rdate.day,f->rdate.month,f->rdate.year);
		fclose(fp1);}
	return arc;
}
//Function to release prisoner and update/modify database.
void release_prisoner(INFO *f)
{
	char day[6],nd[20];
	char pid_release[10];
	int sum=0;
	printf("ENTER PID: ");
	scanf("%s",pid_release);
	 
	printf("**'RELEASING PRISONER NOW'\n");
	sleep(1);
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); //TO STORE CURRENT DATE AND TIME INTO BUFFER
	
	
	

	while(f!=NULL){

		if(strcmp(f->pid,pid_release)==0)
			break;
		//printf("%s\n",f->pid);
		f=f->next;
	}
	
	
	if(f!=NULL)
	{	
		day[0]=buffer[0];
		day[1]=buffer[1];
		day[2]=buffer[2];
		day[3]=buffer[3];
		day[4]='\0';
		strcpy(f->rdate.year,day);
		day[0]=buffer[5];
		day[1]=buffer[6];
		day[2]='\0';
		strcpy(f->rdate.month,day);
		day[0]=buffer[8];
		day[1]=buffer[9];
		day[2]='\0';	
		strcpy(f->rdate.day,day);
		
		print_detail(f);
		printf("** THIS PRISONER IS RECORDED AS RELEASED TODAY**\n");
	}
	if(f==NULL)
		printf("Error no prisoner of this type\n");
}
//Utility functions to copy and replace in another file!.

void  copy_to_file(INFO *f)
{
	FILE *fp3=fopen("file.txt","w");
	while(f!=NULL)
	{
		fprintf(fp3,"%s#%s#%s#%s#%s#%s/%s/%s#%s/%s/%s\n",f->pid,f->name,f->offence,f->region,f->prisonname,f->adate.day,f->adate.month,f->adate.year,f->rdate.day,f->rdate.month,f->rdate.year);
		f=f->next;
	}
	fclose(fp3);
}
//Option to archive evrything.
INFO* archive_all(INFO *f,INFO *arc)
{

	INFO *temp;
	int sum=0,r;
	printf("SENDING  DATA OF PRISONER RELEASED 20 YEARS FROM NOW tO 'Archive Section'" );
	while(f->next!=NULL){

		r=atoi(f->next->rdate.year);
		sum=2017-(int)r;

		if(sum>=20)
		{

			INFO *t,*temp;
			temp=f;
			t=f->next;
			temp->next=temp->next->next;
			arc=archive(t,arc);

		}
		else
			f=f->next;
	}
	return arc;
}
//Function for login of admin.
//Allows 3 wrong credentials after that it terminates.
int check_user(char *str){
	int l,i=0,j=0,f=1;//soumik.m16@iiits.in
	l=strlen(str);
	char b[]="@iiits.in";
	for(i=l-9;i<l;i++){
		if(str[i]!=b[j]){
			f=0;
			break;
		}
		j++;
	}
	if(f==1)
		return 1;
	else
		return 0;
}

void maintain_log(FILE *fp,char u[])  //FUNCTION TO MAINTAIN LOG OF ALL USERS ACCESSING THE DATABASE
{
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); //TO STORE CURRENT DATE AND TIME INTO BUFFER
	fprintf(fp,"%s\t%s\n",u,buffer);
}

int autheticate(){
	char userid[]="DS",password[]="iiits",p[15],u[35];
	int n=1,a,b,ret=0;
	FILE *fp=fopen("loginlog.txt","a");
	printf("\nEnter USER ID and PASSWORD below(You have only three chances to enter)\n");
	while(n<=3)
	{

		printf("\nUSER ID: ");
		scanf("%s",u);
		int log=check_user(u);
		printf("\nPASSWORD: ");
		scanf("%s",p);
		//a=strcmp(u,userid);
		b=strcmp(p,password);
		if(log==1&&b==0)
		{
			printf("\nYou have logged in successfully.\n");ret=1;
			//fprintf(fp,"%s\t",u);
			//fprintf(fp,"%s","\n");
			//printf("%s\n",u);
			maintain_log(fp,u);
			fclose(fp);
			break;
		}
		else
		{
			printf("\nWrong PASSWORD and/or USER ID. Now you have % d more chance/s.\n",3-n);
		}

		n++;
	}
	if(n==4)
		printf("\nYou can't log in.\n");

	return ret;
}
//Switch fucntion to perform various task using main utility functions.
int selection()
{
	int n;

	printf("\nFields to Go:::\n");
	printf("_________________________________________________________________________________________\n\n");
	printf("<<1>> Show entries.\n\n<<2>> Print detailed data.\n\n<<3>> To enter new entry.\n\n<<4>> To search according to ur need.\n\n<<5>> To modify.\n\n<<6>> To archive all prisoners who are released 20 years ago from now.\n\n<<7>> Release prisoner Before Actual Release Date (''TODAY'')\n\n<<8>> Delete entry.\n\n** 9 >Exit code\n");
	printf("_________________________________________________________________________________________\n");
	scanf(" %d",&n);
	return n;

}
//Function to delete a node.
void deletenode(INFO *prenode,INFO *node){

	prenode->next=node->next;
	free(node);

	printf("\n***ENTRY SUCESSFULLY DELETED***\n");

	//copy_to_file(INFO *head);
}
//Main Function.
int main(){

	int c;
	FILE *file;
	file = fopen("initialize.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF)
			putchar(c);
		fclose(file);
	}

	char n;
	int st=autheticate();
	if(st==1){
		INFO *info,*arc;
		FILE *fp=fopen("file.txt","r+");
		info=genDataset(fp);
		fclose(fp);
		INFO *node=info->next;

		n=selection();
		while(1)
		{
			if(n==9)
				break;
			switch(n){

				case 1:
					printd();
					print(info->next);printf("\n");
					break;
				case 2:
					node=info->next;
					while (node!=NULL){
						print_detail(node);
						node=node->next;
					}
					break;
				case 3:
					newentry(info->next);
					printf("\n");
					break;
				case 4:
					printf("Fields to search :::\n1> PID\n2> NAME\n3> OFFENCE\n4> REGION\n5> PRISONNAME\n6> ARRESTED DATE\n7> RELEASE DATE\n\n");
					printf("Enter the choice you want to search\n");
					int n=0;
					scanf("%d",&n);
					search(info,n);printf("\n");
					break;
				case 5:
					modify(info);
					copy_to_file(info->next);printf("\n");
					break;
				case 6:
					arc=NULL;
					arc=archive_all(info,arc);
					copy_to_file(info->next);
					break;
				case 7:
					release_prisoner(info->next);
					copy_to_file(info->next);
					printf("\n");
					break;
				case 8:
					printf("ENTER PID: ");
					char pid[8],quit[]="q";
					while (1){
						int f=1;
						INFO *nod=info;
						scanf("%s", pid);
						if (strcmp(pid,quit)==0){
							printf("\n");
							break;
						}
						while (nod->next != NULL){
							if (strcmp(pid,nod->next->pid)==0){
								printf("\n***found\n");
								f=0;
								break;
							}
							nod=nod->next;
						}
						if (f==0){
							print_detail(nod->next);
							printf("** CONFIRM DELETE  (y/n): ");
							char con[2];
							scanf("%s",con);
							if (con[0] == 'y' || con[0] == 'Y'){
								deletenode(nod,nod->next);
								copy_to_file(info->next);printf("\n");
								printf("\nENTER q TO QUIT or DELETE ANOTHER pid : ");
							} else {
								printf("** deletion canceled **\n");
								break;
							}
						} else {
							printf("INVALID PID!! \n RETRY or ENTER q TO QUIT \n : ");
						}
					}
					break;
				default :
					printf("Wrong Choice\n");

			}
			n=selection();	}}
	else
		printf("You need to login again!.\n");
	return 0;
}
