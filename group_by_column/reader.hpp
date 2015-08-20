#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>


using namespace std;

class Reader
{
private:
  std::string input_file;
  string first_line;
  vector<string> headerv;
  map<string,int> headerm;
  int number_of_fields_in_header;
  string grouping_field;
  set<string> grouping_values;
  vector<string> split_line(string line);
  int set_header_vector();
  map<string,vector<string> > map_json;
  string grouped_json;
public:
  Reader(std::string file, std::string &header);
  string get_file();
  string get_first_line();
  string get_field(int column);
  int get_number_of_fieds(vector<string> linev);
  int get_column(string field);
  string get_field_value(string field,vector<string> linev);
  int group_by(string field,string id);
  set<string> get_grouping_values();
  map<string,vector<string> > get_map_json();
};
