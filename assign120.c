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
	char day[8],nd[20];
	char pid_release[10];
	int sum=0;
	printf("Enter the pid of the prisoner to release\n");
	scanf("%s",pid_release);

	while(f!=NULL){

		if(strcmp(f->pid,pid_release)==0)
			break;
		//printf("%s\n",f->pid);
		f=f->next;
	}

	if(f!=NULL)
	{
		printf("Enter the release date in form dd/mm/yyyy\n");
		scanf("%s",nd);
		day[0]=nd[0];
		day[1]=nd[1];
		day[2]='\0';
		strcpy(f->rdate.day,day);
		day[0]=nd[3];
		day[1]=nd[4];
		day[2]='\0';
		strcpy(f->rdate.month,day);
		day[0]=nd[6];
		day[1]=nd[7];
		day[2]=nd[8];
		day[3]=nd[9];
		day[4]='\0';
		strcpy(f->rdate.year,day);
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
char selection()
{
	char n;
	printf("Fields to Go:::\n\n<<1>>Show entries.\n<<2>>Print detailed data.\n<<3>>To enter new entry.\n<<4>>To search according to ur need.\n<<5>>To modify\n<<6>>To archive all prisoners who are released 20 years ago from now.\n<<7>>Release prisoner\n<<8>>delete entry.\n9>Exit code\n");

	scanf(" %c",&n);
	return n;

}

