#include <iostream>
#include <cmath>
// Дефайны для ввода
#define DEF1(func) ({char _f = (func); (_f == 's' ? (sin_) : (_f == 'c' ? (cos_) : (_f == 'e' ? (exp_) : (ln_))));})
#define DEF2(func) ({char _f = (func); (_f == 's' ? (sin(x)) : (_f == 'c' ? (cos(x)) : (_f == 'e' ? (exp(x)) : (log(x+1)))));})
#define DEF3(func) ({char _f = (func); (((_f == 'e') || (_f == 'c')) ? 1 : (x));})

using namespace std;

// Подсчёт членов ряда
float exp_(float x, int n){
    return x/n;}
float sin_(float x, int n){
    return -(x*x)/(2*n*(2*n+1));}
float cos_(float x, int n){
    return -(x*x)/(2*n*(2*n-1));}
float ln_(float x, int n){
    return (-1)*(x*n/(n+1));}

// Реализация суммирования
// Прямое суммирование
float sumd(float x0, float x, int n, float(*f)(float, int)){
    float mem, res;
    mem=res=x0;
    for(int i=1; i<n; i++){
        mem*=f(x, i);
        res+=mem;}
    return res;}
// Обратное суммирование
float sumr(float x0, float x, int n, float(*f)(float, int)){
    float mem, res=0;
    mem=res=float(x0);
    for(int i=1; i<=n; i++){
        if(mem*f(x, i)==0){
            n=i-1;
            break;}
        mem*=f(x, i);}
    for(int i=0; i<n; i++){
        res+=mem;
        mem/=(f(x, n-i));}
    return res;}
// Парное суммирование
float sumsr(float x0, float x, int n, float(*f)(float, int)){
    float memd, memr, res;
    memr=memd=res=float(x0);
    for(int i=1; i<=n; i=i+1){
        memr*=f(x, i);}
    for(int i=1; i<=(int)n/2; i++){
        memd*=f(x, i);
        memr/=f(x, n-i+1);
        res+=memr+memd;}
    res-=memd;
    return res;}

int main(){
    float x; int n;
    char func;
    cout<<"> sin(x) - s\n> cos(x) - c\n> e^x - e\n> ln(1+x) - l\n> Enter function: "; cin>>func;
    if(func!='s' && func!='c' && func!='e' && func!='l'){
        cout<<"  Input Error! Please, restart programm.";
        return 0;}
    cout<<"> Enter argument: "; cin>>x;
    cout<<"> Enter number of terms: "; cin>>n;
    if(n < 0){
        cout<<"  Input Error! Please, restart programm.";
        return 0;}
    printf("Straight sum = %.15f\n", sumd(DEF3(func), x, n, DEF1(func)), '\n');
    printf("Reverse sum = %.15f\n", sumr(DEF3(func), x, n, DEF1(func)), '\n');
    printf("Pair sum = %.15f\n", sumsr(DEF3(func), x, n, DEF1(func)), '\n');
    printf("Function in cmath = %.15f\n", DEF2(func));
    return 0;}