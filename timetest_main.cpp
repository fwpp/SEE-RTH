#include <iostream>

double cpuTime(){
#ifdef _WIN32
    FILETIME a,b,c,d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0)
        return (double)(d.dwLowDateTime | ((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
    else
        return 0;

#elif defined(__linux__)
    return (double)clock() / CLOCKS_PER_SEC;
#endif
}

void foo(int n){
	if(n == 0)  return;
	foo(n-1);
	foo(n-1);
}

int main(int argc, char* argv[]){
	double start,end;
	start = cpuTime();
	foo(36);
	end = cpuTime();
	std::cout<<"Time: "<<end - start<<'\n';
	return 0;
}
