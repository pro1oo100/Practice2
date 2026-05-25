#include <iostream>
bool simple(int& mod);
bool ferm(int& num, int& mod);
bool input(int& num, int& pow, int& mod);
int modulo(int&num, int& pow, int& mod);
int main(){
	int num, pow, mod;
	if(input(num,pow,mod))
		std::cout<<modulo(num,pow,mod)<<std::endl;
	else
		std::cout<<"Некорректные значения"<<std::endl;
	return 0;
}
bool ferm(int& num, int& mod){
	bool isDone=0;
	if(simple(mod))
		if(num%mod!=0)
			isDone=1;
	return isDone;
}
bool simple(int& mod){
	bool isDone=1;
	for(int i=2;i*i<=mod;++i)
		if(mod%i==0)
			isDone=0;
	return isDone;
}
int modulo(int& num, int& pow, int& mod){
	num%=mod;
	int result=1;
	if(ferm(num, mod))
		pow%=mod-1;
	while(pow>0){
		if(pow%2!=0)
			result=result*num%mod;
		num=(num*num)%mod;
		pow/=2;
	}
	return result;
}
bool input(int& num, int& pow, int& mod){
	bool isDone=0;
	if(std::cin>>num && num>=1 && std::cin>>pow && pow>-1 && std::cin>>mod && mod>1)
		isDone=1;
	return isDone;
}
