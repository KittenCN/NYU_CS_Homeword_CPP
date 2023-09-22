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
    uint32_t row;
    uint32_t col;
    Tile();
    Tile(char color_level, uint32_t row, uint32_t col);

     bool operator!=(const Tile& other) const {
        return color_level != other.color_level || row != other.row || col != other.col;
    }
};

Tile::Tile(void): color_level('^'), row(0), col(0) {}
Tile::Tile(char color1, uint32_t row1, uint32_t col1): color_level(color1), row(row1), col(col1) {}

class Puzzle {
    private:
        Tile start_state;
        Tile end_state;
        //do I have to initialize this start state?
        bool stack_mode = false;
        //last in first out
        bool queue_mode = false;
        //first in first out
        deque<Tile> search_container;
        vector<vector<unordered_map<char, Tile > > > backtracing_map;
        //vector<vector<vector<char> > > backtracing_map;
        //map[k][i][j]
        vector<string> map_2d;
        bool hasSolution = false;

        char intToChar(uint32_t i) {
            if(i == 0) {
                return '^';
            }
            else {
                return static_cast<char>('a' + i - 1);
            }
        }

        uint32_t charToInt(char c) {
            if(c == '@') {
                return 0;
            }
            if(c == '^') {
                return 0;
           }
            return static_cast<uint32_t> (c-'a') + 1;
       }

        bool isInbound(uint32_t row, uint32_t col) {
            // Check if row and col are within the bounds of the map(fixxed)
            if (row < map_2d.size() && col < map_2d[0].size()) {
                return true;
            }
            return false;
        }
        
        bool isWalkable(uint32_t row, uint32_t col, char color_level) {
            // Check if the row and col are within bounds of the map(!! this one and isInbound is duplicated)
            if (row >= map_2d.size() || col >= map_2d[0].size()) {
                return false;
            }

            // Get the character at the specified position
            char tile_char = map_2d[row][col];

            // Check if the tile is walkable. Adjust this condition based on your specific requirements.
            if (tile_char == '#') {
                return false;
            }

            if ((tile_char >= 'A' && tile_char <= 'Z') && ((color_level - 'a' + 'A') != tile_char)) {
                return false;
            }

            // if (tile_char == '.' || tile_char == '@' || (tile_char >= 'a' && tile_char <= 'z')) {
            //     // Additional check to handle color level conditions
            //     if(color_level == '^' || color_level == tile_char) {
            //         return true;
            //     }
            // }
            return true;
        }

        bool hasDiscovered(uint32_t row, uint32_t col, char color_level) {
            // Check if the state represented by the row, col, and color_level
            // is present in the backtracing_map
            return backtracing_map[row][col].find(color_level) != backtracing_map[row][col].end();
        }

    bool algorithms() {
        search_container.push_back(start_state);
        vector<vector<int>> direction = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //North, East, South, West
        hasSolution = false;

        while (!search_container.empty()) {
            Tile current_state;
            if (stack_mode) {
                current_state = search_container.back();
                search_container.pop_back();
            } else if (queue_mode) {
                current_state = search_container.front();
                search_container.pop_front();
            }
            
            if (map_2d[static_cast<size_t>(current_state.row)][static_cast<size_t>(current_state.col)] == '?') {
                end_state.color_level = current_state.color_level;
                hasSolution = true;
                return hasSolution;
            }

            char current_tile_char = map_2d[static_cast<size_t>(current_state.row)][static_cast<size_t>(current_state.col)];
            // Check if there's a chance for color change
            if ((current_tile_char == '^' || (current_tile_char >= 'a' && current_tile_char <= 'z')) && current_state.color_level != current_tile_char) {
                uint32_t next_row = current_state.row;
                uint32_t next_col = current_state.col;
                char next_color = current_tile_char;
                if (!hasDiscovered(next_row, next_col, next_color)) {
                    Tile new_tile(next_color, next_row, next_col);
                    search_container.push_back(new_tile);
                    backtracing_map[static_cast<size_t>(next_row)][static_cast<size_t>(next_col)][next_color] = current_state;
                    // cout << "current_state: " << current_state.color_level << " " << current_state.row << " " << current_state.col << '\n';
                    // cout << "next_state: " << next_color << " " << next_row << " " << next_col << '\n';
                    // cout << endl;
                }
            }
            else {
                // Explore surrounding tiles
                // cout << "current_state: " << current_state.color_level << " " << current_state.row << " " << current_state.col << '\n';
                for (size_t i = 0; i < direction.size(); ++i) {
                    uint32_t next_row = static_cast<uint32_t>(static_cast<int32_t>(current_state.row) + direction[i][0]);
                    uint32_t next_col = static_cast<uint32_t>(static_cast<int32_t>(current_state.col) + direction[i][1]);
                    char next_color = current_state.color_level;
        
                    if (isInbound(next_row, next_col) && isWalkable(next_row, next_col, next_color) && !hasDiscovered(next_row, next_col, next_color)) {
                        Tile new_tile(next_color, next_row, next_col);
                        search_container.push_back(new_tile);
                        backtracing_map[static_cast<size_t>(next_row)][static_cast<size_t>(next_col)][next_color] = current_state;
                        // cout << "next_state: " << next_color << " " << next_row << " " << next_col << '\n';
                    }
                }
                // cout << endl;
            }            
        }
        return hasSolution;
    }

        public:
        void setStackMode(bool mode) {
            stack_mode = mode;
        }
        void setQueueMode(bool mode) {
            queue_mode = mode;
        }
        void printMap() {
            hasSolution = algorithms();
            
            // if there's no solution, see spec "no solution" section
            if(hasSolution == false) {
               cout << "No solution.\n" << "Discovered:\n";
                for (uint32_t i = 0; i < map_2d.size(); ++i) {
                   for (uint32_t j = 0; j < map_2d[i].length(); ++j) {
                       if (backtracing_map[i][j].empty() && map_2d[i][j] != '@') { // I dont't know how to implement this
                           map_2d[i][j] = '#';//DEBUGGGG here
                        }
                    }
                }
            }
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
                    output_map[prev.row][prev.col] = '@'; 
                    for(size_t i = 0; i < map_2d.size(); i++) {
                        for(size_t j = 0; j < map_2d[i].length(); j++){
                            if(map_2d[i][j] == '@') {
                                output_map[i][j] = '.';     
                            }              

                            if(current.color_level == '^' && map_2d[i][j] == '^') {
                                map_2d[i][j] = '.';
                            }        
                        }
                    }


                    string current_map = "// color " + std::string(1, prev.color_level) + "\n";
                    for(const auto& line : output_map) {
                        current_map += line + '\n';
                    }
                    output_strings.push_back(current_map);

                    output_map = map_2d;
                    output_map[prev.row][prev.col] = '+';
                    output_map[current.row][current.col] = '%';
                    prev = current;
                    current = backtracing_map[current.row][current.col][current.color_level];
                }
            }
            string current_map = "// color " + std::string(1, prev.color_level) + "\n";
            for(const auto& line : output_map) {
                current_map += line + '\n';
            }
            output_strings.push_back(current_map);

            std::reverse(output_strings.begin(), output_strings.end());
            for(const auto& output : output_strings) {
                cout << output;
            }
        }
        
        void printList() {
            algorithms();

            Tile prev = end_state;
            Tile current = backtracing_map[end_state.row][end_state.col][end_state.color_level];
            
            // A list to store the steps in the solution path
            deque<Tile> solutionPath;
            solutionPath.push_front(prev);

            while(current != start_state) {
                solutionPath.push_front(current);
                
                // Get the previous step in the solution
                current = backtracing_map[current.row][current.col][current.color_level];
            }
            solutionPath.push_front(start_state);

            // Now, we print the solutionPath list in a formatted way
            for(const auto& step : solutionPath) {
                cout << "(" << step.color_level << ", (" << step.row << ", " << step.col << "))" << "\n";
            }

        }

        vector<string> get_options(int argc, char* argv[]) {
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
                    cout << "This program helps to determine if the provided puzzle has solutions or not, \n";
                    cout << "and output the path if a solution exist. \n";

                    exit(0);
                    
                    case 's' :
                    if(haveFlag) {
                        cerr << "Error: Can not have both stack and queue";
                        exit(1);
                    }
                    output_and_flag[0] = "s";
                    setStackMode(true);
                    haveFlag = true;
                    
                    break;

                    case 'q' :
                    if(haveFlag) {
                        cerr << "Error: Can not have both stack and queue";
                        exit(1);
                    }
                    output_and_flag[0] = "q";
                    setQueueMode(true);
                    haveFlag = true;
                    
                    break;

                    case 'o' :
                        optarg_ = optarg;
                        if(optarg_ == "list") {
                            //cout << "list mode\n";
                            output_and_flag[1] = "list";
                        }
                        else if(optarg_ == "map") {
                            //cout << "map mode\n";
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
            return output_and_flag;
        }
    void read_input() {
        string lines;
        size_t num_color, width, height;
        cin >> num_color >> width >> height;

        if(num_color > 26) {
            cerr << "Error: Invalid numColor. \n";
            exit(1);
        }

        if(width < 1) {
            cerr << "Error: Invalid width. \n";
            exit(1);
        }

        if(height < 1) {
            cerr << "Error: Invalid height. \n";
            exit(1);
        }

        getline(cin, lines);
        int start_count = 0;
        int target_count = 0;
        while(getline(cin, lines)) {
            if(lines[0] != '/') {
                for (char c : lines) {
                    //if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '.' && c != '#' && c != '@' && c != '?' && c != '/') {
                    //    cerr << "Error: Invalid character in map." << endl;
                    //    exit(1);
                    //}(!!!DEBUG this one)

                    if ((c >= 'A' && c <= 'Z') && (c - 'A' >= static_cast<int>(num_color))) {
                        cerr << "Error: Invalid door in map." << endl;
                        exit(1);
                    }

                    if ((c >= 'a' && c <= 'z') && (c - 'a' >= static_cast<int>(num_color))) {
                        cerr << "Error: Invalid button in map." << endl;
                        exit(1);
                    }

                    if (c == '@') start_count++;
                    if (c == '?') target_count++;
                }
                map_2d.push_back(lines);
                backtracing_map.push_back(vector<unordered_map<char, Tile> >(height)); //Initialized a 2D vector of vector(map)
                for(uint32_t i = 0; i < lines.length(); ++i) {
                    if(lines[i] == '@') {
                        start_state = Tile('^', static_cast<uint32_t>(map_2d.size() - 1), static_cast<uint32_t>(i));
                    }
                    if(lines[i] == '?') {
                        end_state = Tile('^', static_cast<uint32_t>(map_2d.size() - 1), static_cast<uint32_t>(i));
                    }
                }
            }

        }   
    if (start_count != 1 || target_count != 1) {
        cerr << "Error: Puzzle must have only one start and one target. \n";
        exit(1);
    }
    }
};


  int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    Puzzle puzzle;
    
    // Get the command line options and configure the puzzle object accordingly
    vector<string> options = puzzle.get_options(argc, argv);

    // Set the stack or queue mode based on the command line options
    if (options[0] == "s") {
        puzzle.setStackMode(true);
    } else if (options[0] == "q") {
        puzzle.setQueueMode(true);
    }

    // Read the input to initialize the puzzle
    puzzle.read_input();

    // Depending on the output mode specified, call the appropriate function to print the output
    if (options[1] == "list") {
        puzzle.printList();
    } else if (options[1] == "map") {
        puzzle.printMap();
    }
    else {
        cerr << "Error: Invalid output mode. \n"; //IDK if I'm doing this correctly!
    }

    return 0;
  }






