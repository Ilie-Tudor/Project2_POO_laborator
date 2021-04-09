#include <iostream>
using namespace std;




class Stack{
public:
    virtual Stack& operator<<(int x) = 0;
    virtual Stack& operator>>(int &x) = 0;
    virtual bool operator!() = 0;
    virtual ~Stack(){};

    void operator-(){
        while(!(*this)){
            int x;
            (*this)>>x;
        }
    }
    bool operator ==(Stack &s){
        int temp1[1000],temp2[1000],lt1=0,lt2=0,h1,h2;
        bool rez = true;
        while(!s && !(*this)){
            s>>h1;
            temp1[lt1++]=h1;
            (*this)>>h2;
            temp2[lt2++]=h2;
            if(h1!=h2){rez = false;}
        }
        if(!s==true)  rez = false;
        if(!(*this)==true)  rez = false;

        while(!s){
            s>>h1;
            temp1[lt1++]=h1;
        }
        while(!(*this)){
            (*this)>>h2;
            temp2[lt2++]=h2;
        }
        for(int i=lt1-1;i>=0;i--){
            s<<temp2[i];
        }
        for(int i=lt2-1;i>=0;i--){
            (*this)<<temp2[i];
        }
        return rez;
    }
    bool operator !=(Stack &s){
        if((*this)==s)  return false;
        return true;
    }
    Stack& operator=(Stack &s){
        int temp[1000],h;
        int lt=0;
        while(!s){
            s>>h;
            temp[lt++]=h;
        }
        -(*this);
        for(int i=lt-1;i>=0;i--){
            (*this)<<temp[i];
            s<<temp[i];
        }
        return (*this);
    }

};
istream& operator>>(istream& in, Stack& s){
    -s;
    int n;
    cout<<"Numarul de elemente citite: ";
    in>>n;
    cout<<"Scrieti elementele: ";
    while(n--){
        int elem;
        in>>elem;
        s<<elem;
    }
    return in;
}
ostream& operator<<(ostream& out, Stack& s){
    int v[1000], n=0;
    while(!s){
        int x;
        s>>x;
        v[n++]=x;
    }
    for(int i=n-1;i>=0;i--){
        s<<v[i];
    }
    for(int i=n-1;i>=0;i--){
        out<<v[i]<<" ";
    }
    out<<'\n';
    return out;
}
class List{
public:
    virtual void Reset() = 0;
    virtual bool Next() = 0;
    virtual bool End() = 0;
    virtual bool Ins_next(int x) = 0;
    virtual bool Del_next() = 0;
    virtual bool Get_next(int &x) = 0;
    virtual ~List(){}
    void operator-(){
        (*this).Reset();
        int nrElem = 0;
        while(!(*this).End()){
            nrElem++;
            (*this).Next();
        }
        while(nrElem>=1){
            (*this).Reset();
            for(int i=0;i<nrElem-1;i++){
                (*this).Next();
            }
            (*this).Del_next();
            nrElem--;
        }
        (*this).Reset();
    }
    bool operator ==(List &l){
        int PozRelativaLaFinalThis=0;
        int nThis=0;
        while(!(*this).End()){
            PozRelativaLaFinalThis++;
            (*this).Next();
        }
        (*this).Reset();
        while(!(*this).End()){
            nThis++;
            (*this).Next();
        }
        (*this).Reset();

        int PozRelativaLaFinalL=0;
        int nL=0;
        while(!l.End()){
            PozRelativaLaFinalL++;
            l.Next();
        }
        l.Reset();
        while(!l.End()){
            nL++;
            l.Next();
        }
        l.Reset();
        bool rez=true;
        while(!l.End() && !(*this).End()){
                int x;
                int y;
                (*this).Get_next(x);
                (*this).Next();
                l.Get_next(y);
                l.Next();
                if(x!=y)
                {

                    rez=false;
                }
        }
        if(!l.End()) rez=false;
        if(!(*this).End()) rez=false;

        l.Reset();
        (*this).Reset();
        for(int i=0;i<nL-PozRelativaLaFinalL;i++){
            l.Next();
        }
        for(int i=0;i<nThis-PozRelativaLaFinalThis;i++){
            (*this).Next();
        }
        return rez;
    }
    bool operator!=(List &l){
        if(!((*this)==l)){
            return true;
        }
        return false;
    }
    void operator=(List &copie){
        -(*this);
        copie.Reset();
        while(!copie.End()){
            int x;
            copie.Get_next(x);
            (*this).Ins_next(x);
            (*this).Next();
            copie.Next();
        }
    }

};
class Vector{
    int *buf;
    int n;
public:
    Vector(){
        buf = new int[0];
        n=0;
    }
    Vector(int x){
        buf = new int[1];
        n = 1;
        buf[0] = x;
    }
    Vector(int x, int *p){ /// am declarat si un constructor pe baza unui vector static normal (for testing purposes)
        n = x;
        buf = new int[n];
        for(int i=0;i<n;i++){
            buf[i] = p[i];
        }
    }
    Vector(Vector &copiat){
        n = copiat.n;
        buf = new int[n];
        for(int i=0;i<n;i++){
            buf[i] = copiat.buf[i];
        }
    }
    ~Vector(){
        delete[] buf;
    }
    int& operator[](int i){
        if(0<=i && i<n)     return buf[i];
        else if(i<0)    return buf[0]; /// aici trebuie sa vad daca vreau sa pastrez asa returnand primul element sau daca mai bine arunc o exceptie;
        else{
            int *bufTemp = new int[i+1];
            int j=0;
            for(j=0;j<n;j++){
                bufTemp[j] = buf[j];
            }
            n = i+1;
            for(;j<n;j++){
                bufTemp[j]=0;
            }
            delete[] buf;
            buf = bufTemp;
            return buf[i];
        }
    }
    int length(){
        return n;
    }
    Vector& operator=(Vector &copiat){
        delete[] buf;
        n = copiat.length();
        buf = new int[copiat.length()];
        for(int i=0;i<n;i++){
            buf[i]=copiat[i];
        }
        return *this;
    }
    bool truncate(int dim){
        if(dim>=n || dim<0) return false;
        else{
            int *temp = new int[dim];
            for(int i=0;i<dim;i++){
                temp[i] = buf[i];
            }
            delete[] buf;
            n=dim;
            buf = temp;
        }
        return true;
    }
};
class Stack_List:public Stack, private List{
public:
    virtual ~Stack_List(){};
    Stack& operator<<(int x){
        (*this).Reset();
        while(!this->End()){
            this->Next();
        }
        this->Ins_next(x);
        this->Reset();
        return (*this);
    }
    Stack& operator>>(int &x){
        (*this).Reset();
        int nrElem = 0;
        while(!(*this).End()){
            nrElem++;
            (*this).Next();
        }
        this->Reset();
        for(int i=0;i<nrElem-1;i++){
            this->Next();
        }
        int g;
        this->Get_next(g);
        x=g;
        this->Del_next();
        (*this).Reset();
        return (*this);
    }
    bool operator!(){
        (*this).Reset();
        if(!this->End()) return true;
        return false;
    }

};
class Stack_List_Vector:public Stack_List, private Vector{

static int nrAparitii;
int k=0;
public:
    static int GetNrAparitii(){
        return nrAparitii;
    }
    Stack_List_Vector(){
        nrAparitii++;
    }
    void Reset(){
        k=0;
    }
    bool Next(){
        if(k!=(*this).length())
        {
            k++;
            return true;
        }
        else{
            return false;
        }
    }
    bool End(){
        if(k==(*this).length()){
            return true;
        }
        return false;
    }
    bool Ins_next(int x){
        for(int i = this->length()-1; i>=k; i--){
            int u=(*this)[i];
            (*this)[i+1]=u;
        }
        (*this)[k]=x;
        return true;
    }
    bool Del_next(){
        for(int i=k+1;i<this->length();i++){
            int u=(*this)[i];
            (*this)[i-1]=u;
        }
        if(k<this->length())    {(*this).truncate(this->length()-1); return true;}
        return false;
    }
    bool Get_next(int &x){
        if(k<this->length())    {x=(*this)[k]; return true;}
        else x=(*this)[k-1];
        return false;
    }
    bool operator == (Stack_List_Vector& l){
        int PozRelativaLaFinalThis=0;
        int nThis=0;
        while(!(*this).End()){
            PozRelativaLaFinalThis++;
            (*this).Next();
        }
        (*this).Reset();
        while(!(*this).End()){
            nThis++;
            (*this).Next();
        }
        (*this).Reset();

        int PozRelativaLaFinalL=0;
        int nL=0;
        while(!l.End()){
            PozRelativaLaFinalL++;
            l.Next();
        }
        l.Reset();
        while(!l.End()){
            nL++;
            l.Next();
        }
        l.Reset();

        bool rez=true;
        while(!l.End() && !(*this).End()){
                int x;
                int y;
                (*this).Get_next(x);
                (*this).Next();
                l.Get_next(y);
                l.Next();
                if(x!=y)
                {

                    rez=false;
                }
        }
        if(!l.End()) rez=false;
        if(!(*this).End()) rez=false;

        l.Reset();
        (*this).Reset();
        for(int i=0;i<nL-PozRelativaLaFinalL;i++){
            l.Next();
        }
        for(int i=0;i<nThis-PozRelativaLaFinalThis;i++){
            (*this).Next();
        }
        return rez;

    }
    bool operator != (Stack_List_Vector& l){
        if((*this)==l) return false;
        return true;
    }
    Stack_List_Vector& operator =(Stack_List_Vector& copie){
        (*this).Reset();
        int nrElem = 0;
        while(!(*this).End()){
            nrElem++;
            (*this).Next();
        }
        copie.Reset();
        while(!copie.End()){
            int x;
            copie.Get_next(x);
            (*this).Ins_next(x);
            (*this).Next();
            copie.Next();
        }
        (*this).Reset();
        return (*this);
    }

};
int Stack_List_Vector::nrAparitii=0;

int main(){

Stack_List_Vector s,t,r;
cin>>s;
t=s;
cout<<"Prima afisare a lui t: "<<t;
cout<<"A doua afisare a lui t: "<<t;
while(!t){
    int x;
    t>>x;
    r<<x;
}
cout<<"Afisarea lui r: "<<r;
if(r==s){
    cout<<"r si s sunt egale";
}
else cout<<"r si s nu sunt egale ";

}

