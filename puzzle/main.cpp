// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <getopt.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <list>
#include <unordered_map>
using namespace std;

struct Tile {
    char color_level; 
    int row;
    int col;
    Tile();
    Tile(char color_level, int row, int col);
    ~Tile();
};

Tile::Tile(void): color_level('^'), row(0), col(0) {}
Tile::Tile(char color1, int row1, int col1): color_level(color1), row(row1), col(col1) {}
Tile::~Tile(void){}

class Puzzle {
    private:
        Tile start_state;
        Tile end_state;
        //do I have to initialize this start state?
        bool stack_mode;
        //last in first out
        bool queue_mode;
        //first in first out
        deque<Tile> search_container;
        vector<vector<unordered_map<char, Tile > > > backtracing_map;
        vector<string> map_2d;

        char intToChar(int i) {
            if(i == 0) {
                return '^';
            }
            else {
                return static_cast<char>('a' + i - 1);
            }
        }

        int charToInt(char c) {
            if(c == '@') {
                return 0;
            }
            if(c == '^') {
                return 0;
            }
            return static_cast<int> (c-'a') + 1;
        }
        bool isInbound(int row, int col, int maxRow, int maxCol) {
            // return true; // have to fix these
            return row >= 0 && row < maxRow && col >= 0 && col < maxCol;
        }
        
        bool isWalkable(int row, int col, const vector<string>& map_2d) {
            // return true; // have to fix these
            return map_2d[static_cast<size_t> (row)][static_cast<size_t> (col)] != '#';
        }

        bool hasDiscovered(int row, int col, char color_level, const vector<vector<unordered_map<char, Tile > > >& backtracing_map) {
            // return true; // have to fix these
            return backtracing_map[static_cast<size_t> (row)][static_cast<size_t> (col)].find(color_level) != backtracing_map[static_cast<size_t> (row)][static_cast<size_t> (col)].end();
        }

        void algorithms() {
            Tile current_state = start_state;
            //how do I record this state so need to discover a second time?
            search_container.push_back(current_state);
            vector<vector<int> > direction = {{-1,0}, {1,0}, {0,1}, {0,-1}}; //North South East West


            while(!(search_container.empty())) {
                if(stack_mode) {
                    current_state = search_container.back();
                }
                else if(queue_mode) {
                    current_state = search_container.front();
                }

                if(stack_mode) {
                    search_container.pop_back();
                }
                else if(queue_mode) {
                    search_container.pop_front();
                }
                
                //maybe I can take this if statement out of the loop?
                if(current_state.color_level == '?') {
                    //maybe something need to output here
                    end_state.color_level = current_state.color_level;
                    break;
                }
                if(map_2d[static_cast<size_t> (current_state.row)][static_cast<size_t> (current_state.col)] >= 'a' && map_2d[static_cast<size_t> (current_state.row)][static_cast<size_t> (current_state.col)] <= 'z' && current_state.color_level != map_2d[static_cast<size_t> (current_state.row)][static_cast<size_t> (current_state.col)]) {
                    //there's a chance for color change, if this button hasen't been discovered before, add it to the search container and marked as "discovered"
                    int next_row = current_state.row;
                    int next_col = current_state.col;
                    char next_color = map_2d[static_cast<size_t> (current_state.row)][static_cast<size_t> (current_state.row)];
                    if(!hasDiscovered()) {
                        Tile new_tile(next_color, next_row, next_col);
                        search_container.push_back(new_tile);
                        backtracing_map[static_cast<size_t>(next_row)][static_cast<size_t>(next_col)][next_color] = current_state;
                    }
                }
                else{
                    for(size_t i = 0; i < direction.size(); ++i) {
                        int next_row = current_state.row + direction[i][0];
                        int next_col = current_state.col + direction[i][1];
                        char next_color = current_state.color_level;
                        if(isInbound() && isWalkable() && !hasDiscovered()){
                            Tile new_tile(next_color, next_row, next_col);
                            search_container.push_back(new_tile);
                            backtracing_map[static_cast<size_t>(next_row)][static_cast<size_t>(next_col)][next_color] = current_state;
                        }
                    }
                }
            }

            //(**)add element to container

        }


    public:
        void printMap() {
            algorithms();
            Tile prev = end_state;
            Tile current = backtracing_map[end_state.row][end_state.col][end_state.color_level];
            vector<string>output_map = map_2d;
            vector<string> output_strings;
            while(current != start_state) {
                if(current.color_level == prev.color_level) {
                    output_map[current.row][current.col] = '+';
                    prev = current;
                    current = backtracing_map[current.row][current.col][current.color_level];
                }
                else {
                    output_map[prev.row][prev.col] = '@'; //before the level has changed
                    for(size_t i = 0; i < map_2d.size(); i++) {
                        for(size_t j = 0; j < i.length(); j++){
                            if(map_2d[i][j] == '@') {
                                output_map[i][j][prev.color_level] = '.';     
                            }                      
                        }
                    }//(??) Here I have to remove the '@' on other maps, and change it to '.' to print out
                    string current_map = "//color " + prev.color_level;
                    output_strings.push_back(current_map);

                    output_map = map_2d;//this is after the level has changed
                    output_map[prev.row][prev.col] = '%';
                    output_map[current.row][current.col] = '+';
                }
            }
            string current_map = "//color " + prev.color_level;
            for(size_t i = 0; i < output_map.size(); i++) {
                current_map += output_map[i] + '\n';
            }
            output_strings.push_back(current_map);

            std::reverse(output_strings.begin(), output_strings.end());
            for(size_t i = 0; i < output_strings.size(); i++) {
                cout << output_strings[i];
            }
        }

        void printList() {
            algorithms();
            if (end_state.color_level == '^') {
                cout << "No solution.\n";
                return;
            }
            // Create a list for storing the path of solution
            list<string> solutionPath;
            // From the end_state, trace back to the start_state
            Tile current = end_state;
            while (current != start_state) {
                // Create a string for storing the current cur_state
                stringstream cur_state;
                cur_state << "(" << current.row << ", " << current.col << ", " << current.color_level << ")";
                // Add the current cur_state to the list
                solutionPath.push_front(cur_state.str());
                // Move to the last state
                current = backtracing_map[current.row][current.col][current.color_level];
            }
            // Create a string for storing the start_state
            stringstream start;
            start << "(" << start_state.row << ", " << start_state.col << ", " << start_state.color_level << ")";
            // Add the start_state to the list
            solutionPath.push_front(start.str());
            // Print the solution
            for (auto it = solutionPath.begin(); it != solutionPath.end(); ++it) {
                cout << *it << endl;
            }
        }


        void get_options(int argc, char* argv[]) {
            int index = 0;
            int option = 0;
            opterr = false;
            bool haveOutput = false; 
            bool haveFlag = false; 
            vector<string> output_and_flag(2);

            struct option long_options[] = {   
                { "help", no_argument,       nullptr, 'h'},
                { "stack", no_argument,       nullptr, 's'},
                { "queue", no_argument,       nullptr, 'q'},    
                { "output", required_argument, nullptr, 'o' },
                { nullptr, 0, nullptr, '\0' }
            };

            while((option = getopt_long(argc,argv,"hsqo:", long_options, &index)) != -1) {
                string optarg_;
                switch(option) {
                    case 'h' :
                    //prohibits arguments and causes the program to print a helpful message of your own design
                    
                    exit(0);
                    
                    case 's' :
                    if(haveFlag) {
                        cerr << "Error: Can not have both stack and queue";
                        exit(1);
                    }
                    output_and_flag[0] = "s";
                    haveFlag = true;
                    
                    break;

                    case 'q' :
                    if(haveFlag) {
                        cerr << "Error: Can not have both stack and queue";
                        exit(1);
                    }
                    output_and_flag[0] = "q";
                    haveFlag = true;
                    
                    break;

                    case 'o' :
                        optarg_ = optarg;
                        if(optarg_ == "list") {
                            cout << "list mode\n";
                            output_and_flag[1] = "list";
                        }
                        else if(optarg_ == "map") {
                            cout << "map mode\n";
                            output_and_flag[1] = "map";
                        }
                        else{
                            if(stoi(optarg_) > 1) {
                                //sth, I didn't figure out what this means
                            }
                            cout << "you specified: " << optarg_ + '\n';
                            //cerr << "you must specify an output type\n";
                        }
                        haveOutput = true;
                        break;
                    
                    default:
                        cerr << "Error: Unknown option";
                        exit(1);
                    
                }
            }
            if(!haveFlag) {
                cerr << "Error: Must have at least one of stack or queue";
                exit(1);
            }
            if(!haveOutput) {
                output_and_flag[1] = "map";
            }
            //do I return? how can I get the value back to main?
        }
    void read_input() {
        string x;
        string lines;
        size_t num_color, width, height;
        cin >> num_color >> width >> height;
        while(getline(cin, lines)) {
            if(lines[0] != '/') {
                map_2d.push_back(lines);
                backtracing_map.push_back(vector<unordered_map<char, Tile> >(width)); //Initialized a 2D vector of vector(map)
                for(size_t i = 0; i < lines.length(); ++i) {
                    if(lines[i] == '@') {
                        start_state = Tile('^', static_cast<int>(map_2d.size() - 1), static_cast<int>(i));
                    }
                    if(lines[i] == '?') {
                        end_state = Tile('^', static_cast<int>(map_2d.size() - 1), static_cast<int>(i));
                    }
                }
            }
        }    
    }
};


  int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cout << "command line arguments:" << argc + '\n';
    for(int i = 0; i < argc; i++) {
        cout << "argv[" << i << "] =" << argv[i] + '\n';
    }
    Puzzle puzzle;
    puzzle.get_options(argc, argv);
    puzzle.read_input();


  }

