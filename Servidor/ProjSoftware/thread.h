#include <windows.h>
#include <iostream>
using namespace std;

class Runnable{
      public: virtual void run() = 0;
};

class Thread{
   private:
      Runnable *runObject;
      HANDLE threadHandle;
      DWORD id;
      
      /*gambiarra para emular o DWORD CALLBACK*/
      static unsigned long __stdcall process(void* obj) {
             ((Runnable*)obj)->run();
            
      } 
      
   public:
          Thread(){}
          
          Thread( Runnable *rO ){
                  this -> runObject = rO;
          }
          
          void start(){
               threadHandle = CreateThread(0,0, process,runObject,0,&id);
          }
};
