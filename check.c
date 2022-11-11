#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/time.h> 
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<math.h>
#include <time.h>

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
    }add,add2,upd,check,rem,transaction;
struct{
    char pt[100];
    char uid[60];
    char type[60];
    int acc_no;
    float amt;
}tran;
int main(){
    
    printf("\n\x1b[30;47m \n");
    system("clear");
    int fd=open("account_details",O_RDWR);
    lseek(fd,0,SEEK_SET);
    struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
    printf("\n\t\t\t\x1b[37;41m========================== Account details ==========================\x1b[30;47m\n\n");
    while(1)
    {   
        int p=read(fd,&add,sizeof(add));
        if(p==0)
        {
            break;
        }
        printf("\n\n\n\t\t\t......................................................");

            printf("\n\t\t\tAccount Number: %d",add.acc_no);
            printf("\n\t\t\tpassword: %s",add.pass);
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
            
    }
    lock.l_type = F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
    close(fd);

    printf("\n\n\n\t\t\t\x1b[37;41m++++++++Transaction details----------\x1b[30;47m\n\n");
    int td=open("transaction_details",O_RDWR);

    lseek(td,0,SEEK_SET);

    lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(td,F_SETLKW,&lock);
    while(1)
    {   
        int p=read(td,&tran,sizeof(tran));
        if(p==0)
        {
            break;
        }
        printf("\n\n\n\t\t\t......................................................");

            printf("\n\t\t\tAccount Number: %d",tran.acc_no);
            printf("\n\t\t\tUSERID: %s",tran.uid);
            printf("\n\t\t\tType: %s",tran.type);
             printf("\n\t\t\tAmount: Rs. %.2f\n",tran.amt);
            printf("\n\t\t\ttime: %s",tran.pt);
    }
     lock.l_type = F_UNLCK;
	fcntl(td,F_SETLK,&lock);
    close(td);
    printf("\n\n\n\n\n\x1b[37;41mpress Enter...to EXIT\x1b[30;47m");
    getchar();
    system("clear");
    printf("\n\n\nBY RUPENKUMAR RAKHOLIYA \nMT2022093\n\n\n.........THANK YOU FOR USING OUR SYSTEM.........\n");
    return 0;
}