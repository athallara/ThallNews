//Libraries
#include <iostream>
#include <cstddef>
#include <cstdlib> // For System Clear
#include <cctype>  // For LowerCase
using namespace std;


//Articles Defined
#define firstArticle(A) A.first
#define lastArticle(A) A.last
#define nextArticle(A) A->next
#define prevArticle(A) A->prev
#define infoArticle(A) A->article

//Tags Defined
#define firstTag(T) T.first
#define lastTag(T) T.last
#define nextTag(T) T->next
#define prevTag(T) T->prev
#define infoTag(T) T->tag

//Pivot Defined
#define firstPivot(P) P.first
#define lastPivot(P) P.last
#define nextPivot(P) P->next
#define prevPivot(P) P->prev
#define articlePivot(P) P->articleElement
#define tagPivot(P) P->tagElement

typedef struct articleElement *articleAddress;
typedef struct pivotElement *pivotAddress;
typedef struct tagElement *tagAddress;

//----------STRUCT LIST DEFINED----------//
struct articleList{
    articleAddress first,last;
};

struct tagList{
    tagAddress first,last;
};

struct pivotList{
    pivotAddress first,last;
};

//----------ARTICLE DEFINED----------//
struct articleInfo{
    string title, desc;
};

struct articleElement{
    articleAddress next,prev;
    articleInfo article;
};

//----------TAG DEFINED----------//
struct tagInfo{
    string tagName;
    int tagCount;
};

struct tagElement{
    tagAddress next,prev;
    tagInfo tag;
};

//----------PIVOT DEFINED----------//
struct pivotElement{
    pivotAddress next,prev;
    articleAddress articleElement;
    tagAddress tagElement;
};

//__Construct
void menuList(articleList &A, tagList &T, pivotList &P, bool &stop);


//Article Function
articleAddress AllocateArticle(articleInfo data);
void createArticleList(articleList &A);
bool isEmptyArticle(articleList A);
void viewArticle(articleList A);
void insertArticle(articleList &A, articleAddress ArticlePointer);
void deleteArticleData(articleList &A, tagList &T, pivotList &P);
articleAddress searchArticle(articleList A, string articleTitle);

//Tag Function
tagAddress AllocateTag(tagInfo data);
void createTagList(tagList &T);
bool isEmptyTag(tagList T);
void viewTag(tagList T);
void insertTag(tagList &T, tagAddress TagPointer);
void addNewTag(articleList &A, tagList &T, pivotList &P);
tagAddress searchTag(tagList T, string tagName);

//Pivot Function
pivotAddress AllocatePivot(articleAddress articleData, tagAddress tagData);
void createPivotList(pivotList &P);
bool isEmptyPivot(pivotList P);
void viewPivot(articleList A, tagList T, pivotList P); 
void insertPivot(pivotList &P, pivotAddress PivotPointer);
void deletePivotFromArticle(pivotList &P, articleAddress ArticlePointer);
void deletePivotFromTag(pivotList &P, tagAddress TagPointer);

//Data Handler Function
void getData(articleList &A, tagList &T, pivotList &P);
void deleteData(articleList &A, tagList &T, pivotList &P);
void mergeData(articleList &A, tagList &T, pivotList &P, articleAddress ArticlePointer, tagAddress TagPointer, pivotAddress PivotPointer);
void deleteArticleData(articleList &A, tagList &T, pivotList &P);
void deleteTagData(articleList &A, tagList &T, pivotList &P);


