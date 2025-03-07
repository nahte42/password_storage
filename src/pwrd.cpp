#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include<curses.h>

using namespace std;


string hash_pwd(string user, string pass);
bool login();
void create();

int main(){

  bool logged = false;
  string ui;
  while(!logged){
    cout<<"Select from the list:\n1) Login\n2) Create New User\n3) Exit\n";
    cin>>ui;
    ui = ui.substr(0,1);
    if(!isdigit(ui[0])){
      cout<<"Please enter a number, not a letter:\n";
      continue;
    }
    if(ui == "1")
      logged = login();
    else if(ui == "2")
      create();
    else if(ui == "3")
      exit(0);
    else
      cout<<"Please enter a number from 1 to 3\n";
    cout<<endl;
  }
  cout<<"You have succesfully logged in\n";
  
  return 0;
}

bool login(){
  bool found = false;
  string check;
  string un = "users.txt";
  string pn = "passwordfile.txt";
  int pos;
  int lgth;
  string username;
  string password;
  fstream usrFile;
  fstream pasFile;
  usrFile.open(un.c_str(), ios::in);
  pasFile.open(pn.c_str(), ios::in);

  while(!found){
    cout<<"user: ";
    cin>>username;
    cout<<"password: ";
    system("stty -echo");
    cin>>password;
    system("stty echo");
    
    while(usrFile >> check){
      if(check == username){
	found = true;
	usrFile >> pos;
	usrFile >> lgth;
	break;
      }
      else{
	usrFile >> check;
	usrFile >> check;
      }
    }
    if(!found){
      cout<<"Username or password was incorrect: \n";
      return false;
    }
    char * pwrd = new char[lgth];
    if(password.length() != lgth){
      cout<<"Username or password was incorrect: \n";
      return false;
    }
    else{
      pasFile.seekp(pos);
      pasFile.read(pwrd,lgth+1);
      password = hash_pwd(username, password);
      for(int i = 0; i < lgth; i ++){
	if(password[i] != pwrd[i]){
	  cout<<"Username or password was incorrect: \n";
	  return false;
	}
      }
    }
  }
  cout<<"\nWelcome "<<username<<"!"<<endl;
  return true;
}

void create(){
  //Files
  bool taken = true;
  string check;
  string un = "users.txt";
  string pn = "passwordfile.txt";
  string username;
  string password;
  fstream usrFile;
  fstream pasFile;
  usrFile.open(un.c_str(),ios::in|ios::out);
  pasFile.open(pn.c_str(),ios::in);
  if(usrFile.fail())
    cout<<1<<endl;

  while(taken){
    taken = false;
    cout << "Please Create A Username: ";
    cin >> username;
    while(usrFile >> check){
      if(username == check){
	taken = true;
	cout<<"Sorry But That Username is Already Taken\n";
      }
      else{
	usrFile >> check;
	usrFile >> check;
      }
    }
    usrFile.close();
    usrFile.open(un.c_str(),ios::in|ios::out);
  }
  usrFile.close();
  usrFile.open(un.c_str(),ios::app);
  taken = true;
  /*  usrFile << username;
      usrFile<<" "<<40<<" "<<9<<endl;*/

  while(taken){
    taken = false;
    cout<<"Please entert a password with 8 or more characters: ";
    system("stty -echo");
    cin >> password;
    system("stty echo");
    if(password.length() < 8){
      taken = true;
      cout<<"That password is less than 8 characters\n";
    }
  }
  password = (hash_pwd(username,password));

  
  int pos;
  int lgth;
  string allPass;
  pasFile >> allPass;
  pasFile.close();
  pasFile.open(pn.c_str(),ios::app);
  pos = allPass.length();
  lgth = password.length();
  pasFile<<password;
  usrFile<<username<<" "<<pos<<" "<<lgth<<endl;
  pasFile.close();
  usrFile.close();
  
}

string hash_pwd(string user, string pass){
  for(int i = 0; i < pass.length(); i++){
    int val = int(pass[i]);
    val *= val;
    val++;
    val+=val/2;
    val = (val%95)+33;
    pass[i] = char(val);
  }
  return pass;
}
