#ifndef ROOMS_H
#define ROOMS_H

ssize_t RoomMaker(int skt, int RoomNum);
ssize_t ConnMaker(int skt, int RoomNum);

struct Creature{
	char name[32];
	char flags;
	unsigned short Atk;
	unsigned short Def;
	unsigned short Reg;
	signed short HP;
	unsigned short GP;
	char RoomNum;
	unsigned short DLength;
	char* Desc;
};
ssize_t CreatureSender(int skt, struct Creature thing);
#endif
