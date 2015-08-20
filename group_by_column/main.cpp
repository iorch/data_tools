#include "reader.cpp"

int main(){
  int tmp;
  std::string header;
  string key = "descripcion";
  string id = "clave_proyecto";
  Reader r("./reconstruccion.psv", header);
  tmp = r.group_by(key,id);
  std::set<string> myset;
  std::set<string>::iterator it;
  myset = r.get_grouping_values();
  map<string,vector<string> > myMap = r.get_map_json();
  for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
  {
    std::cout << "{\""<< key << "\": \"" << (*it).first;
    string _sep = "\", \"proyectos\": [";
    for (auto itv = (*it).second.cbegin(); itv != (*it).second.cend(); ++itv) {
      std::cout << _sep << *itv;
      _sep = ", ";
    }
    std::cout << "]" << "}\n";
  }
  return 0;
}
