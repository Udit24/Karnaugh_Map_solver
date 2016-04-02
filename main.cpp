#include<iostream>
using namespace std;
#define inherits :
#define ROW 4
#define COLUMN 4
#include "KMap.h"
int main(){
KMap k;
k.MapGenerator();
k.displayMap();
k.FringeMapGenerator_Vertical();
k.FringeMapGenerator_Horizontal();
cout<<"\n\n\n";
k.FringeDisplayMap();
}
