#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct book
{
	char code[12];
	char name[30];
	int quantity;
	double cost;
	

}b;

void insert_details();
void viewAll();
bool find(char id[12]);
void delete();
void changeInfo();
int countLines();


void main()
{
    system("cls");

	 int ch;
 	do{
	printf("\n====================================================================");
	printf("\n");	
	printf("\t Moive Ticket booking ");
	printf("\n");
	printf("\n====================================================================");
	
	printf("\nPress <1> Insert Movie");
   	printf("\nPress <2> View All Movie");
	printf("\nPress <3> Change Information ");
    printf("\nPress <4> Delete ");
   	printf("\nPress <5> Exit ");

   	printf("\nEnter your Choice ::");
   	scanf("%d",&ch); 	

   	switch (ch)
   	{
    		case 1 :
    		insert_details();
   		break;
		case 2:
    		viewAll();
   		break;
    		
		case 3:
    		changeInfo();
   		break;
        
        case 4:
            delete();

    		case 5:
    		exit(0);
    		break;

    		default:
    		printf("Wrong choice !");
    		break;
   	}
 }while(ch!=0);

}


void insert_details()
{
	
	FILE *fp;
	struct book b;
    char id[12];
	printf("Enetr movie code :- ");	
	scanf("%s",id);
    while(!find(id))
    {
        printf("Id  already exists please enter again !\n");
        scanf("%s",id);
    }
    strcpy(b.code,id);
	printf("Enter  name :- ");	
	scanf("%s",b.name);
	printf("Enetr quantity:- ");	
	scanf("%d",&b.quantity);
	printf("Enetr Ticket Price:- ");	
	scanf("%lf",&b.cost);
	
	fp=fopen("data.dat","a");
    if(fp != NULL)
    {
        fprintf(fp," ");
    }
	if(fp == NULL)
	{
		printf("FIle not Found");
	}
	else
	{
		fprintf(fp,"%s %s %d %.3lf\n",b.code,b.name,b.quantity,b.cost);
		printf("Record insert Sucessfull");
	}
		printf("\n");
	fclose(fp);
    system("pause");
    system("cls");
    main();
}

void changeInfo()
{
    int lines = countLines();
    printf("%d",lines);
    int flag = 0;
	struct book b;
	FILE *fp;
    FILE *temp;
    char title[30];
    int quan;
    double price;

	char ch[12];
	printf("Enter movie code :");
	scanf("%s",ch);
	fp = fopen("data.dat","r");
	if(fp == NULL)
	{
		printf("file does not found !\n");

	}
	else
	{
        temp = fopen("dataNew.dat","w");
        fprintf(temp," ");	
		while(getc(fp) != EOF && lines > 0)
		{
            lines --;
            fscanf(fp,"%s %s %d %lf",b.code,b.name,&b.quantity,&b.cost);
            if(strcmp(b.code,ch) != 0)
            {
                fprintf(temp,"%s %s %d %.3lf\n",b.code,b.name,b.quantity,b.cost);
            }
            else
            {
                fprintf(temp,"%s ",b.code);
                printf("Enter Name");
                fflush(stdin);
                int i =0;
                char ch;
                while((ch = getchar())!='\n')
                {
                    title[i++] = ch;
                }
                if(i == 0)
                {
                    fprintf(temp,"%s",b.name);
                }
                else
                {
                    fputs(title,temp);
                }
                
                printf("Enter Quantity");
                fflush(stdin);
                ch = getchar();
                quan = 0;
                while(isdigit(ch))
                {
                    quan = (quan * 10) + (ch - '0');
                    ch = getchar();
                }
                if(quan == 0)
                {
                    fprintf(temp," %d ",b.quantity);
                }
                else
                {
                    fprintf(temp," %d ",quan);
                }
                
                printf("Enter Cost");
                fflush(stdin);
                double num = 0.0;
                double j = 1.0;
                while((ch = getchar()) != '\n')
                {
                    if (ch == '.')
                    {
                        j = 0.1;
                    }
                    else if ((ch>= '0') && (ch <='9'))
                    {
                        if (j == 1)
                        {
                            num *= 10;
                            num += ch - '0';
                        }
                        else
                        {
                            num += (ch - '0') * j;
                            j /= 10;
                        }
                    }
                }
                if(num == 0.0)
                {
                    fprintf(temp,"%.3lf\n",b.cost);
                }
                else
                {
                    fprintf(temp,"%.3lf\n",num);
                }
                
                //fprintf(temp,"%s %s %d %.3lf\n",b.code,title,quan,price);
                flag = 1;
            }
		}
        if(flag == 0)
        {
            printf("Movie not found \n");
        }
        else
        {
            printf("Record updated \n");
        }
        
		fclose(fp);
        fclose(temp);
        remove("data.dat");
        rename("dataNew.dat","data.dat");
        printf("here");
	}
    system("pause");
    system("cls");
    main();
}

void delete()
{
    int lines = countLines();
    int flag = 0;
	struct book b;
	FILE *fp;
    FILE *temp;

	char ch[12];
	printf("Enter movie code :");
	scanf("%s",ch);
	fp = fopen("data.dat","r");
	if(fp == NULL)
	{
		printf("file does not found !");

	}
	else
	{	
        temp = fopen("dataNew.dat","w");
        fprintf(temp," ");
		while(getc(fp) != EOF && lines > 0)
		{
            lines --;
            fscanf(fp,"%s %s %d %lf",b.code,b.name,&b.quantity,&b.cost);
            if(strcmp(b.code,ch) != 0)
            {
                fprintf(temp,"%s %s %d %.3lf\n",b.code,b.name,b.quantity,b.cost);
            }
            else
            {
                flag = 1;
            }
		}
        if(flag == 0)
        {
            printf("Record not found");
        }
        else
        {
            printf("Record deleted");
        }

        fclose(fp);
        fclose(temp);
        remove("data.dat");
        rename("dataNew.dat","data.dat");
        system("pause");
        system("cls");
        main();
	}
}

void viewAll()
{
    int flag = 0;
	char ch;
	FILE *fp;

	fp = fopen("data.dat","r");
	if(fp == NULL)
	{
		printf("file does not found !");

	}
	else
	{	
		system("cls");
		while( ( ch = fgetc(fp) ) != EOF )
      		printf("%c",ch);flag = 1;
	}
    if(flag == 0)
    {
        printf("No data found \n");
    }
    fclose(fp);
    system("pause");
    system("cls");
    main();
}

int countLines()
{
    FILE *fp;
    char c;
    int count = 0;
    fp = fopen("data.dat","r");
    if(fp == NULL)
        return 0;
    while( ( c = fgetc(fp) ) != EOF )
    { 
        if (c == '\n')
            count = count + 1;
    }
    fclose(fp);
    return count;
}

bool find(char id[12]){
    FILE *fp;
    int lines = countLines();
    fp = fopen("data.dat","r");
    if(fp == NULL)
        return true;
    else
    {
        while(getc(fp) != EOF && lines > 0)
		{
            lines --;
            fscanf(fp,"%s %s %d %lf",b.code,b.name,&b.quantity,&b.cost);
            if(strcmp(b.code,id) == 0)
            {
                fclose(fp);
                return false;
            }
		}   
    }
    fclose(fp);
    return true;
}
