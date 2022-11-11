#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h> 
#include <netinet/in.h>

struct date{
    int day,month,year;

    };
struct {
    char name[60];
    char uid[60];
    char pass[60];
    int acc_no;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[20];
    float amt;
    struct date dob;
    struct date deposit;
    // struct date withdraw;
    }add,add2,upd,check,rem,transaction,admins;
void update(int sd)
{
    while(1)
    {
        system("clear");
        printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
        printf("\n\n\n\t\t\t..............CHANGE PASSWORD..................");
        
        char op[20],np[20];
        printf("\n\n\n\t\t\t\t\t\tEnter old password : ");
        scanf("%s",op);
        getchar();
        write(sd,&op,sizeof(op));
        char p;
        read(sd,&p,sizeof(p));
        
        if(p=='p')
        {
            printf("\n\n\t\t\t\t\t\tEnter new password : ");
            scanf("%s",np);
            
            write(sd,&np,sizeof(np));
            
            read(sd,&p,sizeof(p));
            
            printf("\n\n\npassword changed successfully");
            printf("\n\n Press ENTER");
            getchar();
            getchar();
            return;
        }
        else if (p=='f')
        {
            printf("\n\n\n\t\t\t\t\t\t wrong password ...... TRY AGAIN\n");
            sleep(2);
        }
        
    }
    
    
}
void deposit(int sd)
{
    system("clear");
    printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
    printf("\n\n\n\t\t\t..............Deposit..................");
        
    printf("\n\n\n\t\t\t\tEnter the amount you want to deposit : ");
    scanf("%f",&transaction.amt);
    getchar();
    
    write(sd,&transaction.amt,sizeof(transaction.amt));
    
    char p;
    read(sd,&p,sizeof(p));
    if(p=='p')
    {
        
        printf("\n\n\t\t\t\t Deposit successfully....");
        printf("\n\n\t\t\t\t Press ENTER");
        getchar();
        return;
    }
    else if(p=='f'){
        printf("\n\n\t\t\t\t may be your account deactive connect to bank....");
        printf("\n\n\t\t\t\t Press ENTER");
        getchar();
        return;
    }
}
void withdraw(int sd)
{
    system("clear");
    printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
    printf("\n\n\n\t\t\t..............Withdraw..................");
        
    printf("\n\n\n\t\t\t\tEnter the amount you want to withdraw : ");
    scanf("%f",&transaction.amt);
    getchar();
    
    write(sd,&transaction.amt,sizeof(transaction.amt));
    
    
    char p;
    read(sd,&p,sizeof(p));
    if(p=='p')
    {
        printf("\n\n\t\t\t\t Withdraw successfully....");
        printf("\n\n\t\t\t\t Press ENTER");
        getchar();
        return;
    }
    else if(p=='f'){
        printf("\n\n\t\t\t\t may be your account deactive connect to bank....");
        printf("\n\n\t\t\t\t Press ENTER");
        getchar();
        return;
    }
    else if(p=='n'){
        printf("\n\n\t\t\t\t Withdraw not possible....Balance is less then you want to withdraw....");
        printf("\n\n\t\t\t\t Press ENTER");
        getchar();
        return;
    }
}

void userMainMenu(int sd)
{
    
    
    while(1) 
    {
        char choice;
        system("clear");
        printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
        printf("\n\n\n\t\t\t..............WELCOME TO THE COUSTMERS 'S MAIN MENU..................");
        printf("\n\n\t\t\t1. Deposit\n\t\t\t2. Withdraw\n\t\t\t3. Balance Enquiry\n\t\t\t4. Password Change\n\t\t\t5. View details\n\t\t\t6. Exit\n\n\n\n\n\t\t\tEnter your choice:");
        scanf("%c",&choice);
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            deposit(sd);
        }
        else if(choice=='2')
        {
            withdraw(sd);
        }
        else if(choice=='3')
        {
            system("clear");
            read(sd,&add,sizeof(add)); //receive full data of user
            printf("\n\n\n\t\t\t\t\t\t Your account balance :-> Rs. %.2f\n\n\n",add.amt);
            sleep(2);
            
            printf("\n\n\n\t\t\t\t\t\tPress ENTER");
            getchar();
            
        }
        else if(choice=='4')
        {
            update(sd);
        }
        else if(choice=='5')
        {
            system("clear");
            read(sd,&add,sizeof(add)); //receive full data of user
            printf("\n\n\t\t\tAccount Number: %d",add.acc_no);
            printf("\n\t\t\tUSERID: %s",add.uid);
            printf("\n\t\t\tName: %s",add.name);
            printf("\n\t\t\tDate of birth(dd/mm/yyyy): %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            printf("\n\t\t\tCeated on (dd/mm/yyyy): %d/%d/%d",add.deposit.day,add.deposit.month,add.deposit.year);
            // printf("\n\t\t\tAge: %d",add.age);
            printf("\n\t\t\tAddress: %s",add.address);
            printf("\n\t\t\tCitizenship number (ADHARCARD NUMBER): %s",add.citizenship);
            printf("\n\t\t\tPhone number: %.0lf",add.phone);
            printf("\n\t\t\tAmount: Rs. %.2f",add.amt);
            printf("\n\t\t\tAccount Type: %s\n\n\n",add.acc_type);
            sleep(2);
            
            printf("\n\n\n\t\t\t\t\t\tPress ENTER");
            getchar();
            
        }
        else if(choice=='6')
        {
                close(sd);
                system("clear");
                printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
                exit(0);
        }
        else 
        {
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
        
    }
}
    
    
void new_acc(int sd)
{
    
    char choice;
    
    while(1) 
    {
        system("clear");
        printf("\t\t\t ==================== CREATE ACCOUNT ====================\n\n\n");
    
        printf("\nEnter your choice for Account Type: \n\t1. Saving\n\t2. Current\n\t3. Joint account\n\t4. Exit\n\n\tEnter your choice:");
        scanf("%c",&choice);
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1' || choice=='2')
        {
            system("clear");
            printf("\t\t\t ==================== CREATE ACCOUNT ====================\n\n\n");
            printf("\t\t\t ....Enter Your details....\n\n\n");
            printf("\nEnter the password for your account: ");
            scanf("%s",add.pass);
            printf("\nEnter the name: ");
            scanf("%s",add.name);
            printf("\nEnter the date of birth(dd/mm/yyyy): ");
            scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year);
            printf("\nEnter today's date(dd/mm/yyyy): ");
            scanf("%d/%d/%d",&add.deposit.day,&add.deposit.month,&add.deposit.year);
            // printf("\nEnter the age: ");
            // scanf("%d",&add.age);
            printf("\nEnter the address: ");
            scanf("%s",add.address);
            printf("\nEnter the citizenship number (ADHARCARD NUMBER): ");
            scanf("%s",add.citizenship);
            printf("\nEnter the phone number: ");
            scanf("%lf",&add.phone);
            printf("\nEnter the amount to deposit: Rs.");
            scanf("%f",&add.amt);
            if(choice=='1')
            {
                strcpy(add.acc_type,"Saving");
            }else{
                strcpy(add.acc_type,"Current");
            }
            
            write(sd,&add,sizeof(add));
            
            read(sd,&add,sizeof(add));
            
            system("clear");
            printf("\n\t\t\t\x1b[42m Congratulations.... Account created successfully!....\x1b[30;47m");
        
            // showAccountDetail(add,sd);
            printf("\n\n\t\t\tAccount Number: %d",add.acc_no);
            printf("\n\t\t\tUSERID: %s",add.uid);
            printf("\n\t\t\tName: %s",add.name);
            printf("\n\t\t\tDate of birth(dd/mm/yyyy): %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            printf("\n\t\t\tCeated on (dd/mm/yyyy): %d/%d/%d",add.deposit.day,add.deposit.month,add.deposit.year);
            // printf("\n\t\t\tAge: %d",add.age);
            printf("\n\t\t\tAddress: %s",add.address);
            printf("\n\t\t\tCitizenship number (ADHARCARD NUMBER): %s",add.citizenship);
            printf("\n\t\t\tPhone number: %.0lf",add.phone);
            printf("\n\t\t\tAmount: Rs. %.2f",add.amt);
            printf("\n\t\t\tAccount Type: %s\n\n\n",add.acc_type);
            printf("\n\n\n\nPress ENTER");
            getchar();
            getchar();
            return;
        }
        else if(choice=='3')
        {
            printf("\nEnter the password for your account(remember this): ");
            scanf("%s",add.pass);
            strcpy(add2.pass,add.pass);
            // sprintf(add2.pass,"%s",add.pass);
            printf("\nEnter the name of the first person: ");
            scanf("%s",add.name);
            printf("\nEnter the name of the second person: ");
            scanf("%s",add2.name);
            printf("\nEnter the date of birth(dd/mm/yyyy) of the first person: ");
            scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year);
            printf("\nEnter the date of birth(dd/mm/yyyy) of the second person: ");
            scanf("%d/%d/%d",&add2.dob.day,&add2.dob.month,&add2.dob.year);
            printf("\nEnter today's date(dd/mm/yyyy): ");
            scanf("%d/%d/%d",&add.deposit.day,&add.deposit.month,&add.deposit.year);
            add2.deposit.day=add.deposit.day;
            add2.deposit.month=add.deposit.month;
            add2.deposit.year=add.deposit.year;
            // printf("\nEnter the age of the first person: ");
            // scanf("%d",&add.age);
            // printf("\nEnter the age of the second person: ");
            // scanf("%d",&add2.age);
            printf("\nEnter the address of the first person: ");
            scanf("%s",add.address);
            printf("\nEnter the address of the second person: ");
            scanf("%s",add2.address);
            printf("\nEnter the citizenship number (ADHARCARD NUMBER) of the first person: ");
            scanf("%s",add.citizenship);
            printf("\nEnter the citizenship number (ADHARCARD NUMBER) of the second person: ");
            scanf("%s",add2.citizenship);
            printf("\nEnter the phone number of the first person: ");
            scanf("%lf",&add.phone);
            printf("\nEnter the phone number of the second person: ");
            scanf("%lf",&add2.phone);
            printf("\nEnter the amount to deposit: Rs.");
            scanf("%f",&add.amt);
            add2.amt=add.amt;
            sprintf(add.acc_type, "%s", "Joint Account");
            strcpy(add2.acc_type,add.acc_type);
            write(sd,&add,sizeof(add));
            write(sd,&add2,sizeof(add2));
            
            read(sd,&add,sizeof(add));
            read(sd,&add2,sizeof(add2));
            
            system("clear");
            printf("\n\t\t\t\x1b[42m Congratulations.... Account created successfully!....\x1b[30;47m");
        
            // showAccountDetail(add,sd);
            
            printf("\n\n\t\t\tAccount Number: %d",add.acc_no);
            
            printf("\n\n\t\t\t........Details of first person........\n");
            printf("\n\t\t\tUSERID: %s",add.uid);
            printf("\n\t\t\tName: %s",add.name);
            printf("\n\t\t\tDate of birth(dd/mm/yyyy): %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            printf("\n\t\t\tCeated on (dd/mm/yyyy): %d/%d/%d",add.deposit.day,add.deposit.month,add.deposit.year);
            // printf("\n\t\t\tAge: %d",add.age);
            printf("\n\t\t\tAddress: %s",add.address);
            printf("\n\t\t\tCitizenship number (ADHARCARD NUMBER): %s",add.citizenship);
            printf("\n\t\t\tPhone number: %.0lf",add.phone);
            printf("\n\t\t\tAmount: Rs. %.2f",add.amt);
            printf("\n\t\t\tAccount Type: %s\n\n\n",add.acc_type);
            
            printf("\n\n\t\t\t........Details of Second person........\n");
            printf("\n\t\t\tUSERID: %s",add2.uid);
            printf("\n\t\t\tName: %s",add2.name);
            printf("\n\t\t\tDate of birth(dd/mm/yyyy): %d/%d/%d",add2.dob.day,add2.dob.month,add2.dob.year);
            printf("\n\t\t\tCeated on (dd/mm/yyyy): %d/%d/%d",add2.deposit.day,add2.deposit.month,add2.deposit.year);
            // printf("\n\t\t\tAge: %d",add2.age);
            printf("\n\t\t\tAddress: %s",add2.address);
            printf("\n\t\t\tCitizenship number (ADHARCARD NUMBER): %s",add2.citizenship);
            printf("\n\t\t\tPhone number: %.0lf",add2.phone);
            printf("\n\t\t\tAmount: Rs. %.2f",add2.amt);
            printf("\n\t\t\tAccount Type: %s\n\n\n",add2.acc_type);
            printf("\n\n\n\nPress ENTER");
            getchar();
            getchar();
            return;
        }
        else if(choice=='4')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            exit(0);
        }
        else 
        {
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
    }
}
void cclogin(int sd)
{  
     
    while(1)
    {
        char choice;
        system("clear");
        printf("\t\t\t ==================== LOGIN IN THE USER ACCOUNT ====================\n\n\n");
        printf("\n\n\t\t\t\t\t1. login\n\t\t\t\t\t2. exit \n\n\t\t\t\t\tEnter your choice : ");
        scanf("%c",&choice);
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            printf("\n\n\t\t\t\t\t Enter your USER ID : ");
            scanf("%s",add.uid);
            getchar();
            printf("\n\n\t\t\t\t\t Enter your PASSWORD : ");
            scanf("%s",add.pass);
            getchar();
            
            write(sd,&add,sizeof(add));  //send uid and pass for checking
            
            char p;
            read(sd,&p,sizeof(p)); //read pss or not
            
            if(p=='f')
            {
                //fail
                printf("\n \x1b[37;41m Sorry,Userid or Password does not match with any record \x1b[30;47m\n\n TRY AGAIN....\n");
                sleep(2);
            }
            else if(p=='p')
            {
                //pass
                printf("\n\nPassword Match!.......\n");
                sleep(1);
                userMainMenu(sd);
                return;
            }
        }
        else if(choice=='2')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            exit(0);
        }
        else{
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
        
    }
        
        
}

void clogin(int sd)
{
    char choice;
    
    while(1) 
    {
        system("clear");
        printf("\n\n\t\t\t*********** CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM *********** ");
        printf("\n\n\n\t\t\t.............. WELCOME .. WELCOME .. WELCOME ..................");
        printf("\n\n\t\t1. Login \n\t\t2. Creat new account\n\t\t3. Exit\n\n\n\n\n\t\tEnter your choice:");
        scanf("%c",&choice); //multiple entry 
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            cclogin(sd);
            return;
        }
        else if(choice=='2')
        {
            new_acc(sd);
            cclogin(sd);
            return;
        }
        else if(choice=='3')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            exit(0);
        }
        else 
        {
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
    }
}

void search_acc(int sd)
{
    char ui[20];
    
    while(1) 
    {
        system("clear");
        printf("\n\n\t\t\t*********** CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM *********** ");
        printf("\n\n\n\t\t\t.............. WELCOME .. ADMIN .. WELCOME ..................");
        printf("\n\n\t\tEnter the USERID to see the details : ");
        scanf("%s",ui);
        getchar();
        write(sd,&ui,sizeof(ui));
        char pass;
        read(sd,&pass,sizeof(pass));
        
        if(pass=='p')
        {
            read(sd,&add,sizeof(add));
            
            printf("\n\n\n\t\t\t..........................ACCOUNT DETAILS............................");

            printf("\n\n\t\t\tAccount Number: %d",add.acc_no);
            printf("\n\n\t\t\tUSERID: %s",add.uid);
            printf("\n\t\t\tName: %s",add.name);
            printf("\n\t\t\tDate of birth(dd/mm/yyyy): %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            printf("\n\t\t\tCeated on (dd/mm/yyyy): %d/%d/%d",add.deposit.day,add.deposit.month,add.deposit.year);
            // printf("\n\t\t\tAge: %d",add.age);
            printf("\n\t\t\tAddress: %s",add.address);
            printf("\n\t\t\tCitizenship number (ADHARCARD NUMBER): %s",add.citizenship);
            printf("\n\t\t\tPhone number: %.0lf",add.phone);
            printf("\n\t\t\tAmount: Rs. %.2f",add.amt);
            printf("\n\t\t\tAccount Type: %s\n\n\n",add.acc_type);
            
            printf("\n\n\n\t\t\t\tPress ENTER");
            getchar();
            
            return;
        }
        else if(pass=='f')
        {
            printf("\n\n\n\n\t\t\t\tUSERID not match with any record");
            printf("\n\n \t\t\t\tPress ENTER");
            getchar();
            return;
        }
        // else 
        // {
        //     close(sd);
        //     system("clear");
        //     printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
        //     exit(0);
        // }
        // else 
        // {
        //     printf("INVALID INPUT ... \n TRY AGAIN\n");
        //     sleep(1);
        // }
    }
}
void checkAdminLogin(int sd)
{
    
    while(1) 
    {
        char choice;
        system("clear");
        printf("\n\n\t\t\t*********** CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM *********** ");
        printf("\n\n\n\t\t\t.............. WELCOME .. ADMIN .. WELCOME ..................");
        printf("\n\n\t\t1. Login \n\t\t2. Exit\n\n\n\n\n\t\tEnter your choice:");
        scanf("%c",&choice);
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            printf("\n\n\n\t\t\t\tEnter password : ");
            scanf("%s",admins.pass);
            getchar();
            write(sd,&admins.pass,sizeof(admins.pass));
            
            char p;
            read(sd,&p,sizeof(p)); //read pss or not
            
            if(p=='f')
            {
                //fail
                printf("\n \x1b[37;41m Sorry,Userid or Password does not match with any record \x1b[30;47m\n\n TRY AGAIN....\n");
                sleep(2);
            }
            else if(p=='p')
            {
                //pass
                
                printf("\n\nPassword Match!.......\n");
                sleep(1);
                return;
            }
        }
        else if(choice=='2')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            exit(0);
        }
        else 
        {
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
    }
        
}
void modify_acc(int sd)
{
    while(1)
    {
        char ui[20];
        system("clear");
        printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
        printf("\n\n\n\t\t\t.............. WELCOME .. ADMIN .. WELCOME ..................");
        printf("\n\n\n\t\t\t..............Modify the User account..................");
        printf("\n\n\t\tEnter the USERID for which you want to modify the details : ");
        scanf("%s",ui);
        getchar();
        write(sd,&ui,sizeof(ui));
        char pass;
        read(sd,&pass,sizeof(pass));
        
        if(pass=='p')
        {
            read(sd,&add,sizeof(add));
            
            printf("\n\n\n\t\t\t..........................ACCOUNT DETAILS............................");

            printf("\n\n\t\t\tAccount Number: %d",add.acc_no);
            printf("\n\t\t\tUSERID: %s",add.uid);
            printf("\n\t\t\tAccount Type: %s",add.acc_type);
            printf("\n\t\t\tAmount: Rs. %.2f",add.amt);
            printf("\n\t\t\tCreated on (dd/mm/yyyy): %d/%d/%d",add.deposit.day,add.deposit.month,add.deposit.year);
            
            printf("\n\n\n\t\t\t\t... What you want to modify ...");
            
            printf("\n\n\t\t\t1. Name: %s",add.name);
            printf("\n\t\t\t2. Date of birth(dd/mm/yyyy): %d/%d/%d",add.dob.day,add.dob.month,add.dob.year);
            // printf("\n\t\t\t3. Age: %d",add.age);
            printf("\n\t\t\t3. Address: %s",add.address);
            printf("\n\t\t\t4. Citizenship number (ADHARCARD NUMBER): %s",add.citizenship);
            printf("\n\t\t\t5. Phone number: %.0lf",add.phone);
            printf("\n\t\t\t6. Exit");
            printf("\n\n\n\t\t\t\t Enter your choice : ");
            char c;
            scanf("%c",&c);
            
            write(sd,&c,sizeof(c));
            
            if(c=='1')
            {
                char new[20];
                printf("\n\n\n\t\t\t\t\t\tEnter new name : ");
                scanf("%s",new);
                
                write(sd,&new,sizeof(new));
                char p;
                read(sd,&p,sizeof(p));
                
                if(p=='p')
                {
                    printf("\n\n\nName changed successfully");
                    printf("\n\n Press ENTER");
                    getchar();
                    getchar();
                    return;
                }
            }
            else if(c=='2')
            {
            
                printf("\n\n\n\t\t\t\t\t\tEnter new date of birth (dd/mm/yy) : ");
                scanf("%d/%d/%d",&add.dob.day,&add.dob.month,&add.dob.year);
                
                write(sd,&add,sizeof(add));
                char p;
                read(sd,&p,sizeof(p));
                
                if(p=='p')
                {
                    printf("\n\n\nDate of birth changed successfully");
                    printf("\n\n Press ENTER");
                    getchar();
                    getchar();
                    return;
                }
            }
            else if(c=='3')
            {
                char new[20];
                printf("\n\n\n\t\t\t\t\t\tEnter new address : ");
                scanf("%s",new);
                
                write(sd,&new,sizeof(new));
                char p;
                read(sd,&p,sizeof(p));
                
                if(p=='p')
                {
                    printf("\n\n\nAddress changed successfully");
                    printf("\n\n Press ENTER");
                    getchar();
                    getchar();
                    return;
                }
            }
            else if(c=='4')
            {
                char new[20];
                printf("\n\n\n\t\t\t\t\t\tEnter new Citizenship number (ADHARCARD NUMBER): ");
                scanf("%s",new);
                
                write(sd,&new,sizeof(new));
                char p;
                read(sd,&p,sizeof(p));
                
                if(p=='p')
                {
                    printf("\n\n\nCitizenship number (ADHARCARD NUMBER) changed successfully");
                    printf("\n\n Press ENTER");
                    getchar();
                    getchar();
                    return;
                }
            }
            else if( c=='5')
            {
                double new;
                printf("\n\n\n\t\t\t\t\t\tEnter new Phone number : ");
                scanf("%lf",&new);
                
                write(sd,&new,sizeof(new));
                char p;
                read(sd,&p,sizeof(p));
                
                if(p=='p')
                {
                    printf("\n\n\nPhone number changed successfully");
                    printf("\n\n Press ENTER");
                    getchar();
                    getchar();
                    return;
                }
            }
           else if(c=='6')
           {
                close(sd);
                system("clear");
                printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
                exit(0);
           }
         
        }
        else if(pass=='f')
        {
            printf("\n\n\n\nUSERID not match with any record");
            printf("\n\n Press ENTER");
            getchar();
            getchar();
            return;
        }
        
        
        
        
        
    }
}
void delete_acc(int sd)
{
    char ui[20];
    system("clear");
    printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
    printf("\n\n\n\t\t\t.............. WELCOME .. ADMIN .. WELCOME ..................");
    printf("\n\n\n\t\t\t..............Modify the User account..................");
    printf("\n\n\t\tEnter the USERID for which you want to modify the details : ");
    scanf("%s",ui);
    getchar();
    write(sd,&ui,sizeof(ui));
    char pass;
    read(sd,&pass,sizeof(pass));
        
    if(pass=='p')
    {
        char c;
        read(sd,&c,sizeof(c));
        
        if(c=='d')
        {
            printf("\n\n\nAcoount deleted successfully");
            printf("\n\nPress ENTER\n");
            getchar();
            return;
        }
    }
    else if(pass=='f')
    {
        printf("\n\n\nUSERID not found");
        printf("\n\n Press ENTER");
        getchar();
        getchar();
        return;
    }
    
        
}
void alogin(int sd)
{
    checkAdminLogin(sd);
    while(1) 
    {
        system("clear");
        char choice;
        printf("\n\n\t\t\t*********** CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM *********** ");
        printf("\n\n\n\t\t\t.............. WELCOME .. ADMIN .. WELCOME ..................");
        printf("\n\n\t\t1. Add account \n\t\t2. Delete Account\n\t\t3. Modify Account\n\t\t4. Search for specific account details\n\t\t5. Exit\n\n\n\n\n\t\tEnter your choice:");
        scanf("%c",&choice);
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            new_acc(sd);
        }
        else if(choice=='2')
        {
            delete_acc(sd);
        }
        else if(choice=='3')
        {
            modify_acc(sd);
        }
        else if(choice=='4')
        {
            search_acc(sd);
            
        }
        else if(choice=='5')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            exit(0);
        }
        else 
        {
            printf("\n\n\nINVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
    }
}

int main() {
	
	struct sockaddr_in serv; 
	int sd;
	char buf[80];
	sd = socket(AF_INET, SOCK_STREAM, 0);
	serv.sin_family = AF_INET; 
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(2812); 
	connect(sd, (void*) (&serv), sizeof(serv));
	
	printf("\n\x1b[30;47m \n");
    // system("clear");
    char choice;
    
    
    while(1) 
    {
        system("clear");
        printf("\n\n\t\t\t###### CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM #######");
        printf("\n\n\n\t\t\t..............WELCOME TO THE MAIN MENU..................");
        printf("\n\n\t\t1. Customer\n\t\t2. Admin\n\t\t3. Exit\n\n\n\n\n\t\t Enter your choice:");
        scanf("%c",&choice);
        getchar();
        write(sd,&choice,sizeof(choice));
        if(choice=='1')
        {
            clogin(sd);
            return 0;
        }
        else if(choice=='2')
        {
            alogin(sd);
            return 0;
        }
        else if(choice=='3')
        {
            close(sd);
            system("clear");
            printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
            return 0;
        }
        else 
        {
            printf("INVALID INPUT ... \n TRY AGAIN\n");
            sleep(1);
        }
        
    }
    close(sd);
    system("clear");
    printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
    
	return 0;
}