// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <getopt.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <unordered_map>
using namespace std;

struct Tile {
    char color_level; 
    uint32_t row = 0;
    uint32_t col = 0;
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
        vector<vector<vector<char> > > backtracing_map;
        //map[k][i][j]
        vector<vector<char> > map_2d;
        vector<pair<int, int>> direction = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //North, East, South, West
        vector<char> direction_char = {'N', 'E', 'S', 'W'};
        bool hasSolution = false;
        uint32_t num_color, width, height;

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
           return static_cast<uint32_t> (c - 'a') + 1;
      }

        bool isInbound(uint32_t row, uint32_t col) {
            // Check if row and col are within the bounds of the map(fixxed)
            
            //((!!!))check here is greater or equal to one
            if (row < map_2d.size() && col < map_2d[0].size()) {
                return true;
            }
            
           /*
            if (row < height && col < width) {
                return true;
            }
            */
            return false;
            
        }
        
        bool isWalkable(uint32_t row, uint32_t col, char color_level) {
            if (row >= map_2d.size() || col >= map_2d[0].size() ) {
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
            return backtracing_map[charToInt(color_level)][row][col] != '$';
        }

    bool algorithms() {
        search_container.push_back(start_state);
        hasSolution = false;
        
        while (!search_container.empty()) {
            Tile current_state;
            if (stack_mode) {
                current_state = search_container.back();
            } else if (queue_mode) {
                current_state = search_container.front();
            }
            
            if (map_2d[static_cast<size_t>(current_state.row)][static_cast<size_t>(current_state.col)] == '?') {
                end_state.color_level = current_state.color_level;
                hasSolution = true;
                return hasSolution;
            }

            if (stack_mode) {
                search_container.pop_back();
            } else if (queue_mode) {
                search_container.pop_front();
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
                    backtracing_map[charToInt(next_color)][next_row][next_col] = current_state.color_level;
                }
            }
            else { //You don't wann
                // Explore surrounding tiles
                // cout << "current_state: " << current_state.color_level << " " << current_state.row << " " << current_state.col << '\n';
                for (size_t i = 0; i < direction.size(); ++i) {
                    uint32_t next_row = static_cast<uint32_t>(static_cast<int32_t>(current_state.row) + direction[i].first);
                    uint32_t next_col = static_cast<uint32_t>(static_cast<int32_t>(current_state.col) + direction[i].second);
                    char next_color = current_state.color_level;
        
                    if (isInbound(next_row, next_col) && isWalkable(next_row, next_col, next_color) && !hasDiscovered(next_row, next_col, next_color)) {
                        Tile new_tile(next_color, next_row, next_col);
                        search_container.push_back(new_tile);
                        backtracing_map[charToInt(next_color)][next_row][next_col] = direction_char[i];
                        // cout << "next_state: " << next_color << " " << next_row << " " << next_col << '\n';
                    }
                }
            }

            
        }
        while(!search_container.empty()) {
            search_container.pop_back();
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
        Puzzle() {
            start_state = Tile('^', 0, 0);
            end_state = Tile('^', 0, 0);
            stack_mode = false;
            queue_mode = false;
            hasSolution = false;
            num_color = 0;
            width = 0;
            height = 0;
        }
        /**
         * We have a start and end location
         * pushback the end location in s a vector<struct(row, col, roomColor)> backVec
         *  backVec size = 1 - eventually this contains the entire path
         *  according to 3d map, and where we cam from, pushback the location (row, col, color)
         * ______
         * for every index in backVec, update 3d Map (%, @, ?)
         * ______
         * for
         *      for
         *      for 3dMap[color][row][col]
        */
         void printMap() {
            hasSolution = algorithms();

            if(hasSolution == false) {
              vector<vector<char> > newMap = map_2d;//可能需要改一下这里因为memory
               cout << "No solution.\n" << "Discovered:\n";
               uint32_t count = 0;
                for (uint32_t i = 0; i < height; ++i) {
                   for (uint32_t j = 0; j < width; ++j) {
                     for(uint32_t c = 0; c < num_color + 1; ++c) {
                       if (!hasDiscovered(i, j, intToChar(c)) && map_2d[i][j] != '@') { 
                        count++;
                        } // if conda
                     } // for c
                     if(count == num_color + 1) {
                        newMap[i][j] = '#'; //数一下，如果这几层的这个地方都没被发现过，才算真正没被发现过
                     }//for if count
                     count = 0; //清零
                     cout << newMap[i][j];
                    }//for j
                    cout << "\n";
                }//for i
                return;
            }
            
            char next_direction = backtracing_map[charToInt(end_state.color_level)][end_state.row][end_state.col];
            Tile prev = end_state;
            Tile current = end_state;
            vector<vector<vector<char> > > color_map(num_color + 1, vector<vector<char> >(height, vector<char> (width, '.')));//3d的地图记录所有的图表
            vector<char> encountered_colors;
            encountered_colors.push_back(current.color_level);

            //这个东西超级无敌大！！！！！
            color_map[charToInt(end_state.color_level)] = map_2d;//把最后一个state的地图print上去
                char target_char = end_state.color_level;
                for (uint32_t i = 0; i < height; ++i) {
                    for (uint32_t j = 0; j < width; ++j) {
                        if (map_2d[i][j] == target_char || map_2d[i][j] == toupper(target_char) || (map_2d[i][j] == '@' && end_state.color_level != '^')) {
                            color_map[charToInt(target_char)][i][j] = '.';
                        }
                    }
                }

            //这里是在改变current的位置
            if (next_direction == 'N') {
                current.row += 1;
            } else if (next_direction == 'E') {
                current.col -= 1;
            } else if (next_direction == 'S') {
                current.row -= 1;
            } else if (next_direction == 'W') {
                current.col += 1;
            }
            else {
                current.color_level = next_direction;//如果没有走路，就说明变颜色，那么不走路，直接换层
            }
            
            //循环，一直到起点之前
            while(current != start_state) {
                //如果没换层
                if(current.color_level == prev.color_level) {
                    color_map[charToInt(current.color_level)][current.row][current.col] = '+'; //把正确路线印上+号
                }
                //如果换层了
                else {
                        //先检查一下这个颜色有没有被找到过
                        bool color_found = false;
                        for(char encountered_color : encountered_colors) {
                            if(encountered_color == current.color_level) {
                                //如果已经找到过这个颜色，直接出loop
                                color_found = true;
                            break;
                            }
                        }

                        //如果颜色找到过
                        //if(color_found) {
                        //    output_map = color_map[current.color_level + 1 - 'a'];//output_map设置成colormap的之前的这个颜色上修改
                        //}
                        if(!color_found) {
                            //换层且颜色没有找到过
                            encountered_colors.push_back(current.color_level);//这一层的颜色已经记录下来了
                            color_map[charToInt(current.color_level)] = map_2d;
                            char target_char = current.color_level;
                            //这个是真的又臭又长
                            for(size_t i = 0; i < height; i++) {
                                for(size_t j = 0; j < width; j++){
                                    if (map_2d[i][j] == target_char || map_2d[i][j] == toupper(target_char)) {
                                        color_map[charToInt(target_char)][i][j] = '.';
                                    }
                                    if(map_2d[i][j] == '@' && current.color_level != '^' && color_map[charToInt(current.color_level)][i][j] != '+') {
                                        //color_map[charToInt(prev.color_level)][i][j] = '.';//这里把不在0层的@全改成.
                                        color_map[charToInt(current.color_level)][i][j] = '.';
                                 }//if 
                                                   
                                }//for j
                                
                            }//for i
                            //color_map[charToInt(current.color_level + static_cast<char>(1 - 'a'))] = map_2d;//给这层的colormap设置一个新图
                        }
                        
                    color_map[charToInt(current.color_level)][prev.row][prev.col] = '+';
                    //color_map[static_cast<size_t>(current.color_level + 1 - 'a')][prev.row][prev.col] = '+';//（！！！）非常有可能出bug这里，要debug，因为我不知道在改变什么
                    color_map[charToInt(current.color_level)][current.row][current.col] = '%';
                    color_map[charToInt(prev.color_level)][prev.row][prev.col] = '@';
                    //color_map[static_cast<size_t>(current.color_level + 1 - 'a')][current.row][current.col] = '%';
                }

                //开始换prev点
                prev = current;
                //开始换current点
                next_direction = backtracing_map[charToInt(current.color_level)][current.row][current.col];
                if (next_direction == 'N') {
                    current.row += 1;
                } else if (next_direction == 'E') {
                    current.col -= 1;
                } else if (next_direction == 'S') {
                    current.row -= 1;
                } else if (next_direction == 'W') {
                    current.col += 1;
                }
                else {
                    current.color_level = next_direction;
                }
            }

            if(current.color_level == '^') {
                for (uint32_t i = 0; i < height; ++i) {
                    for (uint32_t j = 0; j < width; ++j) {
                        if (map_2d[i][j] == '^' && color_map[charToInt(current.color_level)][i][j] != '+' && color_map[charToInt(current.color_level)][i][j] != '@'  && color_map[charToInt(current.color_level)][i][j] != '%') {
                            color_map[charToInt(current.color_level)][i][j] = '.';
                        }
                        if(map_2d[i][j] == '@') {
                            color_map[charToInt(current.color_level)][i][j] = '@';
                        }
                    }
                }
            }//检查新的这个点在不在0层，把trap换成路

            //这里先print没有颜色的那一层
            cout << "// color ^\n";
                for(const auto& line : color_map[0]) {
                    for(char cell : line) {
                        cout << cell;
                    }
                std::cout << '\n';
                }

                vector<char> unencountered_colors;

                //设置哪些颜色是没被找到过的
                for (char color = 'a'; color < static_cast<char>('a' + num_color); ++color) {
                    bool encountered = false;

                    for (char encountered_color : encountered_colors) {
                        if (color == encountered_color) {
                            encountered = true;
                            break;
                        }
                    }

                    if (!encountered) {
                        unencountered_colors.push_back(color);
                    }
                }

            //如果有一些层没有去过,要把这些层的地图保存在colormap里然后，把大小写的字母都变成路‘.’
            //如果有三个颜色，只找到一个颜色，那么就有两个颜色的图要保存
            if(unencountered_colors.size() > 0) {
                for(uint32_t i = 0; i < unencountered_colors.size(); ++i) {
                    color_map[charToInt(unencountered_colors[i])] = map_2d;//might cause a charToInt problem here
                    char target_char = unencountered_colors[i];
                    for (uint32_t i = 0; i < height; ++i) {
                        for (uint32_t j = 0; j < width; ++j) {
                            //说实话不知道要不要把@看成open floor
                            //if (map_2d[i][j] == target_char || map_2d[i][j] == toupper(target_char) || map_2d[i][j] == '@') {
                            if (map_2d[i][j] == target_char || map_2d[i][j] == toupper(target_char) || map_2d[i][j] == '@') {
                                color_map[charToInt(target_char)][i][j] = '.';
                        }
                    }
                }

              }
            }//if loop

            if(num_color > 0) {
                for(char color = 'a'; color < static_cast<char>('a' + num_color); ++color) {
                    cout << "// color " << color << '\n';
                    for(const auto& line: color_map[static_cast<uint32_t>(color - 'a' + 1)]) {
                        for(char cell : line) {
                            cout << cell;
                        }
                        cout << '\n';
                    }//for line
                }//for color
            }//if
        }
        
        void printList() {
            hasSolution = algorithms();

            if(hasSolution == false) {
              vector<vector<char> > newMap = map_2d;//可能需要改一下这里因为memory
               cout << "No solution.\n" << "Discovered:\n";
               uint32_t count = 0;
                for (uint32_t i = 0; i < height; ++i) {
                   for (uint32_t j = 0; j < width; ++j) {
                     for(uint32_t c = 0; c < num_color + 1; ++c) {
                       if (!hasDiscovered(i, j, intToChar(c)) && map_2d[i][j] != '@') { 
                        count++;
                        } // if conda
                     } // for c
                     if(count == num_color + 1) {
                        newMap[i][j] = '#'; //数一下，如果这几层的这个地方都没被发现过，才算真正没被发现过
                     }//for if count
                     count = 0; //清零
                     cout << newMap[i][j];
                    }//for j
                    cout << "\n";
                }//for i
                return;
            }
            Tile prev = end_state;
            Tile current = end_state;
            char next_direction = backtracing_map[charToInt(end_state.color_level)][end_state.row][end_state.col];
            
            //这一步是刷新current row让它不等于end_state的
            if (next_direction == 'N') {
                current.row += 1;
            } else if (next_direction == 'E') {
                current.col -= 1;
            } else if (next_direction == 'S') {
                current.row -= 1;
            } else if (next_direction == 'W') {
                current.col += 1;
            }
            else {
                current.color_level = next_direction;
            }
            
            // A list to store the steps in the solution path
            deque<Tile> solutionPath;

            //这一步把终点记下来
            solutionPath.push_front(prev);

            //开始循环
            while(current != start_state) {
                //把现在的这条路记下来
                 solutionPath.push_front(current);
                
                 // Get the previous step in the solution
                next_direction = backtracing_map[charToInt(current.color_level)][current.row][current.col];
                //std::cout << "Size: " << backtracing_map.size() << ", Indices: " << charToInt(current.color_level) << ", " << current.row << ", " << current.col << std::endl;

                if (next_direction == 'N') {
                    current.row += 1;
                } else if (next_direction == 'E') {
                    current.col -= 1;
                } else if (next_direction == 'S') {
                    current.row -= 1;
                } else if (next_direction == 'W') {
                    current.col += 1;
                }
                else {
                    current.color_level = next_direction;
                }
             }
            solutionPath.push_front(start_state);

             // Now, we print the solutionPath list in a formatted way
             for(const auto& step : solutionPath) {
                 cout << "(" << step.color_level << ", (" << step.row << ", " << step.col << "))" << "\n";
             }

             //go through
             while(!solutionPath.empty()) {
                solutionPath.pop_back();
            }

        }

        vector<string> get_options(int argc, char* argv[]) {
            int index = 0;
            int option = 0;
            opterr = false;;
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
            vector<string> empty_vector;

            while((option = getopt_long(argc,argv,"hsqo:", long_options, &index)) != -1) {
                string optarg_;
                switch(option) {
                    case 'h' :
                    cout << "This program helps to determine if the provided puzzle has solutions or not, \n";
                    cout << "and output the path if a solution exist. \n";

                    return empty_vector;
                    
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
                            cerr << "you must specify an output type.\n";
                        }
                        haveOutput = true;
                        break;
                    
                    default:
                        cerr << "Error: Recognized Nothing";
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
        cin >> num_color >> height >> width;

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
        char foo;
        uint32_t start_count = 0;
        uint32_t target_count = 0;
        uint32_t i = 0;
        backtracing_map.resize(num_color + 1, vector<vector<char> >(height, vector<char>(width, '$'))); // I have resized this
        map_2d.resize(height, vector<char>(width));//resized map2d
        while(getline(cin, lines)) {
            if(lines[0] == '/') continue;//这里可能会有bug哦因为我这里两个if
                for (uint32_t c = 0; c < lines.size(); ++c) {

                    //if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && c != '.' && c != '#' && c != '@' && c != '?' && c != '/') {
                    //    cerr << "Error: Invalid character in map." << endl;
                    //    exit(1);
                    //}(!!!DEBUG this one)
                    foo = lines[c];
                    if ((foo >= 'A' && foo <= 'Z') && (foo - 'A' >= static_cast<int>(num_color))) {
                        cerr << "Error: Invalid door in map." << endl;
                        exit(1);
                    }

                    if ((foo >= 'a' && foo <= 'z') && (foo - 'a' >= static_cast<int>(num_color))) {
                        cerr << "Error: Invalid button in map." << endl;
                        exit(1);
                    }

                    if (foo == '@') {
                        start_count++;
                        start_state = Tile('^', i, c);
                    }
                    if (foo == '?') {
                        target_count++;
                        end_state = Tile('^', i, c);
                    }
                    map_2d[i][c] = foo;
                    

                } //for c
                i++;

        }//while loop   
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
    if(options.size() == 0) return 0;
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





