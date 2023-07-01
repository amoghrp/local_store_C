// SIMPLE LOCAL STORE MANAGEMENT PROCESS USING C 
// INPUT THE CHOICE  USING QUEUE 

#define capacity 5
int queue[capacity];
int front=0;
int rear=0;

void add_queue();
void del_queue();
void display_queue();
int main()
{

       int ch;
    while(1){

        printf("\nenter your choice\n1 to add customer to queue\n2 to finish customer service and to remove customer from queue\n3 to display all customers currently  present in queue\n4 to go into shopping main menu\n"); 
        scanf("%d",&ch);
        if(ch==1){
            add_queue();
        }
        else if(ch==2){
            del_queue();
        }
        else if(ch==3){
            display_queue();
        }
        else if(ch==4){
            d_mainmenu();
        }
        else{
            printf("\n you have entered a wrong choice \n TRY AGAIN !!!\n");
        }
    }

    return 0;
}

void add_queue(){

    if(rear==capacity){
        printf("\nnumber of customers is maximum in queue can't add anymore customers !!!\n");
    }
    else{
      printf("\nenter unique INTEGER customer id of the new customer\n");
      scanf("%d",&queue[rear]);
      printf("\ncustomer added successfully\n");
      rear++;
    }
}
void del_queue(){
    int i;
    if(front==rear){
        printf("\nnot found any customer ids to remove , the queue is empty\n");
    }
    else{
        printf("\n customer with id %d is removed\n",queue[front]);
      for(i=0;i<rear-1;++i){
          queue[i]=queue[i+1];
      }
      rear--;
    }
}
void display_queue(){
    int i;
    if(front==rear){
        printf("\nnot found any customers ids to display , the queue is empty\n");
    }
    else {
        printf("displaying currently present customer ids\n");
       for(i=0;i<rear;++i){
           printf("%d\t",queue[i]);
       }
    }
}
//  MAIN MENU 
void d_mainmenu()
{
    int i;
    char ch;
    const char *menu[]= {"   Calculate Bill","   Add Goods","   Edit Goods","   Display All ","   Search", "   Delete Goods","   Exit"};
    system("cls");
//textbackground(11);
//textcolor(0);
//_setcursortype(_NOCURSOR);
    window(25,50,20,32);
    gotoxy(33,18);
     printf("MAIN MENU");
    for (i=0; i<=6; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(7);
}

//  ADD  ITEMS
void add ()
{
    FILE *file;
    char y[ACS],x[12];
    system("cls");
//textbackground(11);
//textcolor(0);
    gotoxy(25,25);
    printf("Enter new item(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","ab");
        c_code(y);
        strcpy(item.code,y);
        gotoxy(22,28);
        printf("Enter rate of the item:");
        scanf("%f",&item.rate);
        gotoxy(22,30);
        printf("Enter quantity of the item:");
        scanf("%d",&item.quantity);
        gotoxy(22,32);
        printf("Enter name of the item:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        gotoxy(22,34);
        printf("Enter new item(Y/N)?");

    }
    d_mainmenu();
}
//  CALCULATE  BILL 
void dbill()
{
    int i;
    gotoxy(20,10);
//;
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * WELCOME * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("Local Store Conduct");
//textcolor(1);
    gotoxy(32,25);
    printf("CUSTOMER'S BILL") ;
//textcolor(8);
    gotoxy(13,27);
    printf("SN.   Item Name     Quantity     Rate          Total");

}
void bill()
{
    char x[4]= {0};
    int j=29,q=0,size=0,i=1;
    float total=0,gtotal=0;
    FILE *file;
    file=fopen("record.txt","r+b");
    rewind(file);
    system("cls");
    dbill();
    gotoxy(26,15);
    printf("enter  \"end\" to finish input");
    while(1)
    {
        gotoxy(25,18);
        printf("                    ");
        gotoxy(25,19);
        printf("                    ");
        gotoxy(25,18);
        printf("enter item code:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        gotoxy(25,19);
        printf("enter quantity:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
                total=item.rate*q;
                gotoxy(11,j);
                printf("%4d",i);
                printf("%9s",item.name);
                printf("%13d",q);
                printf("%15.2f",item.rate);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoxy(30,j+5);
        printf("TOTAL AMOUNT = NRs. %6.2f",gtotal);
    }
    fclose(file);
    getch();
    d_mainmenu();
}

//  EDIT   ITEM  
void edit()
{
    int flag=0,choice;
    char x[ACS],y[ACS];
    FILE *file;
    int size;
    system("cls");
//textcolor(0);
//textbackground(11);
    window(20,63,20,46);
    gotoxy(35,18);
    printf("EDIT ITEM");
    ;
    gotoxy(25,23);
    printf("enter item code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {
                //textcolor(0);
                gotoxy(25,27);
                printf("name       = %s",item.name);
                gotoxy(25,28);
                printf("code       = %s",item.code);
                gotoxy(25,29);
                printf("rate       = %g",item.rate);
                gotoxy(25,30);
                printf("quantity   = %d",item.quantity);
                gotoxy(25,32);;
                printf("Do you want to edit this item?(y/n):");
                fflush(file);
                if(toupper(getche())=='Y')
                {
                    //textcolor(0);
                    gotoxy(25,34);
                    printf("1- edit name ");
                    gotoxy(25,35);
                    printf("2- edit code ");
                    gotoxy(25,36);
                    printf("3- edit rate ");
                    gotoxy(25,37);
                    printf("4- edit quantity ");
                    gotoxy(25,39);  ;
                    printf(" enter your choice(1, 2, 3, 4) ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        system("cls");
                        window(23,48,20,40);
                        gotoxy(35,18);
                        printf("EDIT ITEMS");
                        gotoxy(25,24);
                        printf(" enter new name: ");
                        scanf("%s",item.name);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT ITEMS");
                        gotoxy(25,24);
                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT ITEMS");
                        gotoxy(25,24);
                        printf(" enter new rate: ");
                        scanf("%f",&item.rate);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT ITEMS");
                        gotoxy(25,24);
                        printf(" enter new quantity: ");
                        scanf("%d",&item.quantity);
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }
                    gotoxy(27,30);
                    printf("--- item edited---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoxy(32,30);
        printf("Item does not exist.");
        gotoxy(36,32);
        printf("TRY ABGAIN");
    }
    getch();
    fclose(file);
    d_mainmenu();
}
//  SEARCH  ITEMS 
void d_search()
{
    char ch;
    int i;
    const char *menu[]= {"   By Code","   By Rate","   By Quantity","   Back to main menu"};
    system("cls");
//textbackground(11);
//textcolor(0);
    window(25,50,20,32);
    gotoxy(33,18);
    printf("SEARCH MENU");
    for (i=0; i<=3; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(4);
}
//  DELETE
void del()
{
    int flag;
    char x[ANS];
    FILE *file,*file1;
    system("cls");
//textbackground(11);
//textcolor(0);
    window(23,51,25,34);
    gotoxy(29,18);
    printf("DELETE ITEMS");
    gotoxy(27,27);
    printf("enter item code: ");
    scanf("%s",&x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        gotoxy(27,29);
        printf("---item deleted---");
        remove("record.txt");
        rename("record1.txt","record.txt");
    }
    if (flag==1)
    {
        gotoxy(25,29);
        printf("---item does not exist---");
        gotoxy(30,31);
        printf("TRY AGAIN");
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}
