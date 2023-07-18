//============================================================================
// Name        : game.cpp
// Author      : Saif Ali Khan (21i-0649) CS Department Section R
// Version     : 1.0
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...


/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
string TaxiColor; // string that stores the taxi color
string name; // varaible storing user name
string timer; // 


char board[20][20]={0}; // 20x20 grid, here 'T' means TRACK and cannot be crossed, 'P' means PERSON , 'O' means obstacle, 'U' means user car

bool flag1 = true; // for first passenger
bool flag2 = true; // for second passenger
bool flag3 = true; // for third passenger
bool destination_flag1 = true; // for first destination
bool destination_flag2 = true;	// for 2nd destination
bool destination_flag3 = true;	// for 3rd destination
bool test1=true;
bool test2=true;
bool test3=true;

bool refresh = true;
bool winner = false;
int score=0;
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

int xI = 20, yI = 760; // coordinates when the car will first spawn on map (top left)
int car1x = 80 , car1y = 0; 
int car2x = 0 ,car2y = 400;
int car3x = 400 ,car3y = 640 ;
int car4x = 400 ,car4y = 80;
int car5x = 640 ,car5y= 320 ;
int counter=0;
int timer_countdown=180*80;		 // 80fps is deafult 3 mins is 180s 
	

void countdown(){ // function that shows countdown of 3mins

	counter++;
	timer_countdown--;
	DrawString(735,775,to_string(timer_countdown),colors[66]);
}

void drawCar() { // function that drawns the user car with tyres and body
	if (TaxiColor=="RED")
	DrawRectangle(xI, yI, 40,20, colors[5]);
	if (TaxiColor=="YELLOW")
	DrawRectangle(xI, yI, 40,20, colors[22]);

	DrawCircle(xI,yI-5,10, colors[75]); // drawing tires of car (coordinate of left tire)
	DrawCircle(xI+35,yI+(-5),10, colors[75]); // right tire coordinate
	glutPostRedisplay();
}
void Random_drawCar(int x, int y , int color) { // draws the random cars

	DrawRectangle(x, y, 40,20, colors[color]);
	DrawCircle(x,y-5,10, colors[75]); // drawing tires of car (coordinate of left tire)
	DrawCircle(x+35,y+(-5),10, colors[75]); // right tire coordinate
	glutPostRedisplay();
}
void Random_obstacle(int column, int row){ // function that draws random obstacles

	int xpixel = (column)*40; // formula for converting column into x pixels
	int ypixel = 760-(row*40); // formula for converting rows into y pixels


	DrawRectangle(xpixel,ypixel+20,40,5,colors[76]);//horizontal line (basically drawing the object)
	DrawRectangle(xpixel,ypixel+30,40,5,colors[76]);//horizontal
	DrawRectangle(xpixel,ypixel+10,40,5,colors[76]);//horizontal
	DrawRectangle(xpixel,ypixel+0,40,5,colors[76]);//horizontal
	

}
void Random_passengers(int column, int row){ // printing the passenger shape

	int xpixel = (column)*40; // formula for converting column into x pixels
	int ypixel = 760-(row*40); // formula for converting rows into y pixels

	DrawTriangle( xpixel, ypixel , (xpixel+20), (ypixel+30) , (xpixel+40) , ypixel, colors[138] ); 
	DrawCircle((xpixel+20),(ypixel+30),10, colors[17]);

}
void Random_destination(int column , int row){ // assigning random destinations to the passengers

	int xpixel = (column)*40; // formula for converting column into x pixels
	int ypixel = 760-(row*40); // formula for converting rows into y pixels

	DrawSquare (xpixel,ypixel,40,colors[30]);

}

bool flag = true;
void moveCar(int xI, int yI, char range , int lower, int upper , int carnumber) {

	if (range=='x'){
		upper-=50; // pixel error fix
		lower+=10;
		if (xI >= lower && flag) { //going left
			
			if (carnumber==1)
			car1x -= 10; 
			if (carnumber==2)
			car2x -= 10; 
			if (carnumber==3)
			car3x -= 10; 
			if (carnumber==4)
			car4x -= 10; 
			if (carnumber==5)
			car5x -= 10; 
		
			if(xI <= lower)
			flag = false;

		}
		else if (xI <= upper && !flag) { //go right
		
			if (carnumber==1)
			car1x += 10; 
			if (carnumber==2)
			car2x += 10; 
			if (carnumber==3)
			car3x += 10; 
			if (carnumber==4)
			car4x += 10; 
			if (carnumber==5)
			car5x += 10; 

			if (xI >= upper)
			flag = true;
	}
	}
	else {
		upper-=30; // pixel error adjusment
		lower+=10;
		if (yI >= lower && flag) { // go down

			if (carnumber==1)
			car1y -= 10; 
			if (carnumber==2)
			car2y -= 10; 
			if (carnumber==3)
			car3y -= 10; 
			if (carnumber==4)
			car4y -= 10; 
			if (carnumber==5)
			car5y -= 10; 
			
			if(yI <= lower)
			
			flag = false;

	}
		else if (yI <= upper && !flag) { // go up

			if (carnumber==1)
			car1y += 10; 
			if (carnumber==2)
			car2y += 10; 
			if (carnumber==3)
			car3y += 10; 
			if (carnumber==4)
			car4y += 10; 
			if (carnumber==5)
			car5y += 10; 

			if (yI >= upper)
			flag = true;
	}
	}
	glutPostRedisplay();
}

/*
 * Main Canvas drawing function.
 * */
bool menu = false;
bool color_menu = true;
bool startgame = false;
int xcoordinate=0;
int ycoordinate=0;
string StartMenu_L_clicked;
string Startleaderboard_L_clicked;
string ColorMenu_clicked;

void drawboardlines(){
	for (int i=0;i<20;i++){ // loop for printing horizontal lines (i runs 20 times because the grid is 20x20)
	DrawLine( 0 , (800-(i*40)) ,  800 , (800-(i*40)) , 0.5 , colors[138] );	// 40 pixels for each block
	}
	for (int i=0;i<20;i++){ // loop for printing vertical lines
	DrawLine( (800-(i*40)) , 800 , (800-(i*40)) , 0 , 0.5 , colors[138] );	// 40 pixels for each block
	}
}

void SetBlackTracks(){ // hardcoding each track in this scenario in a character array of 20x20 for comparison (such as collison and pattern) 
	board[2][1] = 'T';
	board[3][1] = 'T';
	board[4][1] = 'T';
	for (int i=9;i<20;i++){
		board[i][1] = 'T'; // loop for track line in the 2d row,upper right side of given figure 
	}
	board[7][1] = 'T';
	board[7][2] = 'T';
	board[7][3] = 'T';
	board[7][4] = 'T';
	board[2][5] = 'T';
	board[3][5] = 'T';
	board[5][5] = 'T';
	board[6][5] = 'T';
	board[7][5] = 'T';
	board[13][5] = 'T';
	board[14][5] = 'T';
	board[15][5] = 'T';
	for (int i=4;i<10;i++){
		board[12][i-1] = 'T'; 
	}
	for (int i=4;i<9;i++){
		board[18][i-1] = 'T'; 
	}
	board[3][7] = 'T';
	board[3][8] = 'T';
	board[9][6] = 'T';
	board[9][8] = 'T';
	for (int i=7;i<10;i++){
		board[i][9] = 'T'; 
	}
	for (int i=11;i<18;i++){
		board[5][i-1] = 'T'; 
	}
	board[2][12] = 'T';
	board[2][13] = 'T';
	board[2][14] = 'T';
	board[3][12] = 'T';
	board[3][13] = 'T';
	board[3][14] = 'T';
	board[11][11] = 'T';
	board[11][12] = 'T';
	for (int i=7;i<12;i++){
		board[i][13] = 'T'; 
	}
	for (int i=14;i<20;i++){
		board[i][12] = 'T'; 
	}
	for (int i=14;i<17;i++){
		board[14][i-1] = 'T'; 
	}
	for (int i=17;i<20;i++){
		board[9][i-1] = 'T'; 
	}
	board[17][17] = 'T';
	board[18][17] = 'T';

}
int passenger1x,passenger1y;
int passenger2x,passenger2y;
int passenger3x,passenger3y;
bool spawn= true;

void Random_passenger_on_board(){ // assigning different positions to passengers that dont spawn on buildings

	passenger1x = GetRandInRange(0,19);
	sleep(0.001);
	passenger2x = GetRandInRange(0,19);
	sleep(0.001);
	passenger3x = GetRandInRange(0,19);
	sleep(0.001);
	passenger1y = GetRandInRange(0,19);
	sleep(0.001);
	passenger2y = GetRandInRange(0,19);
	sleep(0.001);
	passenger3y = GetRandInRange(0,19);
	sleep(0.001);
	if (board[passenger1x][passenger1y]=='T') // if the passenger spawns on a building, re-assign it a new random number
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		passenger1x = GetRandInRange(0,19);
		sleep(0.001);
		passenger1y = GetRandInRange(0,19);

		if (board[passenger1x][passenger1y]=='T'){
			sleep(0.001);
			cout << "passenger spawned on block";
			passenger1x = GetRandInRange(0,19);
			sleep(0.001);
			passenger1y = GetRandInRange(0,19);

			if (board[passenger1x][passenger1y]=='T'){
				cout << "passenger spawned on block";
				sleep(0.001);
				passenger1x = GetRandInRange(0,19);
				sleep(0.001);
				passenger1y = GetRandInRange(0,19);
			}	

		}
		
	}
	if (board[passenger2x][passenger2y]=='T')
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		passenger2x = GetRandInRange(0,19);
		sleep(0.001);
		passenger2y = GetRandInRange(0,19);

		if (board[passenger2x][passenger2y]=='T')
		{
			cout << "passenger spawned on block";
			sleep(0.001);
			passenger2x = GetRandInRange(0,19);
			sleep(0.001);
			passenger2y = GetRandInRange(0,19);

			if (board[passenger2x][passenger2y]=='T')
			{
				cout << "passenger spawned on block";
				sleep(0.001);
				passenger2x = GetRandInRange(0,19);
				sleep(0.001);
				passenger2y = GetRandInRange(0,19);
			}

		}
	}
	if (board[passenger3x][passenger3y]=='T')
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		passenger3x = GetRandInRange(0,19);
		sleep(0.001);
		passenger3y = GetRandInRange(0,19);

		if (board[passenger3x][passenger3y]=='T')
		{
			cout << "passenger spawned on block";
			sleep(0.001);
			passenger3x = GetRandInRange(0,19);
			sleep(0.001);
			passenger3y = GetRandInRange(0,19);

			if (board[passenger3x][passenger3y]=='T'){
				cout << "passenger spawned on block";
				sleep(0.001);
				passenger3x = GetRandInRange(0,19);
				sleep(0.001);
				passenger3y = GetRandInRange(0,19);
			}
		}
		
	}
	else{
		cout << "all objects spawned correctly";
	}
	board[passenger1x][passenger1y] = 'x'; // assign the value of P for passenger in the board array if they dont spawn on buildings
	board[passenger2x][passenger2y] = 'y';
	board[passenger3x][passenger3y] = 'z';
}

int obstacle1x,obstacle1y;
int obstacle2x,obstacle2y;
int obstacle3x,obstacle3y;
int obstacle4x,obstacle4y;
bool obstacle_spawn= true;

void Random_obstacles_on_board(){ // assigning different positions to obstacles that dont spawn on buildings

	obstacle1x= GetRandInRange(0,19);
	sleep(0.001);
	obstacle2x = GetRandInRange(0,19);
	sleep(0.001);
	obstacle3x = GetRandInRange(0,19);
	sleep(0.001);
	obstacle4x = GetRandInRange(0,19);
	sleep(0.001);
	obstacle1y= GetRandInRange(0,19);
	sleep(0.001);
	obstacle2y = GetRandInRange(0,19);
	sleep(0.001);
	obstacle3y = GetRandInRange(0,19);
	sleep(0.001);
	obstacle4y = GetRandInRange(0,19);
	sleep(0.001);
	if (board[obstacle1x][obstacle1y]=='T' || board[obstacle1x][obstacle1y]=='P') // if the object spawns on a building or passenger, re-assign it a new random number
	{
		cout << "obstacle spawned on block";
		sleep(0.001);
		obstacle1x = GetRandInRange(0,19);
		sleep(0.001);
		obstacle1y = GetRandInRange(0,19);

		if (board[obstacle1x][obstacle1y]=='T' || board[obstacle1x][obstacle1y]=='P'){
			sleep(0.001);
			cout << "obstacle spawned on block";
			obstacle1x = GetRandInRange(0,19);
			sleep(0.001);
			obstacle1y = GetRandInRange(0,19);

			if (board[obstacle1x][obstacle1y]=='T' || board[obstacle1x][obstacle1y]=='P'){
				cout << "obstacle spawned on block";
				sleep(0.001);
				obstacle1x = GetRandInRange(0,19);
				sleep(0.001);
				obstacle1y = GetRandInRange(0,19);
			}	

		}
		
	}
	if (board[obstacle2x][obstacle2y]=='T' || board[obstacle2x][obstacle2y]=='P') // if the object spawns on a building or passenger, re-assign it a new random number
	{
		cout << "obstacle spawned on block";
		sleep(0.001);
		obstacle2x = GetRandInRange(0,19);
		sleep(0.001);
		obstacle2y = GetRandInRange(0,19);

		if (board[obstacle2x][obstacle2y]=='T' || board[obstacle2x][obstacle2y]=='P'){
			sleep(0.001);
			cout << "obstacle spawned on block";
			obstacle2x = GetRandInRange(0,19);
			sleep(0.001);
			obstacle2y = GetRandInRange(0,19);

			if (board[obstacle2x][obstacle2y]=='T' || board[obstacle2x][obstacle2y]=='P'){
				cout << "obstacle spawned on block";
				sleep(0.001);
				obstacle2x = GetRandInRange(0,19);
				sleep(0.001);
				obstacle2y = GetRandInRange(0,19);
			}	

		}
		
	}
	if (board[obstacle3x][obstacle3y]=='T' || board[obstacle3x][obstacle3y]=='P') // if the object spawns on a building or passenger, re-assign it a new random number
	{
		cout << "obstacle spawned on block";
		sleep(0.001);
		obstacle3x = GetRandInRange(0,19);
		sleep(0.001);
		obstacle3y = GetRandInRange(0,19);

		if (board[obstacle3x][obstacle3y]=='T' || board[obstacle3x][obstacle3y]=='P'){
			sleep(0.001);
			cout << "obstacle spawned on block";
			obstacle3x = GetRandInRange(0,19);
			sleep(0.001);
			obstacle3y = GetRandInRange(0,19);

			if (board[obstacle3x][obstacle3y]=='T' || board[obstacle3x][obstacle3y]=='P'){
				cout << "obstacle spawned on block";
				sleep(0.001);
				obstacle3x = GetRandInRange(0,19);
				sleep(0.001);
				obstacle3y = GetRandInRange(0,19);
			}	

		}
		
	}

	if (board[obstacle4x][obstacle4y]=='T' || board[obstacle4x][obstacle4y]=='P') // if the object spawns on a building or passenger, re-assign it a new random number
	{
		cout << "obstacle spawned on block";
		sleep(0.001);
		obstacle4x = GetRandInRange(0,19);
		sleep(0.001);
		obstacle4y = GetRandInRange(0,19);

		if (board[obstacle4x][obstacle4y]=='T' || board[obstacle4x][obstacle4y]=='P'){
			sleep(0.001);
			cout << "obstacle spawned on block";
			obstacle4x = GetRandInRange(0,19);
			sleep(0.001);
			obstacle4y = GetRandInRange(0,19);

			if (board[obstacle4x][obstacle4y]=='T' || board[obstacle4x][obstacle4y]=='P'){
				cout << "obstacle spawned on block";
				sleep(0.001);
				obstacle4x = GetRandInRange(0,19);
				obstacle4y = GetRandInRange(0,19);
			}	

		}
		
	}

	else{
		cout << "all objects spawned correctly";
	}
	board[obstacle1x][obstacle1y]='O'; // store the objects position in the board array if they dont spawn on tracks and passengers
	board[obstacle2x][obstacle2y]='O';
	board[obstacle3x][obstacle3y]='O';
	board[obstacle4x][obstacle4y]='O';
}

int destination1x,destination1y;
int destination2x,destination2y;
int destination3x,destination3y;
bool spawn_destination= true;

void Random_destination_on_board(){ // assigning different positions to destinations that dont spawn on buildings,obstacles and passengers

	destination1x = GetRandInRange(0,19);
	sleep(0.001);
	destination2x = GetRandInRange(0,19);
	sleep(0.001);
	destination3x = GetRandInRange(0,19);
	sleep(0.001);
	destination1y = GetRandInRange(0,19);
	sleep(0.001);
	destination2y = GetRandInRange(0,19);
	sleep(0.001);
	destination3y = GetRandInRange(0,19);
	sleep(0.001);

	if (board[destination1x][destination1y]=='T' || board[destination1x][destination1y]=='P' || board[destination1x][destination1y]=='O') // if the passenger spawns on a building, re-assign it a new random number
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		destination1x = GetRandInRange(0,19);
		sleep(0.001);
		destination1y = GetRandInRange(0,19);

		if (board[destination1x][destination1y]=='T' || board[destination1x][destination1y]=='P' || board[destination1x][destination1y]=='O'){
			sleep(0.001);
			cout << "passenger spawned on block";
			destination1x = GetRandInRange(0,19);
			sleep(0.001);
			destination1y = GetRandInRange(0,19);

			if (board[destination1x][destination1y]=='T' || board[destination1x][destination1y]=='P' || board[destination1x][destination1y]=='O'){
				cout << "passenger spawned on block";
				sleep(0.001);
				destination1x = GetRandInRange(0,19);
				sleep(0.001);
				destination1y = GetRandInRange(0,19);
			}	

		}
		
	}
	if (board[destination2x][destination2y]=='T' || board[destination2x][destination2y]=='P' || board[destination2x][destination2y]=='O')
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		destination2x = GetRandInRange(0,19);
		sleep(0.001);
		destination2y = GetRandInRange(0,19);

		if (board[destination2x][destination2y]=='T' || board[destination2x][destination2y]=='P' || board[destination2x][destination2y]=='O')
		{
			cout << "passenger spawned on block";
			sleep(0.001);
			destination2x = GetRandInRange(0,19);
			sleep(0.001);
			destination2y = GetRandInRange(0,19);

			if (board[destination2x][destination2y]=='T' || board[destination2x][destination2y]=='P' || board[destination2x][destination2y]=='O')
			{
				cout << "passenger spawned on block";
				sleep(0.001);
				destination2x = GetRandInRange(0,19);
				sleep(0.001);
				destination2y = GetRandInRange(0,19);
			}

		}
	}
	if (board[destination3x][destination3y]=='T' || board[destination3x][destination3y]=='P' || board[destination3x][destination3y]=='O')
	{
		cout << "passenger spawned on block";
		sleep(0.001);
		destination3x = GetRandInRange(0,19);
		sleep(0.001);
		destination3y = GetRandInRange(0,19);

		if (board[destination3x][destination3y]=='T' || board[destination3x][destination3y]=='P' || board[destination3x][destination3y]=='O')
		{
			cout << "passenger spawned on block";
			sleep(0.001);
			destination3x = GetRandInRange(0,19);
			sleep(0.001);
			destination3y = GetRandInRange(0,19);

			if (board[destination3x][destination3y]=='T' || board[destination3x][destination3y]=='P' || board[destination3x][destination3y]=='O'){
				cout << "passenger spawned on block";
				sleep(0.001);
				destination3x = GetRandInRange(0,19);
				sleep(0.001);
				destination3y = GetRandInRange(0,19);
			}
		}
		
	}
	else{
		cout << "all Destinations spawned correctly";
	}

	board[destination1x][destination1y] = 'u'; // assign the value of D for Destination in the board array if they dont spawn on buildings
	board[destination2x][destination2y] = 'v';
	board[destination3x][destination3y] = 'x';
}



void drawtracks(){
	for (int i=0;i<20;i++){ // i = columns
		for (int j=0;j<20;j++){ // j= rows
			if (board[i][j]=='T'){ // if on array index, there is a track then draw it
				DrawRectangle((i*40),(760-(j*40)),40,41,colors[138]); // formula for the cooridinates of each track block
			}
		}
	}
}

void GameDisplay()/**/{
	
	
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	if (!menu){ // pop up menu 
	DrawRoundRect(300 , 360 , 200 , 80 , colors[80] ,5); 
	DrawString(322, 390 , "START GAME" , colors[8]);
	DrawRoundRect(300 , 260 , 200 , 80 , colors[27] ,5); 
	DrawString(310, 290 , "LEADER BOARD" , colors[8]);
		if ((StartMenu_L_clicked == "left Button Pressed")) //range of the start game box in menu
		{
			menu = true; // if a user clicks on a button then move to next page (stop showing menu)
			color_menu = false;	
		}
		if (((Startleaderboard_L_clicked == "left Button Pressed"))){
		
			DrawSquare(0,0,801,colors[185]); // The leaderboard hasnt been completed yet 
			ofstream write_score;
			write_score.open("Highscore.txt");
			string characters;
			int hscore = 0 ;
			ifstream score_read; // reads from file
			score_read.open("Highscore.txt"); // creating stream
			DrawString(10, 775, to_string(hscore), colors[137]);
			
		}
	
	}
	if (!(color_menu)){
		DrawRoundRect(275 , 560 , 250 , 80 , colors[45] ,5); // drawing rectangle
		DrawString(285, 590 , "PICK A TAXI COLOR" , colors[CYAN]); // writing text on screen for color selecton options
		DrawCircle(185,225,50,colors[5]);
		DrawCircle(615,225,50,colors[22]);
		if (ColorMenu_clicked == "RED"){ // checking which color user selects
			TaxiColor = "RED";
			cout << "Enter Name : "; // once the user enters an option, they will type their NAME
			cin >> name;
			color_menu = true; // exit from this menu
			startgame = true; // game will only start once the user has selected a taxi color
		}
		if(ColorMenu_clicked == "YELLOW"){
			TaxiColor = "YELLOW";
			cout << "Enter Name : "; // once the user enters an option, they will type their NAME
			cin >> name;
			color_menu = true; // exit from this menu
			startgame = true; // game will only start once the user has selected a taxi color
		}
		
	}
	if (winner==true){ // if you win then show the winner menu

		DrawSquare(0,0,801,colors[138]);
		DrawString(340,560,"CONGRATS",colors[137]);
		DrawString(245,375,name,colors[1]); 
		DrawString(340,375,"YOU WIN",colors[137]);
		

	}

	if(startgame){ // game will only start when user enters a name and selects a taxi color
	
	drawboardlines();
	SetBlackTracks();
	drawtracks();
	DrawString( 15, 770, "Score=", colors[66]);
	DrawString( 87, 770, to_string(score) , colors[66]);
	countdown(); // shows the coutdown
	if (spawn==true){
		Random_passenger_on_board(); // assign random locations (this function runs only 1 time)
		spawn = false;
	}
	Random_passengers(passenger1x,passenger1y);
	Random_passengers(passenger2x,passenger2y);
	Random_passengers(passenger3x,passenger3y);

	if (obstacle_spawn==true){
		Random_obstacles_on_board();
		obstacle_spawn = false;
	}

	Random_obstacle(obstacle1x,obstacle1y); // prints Random obstacles
	Random_obstacle(obstacle2x,obstacle2y);
	Random_obstacle(obstacle3x,obstacle3y);
	Random_obstacle(obstacle4x,obstacle4y);

	if (spawn_destination==true){ // spawn random destinations
		Random_destination_on_board(); // this runs only 1 time
		spawn_destination = false;
	}

	if ((flag1==false) && (test1==true) ){ // if the user has picked the 1st passenger then show 1st destination
		Random_destination(destination1x,destination1y);
		//if (destination_flag1==false){
			//test1 = false;
		//}
	}
	if ((flag2==false) && (test2==true)){ // if the user has picked the 2st passenger then show 2st destination
		Random_destination(destination2x,destination2y);

		//if (destination_flag2==false){
		//	test2 = false;	
		//}	
	}
	if ((flag3==false) && (test3==true)){
		Random_destination(destination3x,destination3y);

		//if (destination_flag3==false){
		//	test3 = false;	
		//}	
	}

	if (refresh==false){ // once all passengers are picked up , respawn new passengers with new destinations
		spawn = true;
		spawn_destination = true;
		flag1 = true; // for first passenger
		flag2 = true; // for second passenger
		flag3 = true; // for third passenger
		destination_flag1 = true; // for first destination
		destination_flag2 = true;	// for 2nd destination
		destination_flag3 = true;	// for 3rd destination
		refresh = true;
	}
	if (score==50){ // when the user reaches 50 points the game ends
		cout << "you win";
		winner = true;
		startgame = false;
	}

	Random_drawCar(car1x,car1y,47); // draws first lower bottom aqua car 
	Random_drawCar(car2x,car2y,31); // draws green left car
	Random_drawCar(car3x,car3y,2); // brown car
	Random_drawCar(car4x,car4y,15); // orange car
	Random_drawCar(car5x,car5y,91); // pink car

	drawCar(); // draws the user car
	}

	glutSwapBuffers(); // do not modify this line..
	

}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) { // this function is used to detect if the car collides with another obstacle
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if (!(xI>=10)){ // boundry check
			xI -= 0;
		}
		else if ((yI>=(40-10) && yI<=(80-10)) && ((xI>=(360) && xI<=400) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(80-10) && yI<=(120-10)) && ((xI>=(680) && xI<=760) || (xI>=(360) && xI<=400) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(720-10) && yI<=(760-10)) && ((xI>=(80) && xI<=200) || (xI>=(280) && xI<=800) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(680-10) && yI<=(720-10)) && ((xI>=(280) && xI<=320))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(600-10) && yI<=(680-10)) && ((xI>=(280) && xI<=320) || (xI>=(480) && xI<=520) || (xI>=(720) && xI<=760))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(560-10) && yI<=(600-10)) && ((xI>=(80) && xI<=160) || (xI>=(200-40) && xI<=320) || (xI>=(480) && xI<=600) || (xI>=(720) && xI<=760))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(520-10) && yI<=(560-10)) && ((xI>=(360) && xI<=400) || (xI>=(480) && xI<=520) || (xI>=(720) && xI<=760))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(480-10) && yI<=(520-10)) && ((xI>=(120) && xI<=160) || (xI>=(480) && xI<=520) || (xI>=(720) && xI<=760))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(440-10) && yI<=(480-10)) && ((xI>=(120) && xI<=160) || (xI>=(360) && xI<=400) || (xI>=(480) && xI<=520))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(400-10) && yI<=(440-10)) && ((xI>=(280) && xI<=400))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(360-10) && yI<=(400-10)) && ((xI>=(200) && xI<=240))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(320-10) && yI<=(360-10)) && ((xI>=(200) && xI<=240) || (xI>=(440) && xI<=480) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(280-10) && yI<=(320-10)) && ((xI>=(80) && xI<=160) || (xI>=(200) && xI<=(240)) || (xI>=(440) && xI<=(480)) || (xI>=(560) && xI<=(800)) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(240-10) && yI<=(280-10)) && ((xI>=(200) && xI<=240) ||(xI>=(80) && xI<=160) || (xI>=(280) && xI<=480) || (xI>=(560) && xI<=600) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(200-10) && yI<=(240-10)) && ((xI>=(80) && xI<=160) || (xI>=(200) && xI<=240) || (xI>=(560) && xI<=600) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(160-10) && yI<=(200-10)) && ((xI>=(200) && xI<=240) || (xI>=(560) && xI<=600) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(120-10) && yI<=(160-10)) && ((xI>=(200) && xI<=240) || (xI>=(360) && xI<=400) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else{
			if (TaxiColor=="RED"){ // this determines the different speed of user selected car
			xI -= 10;
			}
			if (TaxiColor=="YELLOW"){ // yellow car moves faster
			xI -= 20;	
			}
		}

	} else if (key
		
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

		if (!(xI<=750)){ // boundry check
			xI -= 0;
		}	
		else if ((yI>=(720-10) && yI<=(760-10)) && ((xI>=(80-40) && xI<=200-1) || (xI>=(360-40) && xI<=800-1) || (xI>=(280-40) && xI<=320-1) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(680-10) && yI<=(720-10)) && ((xI>=(280-40) && xI<=320-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(600-10) && yI<=(680-10)) && ((xI>=(280-40) && xI<=320-1) || (xI>=(480-40) && xI<=520-1) || (xI>=(720-40) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(560-10) && yI<=(600-10)) && ((xI>=(80-40) && xI<=160-1) || (xI>=(200-40) && xI<=320-1) || (xI>=(480-40) && xI<=600-1) || (xI>=(720-40) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(520-10) && yI<=(560-10)) && ((xI>=(360-40) && xI<=400-1) || (xI>=(480-40) && xI<=520-1) || (xI>=(720-40) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(480-10) && yI<=(520-10)) && ((xI>=(120-40) && xI<=160-1) || (xI>=(480-40) && xI<=520-1) || (xI>=(720-40) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(440-10) && yI<=(480-10)) && ((xI>=(120-40) && xI<=160-1) || (xI>=(360-40) && xI<=400-1) || (xI>=(480-40) && xI<=520-1))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(400-10) && yI<=(440-10)) && ((xI>=(280-40) && xI<=400-5))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(360-10) && yI<=(400-10)) && ((xI>=(200-40) && xI<=240-5))){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(320-10) && yI<=(360-10)) && ((xI>=(200-40) && xI<=240-5) || (xI>=(440-40) && xI<=480-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(280-10) && yI<=(320-10)) && ((xI>=(80-40) && xI<=160-5) || (xI>=(200-40) && xI<=(240-5)) || (xI>=(440-40) && xI<=(480-5)) || (xI>=(560-40) && xI<=(800-5)) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(240-10) && yI<=(280-10)) && ((xI>=(200-40) && xI<=240-5) ||(xI>=(80-40) && xI<=160-5) || (xI>=(280-40) && xI<=480-5) || (xI>=(560-40) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(200-10) && yI<=(240-10)) && ((xI>=(80-40) && xI<=160-5) || (xI>=(200-40) && xI<=240-5) || (xI>=(560-40) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(160-10) && yI<=(200-10)) && ((xI>=(200-40) && xI<=240-5) || (xI>=(560-40) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(120-10) && yI<=(160-10)) && ((xI>=(200-40) && xI<=240-5) || (xI>=(360-40) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(80-10) && yI<=(120-10)) && ((xI>=(680-40) && xI<=760-5) || (xI>=(360-40) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else if ((yI>=(40-10) && yI<=(80-10)) && ((xI>=(360-40) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			xI -= 0;
			
		}
		else{
			if (TaxiColor=="RED"){
			xI += 10;
			}
			if (TaxiColor=="YELLOW"){
			xI += 20;	
			}
		}
		
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		if (!(yI<=770)){ // boundry check
			yI -= 0;
		}
		else if ((yI>=(720-20) && yI<=(760-10)) && ((xI>=(80-35) && xI<=200-1) || (xI>=(360-35) && xI<=800-1) || (xI>=(280-35) && xI<=320-1) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(680-20) && yI<=(720-10)) && ((xI>=(280-35) && xI<=320-5))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(600-20) && yI<=(680-10)) && ((xI>=(280-35) && xI<=320-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(560-20) && yI<=(600-10)) && ((xI>=(80-35) && xI<=160-1) || (xI>=(200-35) && xI<=320-1) || (xI>=(480-35) && xI<=600-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(520-20) && yI<=(560-10)) && ((xI>=(360-35) && xI<=400-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(480-20) && yI<=(520-10)) && ((xI>=(120-35) && xI<=160-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(440-20) && yI<=(480-10)) && ((xI>=(120-35) && xI<=160-1) || (xI>=(360-35) && xI<=400-1) || (xI>=(480-35) && xI<=520-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(400-20) && yI<=(440-10)) && ((xI>=(280-35) && xI<=400-5))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(360-20) && yI<=(400-10)) && ((xI>=(200-35) && xI<=240-5))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(320-20) && yI<=(360-10)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(440-35) && xI<=480-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(280-20) && yI<=(320-10)) && ((xI>=(80-35) && xI<=160-5) || (xI>=(200-35) && xI<=(240-5)) || (xI>=(440-35) && xI<=(480-5)) || (xI>=(560-35) && xI<=(800-5)) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(240-20) && yI<=(280-10)) && ((xI>=(200-35) && xI<=240-5) ||(xI>=(80-35) && xI<=160-5) || (xI>=(280-35) && xI<=480-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(200-20) && yI<=(240-10)) && ((xI>=(80-35) && xI<=160-5) || (xI>=(200-35) && xI<=240-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(160-20) && yI<=(200-10)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(120-20) && yI<=(160-10)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(360-35) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(80-20) && yI<=(120-10)) && ((xI>=(680-35) && xI<=760-5) || (xI>=(360-35) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(40-20) && yI<=(80)) && ((xI>=(360-35) && xI<=400-1) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else{
			if (TaxiColor=="RED"){
			yI += 10;
			}
			if (TaxiColor=="YELLOW"){
			yI += 20;	
			}
		}
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if (!(yI>=10)){ // boundry check
			yI -= 0;
		}
		else if ((yI>=(720-10) && yI<=(760)) && ((xI>=(80-35) && xI<=200-1) || (xI>=(360-35) && xI<=800-1) || (xI>=(280-35) && xI<=320-1) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(680-10) && yI<=(720)) && ((xI>=(280-35) && xI<=320-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(600-10) && yI<=(680)) && ((xI>=(280-35) && xI<=320-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(560-10) && yI<=(600)) && ((xI>=(80-35) && xI<=160-1) || (xI>=(200-35) && xI<=320-1) || (xI>=(480-35) && xI<=600-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(520-10) && yI<=(560)) && ((xI>=(360-35) && xI<=400-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(480-10) && yI<=(520)) && ((xI>=(120-35) && xI<=160-1) || (xI>=(480-35) && xI<=520-1) || (xI>=(720-35) && xI<=760-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(440-10) && yI<=(480)) && ((xI>=(120-35) && xI<=160-1) || (xI>=(360-35) && xI<=400-1) || (xI>=(480-35) && xI<=520-1))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(400-10) && yI<=(440)) && ((xI>=(280-35) && xI<=400-5))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(360-10) && yI<=(400)) && ((xI>=(200-35) && xI<=240-5))){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(320-10) && yI<=(360)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(440-35) && xI<=480-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(280-10) && yI<=(320)) && ((xI>=(80-35) && xI<=160-5) || (xI>=(200-35) && xI<=(240-5)) || (xI>=(440-35) && xI<=(480-5)) || (xI>=(560-35) && xI<=(800-5)) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(240-10) && yI<=(280)) && ((xI>=(200-35) && xI<=240-5) ||(xI>=(80-35) && xI<=160-5) || (xI>=(280-35) && xI<=480-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(200-10) && yI<=(240)) && ((xI>=(80-35) && xI<=160-5) || (xI>=(200-35) && xI<=240-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(160-10) && yI<=(200)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(560-35) && xI<=600-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(120-10) && yI<=(160)) && ((xI>=(200-35) && xI<=240-5) || (xI>=(360-35) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(80-10) && yI<=(120)) && ((xI>=(680-35) && xI<=760-5) || (xI>=(360-35) && xI<=400-5) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else if ((yI>=(40-10) && yI<=(80)) && ((xI>=(360-35) && xI<=400-1) )){ // if track is matching with cars position, then dont allow it to move right
			yI -= 0;
			
		}
		else{
			if (TaxiColor=="RED"){
			yI -= 10;
			}
			if (TaxiColor=="YELLOW"){
			yI -= 20;	
			}
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */


void PrintableKeys(unsigned char key, int x, int y) {
	int car_column,car_row;
	car_column =(xI/40); // convert x pixels to column
	car_row = 19-((yI/40)); // convert y pixels to row
	cout << "car column  " << car_column << endl;
	cout << "car Row  " << car_row << endl; 
	if (key == 27/* Escape key ASCII*/) { // pressing the escape button quits the game
		exit(1); // exit the program when escape key is pressed.
	}
	
	if (key == 32) // ASCII Code of Space Bar
	{
		cout << "Space Pressed" << endl;
		if (flag1==true){ // using this if statement ensures that we dont get Core Dump (Segmentation fault) 

			if ( ( ( board[car_column+1][car_row] == board[passenger1x][passenger1y] ) || ( board[car_column-1][car_row] == board[passenger1x][passenger1y] ) || ( board[car_column][car_row+1] == board[passenger1x][passenger1y] ) || ( board[car_column][car_row-1] == board[passenger1x][passenger1y] ) ) && (flag1) ) // check if a passenger is nearby when the user presses SPACE
			{
			
			passenger1x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
			flag1 = false;

			}
		}
		if (flag2==true) // using this if statement ensures that we dont get Core Dump (Segmentation fault) 
		{

			if ( ( ( board[car_column+1][car_row] == board[passenger2x][passenger2y] ) || ( board[car_column-1][car_row] == board[passenger2x][passenger2y] ) || ( board[car_column][car_row+1] == board[passenger2x][passenger2y] ) || ( board[car_column][car_row-1] == board[passenger2x][passenger2y] ) ) && (flag2) ) // check if a passenger is nearby when the user presses SPACE
			{
			
			passenger2x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
			flag2 = false;

			}
			
		}
		else
		{

			if (flag3==true){

				if ( ( ( board[car_column+1][car_row] == board[passenger3x][passenger3y] ) || ( board[car_column-1][car_row] == board[passenger3x][passenger3y] ) || ( board[car_column][car_row+1] == board[passenger3x][passenger3y] ) || ( board[car_column][car_row-1] == board[passenger3x][passenger3y] ) ) && (flag3) ) // check if a passenger is nearby when the user presses SPACE
				{
				
				passenger3x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
				flag3 = false;

				}
			}
		}

			if (destination_flag1==true){

				if (  ( board[car_column][car_row] == board[destination1x][destination1y] ) && (destination_flag1) ) // check if a passenger is nearby when the user presses SPACE
				{
				
				destination1x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
				destination_flag1 = false;
				score+=10;

				}
			}

			if (destination_flag2==true){

				if ( (( board[car_column][car_row] == board[destination2x][destination2y] )) && (destination_flag2) ) // check if a passenger is nearby when the user presses SPACE
				{
				
				destination2x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
				destination_flag2 = false;
				score+=10;
				}
			}

			if (destination_flag3==true){

				if ( ( ( board[car_column][car_row] == board[destination3x][destination3y] )) && (destination_flag3) ) // check if a passenger is nearby when the user presses SPACE
				{
				
				destination3x+=1000; // to make the passenger dissapear from the map, assign it a value greater than the window resolution (basically kicking it out from the map)
				destination_flag3 = false;
				score+=10;
				refresh = false;
				}
			}		
	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
int car_speed = 210; //speed of random cars on board
bool speed1=true;
bool speed2=true;	
void Timer(int m) {
	// implement your functionality here
	

	moveCar(car1x,car1y,'y',0, 200 ,1); // move function for first car
	moveCar(car2x,car2y,'x',0,280,2); // move function car for second car
	moveCar(car3x,car3y,'y',480,720,3); // move function for 3rd car
	moveCar(car4x,car4y,'x',400,560,4); // move function for 4th car
	moveCar(car5x,car5y,'y',320,680,5); // move function for 5th car
	// once again we tell the library to call our Timer function after next 1000/FPS
	if ( score==20 && speed1 ){ // if 2 drops are made secessfully then, increase speed of car
		car_speed-=100;
		speed1 = false;
	}
	if ( score==40 && speed2 ){
		car_speed-=100; // increasing speed of oponents cars
		speed2 = false;
	}
	glutTimerFunc(car_speed, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	y=800-y;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	y=800-y;
	xcoordinate=x; // store these coordinates in a variable for comparison
	ycoordinate=y;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	y=800-y; // the value of y is inverted (it should be 0 at the bottom but instead it shows 800) so we fix this 
	StartMenu_L_clicked=""; // reinitialize this button everytime new
	ColorMenu_clicked="";
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		//cout << "left Button Pressed"<< endl;
		if ((xcoordinate >= 300 && xcoordinate <= 500) && (ycoordinate>=360 && ycoordinate<=440)){ // range for menu button
		StartMenu_L_clicked = "left Button Pressed";
		}
		if ((xcoordinate >= 300 && xcoordinate <= 500) && (ycoordinate>=260 && ycoordinate<=340)){ // coordinate ranges for leaderboard button
		Startleaderboard_L_clicked = "left Button Pressed";
		}
		if (color_menu==false){
			if ((xcoordinate >= 145 && xcoordinate <= 227) && (ycoordinate>=195 && ycoordinate<=250)){ //range for left red circle
				ColorMenu_clicked = "RED";
			}
			if ((xcoordinate >= 573 && xcoordinate <= 665) && (ycoordinate>=195 && ycoordinate<=250)){ //range for right yellow circle
				ColorMenu_clicked = "YELLOW";
			}
		}	
		
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			//cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 800, height = 800; // i have set my window size to be 800 x 800
	
	InitRandomizer(); // seed the random number generator...
	
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */


