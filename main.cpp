#include <iostream>
using namespace std;




class Stack{
//- clasa abstracta 'stack', care descrie conceptul de stiva de intregi, avand:
//  metode pure publice:
//    operatorii '<<' (push), '>>' (pop), '!' (test stiva vida);
//    detalii: '<<', resp. '>>',  au intregul inserat, resp. extras, ca
//     parametru prin valoare, resp. referinta; '<<' si '>>' returneaza stiva
//     curenta prin referinta (pentru a permite push/pop miltiple); '!'
//     returneaza true/false;
//  metode virtuale publice:
//    destructor;
//  metode publice:
//    operatorii '-' (unar, videaza stiva curenta), '==' (testeaza egal) '!='
//    (testeaza diferit), '=' (atribuire);
//    detalii: '==', '!=', '=' au ca parametru prin referinta o stiva; '-' nu
//      returneaza nimic, '==' si '!=' returneaza 'true'/'false', '='
//      returneaza referinta la stiva curenta; '-', '==', '!=', '=' se vor
//      implementa deasupra primitivelor '<<', '>>', '!';
//- functiile independente (ne-prieten pentru 'stack'):
//    operatorii '>>' (citire 'stack' dintr-un 'istream'), '<<' (scriere
//      'stack'intr-un 'ostream');
//    detalii: '>>' si '<<' au ca parametri prin referinta streamul si stiva si
//     returneaza prin referinta streamul; ei se vor implementa deasupra
//     metodelor publice ale clasei 'stack';
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

}; // todo ... functiile independente pentru stack de citire si afisare din stream
//class stivaV : public Stack{
//    int n=0;
//    int v[100];
//public:
//    Stack& operator<<(int x){
//        v[n++]=x;
//        return (*this);
//    }
//    Stack& operator>>(int &x){
//        v[n-1]=0;
//        n--;
//        return (*this);
//    }
//    bool operator!(){}
//    void afis(){
//        for(int i=0;i<n;i++){
//            cout<<v[i]<<" ";
//        }
//        cout<<endl;
//    }
//};
class List{
//    - clasa abstracta 'list', care descrie conceptul de lista de intregi simplu
//    inlantuita, avand o pozitie curenta si permitand inserarea/eliminarea/
//    consultarea unui element dupa pozitia curenta; clasa contine:
//  metode publice pure:
//    'reset' (pozitia curenta se plaseaza inaintea primului element);
//    'next' (pozitia curenta avanseaza un element, daca se poate);
//    'end' (test daca dupa pozitia curenta nu mai sunt elemente);
//    'ins_next' (insereaza un intreg dupa pozitia curenta, daca se poate);
//    'del_next' (elimina elementul de dupa pozitia curenta, daca exista):
//    'get_next' (furnizeaza elementul de dupa pozitia curenta, daca exista);
//    detalii: 'ins_next' / 'get_next' au intregul inserat, resp. furnizat, ca
//     parametru prin valoare, resp. referinta; celelalte metode nu au
//     parametri; 'reset' nu returneaza nimic, celelalte metode returneaza
//     'true'/'false';
//  metode virtuale publice:
//    destructor;
//  metode publice:
//    operatorii '-' (unar, videaza lista curenta), '==' (testeaza egal) '!='
//    (testeaza diferit), '=' (atribuire);
//    detalii: '==', '!=', '=' au ca parametru prin referinta o lista; '-' nu
//      returneaza nimic, '==' si '!=' returneaza 'true'/'false', '='
//      returneaza referinta la lista curenta; '-', '==', '!=', '=' se vor
//      implementa deasupra primitivelor 'reset', 'next', 'end', 'ins_next',
//      'del_next', 'get_next'; '==' si '!=' vor lasa la sfarsit lista curenta
//      nemodificata, inclusiv in privinta pozitiei curente;
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
//class ListaTest:public List{
//private:
//    int n;
//    int v[100];
//    int pozCurent;
//public:
//    ListaTest(){
//        n=0;
//        pozCurent=0;
//    }
//    void Reset(){
//        pozCurent=0;
//    }
//    bool Next(){
//        if(pozCurent<n) pozCurent++;
//        else    return false;
//        return true;
//    }
//    bool End(){
//        if(pozCurent==n){
//            return true;
//        }
//        return false;
//    }
//    bool Ins_next(int x){
//        for(int i=n-1;i>=pozCurent; i--){
//            v[i+1]=v[i];
//        }
//        v[pozCurent] = x;
//        n++;
//    }
//    bool Del_next(){
//        for(int i=pozCurent;i<n-1;i++){
//            v[i]=v[i+1];
//        }
//        n--;
//    }
//    bool Get_next(int &x){
//        x = v[pozCurent];
//        return true;
//    }
//    void afisare(){
//        cout<<"l: ";
//        for(int i=0;i<n;i++){
//           cout<<v[i]<<" ";
//        }
//        cout<<endl;
//    }
//};
class Vector{
//    clasa 'vector', care descrie conceptul de vector de intregi, avand:
//  membri data privati:
//    'buf' (pointer la 'int', retine adresa zonei cu elementele, care este
//     alocata dinamic), 'n' ('int', numarul de elemente);
//  metode publice:
//    constructor implicit (initializeaza 'buf' si 'n' pentru vectorul vid);
//    constructor de conversie dinspre 'int' (creaza un vector cu un intreg);
//    constructor de copiere;
//    destructor (elibereaza resursele vectorului);
//    operatorul '[]' (indezare, returneaza referinta la intregul corespunzator
//      indicelui dat ca parametru, iar daca indicele este >= 'n', realoca zona
//      cu elementele);
//    operatorul '=' (atribuire, sursa este primita ca parametru prin referinta
//      la zona constanta, returneaza prin referinta vectorul curent);
//    'truncate" (realoca/truncheaza vectorul la dimensiunea data ca parametru
//      si returneaza 'true'/'false', insemnand succes/esec);
//    'length' (fara parametri, returneaza 'n');
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
    void afis(){
        for(int i=0;i<n;i++){
            cout<<buf[i]<<" ";
        }
        cout<<endl;
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
        if(dim>=n || dim<=0) return false;
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
        return (*this);
    }
    Stack& operator>>(int &x){
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
        return (*this);
    }
    bool operator!(){
        (*this).Reset();
        if(!this->End()) return true;
        return false;
    }

};
class Stack_List_Vector:public Stack_List, private Vector{
int k=0;
public:
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
            (*this)[i+1]=(*this)[i];
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
        return false;
    }
    void afisare(){this->afis();}
};

class T{
public:
    int x,y;
    T(int i, int j){
        x=i;y=j;
    }
    bool operator=(T& copie){
        (*this).x=3;y=3;
        copie.x=88;
    }
};
class Tderiv:public T{
public:
    Tderiv(int i=0, int j=0):T(i,j){};
    int z=7;
};
int main(){
//    int t[] = {1,2,3,4,5};
//    int tL = 5;
//    Vector v(tL, t),f,a;
//    v.afis();
//    a=f=v;
//    f.afis();
//    a.afis();
//    a.truncate(1);
//    a.afis();

//    Stack *stv,*stvC;
//    stv = new stivaV;
//    stvC = new stivaV;
//    (*stv)<<3<<4<<5<<6;
//    stv -> afis();
//    (*stvC)=(*stv);
//    int x;
//    (*stvC).afis();
//    while(!(*stv)){
//        (*stv)>>x;
//        cout<<x<<" ";
//    }
//    cout<<endl;
//    while(!(*stvC)){
//        (*stvC)>>x;
//        cout<<x<<" ";
//    }
//List *l1=new ListaTest,*l2=new ListaTest;
//(*l1).Ins_next(5);
//(*l1).Ins_next(6);
//(*l1).Ins_next(7);
//(*l2).Ins_next(4);
//
//(*l2)=(*l1);
//(*l1).afisare();
//(*l2).afisare();

Stack_List_Vector v;
v.Ins_next(13);
v.Next();
v.Ins_next(43);
v.Next();
v.Ins_next(53);
v.Next();
v.Ins_next(163);
v.Next();
v.Ins_next(23);
v.Del_next();
int x;
v.Get_next(x);
cout<<x<<endl;
v.afisare();

}

