// int f(int a){
//     return 2*a;
//     a=9;
// }

// int g(int a, int b){
//     int x;
//     x=f(a)+a+b;
//     return x;
// }

int main(){
    
    
    int a,b;
    int c[53];
    a=1;
    b=2 * a;
    a = b / a;
    
    a = 0;

    for( a = 0; a < 20; a = a + 1) {
        c[a] = a;
        
        b = c[a];

        println(b);
    }



    int j, asd; 

	j= 5 % 3;
    
    a = j + j;

	asd = 213;
	
    println(a);
    return 0;
}
