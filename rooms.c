#include <string.h>
#include <unistd.h>
#include "rooms.h"
ssize_t RoomMaker(int skt, int RoomNum){
char fullRoom[1028];
	fullRoom[0] = 9;
	unsigned short RoomNumS = RoomNum;
	memcpy(fullRoom + 1, &RoomNumS, 2);
	unsigned short RDLength;
	char* RName;
	char* RDesc;
	switch(RoomNum){
		case 0:
			RName = "Top of Stairs";
			RDesc = "You enter the building. From where you are standing, you see a staircase going downward, and a door to your left. The door is locked. Only one way to go...";
			break;
		case 1:
			RName = "Bottom of Stairs";
			RDesc = "To your Left seems to be a Kitchen and a Hallway, ahead of you is a Table, and beyond that, a computer. To Your right is a TV, Couch, recliner, and an entrance to some room";
			break;
		case 2:
			RName = "Kitchen";
			RDesc = "This room has a Fridge, Freezer, Toaster, Blender, Oven, Microwave and a whole lot of Cabinent Space... doesn't seem well-stocked though...";
			break;
		case 3:
			RName = "Hallway";
			RDesc = "On the right seems to be a Bathroom, and Straight Ahead seems to be a Bedroom... because that's what they are... you are starting to think that your brain may be a little off today..";
			break;
		case 4:
			RName = "Bathroom";
			RDesc = "A Toilet, a Shower stall, and a Sink... Yep... This is a Bathroom...";
			break;
		case 5:
			RName = "Bedroom";
			RDesc = "Clothes are Strewn across the floor, a dresser sits in front of you, a Bed tucked in the far corner, and a Closet to your left"; 
			break;
		case 6:
			RName = "Closet";
			RDesc = "Ha Ha, you are hiding in the closet... aren't you funny... Maybe when you leave we will tell everyone you are now out of the closet... wouldn't that be funny? Come on... let's go...";
			break;
		case 7:
			RName = "Table";
			RDesc = "A table Littered with asorted knick-nacks... The Computer is in reach now...";
			break;
		case 8: 
			RName = "Computer";
			RDesc = "A Computer. On the Screen is your thoughts when you entered each room... weird...";
			break;
		case 9:
			RName = "Entertainment Room";
			RDesc = "A corner of the Living Room with a TV, Wii U, XBox 360, and a PS4 surrounded by a Sofa and Recliner";
			break;
		case 10:
			RName = "Laundry Room";
			RDesc = "Washer and Drier Combo, a countertop with a large assortment of clothes, and a Broom closet.";
			break;
		case 11:
			RName = "Broom Closet";
			RDesc = "You entered the Broom Closet, it would be best if you Turned around and got back on track...";
			break;
	}
		
	RDLength = strlen(RDesc);
	memcpy(fullRoom + 3, RName, strlen(RName) + 1);
	memcpy(fullRoom + 35, &RDLength, 2);
	memcpy(fullRoom + 37, RDesc, RDLength);
	return write(skt, fullRoom, 37 + RDLength);
}
ssize_t ConnMaker(int skt, int RoomNum){
	char fullCon[1028];
	fullCon[0] = 13;
	unsigned short RoomNumS = RoomNum;
	memcpy(fullCon + 1, &RoomNumS, 2);
	unsigned short RDLength;
	char* RName;
	char* RDesc;
	switch(RoomNum){
		case 0:
			 RName = "Top of Stairs";
			 RDesc = "Going back up?";
			break;
		case 1:
			 RName = "Bottom of Stairs";
			 RDesc = "Maybe it's time to Leave...";
			break;
		case 2:
			 RName = "Kitchen";
			 RDesc = "Time to get some Grub!";
			break;
		case 3:
			 RName = "Hallway";
			 RDesc = "What's over here?";
			break;
		case 4:
			 RName = "Bathroom";
			 RDesc = "Because one needs to be clean!";
			break;
		case 5:
			 RName = "Bedroom";
			 RDesc = "After all you have been through, you earned a rest..."; 
			break;
		case 6:
			 RName = "Closet";
			 RDesc = "Probably just clothes in there...";
			break;
		case 7:
			 RName = "Table";
			 RDesc = "What's on the table?";
			break;
		case 8: 
			 RName = "Computer";
			 RDesc = "Oh hey! I know how to work one of those!";
			break;
		case 9:
			 RName = "Entertainment Room";
			 RDesc = "Not exactly a room... more like a corner...";
			break;
		case 10:
			 RName = "Laundry Room";
			 RDesc = "Machinery can be heard from inside...";
			break;
		case 11:
			 RName = "Broom Closet";
			 RDesc = "A closet, with Brooms!";
			break;
	}
		
	RDLength = strlen(RDesc);
	memcpy(fullCon + 3, RName, strlen(RName) + 1);
	memcpy(fullCon + 35, &RDLength, 2);
	memcpy(fullCon + 37, RDesc, RDLength);
	return write (skt, fullCon, 37 + RDLength);
}
ssize_t CreatureSender(int skt, struct Creature thing){
	char FullThing[1028];
	FullThing[0] = 10;
	memcpy(FullThing + 1, thing.name, 32);
	memcpy(FullThing + 33, &thing.flags, 1);
	memcpy(FullThing + 34, &thing.Atk, 2);
	memcpy(FullThing + 36, &thing.Def, 2);
	memcpy(FullThing + 38, &thing.Reg, 2);
	memcpy(FullThing + 40, &thing.HP, 2);
	memcpy(FullThing + 42, &thing.GP, 2);
	memcpy(FullThing + 44, &thing.RoomNum, 2);
	memcpy(FullThing + 46, &thing.DLength, 2);
	memcpy(FullThing + 48, thing.Desc, thing.DLength);
	return write(skt, FullThing, 48 + thing.DLength);
}