// int otherfunc(int arg1, int arg2) {
//     return 0;
// }

// int otherfunc2(int arg3, int arg4) {
//     return 0;
// }

// int noargfunc() {
//     int a;
//      a = 5;
//     return a;
// }


// int main(){

// int a;

// a = 1 + 2 + 3;
// println(a);
//     return 0;
// }



int funcOneParam(int arg1){
    
    return arg1 + 2;
}

int funcVoidTwoParam(int arg2, int arg3){
  return arg2 + arg3;
}

int funcNoparam()
 {
     return 5;
 }

int main(){
    int a,b;
    a=1;
    b = funcOneParam(7);
    println(b);

    a = funcNoparam();

    println(a);

    a=funcVoidTwoParam(a,b);
    println(a);
    return 0;
}
