#include <vector>
#include <string>

#include <cstdio>

#include <iostream>

using namespace std;

/*
Xmas tree
     **
    *  *
   *    *
  *      *
 *        *
************
    ****
    ****
    ****

5W 2F
4W 1F 2W 1F
3W 1F 4W 1F
2W 1F 6W 1F
1W 1F 8W 1F
12F
4W 4F 
4W 4F 
4W 4F 
*/

//First step - define a command
struct command {
    command(char count, char pencil) : 
        count(count), pencil(pencil) { }
    char count;
    char pencil;
};

void draw_cmd(const command &cmd) {
    if( cmd.count == 0 ) {
        putc(10, stdout);
    }
    for(int i=0; i < cmd.count; ++i) {
        putc(cmd.pencil, stdout);
    }
}

void draw(const vector<command> &img) {
    for(auto &c : img)
        draw_cmd(c);
}

vector<command> load(const string &img) {
    vector<command> v;
    for(auto it = img.begin(); it != img.end(); ++it) {
        char count = (*it) - '0';
        ++it;
        char pencil = *it;
        v.push_back(command(count, pencil));
    }
    return std::move(v);
}

int main() {
    
string img = 
    "5 2*00"
    "4 1*2 1*00"
    "3 1*4 1*00"
    "2 1*6 1*00"
    "1 1*8 1*00"
    "<*00"
    "4 4*00"
    "4 4*00"
    "4 4*00";
    
    auto v = load(img);
    draw(v);

    return 0;
}