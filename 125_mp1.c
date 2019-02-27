/*
==============================================
Cmsc 125
Machine Problem

VELASCO, Gimel David F.
RAMOS, Ron Isaiah
==============================================
CUSTOMIZED LOTTERY SCHEDULING
==============================================
- Doubly Linked List Implementation
==============================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define max_tickets 50 //the maximum ticket number of all the tickets
#define pid_tickets 10 //the maximum number of tickets that a process can hold

struct client{
	int pid;					//Process ID number
	int tickets[pid_tickets];	//holds the tickets of the process
	int burstTime;				//time it takes to finish all the process
	int pTime;					//time it takes for each process to run after each draw
	struct client *next;		//pointer to the next neighbor process
	struct client *prev;		//pointer to the previous neighbor process
};

void list_insert(struct client *e,struct client **h);				//inserts a process in the doubly linked list

void print_clientlist(struct client **h);							//prints the pid, tickets and burst time of all the processes

int get_totalTickets(struct client **h);							//gets the total number of tickets

void getrun_winnerTicket(struct client **h, int total_tickets);		//this is the main backbone of the lottery scheduling

struct client * srch_process(struct client **h, int spid);			//searches for a process using its id number

void del_process(struct client **h, struct client *del);			//deletes a process

void list_deleteAll(struct client **h);								//deletes all processes

int srch_ticket(struct client **h, int tnum);						//this is used for checking whether a ticket is already used by another process

int main(){
	printf("\n\t\tCUSTOMIZED LOTTERY SCHEDULING\n\n");
	////////////
	struct client **head = (struct client **) malloc(sizeof(struct client *));
	*head = NULL;
	////////////
	int i,j,chc,chcstep,total_clients, winning_ticket, client_t, total_tickets,dpid,ati,bt,tnum;
	////////////
	struct client *temp = (struct client *) malloc(sizeof(struct client));
	////////////
	srand(time(NULL));
	////////////
	//PID 1
	temp = (struct client *) malloc(sizeof(struct client));
	for(j=0;j<pid_tickets;j++){temp->tickets[j] = 0;}
	//////////////////////////////////////////////
	//Input Initial Processes in this section/////
	//////////////////////////////////////////////
	temp->pid = 1;
	temp->tickets[0] = 10;
	temp->tickets[1] = 5;
	temp->tickets[2] = 8;
	temp->burstTime = 15;
	temp->pTime = temp->burstTime/3;
	//
	temp->next = NULL;
	temp->prev = NULL;
	list_insert(temp,head);
	////////////
	//PID 2
	temp = (struct client *) malloc(sizeof(struct client));
	for(j=0;j<pid_tickets;j++){temp->tickets[j] = 0;}
	//Input Process in this section
	temp->pid = 2;
	temp->tickets[0] = 2;
	temp->burstTime = 10;
	temp->pTime = temp->burstTime/1;
	//
	temp->next = NULL;
	temp->prev = NULL;
	list_insert(temp,head);
	////////////
	//PID 3
	temp = (struct client *) malloc(sizeof(struct client));
	for(j=0;j<pid_tickets;j++){temp->tickets[j] = 0;}
	//Input Process in this section
	temp->pid = 3;
	temp->tickets[0] = 6;
	temp->tickets[1] = 9;
	temp->tickets[2] = 11;
	temp->tickets[3] = 3;
	temp->burstTime = 20;
	temp->pTime = temp->burstTime/4;
	//
	temp->next = NULL;
	temp->prev = NULL;
	list_insert(temp,head);
	//////////////////////////////////////////////
	do{
		printf("------------------------------------------------\n\tSELECT OPERATION:\n[1] Execute Processes\n[2] View List of Processes\n[3] Exit\n\nSelect:");
		scanf("\n%d",&chc);
		printf("------------------------------------------------\n");
		switch(chc){
			case 1://Function #1
				///////////////Pseudocode/////////////////////
				//Get winning ticket (lottery)
				//run winning ticket (process time)
				//Repeat until there is no more ticket
				//////////////////////////////////////////////
				if(*head == NULL){
					printf("No Processes Available.\n");
					break;
				}
				while(get_totalTickets(head) > 0 && *head != NULL){	//this is main while loop of the program. this stops if there is no more tickets and hence no more processes
					total_tickets = get_totalTickets(head);
					getrun_winnerTicket(head,total_tickets);
					if(get_totalTickets(head) == 0){
						printf("------------------------------------------------\nAll Processes Successfully Executed.\n");
						sleep(1);
						printf("Program Terminated.\n");
						return 0;
					}
					else{
						do{
							printf("------------------------------------------------\n\tSELECT STEP:\n[1] Continue\n[2] Add Process\n[3] Remove Process\n[4] View Processes\n[5] Cancel\n\nSelect:");
							scanf("\n%d",&chcstep);
							printf("------------------------------------------------\n");
							switch(chcstep){
								case 1:
									//exit switch statement and continue process
								break;
								case 2:
									printf("Add PID\nInput Process ID Number: ");
									scanf("\n%d",&dpid);
									printf("Input Number of Tickets: ");
									scanf("\n%d",&ati);
									printf("Input Burst Time: ");
									scanf("\n%d",&bt);
									////////////
									//PID New
									temp = (struct client *) malloc(sizeof(struct client));
									for(j=0;j<pid_tickets;j++){temp->tickets[j] = 0;}
									//////////////////////////////////////////////
									//Inputs a process in this section////////////
									temp->pid = dpid;
									for(j=0;j<ati;j++){
										do{
											printf("Input Ticket Number [%d/%d]: ",j+1,ati);
											scanf("\n%d",&tnum);
										}while(srch_ticket(head,tnum) != 1);//1clear | 2sameticketfound	//checks if a ticket is already taken
										temp->tickets[j] = tnum;
									}
									temp->burstTime = bt;
									temp->pTime = bt/ati;
									//
									temp->next = NULL;
									temp->prev = NULL;
									list_insert(temp,head);
									//////////////////////////////////////////////
									printf("Successfully Added Process\n");
								break;
								case 3:
									printf("Remove PID: ");
									scanf("\n%d",&dpid);
									struct client *del = srch_process(head,dpid);
									del_process(head,del);
									printf("Successfully Removed PID %d\n",dpid);
								break;
								case 4:
									print_clientlist(head);
								break;
								case 5:
									printf("Process Cancelled. Program Terminated.\n");
									return 0;
								break;
								default:
									printf("Invalid Choice.\n");
								break;
							}
						}while(chcstep != 1);
					}
				}
			break;
			case 2://Function #2
				print_clientlist(head);
			break;
			case 3://Exit
				printf("Program Terminated.\n");
			break;
			default:
				printf("Invalid Choice.\n");
			break;
		}
	}while(chc != 3);
	return 0;
}

void list_insert(struct client *e,struct client **h){
	if(*h == NULL){//if empty
		*h = e;
	}
	else{
		struct client *p = *h;
		while(p->next != NULL){
			p = p->next;
		}
		e->next = p->next;
		p->next = e;
		e->prev = p;
	}
}

void print_clientlist(struct client **h){
	struct client *p = *h;
	int ti;
	if(p == NULL){
		printf("No Processes in list.\n");
	}
	else{
		printf("\t\tPROCESS LIST\n");
		while(p != NULL){
			printf("PID: %d | Tickets: ", p->pid);
			for(ti=0;ti<pid_tickets;ti++){
				if(p->tickets[ti] != 0){
					printf("%d ", p->tickets[ti]);
				}
				else{
					printf("  ");
				}
			}
			printf("| Burst Time: %d\n",p->burstTime);
			p = p->next;
		}
	}
}

int get_totalTickets(struct client **h){
	struct client *p = *h;
	int total_tickets=0;
	int ti;
	if(p == NULL){
		
	}
	else{
		while(p != NULL){
			ti = 0;
			while(p->tickets[ti] != 0){
				total_tickets += p->tickets[ti];
				ti++;
			}
			p = p->next;
		}
	}
	return total_tickets;
}

void getrun_winnerTicket(struct client **h, int total_tickets){
	struct client *p = *h;
	struct client *del;
	struct client *w = NULL;
	struct client *s;
	int winning_ticket = rand()%total_tickets + 1;
	int cumu_tickets=0;
	int wti, ti;
	if(p == NULL){
		printf("No Processes in list.\n");
	}
	else{
		while(p != NULL){
			for(ti=0;ti<pid_tickets;ti++){
				if(p->tickets[ti] == 0){
					break;
				}
				if((winning_ticket > cumu_tickets) && (winning_ticket <= (cumu_tickets + p->tickets[ti]))){
					wti = ti;
					w = p;
					break;
				}
				cumu_tickets += p->tickets[ti];
			}
			p = p->next;
		}
	}
	////////////////////
	printf("PID %d: ticket %d",w->pid,w->tickets[wti]);
	//sleep(w->pTime);
	printf(" took %d seconds to execute\n",w->pTime);
	////////////////////
	///////kelangan imove ung lahat ng tickets sa left
	for(ti=wti;ti<pid_tickets-1;ti++){
		w->tickets[ti] = w->tickets[ti+1];
	}
	w->tickets[pid_tickets-1] = 0;
	
	w->burstTime = w->burstTime - w->pTime;

	if(w->tickets[0] == 0){
		del_process(h,w);	
	}
}

struct client * srch_process(struct client **h, int spid){
	struct client *p = *h;
	while(p != NULL){
		if(p->pid == spid){
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void del_process(struct client **h, struct client *del){
	if((del->next == NULL) && (del->prev == NULL)){
		list_deleteAll(h);
		return;
	}
	else if(del->prev == NULL){//if leftmost
		del->next->prev = del->prev;
		*h = del->next;
	}
	else if(del->next == NULL){//if rightmost
		del->prev->next = del->next;
	}
	else{//if middle
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}
	free(del);
}

void list_deleteAll(struct client **h){
	struct client *p = *h;
	while(*h != NULL){
		p = *h;
		*h = p->next;
		free(p);
	}
}

int srch_ticket(struct client **h, int tnum){
	struct client *p = *h;
	int ti;
	while(p != NULL){
		for(ti=0;ti<pid_tickets;ti++){
			if(p->tickets[ti] == 0){
				break;
			}
			if(p->tickets[ti] == tnum){
				printf("Same Ticket Found. Try Again.\n");
				return 2;//nope
			}
		}
		p = p->next;
	}
	return 1;//okay go
}