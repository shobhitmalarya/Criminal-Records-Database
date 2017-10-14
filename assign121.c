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
  int flag = 0;
  char nd[10],day[6];

    printf("\nENTER NEW ARREST DATE:\t");
    scanf("%s",nd);
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

    if(d_check==1 && rcheck==1)  //CHECKING WHETHER THE DATE ENTERED IS VALID OR NOT
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

      printf("\n..............MODIFYING................\n");        sleep(2);  
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
  printd();
  print_node(status);   sleep(1);
  printf("\n---------------------------------------------\nENTER THE FIELD TO BE MODIFIED\n1>PID\n2>NAME\n3>OFFENCE\n4>REGION\n5>PRISONNAME\n6>ARRESTED DATE\n7>RELEASE DATE\n\n");
  scanf("%d",&ch);

  switch(ch){
    case 1: modifyPID(status,f);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd();
    print_node(status);break;
    
    case 2: modifyNAME(status);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd(); 
    print_node(status);break;
    
    case 3: modifyOFFENCE(status);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd();  
    print_node(status);break;
    
    case 4: modifyREGION(status);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd();  
    print_node(status);break;
    
    case 5: modifyPRISONNM(status);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd();  
    print_node(status);break;
    
    case 6: modifyADATE(status);
    printf("\n\n-------------RECORD AFTER MODIFICATION---------------------\n\n");  sleep(1);
    printd();   
    print_node(status);break;
    
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