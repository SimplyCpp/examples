#include <vector>
#include <string>
#include <functional>

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
    command(char count, char pencil) {
        this->count = count;
        this->pencil = pencil;
    }
    char count;
    char pencil;
};

void plot(char c) {
    putc(c, stdout);
}

void draw_cmd(const command &cmd, function<void(char)> f_plot) {
    if( cmd.count == 0 ) {
        f_plot(10);
    }
    for(int i=0; i < cmd.count; ++i) {
        f_plot(cmd.pencil);
    }
}

template<typename SequenceContainer, typename DrawFunction>
void draw(SequenceContainer &img, DrawFunction f_draw) {
    for(auto &c : img)
        f_draw(c);
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
        "5 2*5 00"
        "4 1*2 1*4 00"
        "3 1*4 1*3 00"
        "2 1*6 1*2 00"
        "1 1*8 1*1 00"
        "<*00"
        "4 4*4 00"
        "4 4*4 00"
        "4 4*4 00";
    
    vector<command> v = load(img);
    auto console_draw = [](command cmd) {
        draw_cmd(cmd, plot);
    };
    auto inverse_draw = [](command cmd) {
        if( cmd.pencil == ' ' )
            cmd.pencil = '*';
        else
            cmd.pencil = ' ';
        draw_cmd(cmd, plot);
    };

    auto funny_draw = [](command cmd) -> void {
        if( cmd.pencil != ' ' ) {
            if( cmd.count > 2 )
                cmd.pencil = '=';
            else
                cmd.pencil = '^';
        }
        draw_cmd(cmd, [](char c) -> void {
            if( c == '^' )
                cout << "\033[13;32m" << c;
            else if( c == '=' )
                cout << "\033[12;33m" << c;
            else
                cout << c;
        });
    };
    
    draw(v, console_draw);
    draw(v, inverse_draw);
    draw(v, funny_draw);

    return 0;
}