#ifndef FIELD_H
#define FIELD_H

	typedef struct {
		int x;
		int y;
	} Destination_t;
	
	
	struct Destination_t getPackage();
	void setPosition(int, int, int);
	int getPosition(int, int);
	void Pos(int);
#endif
