int f(int a){
    return 2*a;
    a=9;
}

int g(int a, int b){
    int x;
    x=f(a)+a+b;
    return x;
}

int main(){
    int a,b;
    int c[53];
    int d[100];
    a=1;
    b=2;
    a=f(a);
    println(a);
    return 0;
}
