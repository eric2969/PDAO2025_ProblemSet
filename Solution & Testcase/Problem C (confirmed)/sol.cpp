//check whether the general can move in chinese chess
#include <bits/stdc++.h>
using namespace std;

// const int EMPTY = 0;
// const int ATTACKED = 1;
// const int FORBIDDEN = 2;
char board[10][10];
uint8_t pinned[10][10] = {0};
uint8_t attacked[10][10] = {0}; //threatMap
uint8_t blockableCount[10][10] = {0};
uint8_t forbidden[10][10] = {0};
typedef pair<int,int> Point;
//bool failed = false;

Point operator+(const Point p1, const Point p2) { //operator overloading
    return Point(p1.first + p2.first, p1.second + p2.second);
}
void operator+=(Point &p1, const Point p2) { //operator overloading
    p1.first += p2.first;
    p1.second += p2.second;
}
Point operator-(const Point p1, const Point p2) { //operator overloading
    return Point(p1.first - p2.first, p1.second - p2.second);
}
void operator-=(Point &p1, const Point p2) { //operator overloading
    p1.first -= p2.first;
    p1.second -= p2.second;
}

Point bGeneral, rGeneral;
Point horse[8] = { {2,1},{2,-1},{-2,1},{-2,-1},{1,2},{-1,2},{1,-2},{-1,-2} },
	cripple[8] = { {1,0},{1,0},{-1,0},{-1,0},{0,1},{0,1},{0,-1},{0,-1} };
Point elephant[4] = { {2,2},{2,-2},{-2,2},{-2,-2} },
      blocking[4] = { {1,1},{1,-1},{-1,1},{-1,-1} };
Point dir[4] = { {1,0},{-1,0},{0,1},{0,-1} };
vector<Point> troubles; //directThreats
vector<Point> blacks, reds;

void printBoard(uint8_t board[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            cout << int(board[i][j]);
        }
        cout << "\n";
    }
}
void printBoard(){
    for(int i=0;i<10;i++){
        for(int j=0;j<9;j++){
            cout << board[i][j];
        }
        cout << "\n";
    }
}
bool inBoard(const Point p){
    return !(p.first < 0 || p.first > 8 || p.second < 0 || p.second > 9);
}
bool inPalace(Point p){
    return (p.first >= 3 && p.first <= 5 && ((p.second >= 0 && p.second <= 2 )||( p.second >= 7 && p.second <= 9)));
}
void attack(const Point p, const Point attacker){
    if(!inBoard(p)) return;
    attacked[p.second][p.first] = 1;
    if(p == bGeneral) {
        troubles.push_back(attacker);
        switch (board[attacker.second][attacker.first]){
        case 'h':{
            blockableCount[attacker.second][attacker.first]++;
            Point d = p - attacker;
            int index = find(horse, horse+8, d) - horse;
            d = attacker + cripple[index];
            blockableCount[d.second][d.first]++;
            break;
        }
        case 'c': {
            Point d = p - attacker;
            if(d.first != 0) d.first = (d.first > 0? 1: -1);
            if(d.second != 0) d.second = (d.second > 0? 1: -1);
            Point dest = attacker;
            while(dest != p){
                if(board[dest.second][dest.first] == '.') blockableCount[dest.second][dest.first]++;
                dest += d;
            }
            break;
        }
        case 'r':{
            Point d = p - attacker;
            if(d.first != 0) d.first = (d.first > 0? 1: -1);
            if(d.second != 0) d.second = (d.second > 0? 1: -1);
            Point dest = attacker;
            while(dest != p){
                blockableCount[dest.second][dest.first]++;
                dest += d;
            }
            break;
        }
        case 'p':{
            blockableCount[attacker.second][attacker.first]++;
            break;
        }
        default:
            break;
        }
    }
}

void mark(const Point p){
    char c = board[p.second][p.first];
    if(c == '.') return;
    bool red=1;
    if(isupper(c)) red=0;
    Point forward = (red? make_pair(0,-1): make_pair(0,1));
    c = tolower(c);
    
    switch(c){
        case 'p':{
            Point dest = p + forward;
            attack(dest,p);
            if((red? p.second <= 4 : p.second >= 5)){ //crossed the river
                dest = p+ make_pair(1,0);
                attack(dest,p);
                dest = p+ make_pair(-1,0);
                attack(dest,p);
            }
            break;
        }
        case 'c':{
            Point dest;
            for(int i=0;i<4;i++){
                dest = p;
                dest += dir[i];
                while(inBoard(dest) && board[dest.second][dest.first] == '.') dest += dir[i];
                if(dest == bGeneral) {
                    dest = p + dir[i];
                    while(dest != bGeneral) {
                        forbidden[dest.second][dest.first] = 1;
                        dest += dir[i];
                    }
                    continue;
                }
                dest += dir[i];
                while(inBoard(dest) && (board[dest.second][dest.first] == '.' || dest == bGeneral)){
                    attack(dest,p);
                    dest += dir[i];
                }
                attack(dest,p);
                //pin
                if(!inBoard(dest)) continue;
                Point tar = dest;
                dest += dir[i];
                while(inBoard(dest) && board[dest.second][dest.first] == '.') dest += dir[i];
                if(dest == bGeneral) pinned[tar.second][tar.first] = 1;
            }

            break;
        }
        case 'h':{
            for(int i=0;i<8;i++){
                Point criPoint = p+cripple[i];
                Point dest = p+horse[i];
                if(!inBoard(dest)) continue;
                if(board[criPoint.second][criPoint.first] == '.') attack(dest,p);
                else if(dest == bGeneral) pinned[criPoint.second][criPoint.first] = 1; //pin
            }
            break;
        }
        case 'r':{
            Point dest;
            for(int i=0;i<4;i++){
                dest = p;
                dest += dir[i];
                while(inBoard(dest) && (board[dest.second][dest.first] == '.'|| dest == bGeneral)) {
                    attack(dest,p);
                    dest += dir[i];
                }
                attack(dest,p);
                //pin
                Point tar = dest;
                dest += dir[i];
                while(inBoard(dest) && board[dest.second][dest.first] == '.') dest += dir[i];
                if(dest == bGeneral) pinned[tar.second][tar.first] = 1;
            }
            break;
        }   
        case 'g':{
            Point dest = p;
            dest+=forward;
            while(board[dest.second][dest.first] == '.'){
                attack(dest,p);
                dest+=forward;
            }
            // if(p == bGeneral) {
            //     failed = true;
            //     return;
            // }
            attack(dest,p);
            //pin
            if(p.first == bGeneral.first){
                Point tar = dest;
                dest += forward;
                while(board[dest.second][dest.first] == '.') dest += forward;
                if(dest == bGeneral) pinned[tar.second][tar.first] = 1;
            }
            break;
        }
        default:
            return;
    }
}
bool test(Point dest, Point src){
    if(!inBoard(dest)) return false;
    char tmp = board[dest.second][dest.first];
    board[dest.second][dest.first] = board[src.second][src.first];
    board[src.second][src.first] = '.';
    for(int i=0;i<10;i++) memset(attacked[i],0,sizeof(attacked[i]));
    for(Point p:reds) mark(p);
    //printBoard();
    //cout << endl;
    board[src.second][src.first] = board[dest.second][dest.first];
    board[dest.second][dest.first] = tmp;
    return !attacked[bGeneral.second][bGeneral.first];
}
bool isWin(){
    
    for(int i=0;i<4;i++) {
        Point dest = bGeneral+dir[i];
        //if(failed) return false; 
        if(inPalace(dest) && !isupper(board[dest.second][dest.first]) && !attacked[dest.second][dest.first]) return false;
    }
    for(int i=0;i<10;i++) memset(attacked[i],0,sizeof(attacked[i]));
    for(Point p:blacks) mark(p);
    mark(bGeneral);
    if(attacked[rGeneral.second][rGeneral.first]) return false;

    for (Point p : blacks) {
        char c = board[p.second][p.first];
        c = tolower(c);
        switch(c){
            case 'p':{
                Point dest = p+make_pair(0,1);
                if(!isupper(board[dest.second][dest.first]) && test(dest,p)) return false;
                if(p.second > 4){ //crossed the river
                    dest = p+make_pair(-1,0);
                    if(!isupper(board[dest.second][dest.first]) && test(dest,p)) return false;
                    dest = p+make_pair(1,0);
                    if(!isupper(board[dest.second][dest.first]) && test(dest,p) ) return false;
                }
                break;
            }
            case 'c':{
                Point dest;
                for(int i=0;i<4;i++){
                    dest = p;
                    dest += dir[i];
                    while(inBoard(dest) && board[dest.second][dest.first] == '.') {
                        if(test(dest,p)) return false;
                        dest += dir[i];
                    }
                    dest += dir[i];
                    while(inBoard(dest) && board[dest.second][dest.first] == '.'){
                        dest += dir[i];
                    }
                    if(inBoard(dest) && islower(board[dest.second][dest.first]) && test(dest,p)) return false;
                }
    
                break;
            }
            case 'h':{
                for(int i=0;i<8;i++){
                    Point criPoint = p+cripple[i];
                    Point dest = p+horse[i];
                    if(!inBoard(dest)) continue;
                    if(board[criPoint.second][criPoint.first] == '.' && test(dest,p)) return false;
                }
                break;
            }
            case 'r':{
                Point dest;
                for(int i=0;i<4;i++){
                    dest = p;
                    dest += dir[i];
                    while(inBoard(dest) && board[dest.second][dest.first] == '.'){
                        if(test(dest,p)) return false;
                        dest += dir[i];
                    }
                    if(inBoard(dest) && islower(board[dest.second][dest.first]) && test(dest,p)) return false;
                }
                break;
            }   
            case 'e':{
                for(int i=0;i<4;i++){
                    Point criPoint = p+blocking[i];
                    Point dest = p+elephant[i];
                    if(!inBoard(dest) || dest.second >= 5 || isupper(board[dest.second][dest.first])) continue;
                    if(board[criPoint.second][criPoint.first] == '.' && test(dest,p)) return false;
                }
                break;
            }
            case 's':{
                for(int i=0;i<4;i++){
                    Point dest = p+blocking[i]; //just a coincidence
                    if(!inBoard(dest) || !inPalace(dest)) continue;
                    if(!isupper(board[dest.second][dest.first]) && test(dest,p)) return false;
                }
                break;
            }
            default:
                string msg = "Unknown piece: ";
                msg += c;
                throw range_error(msg);
                return false;
        }
    }
    return true;
}
int main(){
    for (int i=0;i<10;i++){
        cin.getline(board[i],10);
        for(int j=0;j<9;j++){
            if(board[i][j] == 'g') rGeneral = {j,i};
            if(board[i][j] == 'G') bGeneral = {j,i};
            else if(isupper(board[i][j])) blacks.push_back({j,i});
            else if(islower(board[i][j])) reds.push_back({j,i});
        }
    }
    for (Point p : reds) mark(p);
    cout << (isWin()?"Yes":"No") << "\n"; 
    return 0;
}