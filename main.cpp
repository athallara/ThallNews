/* 
//   TUGAS BESAR STRUKTUR DATA - THALL NEWS!
//   IMPLEMENT MULTI LINKED LIST with STUPID FCKIN' OOP CONCEPT :v
//   PROGRESS : 80%, Will be Countinued if(!Mager)

//   Created By : Athalla Rizky w/ Iyank (Collabolator)
//   Message: GOODBYE LINKED LIST! :P 27/05/19
*/

#include "header.h"

int main(){
    system("clear");
    bool stop = false;

    articleList A;
    createArticleList(A);

    tagList T;
    createTagList(T);

    pivotList P;
    createPivotList(P);

    while(not(stop)) {
        menuList(A,T,P,stop);
    }

    cout << endl;
    return 0;
}