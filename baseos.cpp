#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    if (argc == 1){
       printf("Debes ingresar mas parametros...\n");
       return 1;
    }
    for(int i = 0; i < argc; i++)
        cout<<"Parametro "<< i + 1 << " " << argv[i]<< endl;
    return 0;
}
