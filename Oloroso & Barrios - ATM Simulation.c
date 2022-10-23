/*Project 1 - ATM SIMULATION in C using linked list
by Andrew R. Oloroso and Armand Angelo C. Barrios*/
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

/*
Mga Problema/Kulang:
1. Nastustuck sa pincheck pag nakalimutan HAHA
2. Fund Transfer (di nababawasan si sender)
3. Yung decrypt (san banda to nakalagay)
4. Encrypt (san din to nakalagay)
5. Account number kailangan unique or kailangan icompare yung acc number sa database (ok na ata to?)
6. di maverify yung pin pag di pa nag-eexit sa first time use si user
7. FEEELING KO MAY MALI SA RETRIEVE/SAVE YATA EWAN NAG-IIBA YUNG LAMAN NG ATM HAHAHA
*/

typedef struct details{
    int accountNumber;
    char accountName[31];
    int balance;
    char pinCode[7];
    int month,day,year;
    char contactNumber[12];
}REC;
typedef struct node{
    REC atm;
    struct node* next;
}LIST;LIST *L;

//global variables
int balanceFD, accNumFD;
char nameFD[31];
char pinCodeFD[7];

void makenull(){
    L=NULL;
}

int insertcard(){
    FILE *fp;
    do{
        system("cls");
        printf("Please insert card...");
        fp=fopen("F:\\Check.txt","w"); //in flashdrive
    }while(fp==NULL);
    fclose(fp);

    fp=fopen("F:\\ATM.txt","r");
    if(fp==NULL){
        printf("\nNOT YET REGISTERED\n"); system("pause");
        system("cls"); return 1;
    }else{
        printf("\nWELCOME\n");system("pause");
        system("cls"); return 2;
    }
    fclose(fp);
}

void addNewATMaccount(REC x){
    LIST *p,*q,*temp;
    q=p=L;
    temp = (LIST*) malloc(sizeof(LIST));
    temp->atm = x;
    while (p!=NULL && strcmp (x.accountName, p->atm.accountName)>=0){
        q=p;
        p=p->next;
    }
    if (p==L){
        L=temp;
    }else{
        q->next = temp;
    }temp->next = p;
}

void retrieve(){
    FILE *fp;
    REC z;
    fp=fopen("D:\\Database.txt","r+");
    if(fp==NULL){
        printf("File not found.\n");
        system("pause");
    }else{
        while(!feof(fp)){
            fscanf(fp," %[^\t]s", z.accountName);
            fscanf(fp,"%d",&z.accountNumber);
            fscanf(fp," %[^\t]s", z.pinCode);
            fscanf(fp,"%d", &z.balance);
            fscanf(fp," %[^\t]s", z.contactNumber);
            fscanf(fp,"%d %d %d\n", &z.month, &z.day, &z.year);
            addNewATMaccount(z);
        }fclose(fp);
    }

    fp=fopen("F:\\ATM.txt","r+");
    if(fp==NULL){
        printf("File not found.\n");
        system("pause");
    }else{
        while(!feof(fp)){
            fscanf(fp," %[^\t]s", z.accountName);
            fscanf(fp,"%d", &z.balance);
            fscanf(fp," %[^\t]s", z.pinCode);
            fscanf(fp,"%d", &z.accountNumber);
        }fclose(fp);
        strcpy(nameFD,z.accountName);
        balanceFD = z.balance;
        strcpy(pinCodeFD,z.pinCode);
        accNumFD = z.accountNumber;
    }
}

void birthDayy(REC *bday){
    printf("\nBirthday (MM/DD/YYYY)\n");
    a:
    printf("\nIf your birth month is January, enter 01");
    printf("\nEnter your birth month: ");scanf("%d",&bday->month);
    if(bday->month<=0 || bday->month>12){
        printf("\nInvalid Month.");system("pause");
        goto a;
    }
    b:
    printf("\nEnter your birth day: ");scanf("%d",&bday->day);
    if(bday->day<=0 || bday->day>31){
        printf("\nInvalid Day.");system("pause");
        goto b;
    }
    c:
    printf("\nEnter your birth year: ");scanf("%d",&bday->year);
    if(bday->year<=1900 || bday->year>2022){
        printf("\nInvalid Year.");system("pause");
        goto c;
    }
}

int checkPin(char *n[7]){
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, pinCodeFD)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nWrong PIN Code\n");system("pause");
        return 1;
    }else{
        printf("\nPIN verified.");system("pause");
        return 2;
    }
}

void pin(REC *x, int a){
    int index=0;
    int y=0,z=0;
    char ch;
    if(a==1){
        b:
        printf("\nPIN Code: ");
        while((ch=getch())!=13 && index<5){
            if (index<0){
                index=0;
            }
            if(ch==8){
                putch('\b'); putch(' ');
                putch('\b'); index--;
                continue;
            }
            if(isdigit(ch)){
                x->pinCode[index++]=ch;
                putchar('*');
            }
        }
        if (index==5){
            x->pinCode[index++]=ch;
            putchar('*');
        }x->pinCode[index]='\0';
        if(strlen(x->pinCode)<4){
            index=0;
            goto b;
        }
    }else if(a==2){
        do{
            c:
            index=0;
            system ("cls");
            printf("\nPIN Code: ");
            while((ch=getch())!=13 && index<5){
                if (index<0){
                    index=0;
                }
                if(ch==8){
                    putch('\b'); putch(' ');
                    putch('\b'); index--;
                    continue;
                }
                if(isdigit(ch)){
                 x->pinCode[index++]=ch;
                 putchar('*');
                }
            }
            if (index==5){
                x->pinCode[index++]=ch;
                putchar('*');
            }x->pinCode[index]='\0';
            if(strlen(x->pinCode)<4)
                goto c;
        }while(checkPin(&x->pinCode)==1);
    }

    /*printf("\n\nPin Code = %s\n",x.pinCode); system("pause");
    while(x->pinCode[y]!='\0'){
        x->pinCode[y]=x->pinCode[y] + 70;
        y++;
    }printf("\n\nEncrypted Pin Code = %s\n",x->pinCode); system("pause");
    while(x->pinCode[z]!='\0'){
        x->pinCode[z]=x->pinCode[z] - 70;
        z++;
    }printf("\nDecrypted Pin Code = %s\n",x->pinCode); system("pause");*/
}

void updateAccount(char n[31]){
    int x,index=2;
    char ch;
    REC bdo;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if(p==NULL){
            printf("Account not found.\n");system("pause");
    }else{
        while(x!=5){
            system("cls");
            printf("Updating Account: \n");
            printf("\nAccount Number: %d",p->atm.accountNumber);
            printf("\nAccount Name: %s",p->atm.accountName);
            printf("\nBirthday: %d / %d / %d",p->atm.month,p->atm.day,p->atm.year);
            printf("\nContact Number: %s",p->atm.contactNumber);
            printf("\nPIN Code: %s",p->atm.pinCode);
            printf("\nUPDATE: \n");
            printf("\n[1] Account Name");
            printf("\n[2] Birthday");
            printf("\n[3] Contact Number");
            printf("\n[4] Change PIN Code");
            printf("\n[5] Back");
            printf("\n\nEnter a Number: ");scanf("%d", &x);
            switch(x){
                case 1: printf("\nInput new Account Name: ");scanf(" %[^\n]s",bdo.accountName);
                        strcpy(p->atm.accountName,bdo.accountName); break;
                case 2: birthDayy(&bdo);
                        p->atm.month=bdo.month; p->atm.day=bdo.day; p->atm.year=bdo.year;
                        break;
                case 3: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                        printf("\nInput new Contact Number: 09");
                        b:
                        while((ch=getch())!=13 && index<10){
                            if (index<0){
                                index=0;
                            }
                            if(ch==8){
                                putch('\b'); putch(' ');
                                putch('\b'); index--;
                                continue;
                            }
                            if(isdigit(ch)){
                                bdo.contactNumber[index++]=ch;
                                putch('*');
                            }
                        }
                        if (index==10){
                            bdo.contactNumber[index++]=ch;
                            putchar('*');
                        }bdo.contactNumber[index]='\0';
                        if(strlen(bdo.contactNumber)<11)
                            goto b;
                        strcpy(p->atm.contactNumber,bdo.contactNumber);
                        break;
                case 4: printf("\nPlease Enter CURRENT Pin Code\n");system("pause");pin(&bdo,2);//checkPin(); kailangan i-compare to every lagay ng user
                        printf("\nPlease Enter NEW Pin Code");pin(&bdo,1);
                        strcpy(p->atm.pinCode,bdo.pinCode); break;
                case 5: printf("\n%s's account is successfully updated.", p->atm.accountName);system("pause");break;
                default: printf("\nSelect 1-6 only\n");system("pause");
            }
        }
    }
}

void deleteAccount(char n[31]){
    int userChoice;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && strcmp (n, p->atm.pinCode)!=0){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("Account not found.\n");system("pause");
    }else{
        printf("\n\nAre you sure you want to delete your account?\n");
        printf("[1]YES\n");
        printf("[2]NO\n");
        scanf("%d", &userChoice);
        if(userChoice==1){
            if (p==L){
                L=p->next;
            }else{
                q->next=p->next;
            }
            if(remove("F:\\ATM.txt")==0){
                free(p);printf("%s's account is successfully deleted.\n",n);system("pause");
            }else{
                printf("\nDeletion not successfull.");system("pause");
            }
        }else{
            AccountMenu();
        }
    }
}

void save(){
    FILE *fp;
    LIST *p; p=L;
    fp = fopen("D:\\Database.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        while(p!=NULL){
        fprintf(fp,"%s\t%d\t%s\t%d\t%s\t%d %d %d\n",
                p->atm.accountName,p->atm.accountNumber,p->atm.pinCode,p->atm.balance,p->atm.contactNumber,p->atm.month,p->atm.day,p->atm.year);
        p=p->next;
        }fclose(fp);
    }
}
void saveFD(){
    FILE *fp;
    LIST *p; p=L;
    fp = fopen("F:\\ATM.txt","w+");
    if (fp==NULL){
        printf("Error 404. File not found.\n");
        system("pause");
    }
    else {
        fprintf(fp,"%s\t%d\t%s\t%d\n",p->atm.accountName,p->atm.balance,p->atm.pinCode,p->atm.accountNumber);
        fclose(fp);
    }
}

int menu(){
    int UserNum;
    system("cls");
    printf("Choose Module: \n");
    printf("[1] ACCOUNT SETTINGS\n");
    printf("[2] TRANSACTION MODULE\n");
    printf("[3] EXIT\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int AccountMenu(){
    system("cls");
    REC other;
    int UserNum;
    printf("Choose account option: \n");
    printf("[1] Update Account\n");
    printf("[2] Delete Account\n");
    printf("[3] Back\n");
    printf("\nEnter your choice 1-3: ");
    scanf("%d", &UserNum);
    return UserNum;
}
int transactionMenu(){
    int UserNum;
    while(1){
    system("cls");
    printf("Choose Transaction: \n");
    printf("[1] Balance Inquiry\n");
    printf("[2] Withdraw\n");
    printf("[3] Deposit\n");
    printf("[4] Fund Transfer\n");
    printf("[5] Other Transactions\n");
    printf("[6] Back\n");
    printf("\nEnter your choice 1-6: ");
    scanf("%d", &UserNum);
    return UserNum;
    }
}

void display(){
    LIST *p;
    int x = 1;
    p=L;
    printf("ALL LIST: \n");
    while (p!=NULL){
        printf("%d.) %d\t%s\t%d\t%s\t%d %d %d\t%s\n",x++,p->atm.accountNumber,p->atm.accountName,p->atm.balance,p->atm.pinCode,p->atm.month,p->atm.day,p->atm.year,p->atm.contactNumber);
        p=p->next;
    }
    system("pause");
}

void transfer(int x, REC *bdo){
    FILE *fp;
    int transfer;
    LIST *p, *q;
    p=q=L;
    while(p!=NULL && x!=p->atm.accountNumber){
        q=p;
        p=p->next;
    }
    if (p==NULL){
        printf("\nAccount not found.\n");
    }else{
        printf("\nAccount found!");
        do{
            printf("\nInput amount to transfer: Php ");
            scanf("%d",&transfer);
            if(transfer>bdo->balance)
                    printf("\nInsufficient balance.");
            else if(transfer<=0)
                    printf("\nMinimum transfer amount is Php 1.");
        }while(transfer>bdo->balance || transfer<=0);
        bdo->balance-=transfer;
        p->atm.balance+=transfer;
        printf("\nAmount was successfully transferred to %s.\n",p->atm.accountName);
        printf("Your new balance: Php %d", bdo->balance);
    }
}

int uniqueAcc(int x){
LIST *p, *q;
p=q=L;
while(p!=NULL && x!=p->atm.accountNumber){
        q=p;
        p=p->next;
}
if(p==NULL)
    return 2;
else
    return 1;
}

int main(){
    int x,withdraw,deposit,accTransfer,index=2;
    char ch;
    REC bdo;
    srand(time(NULL));
    makenull();
    retrieve();
    switch(insertcard()){
        case 1: bdo.contactNumber[0]='0'; bdo.contactNumber[1]='9';
                do{
                        bdo.accountNumber = rand() % 999999 + 10000;
                }while(uniqueAcc(bdo.accountNumber)==1);
                system("cls");
                printf("REGISTRATION MODULE\n");
                printf("Please fill out the following informations: \n\n");
                printf("\nAccount Number: %d",bdo.accountNumber);
                printf("\nAccount Name: ");scanf(" %[^\n]s",bdo.accountName);
                birthDayy(&bdo);system("cls");
                printf("REGISTRATION MODULE\n");
                printf("Please fill out the following informations: \n\n");
                printf("\nAccount Number: %d",bdo.accountNumber);
                printf("\nAccount Name: %s",bdo.accountName);
                printf("\nBirthdate (MM/DD/YYYY): %d / %d / %d",bdo.month,bdo.day,bdo.year);
                printf("\nContact Number: 09");
                a:
                while((ch=getch())!=13 && index<10){
                    if (index<0){
                        index=0;
                    }
                    if(ch==8){
                        putch('\b'); putch(' ');
                        putch('\b'); index--;
                        continue;
                    }
                    if(isdigit(ch)){
                     bdo.contactNumber[index++]=ch;
                     putch('*');
                    }
                }
                if (index==10){
                    bdo.contactNumber[index++]=ch;
                    putchar('*');
                }bdo.contactNumber[index]='\0';
                if(strlen(bdo.contactNumber)!=11)
                    goto a;
                printf("\nContact Number: %s",bdo.contactNumber);

                do{
                    printf("\nInitial Deposit (Min. 5,000): Php ");scanf("%d", &bdo.balance);
                    if(bdo.balance<5000)
                        printf("Minimum deposit is Php 5000.\n");
                }while(bdo.balance<5000);
                pin(&bdo,1); printf("\nPIN Code: %s\n\n", bdo.pinCode);system("pause");
                addNewATMaccount(bdo);
                printf("\nREGISTRATION SUCCESSFUL\n"); system("pause");
                break;
        case 2: pin(&bdo,2);
                display();
                break;
    }
    x:
    while(1){
        system ("cls");
        switch(menu()){
            case 1: system("cls"); printf("ACCOUNT MODULE\n\n");
                    b:
                    x = AccountMenu();
                    if(x==1){
                        system("cls");printf("Input Account Pin Code: \n");system("pause");pin(&bdo,2);
                        updateAccount(bdo.pinCode); break;
                    }else if(x==2){
                        system("cls");printf("Input Account Pin Code: \n");system("pause");pin(&bdo,2);
                        deleteAccount(bdo.pinCode); break;
                    }else if(x==3){
                        break;
                    }else{
                        printf("\nSelect 1-3 only.");system("pause");goto b;
                    }break;
            case 2: system("cls"); printf("TRANSACTION MODULE\n\n");
                    while(1){
                        switch(transactionMenu()){
                            case 1:printf("BALANCE INQUIRY\n");
                                   printf("Current Balance: Php %d", bdo.balance);system("pause");break;
                            case 2:printf("WITHDRAW MONEY\n");
                                   if(bdo.balance!=0){
                                        do{
                                            printf("Please input amount to withdraw: Php ");scanf("%d",&withdraw);
                                            if(withdraw>(bdo.balance))
                                                printf("\nInsufficient Balance.\n");
                                            else if(bdo.balance<0)
                                                printf("Invalid amount.\n");
                                            else if(bdo.balance==0)
                                                printf("Insufficient Balance.\n");
                                        }while(withdraw>(bdo.balance) || bdo.balance<0 || bdo.balance==0);
                                        bdo.balance-=withdraw;
                                        printf("\n\nWithdraw successful.");
                                        printf("\nYour new balance: Php %d\n", bdo.balance);system("pause");break;
                                   }else{
                                        printf("\nYou have no balance.\n");system("pause");break;
                                   }
                            case 3:printf("DEPOSIT MONEY\n");
                                   do{
                                   printf("Please input amount to deposit: Php ");scanf("%d",&deposit);
                                   if(deposit<=0)
                                        printf("\nMinimum deposit amount is Php 1.\n");
                                   }while(deposit<=0);
                                   bdo.balance+=deposit;
                                   printf("\n\nDeposit successful.");
                                   printf("\nYour new balance: Php %d\n",bdo.balance);system("pause");break;
                            case 4:printf("FUND TRANSFER\n");
                                   do{
                                        printf("Enter the Account No. you want to transfer: ");
                                        scanf("%d",&accTransfer);
                                        if(accTransfer<10000 || accTransfer>99999)
                                            printf("\nInvalid Account Number.");
                                   }while(accTransfer<10000 || accTransfer>99999);
                                   transfer(accTransfer,&bdo);
                                   system("pause");break;
                            case 5:printf("PAY UTILITY BILLS\n");
                                   int Meralco,Maynilad;
                                   Meralco=rand()%1000 + 1;
                                   Maynilad=rand()%500 + 1;
                                   printf("Meralco Bill: Php %d\n", Meralco);
                                   printf("Maynilad Bill: Php %d\n", Maynilad);
                                   printf("\n\n");
                                   printf("Total Utility Bill: Php %d\n", Meralco+Maynilad);
                                   while(1){
                                        int userNum;
                                        printf("[1]Pay Utility Bills.\n");
                                        printf("[2]Back\n");
                                        scanf("%d", &userNum);
                                        switch(userNum){
                                            case 1: do{
                                                        if(bdo.balance>=(Maynilad+Meralco)){
                                                            bdo.balance-=(Maynilad+Meralco);
                                                            printf("\nPayment successful.\n");break;
                                                        }else
                                                            printf("\nInsufficient Balance.\n");break;
                                                    }while(1);
                                                    system("pause");break;
                                            case 2:transactionMenu();break;
                                            default:printf("Invalid input.\n");system("pause\n");
                                        }
                                    break;
                                   }
                                   break;
                            case 6:goto x;break;
                            default:printf("Invalid input.\n");transactionMenu();
                        }
                    }break;
            case 3: save();saveFD();exit(0);
            default: printf("Invalid input. Try again."); system("pause\n");
        }
        break;
    }
}
