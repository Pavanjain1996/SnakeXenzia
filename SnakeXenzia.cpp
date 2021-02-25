#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
void gotoxy(short x,short y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
bool gameOver;
const int width=50;
const int height=20;
int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void Setup(){
	gameOver = false;
	dir=STOP;
	x=width/2;
	y=height/2;
	fruitX=rand()%width;
	fruitY=rand()%height;
	score=0;
}
void Draw(){
	system("cls");
	for(int i=0;i<width+2;i++)
		cout<<"_";
	cout<<endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(j==0)
				cout<<"|";
			if(i==y && j==x)
				cout<<(char)24;
			else if(i==fruitY && j==fruitX)
				cout<<(char)2;
			else{
				bool print =false;
				for(int k=0;k<nTail;k++){
					if(tailX[k]==j && tailY[k]==i){
		   				cout<<(char)24;
						print=true;
					}	
				}
			if(!print)
				cout<<" ";
			}
			if(j==width-1)
				cout<<"|";
		} 
		cout<<endl;
	}
	for(int i=0;i<width+2;i++)
		cout<<"_";
	cout<<endl;
	cout<<"\nScore : "<<score<<endl;
}
void Input(){
	if(_kbhit()){
		switch(_getch()){
			case 'a':
				dir=LEFT;
				break;
			case 'd':
				dir=RIGHT;
				break;
			case 'w':
				dir=UP;
				break;
			case 's':
				dir=DOWN;
				break;
		}
	}
}
void Logic(){
	int prevX=tailX[0];
	int prevY=tailY[0];
	int prev2X,prev2Y;
	tailX[0]=x;
	tailY[0]=y;
	for(int i=1;i<nTail;i++){
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(dir){
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if(x>width || x<0 || y>height || y<0)
		gameOver=true;
	for(int i=0;i<nTail;i++){
		if(tailX[i]==x && tailY[i]==y)
			gameOver = true;
	}
	if(x==fruitX && y==fruitY){
		score+=10;
		fruitX=rand()%width;
		fruitY=rand()%height;
		nTail++;
		Beep(2500,100);
	}
}
main(){
	system("color E");
	srand(time(NULL));
	cout<<"\n\n\n\n\n\tPlease wait while the game is loading........\n\n\t";
	for(int i=1;i<=45;i++){
		cout<<(char)178;
		Sleep(100);
	}
	cout<<"\n\n\tPress any key to continue/ESC to exit";
	getch();
	system("cls");
	gotoxy(10,4);
	printf("1.Easy Level");
	gotoxy(10,6);
	printf("2.Medium Level");
	gotoxy(10,8);
	printf("3.Hard Level");
	gotoxy(10,10);
	int lno;
	printf("Choose Your Level : ");
	lno=getch()-48;
	Setup();
	while(!gameOver){
		Draw();
		Input();
		Logic();
		Sleep(10/lno);
	}
	cout<<"\n\nYour Game is ended";
	getch();
}
