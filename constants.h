#ifndef CONSTANTS_H
#define CONSTANTS_H

#define VAR_STATE 11
#define BEGINZ_STATE 12
#define END_STATE 13

using namespace std;

extern vector<string> ids;
extern map<string, long> arrayIdsToSize;
extern map<string, long> arrayIdsToFirstPosition;
extern map<string, int> forLoopsVariables;
extern long ids_count;
extern long normal_ids_count;

extern long free_tmp_pointer;
extern long printK;
extern long bisonDebug;

void yyerror (char const *);
int doesStringContainNumber(string str);
long searchForIdNum(char* id);

long getIdNumIfExists(char* id) {
  long idNum = searchForIdNum(id);
  if (idNum != -1) {
    return idNum;
  }
  if(forLoopsVariables.find(id) != forLoopsVariables.end()) {
    if(bisonDebug) printf("Matching id loop variable adress: %s %d", id, forLoopsVariables[id]);
    return forLoopsVariables[id];
  }
  yyerror(UNDECLARED_VARIABLE);
}

long getIdNumIfExistsOrFreeMemoryAddressOtherwise(char* id) {
  long idNum = searchForIdNum(id);
  if (idNum != -1) {
    return idNum;
  }
  free_tmp_pointer++;
  return free_tmp_pointer;
}

long getFreeMemoryAddress(){
  free_tmp_pointer++;
  return free_tmp_pointer;
}

long searchForIdNum(char* id) {
  for(long i=0; i < normal_ids_count; i++){
    if(ids[i].compare(id) == 0){
      long j =i;
      vector<string> alreadyChecked;
      for (long k = 0; k < arrayIdsToFirstPosition.size(); k++) {
        for (map<string, long>::iterator it = arrayIdsToFirstPosition.begin(); it != arrayIdsToFirstPosition.end(); it++ ) {
          if (j >= it->second && find(alreadyChecked.begin(), alreadyChecked.end(), it->first) == alreadyChecked.end()) {
            if (bisonDebug) { cout << "increasing because of array " << it->first << " by: " << arrayIdsToSize[it->first] << endl; }
            j += arrayIdsToSize[it->first];
            alreadyChecked.push_back(it->first);
          }
        }
      }
      if (bisonDebug) { printf("Matching id with number: %s %ld\n", id, j); }
      return j;
    }
  }
  string idStringWithNumbers = string(id); // check if is an array
  int firstNumIndex = doesStringContainNumber(idStringWithNumbers);
  if(firstNumIndex) {
    string idString = idStringWithNumbers.substr(0, firstNumIndex);
    string idNumbers = idStringWithNumbers.substr(firstNumIndex, idStringWithNumbers.length());
    if(arrayIdsToFirstPosition.find(idString) != arrayIdsToFirstPosition.end()) {
      if (bisonDebug) {
        printf("Matching id with number: %s ", id);
        cout << idString << " " << idNumbers << " " << (arrayIdsToFirstPosition[idString] + stol(idNumbers)) << endl;
      }
      return (arrayIdsToFirstPosition[idString] + stol(idNumbers));
    }
  }
  return -1;
}

int doesStringContainNumber(string str) {
  for (long i = 0; i < str.length(); i++) {
    if(str[i]=='0'||str[i]=='1'||str[i]=='2'||str[i]=='4'
        || str[i]=='3' ||str[i]=='5'||str[i]=='6'
        || str[i]=='7' ||str[i]=='8'||str[i]=='9') {
          return i;
        }
  }
  return 0;
}


char* concat(char* a, char* b) {
  char *result = (char*) malloc(strlen(a)+strlen(b)+1);
  strcpy(result, a);
  strcat(result, b);
  return result;
}

long doesStringContainIdSeparator(char* text) {
  char* position = strchr(text, '|');
  if (position) {
    return 1;
  }
  return 0;
}
#endif
