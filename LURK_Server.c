#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include "rooms.h"


struct Creature *structArray[50];
int numInArray = 0;
char* compName = "Computer";
char* compDesc = "Is it really a good idea to smash this?";
char* lentName = "Bit of Lent";
char* lentDesc = "... It's Just a bit of Lent...";
char* unName = "Uncertainty";
char* unDesc = "WHICH WAY DO I GO?!";
char* munchName = "The Munchies";
char* munchDesc = "Grimbo... bring me food... I am HUNGRY!";
char foolsDeath[1028];
unsigned short FLength = 33;
char foolsMsg[] = "You Fool... you Killed yourself!";

char* ServerUser = "Server";

void* Multithread(void* nothing){
		char fullGame[128];
		char fullError[128];
		char Accept[2];
		Accept[0] = 8;
		Accept[1] = 10;
		fullGame[0] = 11;
		unsigned short InitPoints = 100;
		unsigned short StatLimit = 65535;
		unsigned short ChangeRoom;
		char GDesc[] = "While driving around town with the girl you love, some random guy started yelling profanities at you. You chase him into an odd building, where he vanished...";
		unsigned short GDLength = strlen(GDesc);
		unsigned short ELength;
		memcpy(fullGame + 1, &InitPoints, 2);
		memcpy(fullGame + 3, &StatLimit, 2);
		memcpy(fullGame + 5, &GDLength, 2);
		memcpy(fullGame + 7, GDesc, GDLength);
		write(nothing, fullGame, 7 + GDLength);	
		int check = 0;
		char dump[1024];
		char* error;
		char type;
		struct Creature player;
		while(check == 0){ 
			read(nothing, &type, 1);
			if(type == 10){ 
				read(nothing, player.name, 32);
				read(nothing, dump, 1);
				read(nothing, &player.Atk, 2);
				read(nothing, &player.Def, 2);
				read(nothing, &player.Reg, 2);
				if(player.Atk + player.Def + player.Reg > InitPoints || player.Atk + player.Def + player.Reg > StatLimit){
					read(nothing, dump, 256); 
					fullError[0] = 7;
					fullError[1] = 4;
					error = "Stat Error";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
				}
				else{
					read(nothing, dump, 6);
					read(nothing, &player.DLength, 2);
					player.Desc = malloc(player.DLength + 1);
					read(nothing, player.Desc, player.DLength);
					player.flags = 136;
					player.RoomNum = 0;
					write(nothing, Accept, 2);
					printf("Accepted Char");
					structArray[numInArray] = &player;
					numInArray++;
					check = 1;
					
				}
			}
			else{
				read(nothing, dump, 256); 
				fullError[0] = 7;
				fullError[1] = 0;
				error = "Bad Type";
				ELength = strlen(error);
				memcpy(fullError + 2, &ELength, 2);
				memcpy(fullError + 4, error, ELength);
				write(nothing, fullError, 4 + ELength);
				
			}
		}
		while(check == 1){
			printf("In Check #1");
			
			read(nothing, &type, 1);
			if(type == 6){
				player.flags += 16;
				check = 2;
			} else {
				fullError[0] = 7;
				fullError[1] = 0;
				error = "Bad Type";
				ELength = strlen(error);
				memcpy(fullError + 2, &ELength, 2);
				memcpy(fullError + 4, error, ELength);
				write(nothing, fullError, 4 + ELength);
			}
		}
		while (check == 2){	
			RoomMaker(nothing, player.RoomNum);
			printf("%i/n", numInArray);
			for(int x = 0; x < numInArray; x++){
				if (structArray[x]->RoomNum == player.RoomNum && structArray[x]->name != player.name ){
					CreatureSender(nothing, *structArray[x]);
				}
			}
			switch(player.RoomNum){
				case 0:
					ConnMaker(nothing, 1);
					break;
				case 1:
					ConnMaker(nothing, 0);
					ConnMaker(nothing, 2);
					ConnMaker(nothing, 3);
					ConnMaker(nothing, 7);
					ConnMaker(nothing, 9);
					ConnMaker(nothing, 10);
					break;
				case 2:
					ConnMaker(nothing, 1);
					ConnMaker(nothing, 3);
					break;
				case 3:
					ConnMaker(nothing, 1);
					ConnMaker(nothing, 2);
					ConnMaker(nothing, 4);
					ConnMaker(nothing, 5);
					break;
				case 4:
					ConnMaker(nothing, 3);
					break;
				case 5:
					ConnMaker(nothing, 3);
					ConnMaker(nothing, 6);
					break;
				case 6:
					ConnMaker(nothing, 5);
					break;
				case 7:
					ConnMaker(nothing, 1);
					ConnMaker(nothing, 8);
					break;
				case 8:
					ConnMaker(nothing, 7);
					break;
				case 9:
					ConnMaker(nothing, 1);
					break;
				case 10:
					ConnMaker(nothing, 11);
					ConnMaker(nothing, 1);
					break;
				case 11:
					ConnMaker(nothing, 10);
					break;
			}
			read(nothing, &type, 1);
			switch(type){
				case 1:
					fullError[0] = 7;
					fullError[1] = 0;
					error = "Not Implemented";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
					break;
				case 2:
					read(nothing, &ChangeRoom, 2);
					switch(player.RoomNum){
						case 0:
							if(ChangeRoom == 1){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 1:
							if(ChangeRoom == 0 || ChangeRoom == 2 || ChangeRoom == 3 || ChangeRoom == 7 || ChangeRoom == 9 || ChangeRoom == 10){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 2:
							if(ChangeRoom == 1 || ChangeRoom == 3){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 3:
							if(ChangeRoom == 1 || ChangeRoom == 2 || ChangeRoom == 4 || ChangeRoom == 5){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 4:
							if(ChangeRoom == 3){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 5:
							if(ChangeRoom == 3 || ChangeRoom == 6){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 6:
							if(ChangeRoom == 5){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 7:
							if(ChangeRoom == 1 || ChangeRoom == 8){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 8:
							if(ChangeRoom == 7){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 9:
							if(ChangeRoom == 1){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 10:
							if(ChangeRoom == 11 || ChangeRoom == 1){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						case 11:
							if(ChangeRoom == 10){
								player.RoomNum = ChangeRoom;
							} else {
								fullError[0] = 7;
								fullError[1] = 1;
								error = "Bad Room";
								ELength = strlen(error);
								memcpy(fullError + 2, &ELength, 2);
								memcpy(fullError + 4, error, ELength);
								write(nothing, fullError, 4 + ELength);
							}
							break;
						default:
							fullError[0] = 7;
							fullError[1] = 1;
							error = "Bad Room";
							ELength = strlen(error);
							memcpy(fullError + 2, &ELength, 2);
							memcpy(fullError + 4, error, ELength);
							write(nothing, fullError, 4 + ELength);
							break;
					}
				case 3:
					//if(structArray[0]->RoomNum == player.RoomNum){
						//foolsDeath[0] = 1;
						//memcpy(foolsDeath + 1, FLength, 2);
						//memcpy(foolsDeath + 3, player.name, 32);
						//memcpy(foolsDeath + 35, ServerUser, 32);
						//memcpy(foolsDeath + 67, foolsMsg, FLength);
						//write(nothing, foolsDeath, 67 + FLength);
						//player.flags -= 128;
						//return 0;
					//}
					//else{
						fullError[0] = 7;
						fullError[1] = 0;
						error = "Not Implemented";
						ELength = strlen(error);
						memcpy(fullError + 2, &ELength, 2);
						memcpy(fullError + 4, error, ELength);
						write(nothing, fullError, 4 + ELength);
					//}
					break;
				case 4:
					fullError[0] = 7;
					fullError[1] = 0;
					error = "Not Implemented";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
					break;
				case 5:
					fullError[0] = 7;
					fullError[1] = 0;
					error = "Not Implemented";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
					break;
				case 12:
					fullError[0] = 7;
					fullError[1] = 0;
					error = "Not Implemented";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
					break;
				default:
					fullError[0] = 7;
					fullError[1] = 0;
					error = "Not Implemented";
					ELength = strlen(error);
					memcpy(fullError + 2, &ELength, 2);
					memcpy(fullError + 4, error, ELength);
					write(nothing, fullError, 4 + ELength);
					break;
			}
		}
}



int main(int argc, char ** argv){
	struct Creature computer;
	memcpy(computer.name, compName, strlen(compName) + 1);
	computer.flags = 184;
	computer.Atk = 0;
	computer.Def = 0;
	computer.Reg = 0;
	computer.HP = 10;
	computer.GP = 10000;
	computer.RoomNum = 8;
	computer.Desc = malloc(strlen(compDesc) + 1);
	memcpy(computer.Desc, compDesc, strlen(compDesc) + 1);
	computer.DLength = strlen(compDesc);
	structArray[numInArray] = &computer;
	numInArray++;
	struct Creature lent;
	memcpy(lent.name, lentName, strlen(lentName) + 1);
	lent.flags = 184;
	lent.Atk = 0;
	lent.Def = 0;
	lent.Reg = 0;
	lent.HP = 10;
	lent.GP = 0;
	lent.RoomNum = 0;
	lent.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent.Desc, lentDesc, strlen(lentDesc) + 1);
	lent.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent;
	numInArray++;
	struct Creature lent0;
	memcpy(lent0.name, lentName, strlen(lentName) + 1);
	lent0.flags = 184;
	lent0.Atk = 0;
	lent0.Def = 0;
	lent0.Reg = 0;
	lent0.HP = 10;
	lent0.GP = 0;
	lent0.RoomNum = 1;
	lent0.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent0.Desc, lentDesc, strlen(lentDesc) + 1);
	lent0.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent0;
	numInArray++;
	struct Creature lent1;
	memcpy(lent1.name, lentName, strlen(lentName) + 1);
	lent1.flags = 184;
	lent1.Atk = 0;
	lent1.Def = 0;
	lent1.Reg = 0;
	lent1.HP = 10;
	lent1.GP = 0;
	lent1.RoomNum = 4;
	lent1.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent1.Desc, lentDesc, strlen(lentDesc) + 1);
	lent1.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent1;
	numInArray++;
	struct Creature lent2;
	memcpy(lent2.name, lentName, strlen(lentName) + 1);
	lent2.flags = 184;
	lent2.Atk = 0;
	lent2.Def = 0;
	lent2.Reg = 0;
	lent2.HP = 10;
	lent2.GP = 0;
	lent2.RoomNum = 5;
	lent2.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent2.Desc, lentDesc, strlen(lentDesc) + 1);
	lent2.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent2;
	numInArray++;
	struct Creature lent3;
	memcpy(lent3.name, lentName, strlen(lentName) + 1);
	lent3.flags = 184;
	lent3.Atk = 0;
	lent3.Def = 0;
	lent3.Reg = 0;
	lent3.HP = 10;
	lent3.GP = 0;
	lent3.RoomNum = 7;
	lent3.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent3.Desc, lentDesc, strlen(lentDesc) + 1);
	lent3.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent3;
	numInArray++;
	struct Creature lent4;
	memcpy(lent4.name, lentName, strlen(lentName) + 1);
	lent4.flags = 184;
	lent4.Atk = 0;
	lent4.Def = 0;
	lent4.Reg = 0;
	lent4.HP = 10;
	lent4.GP = 0;
	lent4.RoomNum = 9;
	lent4.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent4.Desc, lentDesc, strlen(lentDesc) + 1);
	lent4.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent4;
	numInArray++;
	struct Creature lent5;
	memcpy(lent5.name, lentName, strlen(lentName) + 1);
	lent5.flags = 184;
	lent5.Atk = 0;
	lent5.Def = 0;
	lent5.Reg = 0;
	lent5.HP = 10;
	lent5.GP = 0;
	lent5.RoomNum = 10;
	lent5.Desc = malloc(strlen(lentDesc) + 1);
	memcpy(lent5.Desc, lentDesc, strlen(lentDesc) + 1);
	lent5.DLength = strlen(lentDesc);
	structArray[numInArray] = &lent5;
	numInArray++;
	struct Creature un;
	memcpy(un.name, unName, strlen(unName) + 1);
	un.flags = 184;
	un.Atk = 0;
	un.Def = 0;
	un.Reg = 0;
	un.HP = 10;
	un.GP = 0;
	un.RoomNum = 1;
	un.Desc = malloc(strlen(unDesc) + 1);
	memcpy(un.Desc, unDesc, strlen(unDesc) + 1);
	un.DLength = strlen(unDesc);
	structArray[numInArray] = &un;
	numInArray++;
	struct Creature munch;
	memcpy(munch.name, munchName, strlen(munchName) + 1);
	munch.flags = 184;
	munch.Atk = 0;
	munch.Def = 0;
	munch.Reg = 0;
	munch.HP = 10;
	munch.GP = 10000;
	munch.RoomNum = 2;
	munch.Desc = malloc(strlen(munchDesc) + 1);
	memcpy(munch.Desc, munchDesc, strlen(munchDesc) + 1);
	munch.DLength = strlen(munchDesc);
	structArray[numInArray] = &munch;
	
	
	if(argc < 2){
		printf("Usage:  %s port\n", argv[0]);
		return 1;
	}
	int skt = socket(AF_INET, SOCK_STREAM, 0);
	if(skt == -1){
		perror("Socket:  ");
		return 1;
	}
	
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(argv[1]));
	saddr.sin_addr.s_addr = INADDR_ANY;
	if(bind(skt, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in))){
		perror("Bind:  ");
		return 1;
	}

	if(listen(skt, 5)){
		perror("Listen:  ");
		return 1;
	}
	struct sockaddr_in caddr;
	socklen_t caddr_size = sizeof(caddr);
	for(;;){
		int cskt = accept(skt, (struct sockaddr*)&caddr, &caddr_size);
		if(cskt == -1){
			perror("Accept:  ");
			return 1;
		}
		printf("Accepted connection from:  %s\n", inet_ntoa(caddr.sin_addr));
		
		// Interaction with the client starts here
		//multithread starts
		pthread_t tid;
		pthread_create(&tid, NULL, Multithread, (void*)cskt);
		

		//multithread ends here
		// End of interaction with client
	}
	close(skt);

}