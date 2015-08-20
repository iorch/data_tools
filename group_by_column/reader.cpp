#include "reader.hpp"

Reader::Reader(std::string file, std::string &header){
    input_file = file;
    ifstream my_read_file;
    my_read_file.open(input_file);
    if (my_read_file.is_open()) {
      while (!my_read_file.eof()) {
        my_read_file >> header;
        first_line = header;
        break;
      }
    }
    my_read_file.close();
}

int Reader::set_header_vector(){
  if (headerv.empty()){
    string _tmp_string;
    headerv = split_line(first_line);
    number_of_fields_in_header = get_number_of_fieds(headerv);
    int col = 1;
    for (std::vector<string>::iterator it = headerv.begin() ; it != headerv.end(); ++it){
        headerm[*it] = col;
        col++;
    }
  }
  return 0;
}

vector<string> Reader::split_line(string line){
  vector<string> _tmp_vector;
  string _tmp_string;
  std::stringstream ss(line);
  while (ss.good()){
    getline( ss, _tmp_string, '|' );
    _tmp_string.erase(
      remove(_tmp_string.begin(),_tmp_string.end(), '\"'),
      _tmp_string.end()
    );
    _tmp_vector.push_back(_tmp_string);
  }
  return _tmp_vector;
}

string Reader::get_file(){
  return input_file;
}

string Reader::get_first_line(){
  return first_line;
}

string Reader::get_field(int column){
  if (headerv.empty()) set_header_vector();
  string field;
  if (column > 0 && column < headerv.size())
    field = headerv.at(column-1); // There is no column 0
  else if (column < 0 && headerv.size() > -1*column)
    field = headerv.at(headerv.size() + column);
  else
  field = "NA";
  return field;
}

int Reader::get_number_of_fieds(vector<string> linev){
  return linev.size();
}

int Reader::get_column(string field){
  if (headerm.empty()) set_header_vector();
  int column = headerm[field];
  return column;
}

string Reader::get_field_value(string field,vector<string> linev){
  if (headerm.empty()) set_header_vector();
  int column = headerm[field];
  return linev[column-1]; //There is no field 0
}

int Reader::group_by(string field,string id){
  grouping_field = field;
  int _column = get_column(grouping_field);
  int _id_column = get_column(id);
  grouping_field = field;
  ifstream my_read_file;
  vector<string> _tmp_vector;
  string _tmp_value;
  my_read_file.open(input_file);
  string line;
  char _tmp_json[100];
  int line_number = 0;
  if (my_read_file.is_open()) {
    while (getline( my_read_file, line )) {
      if (line_number == 0){
        line_number++;
        continue;
      }
      _tmp_vector = split_line(line);
      int _nfields = get_number_of_fieds(_tmp_vector);
      if (_nfields != number_of_fields_in_header) continue;
      if (_column-1 <= _tmp_vector.size()) _tmp_value = _tmp_vector.at(_column-1);
      grouping_values.insert(_tmp_value);
      string _id_val = get_field_value(id,_tmp_vector);
      int n = sprintf(_tmp_json,"{\"%s\": \"%s\"}",id.c_str(),_id_val.c_str());
      map_json[_tmp_value].push_back(_tmp_json);
      //if (line_number > 20) break;
      line_number++;
    }
  }
  my_read_file.close();
  return 0;
}

set<string> Reader::get_grouping_values(){
  return grouping_values;
}

map<string,vector<string> > Reader::get_map_json(){
  return map_json;
}
