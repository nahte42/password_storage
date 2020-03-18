#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<time.h>

using namespace std;

int main(){
  srand(time(0));
  string name = "passwordfile.txt";
  fstream password;
  password.open(name.c_str(),ios::in);

  string fullist;

  password >> fullist;

  for(int i = 0; i < fullist.length(); i++){
    int val = int(fullist[i]);
    val *= rand()%100+1;
    val += rand()%100+1;
    val = (val%95)+33;
    //cout<<"val: \t\t"<<val<<" ";
    //cout<<"char(val)\t\t"<<char(val)<<" ";
    fullist[i] = char(val);
    //cout<<"fullist[i]:\t\t"<<fullist[i]<<endl;
    //cin.get();
  }
  //cin.get();
  password.close();
  password.open(name.c_str(),ios::out);
  password << fullist;
  return 0;

}
