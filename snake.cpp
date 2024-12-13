#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;
#define MAX_LENGTH 1000

const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_LEFT='L';
const char DIR_RIGHT='R';

int consolewidth,consoleheight;

void screen(){
    HANDLE hconsole =GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO c;
    GetConsoleScreenBufferInfo(hconsole,&c);
    consoleheight=c.srWindow.Bottom-c.srWindow.Top+1;
    consolewidth=c.srWindow.Right-c.srWindow.Left+1; 
}

struct point{
    int x;
    int y;
    point(){
    }
    point(int xx,int yy){
        x=xx;
        y=yy;
    }
};

class snake{
    int l;
    char d;
public:
    point body[MAX_LENGTH];
    snake(int xx,int yy){
        l=1;
        body[0]=point(xx,yy);
        d=DIR_RIGHT;
    }
    ~snake(){
        delete[] body;
    }

    int getl(){
        return l;
    }

    void changed(char newd){
        if(newd==DIR_UP && d!=DIR_DOWN){
                d=newd;
        }
        else if(newd==DIR_DOWN && d!=DIR_UP){
                d=newd;
        }
        else if(newd==DIR_RIGHT && d!=DIR_LEFT){
                d=newd;
        }
        else if(newd==DIR_LEFT && d!=DIR_RIGHT){
                d=newd;
        }
}

    bool move(point food){
        for(int i=l-1;i>0;i--){
            body[i]=body[i-1];
        }
        switch(d){
            int val;
            case DIR_UP:
                val=body[0].y;
                body[0].y=val-1;
                break;
            case DIR_DOWN:
                val=body[0].y;
                body[0].y=val+1;
                break;
            case DIR_LEFT:
                val=body[0].x;
                body[0].x=val-1;
                break;
            case DIR_RIGHT:
                val=body[0].x;
                body[0].x=val+1;
                break;        
        }
        for(int i=1;i<l;i++){
            if(body[0].x==body[i].x && body[0].y==body[i].y){
                return false;
            }
        }
        if(food.x==body[0].x && food.y==body[0].y){
            body[l]=point(body[l-1].x,body[l-1].y);
            l++;
        }
        return true;
    }
};

class board{
    snake *s;
    const char SNAKE_BODY='O';
    point food;
    const char FOOD='0';
    int score;
public:
    board(){
        spawnfood();
        s=new snake(10,10);
        score=0;
    }
    ~board(){
        delete s;
    }
    int getscore(){
        return score;
    }
    void spawnfood(){
        int xx=rand()%consolewidth;
        int yy=rand()%consoleheight;
        food=point(xx,yy);
    }

    void displayscore(){
        gotoxy(consolewidth/2,0);
        cout<<"CURRENT SCORE: "<<score;
    }
    void gotoxy(int xx,int yy){
        COORD c;
        c.X=xx;
        c.Y=yy;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }
    void draw(){
        system("cls");
        for(int i=0;i<s->getl();i++){
            gotoxy(s->body[i].x,s->body[i].y);
            cout<<SNAKE_BODY;
        }
        gotoxy(food.x,food.y);
        cout<<FOOD;
        displayscore();
    }
    bool update(){
        bool isalive=s->move(food);
        if(isalive==false){
            return false;
        }
        if(food.x==s->body[0].x && food.y==s->body[0].y){
            score++;
            spawnfood();
        }
        return true;
    }
    void getinput(){
        if(kbhit()){
            int key=getch();
            if(key=='w' || key=='W'){
                s->changed(DIR_UP);
            }
            else if(key=='a' || key=='A'){
                s->changed(DIR_LEFT);
            }
            else if(key=='d' || key=='D'){
                s->changed(DIR_RIGHT);
            }
            else if(key=='s' || key=='S'){
                s->changed(DIR_DOWN);
            }
        }
    }   
};

int main(){
    srand(time(0));
    screen();
    board * b=new board();
    while(b->update()){
        b->getinput();
        b->draw();
        Sleep(100);
    }
    cout<<"GAME OVER"<<endl;
    cout<<"FINAL SCORE IS :"<<b->getscore();
    return 0;
}