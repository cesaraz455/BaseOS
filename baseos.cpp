#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

#define HELP "--help"
#define HELP_ABBREVIATION "-h"
#define TIME "--time"
#define TIME_ABBREVIATION "-t"
#define PROCESSLIST "--processlist"
#define PROCESSLIST_ABBREVIATION "-p"
#define DELETEPROCESS "--deleteprocess"
#define DELETEPROCESS_ABBREVIATION "-d"
#define ADDITION "--addition"
#define ADDITION_ABBREVIATION "-a"
#define MONTHDAYS "--monthdays"
#define MONTHDAYS_ABBREVIATION "-m"

void showHelp(){
    cout << "Welcome to Base Operative System" << endl;
    cout << "Usage: baseos --function [params...]" << endl << endl;
    cout << "--help or -h" << "\t\t" << "Muestra esta documentacion del sistema." << endl;
    cout << "--time or -t" << "\t\t" << "Muestra la fecha y hora." << endl;
    cout << "--processlist or -p" << "\t" << "Lista todos los procesos que se estan ejecutando." << endl;
    cout << "--deleteprocess or -d" << "\t" << "Elimina un proceso. Espera como parametro el ID del proceso a eliminar." << endl;
    cout << "--addition or -a" << "\t" << "Sumar dos enteros. Espera como parametros dos numeros enteros." << endl;
    cout << "--monthdays or -m" << "\t" << "Muestra la cantidad de dias que tiene un mes. Espera el numero del mes, (eje: 1 o 12)" << endl;
}

bool isFunction(string argument, string needle = "-"){
    return strstr(argument.c_str(), needle.c_str());
}

void showTime(){
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    cout << "La hora actual de la BIOS es " << put_time(&tm, "%d-%m-%Y %H-%M-%S") << endl;
}

int addition(int number1, int number2){
    return number1 + number2;
}

string monthdays(int monthnumber){
    switch(monthnumber) {
		case 1:
            return "El mes de Enero tiene 31 dias";
		break;
		case 2:
		    return "El mes de Febrero tiene 28 dias";
		break;
		case 3:
		    return "El mes de Marzo tiene 31 dias";
		break;
		case 4:
		    return "El mes de Abril tiene 30 dias";
		break;
		case 5:
		    return "El mes de Mayo tiene 31 dias";
		break;
		case 6:
		    return "El mes de Junio tiene 30 dias";
		break;
		case 7:
		    return "El mes de Julio tiene 31 dias";
		break;
		case 8:	
		    return "El mes de Agosto tiene 31 dias";
		break;
		case 9:
		    return "El mes de Septiembre tiene 30 dias";
		break;
		case 10:
		    return "El mes de Octubre tiene 31 dias";
		break;
		case 11:
		    return "El mes de Noviembre tiene 30 dias";
		break;
		case 12:
		    return "El mes de Diciembre tiene 31 dias";
		break;
		default:
		    return "Opcion no valida ingrese un numero de 1 a 12";
		break;
	}
}

void showProcesses(DWORD processID){
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );
    if (NULL != hProcess){
        HMODULE hMod;
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
    }
    if(string(szProcessName) != "<unknown>"){
        cout << szProcessName << " (" << processID << ")" << endl;
    }
    CloseHandle( hProcess );
}

void deleteProcess(int pid){
    HANDLE handy;
	handy =OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE, TRUE,pid);
	TerminateProcess(handy,0);
}

int main(int argc, char const *argv[]){

    cout << "\n";

    if (argc == 1){
       showHelp();
       cout << endl;
       return 1;
    } else {
        for(int i = 1; i < argc; i++){
            string argument = string(argv[i]);
            if (isFunction(argument)) {
                if(string(argv[i]) == HELP or string(argv[i]) == HELP_ABBREVIATION){
                    showHelp();
                } else if(string(argv[i]) == TIME or string(argv[i]) == TIME_ABBREVIATION){
                    showTime();
                } else if(string(argv[i]) == PROCESSLIST or string(argv[i]) == PROCESSLIST_ABBREVIATION){
                    DWORD aProcesses[1024], cbNeeded, cProcesses;
                    unsigned int i;
                    if (!EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded )) return 1;
                    cProcesses = cbNeeded / sizeof(DWORD);
                    for (i = 0; i < cProcesses; i++){
                        if(aProcesses[i] != 0){
                            showProcesses( aProcesses[i] );
                        }
                    }
                } else if(string(argv[i]) == DELETEPROCESS or string(argv[i]) == DELETEPROCESS_ABBREVIATION){
                    if(argv[i+1] and !isFunction(argv[i+1])){
                        deleteProcess(stoi(string(argv[i+1])));
                    } else {
                        cout << "Debe proporcionar el PID para hacer la respectiva eliminacion. Ejemplo: baseos --deleteprocess 15840" << endl;
                    }
                } else if(string(argv[i]) == ADDITION or string(argv[i]) == ADDITION_ABBREVIATION){
                    if(argv[i+1] and argv[i+2] and !isFunction(argv[i+1]) and !isFunction(argv[i+2])){
                        int result = addition(stoi(string(argv[i+1])), stoi(string(argv[i+2])));
                        cout << "El resultado es la suma es: " << result << endl;
                    } else {
                        cout << "Debe proporcionar los dos numeros enteros despues de la funcion. Ejemplo: baseos --addition 20 30" << endl;
                    }
                } else if(string(argv[i]) == MONTHDAYS or string(argv[i]) == MONTHDAYS_ABBREVIATION){
                    if(argv[i+1] and !isFunction(argv[i+1])){
                        string result = monthdays(stoi(string(argv[i+1])));
                        cout << result << endl;
                    } else {
                        cout << "Debe proporcionar el numero del mes despues de la funcion. Ejemplo: baseos --monthdays 12" << endl;
                    }
                } else {
                    cout << "No se encontro la funcion especificada, puede consultar las funciones disponibles mediante el comando baseos --help" << endl;
                }  
            }
        }
        cout << endl;
        return 0;
    }
}