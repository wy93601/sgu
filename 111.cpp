#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

typedef int digit;
class bigNum{
public:
    vector <digit> a;
    int n;
public:
    bigNum(){//构造函数 
	n=0;
    }
    int make (int c){//将数字转化为向量 
	int l=0;
	a.resize(30);
	while (c>0){
	    a[l++]=c%10;
	    c/=10;
	}
	--l;
	while (l>0 && a[l]==0) --l;
	n=l+1;
	return l+1;
    }
    int make (string c){//将字符数组转化为向量 
	int l=c.size();
	a.resize(l);
	n=l;
	for (int i=0;i<l;++i){
	    a[i]=c[l-i-1]-'0';
	}
	--l;
	while (l>0 && a[l]==0) --l;
	n=l+1;
	return l+1;
    }
    void pout(){//输出 
	for (int i=n-1;i>-1;--i)
	    cout<<a[i];
	cout<<endl;
    }
    friend bigNum operator+(bigNum &a,bigNum &b){//重载+ 
	bigNum r;
	int m=a.n>b.n?a.n:b.n;
	r.n=m;
	r.a.resize(m+10);
	for (int i=0;i<m;++i){
	    if (a.n>i) r.a[i]+=a.a[i];
	    if (b.n>i) r.a[i]+=b.a[i];
	    r.a[i+1]+=r.a[i]/10;
	    r.a[i]%=10;
	}
	++r.n;
	while (r.n>0 && r.a[r.n]==0) --r.n;
	++r.n;
	return r;
    }
    friend bigNum operator -(bigNum &a,bigNum &b){//默认传入a>b 重载- 	
	bigNum r=a;
	int m=r.n;
	for (int i=0;i<m;++i){
	    if (b.n>i) r.a[i]-=b.a[i];int j=i;
	    while (r.a[j]<0){
		r.a[j]+=10;
		--r.a[j+1];
	    }
	}
	--m;
	while (m>0 && r.a[m]==0) --m;
	r.n=m+1;
	return r;
    }
    friend bool operator >(bigNum &a,bigNum &b){//重载> 比较大小 
	if (a.n>b.n) return 1;
	if (a.n<b.n) return 0;
	for (int i=a.n-1;i>=0;--i){
	    if (a.a[i]>b.a[i]) return 1;
	    if (a.a[i]<b.a[i]) return 0;
	}
	return 0;
    }
    friend bool operator >=(bigNum &a,bigNum &b){//重载>= 比较大小 
	if (a.n>b.n) return 1;
	if (a.n<b.n) return 0;
	for (int i=a.n-1;i>=0;--i){
	    if (a.a[i]>b.a[i]) return 1;
	    if (a.a[i]<b.a[i]) return 0;
	}
	return 1;
    }
    friend bool operator <(bigNum &a,bigNum &b){//重载< 比较大小
	if (a.n<b.n) return 1;
	if (a.n>b.n) return 0;
	for (int i=a.n-1;i>=0;--i){
	    if (a.a[i]>b.a[i]) return 0;
	    if (a.a[i]<b.a[i]) return 1;
	}
	return 0;
    }
    friend bool operator <=(bigNum &a,bigNum &b){//重载<= 比较大小
	if (a.n<b.n) return 1;
	if (a.n>b.n) return 0;
	for (int i=a.n-1;i>=0;--i){
	    if (a.a[i]>b.a[i]) return 0;
	    if (a.a[i]<b.a[i]) return 1;
	}
	return 1;
    }
    friend bool operator ==(bigNum &a,bigNum &b){//重载== 
	if (a.n!=b.n) return 0;
	for (int i=0;i<a.n;++i)
	    if (a.a[i]!=b.a[i]) return 0;
	return 1;
    }
    friend bigNum operator * (bigNum &a,int b){//重载* 高精度*低精度 
	bigNum r=a;
	r.a.resize(r.n+100);
	int m=r.n;
	for (int i=0;i<m;++i)
	    r.a[i]*=b;
	for (int i=0;i<m;++i){
	    r.a[i+1]+=r.a[i]/10;
	    r.a[i]%=10;
	}
	while (r.a[m]>=10) {r.a[m+1]+=r.a[m]/10;r.a[m++]%=10;}
	r.n=m+1;while (r.a[r.n-1]==0) --r.n;
	return r;
    }
    friend bigNum operator * (bigNum &a,bigNum &b){//重载* 高精度*高精度 
	bigNum r,temp;
	r.a.resize(a.n+b.n);
	int k;
	for (int i=0;i<a.n;++i){
	    if (b.n<=i) continue;
	    temp=a*b.a[i];
	    temp=temp<<i;
	    r=r+temp;
	}
	r.n=a.n+b.n-1;
	for (int i=0;i<r.n;++i){
	    r.a[i+1]+=r.a[i]/10;
	    r.a[i]%=10;
	}
	while (r.n>0 && r.a[r.n]==0) --r.n;
	++r.n;
	return r;
    }
    friend bigNum operator << (bigNum &a,int b){//重载左移运算符，扩大10倍 
	bigNum r;
	r.a.resize(a.n+b);
	for (int i=0;i<a.n;++i)
	    r.a[i+b]=a.a[i];
	r.n=a.n+b;
	return r;
    }
};

string num,numTmp="";
bigNum tmp,tmp1,tmp2,divisor,divisorTmp;
int pos;

int main(){
    cin >> num;
    if (num.size()%2==1){
	numTmp=num[0];
	tmp.make(numTmp);
	pos++;
    }
    else{
	numTmp+=num[0];numTmp+=num[1];
	tmp.make(numTmp);
	pos+=2;
    }
    for (int i=9;i>=1;i--){
	bigNum tryIt;
	tryIt.make(i);tryIt=tryIt*tryIt;
	if (tryIt<=tmp) {divisor.make(i);break;}
    }
    tmp2=divisor*divisor;
    tmp1=tmp-tmp2;
    while (pos!=num.size()){
	numTmp="";
	numTmp+=num[pos];numTmp+=num[pos+1];pos+=2;;
	tmp.make(numTmp);
	tmp1=tmp1*100;tmp1=tmp1+tmp;
	for (int i=9;i>=0;i--){
	    bigNum tryIt;tryIt.make(i);
	    tmp2 = divisor*20;tmp2=tmp2+tryIt;tmp2=tmp2*tryIt;
	    if (tmp2<=tmp1){
		divisorTmp.make(i);
		break;
	    }
	}
	tmp1=tmp1-tmp2;	
	divisor=divisor*10;divisor=divisor+divisorTmp;
    }
    divisor.pout();
}
