#include <iostream>
#include <string.h>
#include <fstream>
#include "include/graph.h"

int main(int argv, char *argc[]){
  if(argv < 2){
    std::cout << "Entre com um arquivo de imput!\n";
    return 1;
  }
  std::fstream file;
  std::ofstream out;
  
  out.open("out.txt"); 
  file.open(argc[1]);

  int N, M, I;
  int age, rel1, rel2;
  std::string Inst;
  int C, S1, S2;
  std::stack<int> *meeting;
  
  file >> N >> M >> I;

  Graph *G = new Graph(N,M);
  char *inst[I];
  int result[I];


  for(int i = 0; i < N; i++){
    file >> age;
    G->addNode(i, age);
  }

  for(int i = 0; i < M; i++){
    file >> rel1 >> rel2;
    G->addEdge(rel1-1, rel2-1); //vector initialize with 0 but students with 1 
  }
 
  
  for(int i = 0; i < I; i++){
    file >> Inst;
    if(Inst.compare("M") == 0){
      meeting = G->Meeting();
      inst[i] = (char *)"M";
    }else if(Inst.compare("C") == 0){
      file >> C;
      inst[i] = (char *)"C";
      result[i] = G->Commander(C-1);
    }else if(Inst.compare("S") == 0){
      file >> S1 >> S2;
      inst[i] = (char *)"S";
      if(G->swapEdge(S1-1,S2-1))
        result[i] = 1;
      else
        result[i] = 0;
    }
  }

  for(int i = 0; i < I; i++){
    if(strncmp (inst[i],"C",1) == 0){
      if(result[i] != -1)
        out << "C " << result[i] << "\n";
      else
        out << "C *\n";
    }else if(strncmp(inst[i],"S",1) == 0){
      if(result[i] == 1)
        out << "S T\n";
      else
         out << "S N\n";
    }else if(strncmp(inst[i],"M",1) == 0){
      out << "M ";
      while(!meeting->empty()){
        out << meeting->top() + 1 << " ";
        meeting->pop();
      }
  
      out << "\n";
    }
  } 

  out.close();
  file.close();
  return 0;
}
