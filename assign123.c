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

void deletenode(INFO *prenode,INFO *node){

    prenode->next=node->next;
    free(node);

    printf("\n***ENTRY SUCESSFULLY DELETED***\n");

    //copy_to_file(INFO *head);
}

// ***** piece of code used in deletion
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
// *****
