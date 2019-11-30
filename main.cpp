#include<iostream>
#include<thread>
#include<map>
#include<algorithm>
using namespace std;

long long int sumaDivisores(long long int n){
    long long int suma = 0;
    for(long long int i=1;i<n;i++){
        if(n%(n/2)==0){
            if(n%i==0)
                suma = suma+i;
        }
        else{
            if(i>=n/2)
                break;
            if(n%i==0)
                suma = suma+i;
        }
    }
    return suma;
}

map<long long int,long long int> mapaDivisores(long long int final,long long int start){
    map<long long int,long long int> md;
    auto suma=0;
    for(long long int i=start;i<final;i++){
        suma=sumaDivisores(i);
        md.insert(pair<long long int,long long int>(i,suma));
    }
    return md;
}

map<long long int,long long int> mapaAmigos(map<long long int,long long int> m){
    map<long long int,long long int> temp;
    map<long long int,long long int> final;
    for(map<long long int,long long int>::iterator it1=m.begin();it1!=m.end();++it1){
        for(map<long long int,long long int>::iterator it2=m.begin();it2!=m.end();++it2){
            if(it1->first == it2->second && it1->second ==it2->first ){
                if(it1!=it2){
                    temp.insert(pair<long long int,long long int>(it1->first,it2->first));
                }
            }
        }
    }
    auto contador=0;
    for(map<long long int,long long int>::iterator it=temp.begin();it!=temp.end();++it){
        contador++;
        if(contador%2==0){
            final.insert(pair<long long int,long long int>(it->first,it->second));
        }
    }
    return final;
}

void mostrarMapa(long long int end, long long int start){
    map<long long int, long long int> m;
    m = mapaDivisores(end,start);
    m = mapaAmigos(m);
    for_each(m.begin(),m.end(),[](const pair<long long int,long long int> p){cout<<p.second<<"  es amigo de  "<<p.first<<endl;});
}

void mapaFinal(long long int n){
    int max_thread = thread::hardware_concurrency();
    auto cant_thread = n/max_thread;
    long long int v1=0,v2=0,v3=0,v4=0;
    int j = 0;
    for (int i=0;i<max_thread;i++){
        switch(i){
            case 0:
                v1 = j+2;
                break;
            case 1:
                v2 = j-1;
                break;
            case 2:
                v3 = j-1;
                break;
            case 4:
                v4 = j-1;
                break;
        }
        j+=cant_thread;
    }

    thread t1(mostrarMapa(v1,2));
    thread t2(mostrarMapa(v3,v2);
    thread t3(mostrarMapa(v4,v3);
    thread t4(mostrarMapa(n,v4));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

int main(){
    mapaFinal(200000);
    return 0;
}
