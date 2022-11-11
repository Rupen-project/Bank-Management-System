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
struct{
	char pt[100];
	char uid[60];
	char type[60];
	int acc_no;
	float amt;
}tran;
void updateHandler(int sd,char *u)
{
	
	while(1)
	{
		char op[20],np[20];
		int fd=open("account_details",O_RDWR);
	    read(sd,&op,sizeof(op));
	    
	    
		lseek(fd,0,SEEK_SET);
		
		// printf("uid given %s",u);
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(fd,F_SETLKW,&lock);
		while(1)
		{
			int c=read(fd,&check,sizeof(check));
			if(c==0)
		    {
		    	break;
		    }
			if(strcmp(u,check.uid)==0)
		    {
		        // printf("match %s",check.uid);
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				
				if(strcmp(check.pass,op)==0)
				{
					char p='p';
					write(sd,&p,sizeof(p));
					read(sd,&np,sizeof(np));
					
					
					lseek(fd,-sizeof(check),SEEK_CUR);
			        lock.l_type = F_WRLCK;
					lock.l_whence = SEEK_CUR;
					lock.l_start = 0;
					lock.l_len = sizeof(check);
		        	lock.l_pid = getpid();
					fcntl(fd,F_SETLKW,&lock);
					
					// printf("%s",np);
			        strcpy(check.pass,np);
			        
			        write(fd,&check,sizeof(check));
			        // printf("match %s",check.uid);
		        	lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd);
					p='d';
					write(sd,&p,sizeof(p));
					return;   
						        
				}
				else
				{
					char p='f';
					write(sd,&p,sizeof(p));
					lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd);
					break;
				}
		        
		    }
		   
		}
	}
}
	

void depositHandler(int sd,char *u)
{
	int fd=open("account_details",O_RDWR);
	lseek(fd,0,SEEK_SET);
	
	// printf("uid given %s",u);
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
	int c=0;
	while(1)
	{
		c=read(fd,&check,sizeof(check));
		if(c==0)
	    {
	    	break;
	    }
		if(strcmp(u,check.uid)==0)
	    {
	        // printf("match %s",check.uid);
	        lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			
			//write lock on user record
	        lseek(fd,-sizeof(check),SEEK_CUR);
	        lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_CUR;
			lock.l_start = 0;
			lock.l_len = sizeof(check);
        	lock.l_pid = getpid();
			fcntl(fd,F_SETLKW,&lock);

        	break;
	        
	    }
	   
	}
	char p;
		
	if(c==0)
	{
		//just to avoid sckot race
		read(sd,&transaction.amt,sizeof(transaction.amt));
		
		
		p='f';
		write(sd,&p,sizeof(p));
		
		lock.l_type = F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);
		return;
	}
	else
	{
		
		read(sd,&transaction.amt,sizeof(transaction.amt));

		check.amt=check.amt+transaction.amt;

		write(fd,&check,sizeof(check));
		lock.l_type = F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);
		
		int td=open("transaction_details",O_RDWR);
	    
	    
	    
	    time_t mytime = time(NULL);
	    char * time_str = ctime(&mytime);
	    time_str[strlen(time_str)-1] = '\0';
	    
	    
	    strcpy(tran.pt,time_str);
	    strcpy(tran.type,"Deposit");
	 
	    tran.amt=transaction.amt;
	    strcpy(tran.uid,check.uid);
	    tran.acc_no=check.acc_no;
	    
	    lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(td,F_SETLKW,&lock);
		
		lseek(td,0,SEEK_END);
	    write(td,&tran,sizeof(tran));
	    
	    
	    lock.l_type = F_UNLCK;
		fcntl(td,F_SETLK,&lock);
		close(td);
	    
	   	
	    
	  
		p='p';
		write(sd,&p,sizeof(p));
		return;
	}
		
		
}
void withdrawHandler(int sd,char *u){
	
	int fd=open("account_details",O_RDWR);
	lseek(fd,0,SEEK_SET);
	
	// printf("uid given %s",u);
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
	int c=0;
	while(1)
	{
		c=read(fd,&check,sizeof(check));
		if(c==0)
	    {
	    	break;
	    }
		if(strcmp(u,check.uid)==0)
	    {
	        
	        lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			
			//write lock on user record
	        lseek(fd,-sizeof(check),SEEK_CUR);
	        lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_CUR;
			lock.l_start = 0;
			lock.l_len = sizeof(check);
        	lock.l_pid = getpid();
			fcntl(fd,F_SETLKW,&lock);

        	break;
	        
	    }
	   
	}
	char p;
		
	if(c==0)
	{
		//just to avoid sckot race
		read(sd,&transaction.amt,sizeof(transaction.amt));
		
		
		p='f';
		write(sd,&p,sizeof(p));
		
		lock.l_type = F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);
		return;
	}
	else
	{
		
		
		read(sd,&transaction.amt,sizeof(transaction.amt));

		
		if(check.amt>=transaction.amt)
		{
			check.amt=check.amt-transaction.amt;
			write(fd,&check,sizeof(check));
			
			lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			close(fd);
			
			int td=open("transaction_details",O_RDWR);
	    
	    
	    
		    time_t mytime = time(NULL);
		    char * time_str = ctime(&mytime);
		    time_str[strlen(time_str)-1] = '\0';
		    
		    
		    strcpy(tran.pt,time_str);
		    strcpy(tran.type,"withdraw");
		 
		    tran.amt=transaction.amt;
		    strcpy(tran.uid,check.uid);
		    tran.acc_no=check.acc_no;
		    
		    lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(td,F_SETLKW,&lock);
			
			lseek(td,0,SEEK_END);
		    write(td,&tran,sizeof(tran));
		    
		    
		    lock.l_type = F_UNLCK;
			fcntl(td,F_SETLK,&lock);
			close(td);
				
			p='p';
			write(sd,&p,sizeof(p));
			return;
		}
		else
		{
			
			lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			close(fd);
			
			p='n';
			write(sd,&p,sizeof(p));
			return;
		}
	}
		
		
		
		return;
}
	
void userMainMenuHandler(int sd,char *u)
{
	int fd=open("account_details",O_RDWR);
	lseek(fd,0,SEEK_SET);
	
	// printf("uid given %s",u);
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(fd,F_SETLKW,&lock);
	while(1)
		{
			int c=read(fd,&check,sizeof(check));
			if(c==0)
		    {
		    	break;
		    }
			if(strcmp(u,check.uid)==0)
		    {
		        // printf("match %s",check.uid);
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				close(fd);

	        	break;
		        
		    }
		   
		}
	// write(sd,&check,sizeof(check)); \\send full details	
	while(1)
	{
		char choice;
		read(sd,&choice,sizeof(choice));
		if(choice=='1')
		{
			depositHandler(sd,u);
		}
		else if(choice=='2')
		{
			withdrawHandler(sd,u);
		}
		else if(choice=='3')
		{
			write(sd,&check,sizeof(check));
		}
		else if(choice=='4')
		{
			updateHandler(sd,u);
			return;
		}
		else if(choice=='5')
		{
			write(sd,&check,sizeof(check));
		}
		else if(choice=='6')
		{
			return;
		}
	}   	
}
void coustemerLoginHandler(int sd)
{
	while(1)
	{
		char choice;
		read(sd,&choice,sizeof(choice));
		if(choice=='1')
		{
			read(sd,&add,sizeof(add)); //read uid and pass
			// printf("uid %s",add.uid);
			// printf("pass %s",add.pass);
			
			int fd=open("account_details",O_RDWR);
			lseek(fd,0,SEEK_SET);
			
			int k=0;
			
			struct flock lock;
			lock.l_type = F_RDLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(fd,F_SETLKW,&lock);
			// Inside Critical section
				
			while(1)
			{
				
				int c=read(fd,&check,sizeof(check));
				
				if(c==0)
				{
					lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
					break;
				}
				if(strcmp(add.uid,check.uid)==0)
			    {
			        if(strcmp(add.pass,check.pass)==0)
			        {	
			        	lock.l_type = F_UNLCK;
						fcntl(fd,F_SETLK,&lock);
						close(fd); 
						
			        	k++;
			        	char p='p';
			        	write(sd,&p,sizeof(p)); //pass
			        	
			        	
			        	userMainMenuHandler(sd,add.uid);
			        	
			        	
			        	break;
			        }
			    }
			}
			
			if(k==0)
			{
				char p='f';
				write(sd,&p,sizeof(p)); //fail
			}
			else{
				return;
			}
		}
		else
		{
			return;
		}
	}
	
      	
	
	
}

void accountCreateHandler(int sd)
{
	// printf("in create\n");
	while(1)
	{
		char choice;
		read(sd,&choice,sizeof(choice));
		if(choice=='1' || choice=='2')
		{	
			read(sd,&add,sizeof(add));
			
			int fd=open("account_number",O_RDWR);
			lseek(fd,0,SEEK_SET);
			int acc=0;
			char buff;
			int k=0;
			
			//protect file with write lock as we wnat to update the account number
			struct flock lock;
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(fd,F_SETLKW,&lock);
			// Inside Critical section
			while(1)
			{	int q = read(fd,&buff,1);
				if(q==0) break;
				acc= (acc*10) + (buff-'0');
				// printf("%d\n",acc);
				
			}
			
			// if(k==0)
			// {
			// 	k++;
			// }
			// printf("%d\n",acc);
			acc++;
			sprintf(add.uid,"%d",acc+100000);
			
			char accno[1000];
			sprintf(accno,"%d",acc);
			add.acc_no=acc;
			
			lseek(fd,0,SEEK_SET);
			write(fd,accno,floor(log10(acc))+1);
			
			lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			close(fd);
			
			int afd=open("account_details",O_RDWR);
			lseek(afd,0,SEEK_END);

			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(afd,F_SETLKW,&lock);
			// Inside Critical section
			// printf("read niche\n%d",add.age);
			write(afd,&add,sizeof(add));
			
			lock.l_type = F_UNLCK;
			fcntl(afd,F_SETLK,&lock);
			
			
			//write to socket for showing uid and account number
			write(sd,&add,sizeof(add));
			close(afd);
			return;
		}
		else if(choice=='3')
		{
			read(sd,&add,sizeof(add));
			read(sd,&add2,sizeof(add2));
			int fd=open("account_number",O_RDWR);
			lseek(fd,0,SEEK_SET);
			int acc=0;
			char buff;
			int k=0;
			
			//protect file with write lock as we wnat to update the account number
			struct flock lock;
			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(fd,F_SETLKW,&lock);
			// Inside Critical section
			while(1)
			{	int q = read(fd,&buff,1);
				if(q==0) break;
				acc= (acc*10) + (buff-'0');
				// printf("%d\n",acc);
				
			}
			acc++;
			
			// User id for first person from 100000 onwords
			// User id for second person from 200000 onwords
			sprintf(add.uid,"%d",acc+100000);
			sprintf(add2.uid,"%d",acc+200000);
			
			char accno[k];
			sprintf(accno,"%d",acc);
			
			//account number same
			add.acc_no=acc;
			add2.acc_no=acc;
			
			lseek(fd,0,SEEK_SET);
			write(fd,accno,floor(log10(acc))+1);
			
			lock.l_type = F_UNLCK;
			fcntl(fd,F_SETLK,&lock);
			close(fd);
			
			// gocreateAcc(&add,sd,1);
			int afd=open("account_details",O_RDWR);
			lseek(afd,0,SEEK_END);

			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();
			fcntl(afd,F_SETLKW,&lock);
			// Inside Critical section
			
			write(afd,&add,sizeof(add));
			write(afd,&add2,sizeof(add2));
			
			lock.l_type = F_UNLCK;
			fcntl(afd,F_SETLK,&lock);
			
			write(sd,&add,sizeof(add));
			write(sd,&add2,sizeof(add2));
			close(afd);
			
			return;
		}
	}
}
void cloginHandler(int sd)
{
	while(1)
	{
		char choice;
		// printf("p");
		read(sd,&choice,sizeof(choice));
		if(choice=='1')
		{
			coustemerLoginHandler(sd);
			return;
		}
		else if(choice=='2')
		{
			accountCreateHandler(sd);
			coustemerLoginHandler(sd);
			return;
		}
		else if(choice=='3')
		{
			return;
		}
	}
	
}

void searchHandler(int sd)
{
	printf("in search\n");
	char ui[20];
	while(1)
	{
		read(sd,&ui,sizeof(ui));
		
		int fd=open("account_details",O_RDWR);
	    lseek(fd,0,SEEK_SET);
	    
	    struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(fd,F_SETLKW,&lock);
		// Inside Critical section
		char pass;
	    while(1)
	    {  
	        int p=read(fd,&add,sizeof(add));
	        if(p==0)
			{
				pass='f';
				write(sd,&pass,sizeof(pass));
				lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				close(fd); 
				
				return;
			}
			 
	        if(strcmp(add.uid,ui)==0)
	        {	
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				
				
	        	pass='p';
	        	write(sd,&pass,sizeof(pass)); //pass
	        	
	        	
	        	write(sd,&add,sizeof(add));
	        	
	        	
	        	return;
	        }
			    
	        
	    }		
			   
	}
}
int chekAdminLoginHandler(int sd)
{
	while(1)
	{
		char choice,p;
		read(sd,&choice,sizeof(choice));
		if(choice=='1'){
			read(sd,&admins.pass,sizeof(admins.pass));
			if(strcmp(admins.pass,"rupen")==0)
			{
				
				p='p';
				write(sd,&p,sizeof(p));
				return 1;
			}
			else
			{
				p='f';
				write(sd,&p,sizeof(p));
				
			}
		}
		else if (choice=='2'){
			return 0;
		}
	}
}
void modifyHandler(int sd)
{
	
	while(1)
	{
		char ui[20];
		read(sd,&ui,sizeof(ui));
		
		int fd=open("account_details",O_RDWR);
	    lseek(fd,0,SEEK_SET);
	    
	    struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(fd,F_SETLKW,&lock);
		// Inside Critical section
		char pass;
	    while(1)
	    {  
	        int p=read(fd,&add,sizeof(add));
	        if(p==0)
			{
				pass='f';
				write(sd,&pass,sizeof(pass));
				lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				close(fd); 
				
				return;
			}
			 
	        if(strcmp(add.uid,ui)==0)
	        {	
	        	pass='p';
	        	write(sd,&pass,sizeof(pass)); //pass
	        	
	        	
	        	write(sd,&add,sizeof(add)); //sed full details
	        	
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				
				//write lock on user record
		        lseek(fd,-sizeof(add),SEEK_CUR);
		        lock.l_type = F_WRLCK;
				lock.l_whence = SEEK_CUR;
				lock.l_start = 0;
				lock.l_len = sizeof(add);
	        	lock.l_pid = getpid();
				fcntl(fd,F_SETLKW,&lock);
				
	        	
	        	char c;
	        	read(sd,&c,sizeof(c));
	        	
	        	if(c=='1')
	        	{
	        		read(sd,&add.name,sizeof(add.name));
	        		write(fd,&add,sizeof(add));
	        		
	        		lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
	        		char p='p';
	        		write(sd,&p,sizeof(p));
	        		return;
	        	}
	        	else if(c=='2')
	        	{
	        		read(sd,&rem,sizeof(rem));
	        		
	        		add.dob.day=rem.dob.day;
	        		add.dob.month=rem.dob.month;
	        		add.dob.year=rem.dob.year;
	        		
	        		write(fd,&add,sizeof(add));
	        		
	        		lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
	        		char p='p';
	        		write(sd,&p,sizeof(p));
	        		return;
	        	}
	        	else if(c=='3')
	        	{
	        		read(sd,&add.address,sizeof(add.address));
	        		write(fd,&add,sizeof(add));
	        		
	        		lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
	        		char p='p';
	        		write(sd,&p,sizeof(p));
	        		return;
	        	}
	        	else if(c=='4')
	        	{
	        		read(sd,&add.citizenship,sizeof(add.citizenship));
	        		write(fd,&add,sizeof(add));
	        		
	        		lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
	        		char p='p';
	        		write(sd,&p,sizeof(p));
	        		return;
	        	}
	        	else if(c=='5')
	        	{
	        		read(sd,&add.phone,sizeof(add.phone));
	        		write(fd,&add,sizeof(add));
	        		
	        		lock.l_type = F_UNLCK;
					fcntl(fd,F_SETLK,&lock);
					close(fd); 
					
	        		char p='p';
	        		write(sd,&p,sizeof(p));
	        		return;
	        	}
	        	else if(c=='6')
	           {
	               return;
	           }
	        	
	  
	        }  
	        
	    }
	    
	}
}

void deleteAccountHandler(int sd)
{
	// printf("in delete\n");
	char ui[20];
	while(1)
	{
		read(sd,&ui,sizeof(ui));
		
		int fd=open("account_details",O_RDWR);
	    lseek(fd,0,SEEK_SET);
	    
	    struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(fd,F_SETLKW,&lock);
		// Inside Critical section
		char pass;
	    while(1)
	    {  
	        int p=read(fd,&add,sizeof(add));
	        if(p==0)
			{
				pass='f';
				write(sd,&pass,sizeof(pass));
				lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock); 
				close(fd);
				return;
			}
			 
	        if(strcmp(add.uid,ui)==0)
	        {	
	        	pass='p';
	        	write(sd,&pass,sizeof(pass));
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
	        	
	        	
				
				//write lock on user record
		        lseek(fd,-sizeof(add),SEEK_CUR);
		        lock.l_type = F_WRLCK;
				lock.l_whence = SEEK_CUR;
				lock.l_start = 0;
				lock.l_len = sizeof(add);
	        	lock.l_pid = getpid();
				fcntl(fd,F_SETLKW,&lock);
				
				strcpy(add.uid,"removed");
	        	write(fd,&add,sizeof(add));
	        	
	        	lock.l_type = F_UNLCK;
				fcntl(fd,F_SETLK,&lock);
				close(fd);
				
	        	pass='d';
	        	write(sd,&pass,sizeof(pass));
	        	
	        	return;
	        }
			    
	        
	    }		
			   
	}
}
void aloginHandler(int sd)
{
	int d=chekAdminLoginHandler(sd);
	if(d==0)
	{
		return;
	}
	while(1)
	{
		char choice;
		// printf("p");
		read(sd,&choice,sizeof(choice));
		if(choice=='1')
		{
			// printf("create\n");
			accountCreateHandler(sd);
		}else if(choice=='2')
		{
			// printf("delete\n");
			deleteAccountHandler(sd);
		}
		else if(choice=='3')
		{
			
			modifyHandler(sd);
		}
		else if(choice=='4')
		{
			// printf("search\n");
			searchHandler(sd);
			
		}
		else if(choice=='5')
		{
			return;
		}
		
	}
}
void clientHandler(int sd){
	while(1)
	{
		char choice;
		read(sd,&choice,sizeof(choice));
		if(choice=='1')
		{
			cloginHandler(sd);
			return;
		}
		else if(choice=='2')
		{
			aloginHandler(sd);
			return;
		}
		else if(choice=='3')
		{
			return;
		}
	}
}

int main()
{
		struct sockaddr_in serv, cli;
		int sd, nsd; 
		char buf[80];
		sd = socket(AF_INET, SOCK_STREAM, 0);
		serv.sin_family = AF_INET; 
		serv.sin_addr.s_addr = INADDR_ANY; 
		serv.sin_port = htons(2812);
		bind(sd, (struct sockaddr *) (&serv), sizeof(serv)); 
		listen(sd, 5); 
		while(1){
			socklen_t sz = (int)sizeof(cli);
			nsd = accept(sd, (struct sockaddr *) (&cli),&sz);
			if(!fork())
			{
				clientHandler(nsd);
				close(nsd);
				exit(0);
			}
			else
			{
				close	(nsd);
			}
		
		}
		
}
