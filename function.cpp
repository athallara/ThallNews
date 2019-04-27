#include "header.h"
/*----------------------- CONSTRUCT -----------------------*/
void pause(){
    //UNIX Cannot Using System Pause
    char x;
    do
    {
        cout << "Press (y) to continue...";
        cin >> x;
    } while (tolower(x) != 'y');
}

void menuList(articleList &A, tagList &T, pivotList &P, bool &stop){
    system("clear");
    articleAddress articlePointer;
    tagAddress tagPointer;

    int choose;

    do{
    cout << "=========================" << endl;
    cout << "   WELCOME TO  THALLNEWS   " << endl;
    cout << "=========================" << endl;
    cout << "1. Create Article" << endl;
   
    cout << "2. Show Articles Only" << endl;
    cout << "3. Show Tags Only" << endl;
    cout << "4. Show All Articles & Tags" << endl;

    cout << "5. Delete Data (Article/Tag)" << endl;
    cout << "6. Add new Tags" << endl;
    cout << "0. Exit" << endl;
    cout << "Pilih Menu : "; 
    cin >> choose;
    
    }while(choose < 0 or choose >= 7);
    
    switch (choose)
        {
        case 1:
            system("clear");
            getData(A,T,P);
            break;
        case 2:
            system("clear");
            viewArticle(A);
            break;
        case 3:
            system("clear");
            viewTag(T);
            break;
        case 4:
            system("clear");
            viewPivot(A,T,P);
            break;
        case 5:
            system("clear");
            deleteData(A,T,P);
            break;
        case 6:
            system("clear");
            addNewTag(A,T,P);
            break;
        case 0:
            cout << "See You Later..";
            stop = true;
            break;
        default:
            cout << "Sorry, Menu not Found!";
            break;
        }
}

/*----------------------- ARTICLE FUNCTION -----------------------*/
void createArticleList(articleList &A){
    firstArticle(A) = NULL;
    lastArticle(A)  = NULL;
}

articleAddress AllocateArticle(articleInfo data){
    articleAddress Article = new articleElement;
    nextArticle(Article) and prevArticle(Article) == NULL;
    infoArticle(Article) = data;

    return Article;
}

articleAddress searchArticle(articleList A, string articleTitle){
    articleAddress ArticlePointer = firstArticle(A);

    while(ArticlePointer != NULL){
        if(infoArticle(ArticlePointer).title == articleTitle) return ArticlePointer;
        else ArticlePointer = nextArticle(ArticlePointer);
    }
}

bool isEmptyArticle(articleList A){
    return firstArticle(A) == NULL;
}

void viewArticle(articleList A){
    cout << "=============================" << endl;
    cout << "         ARTICLE LIST        " << endl;
    cout << "=============================" << endl;

    if(isEmptyArticle(A)){
        cout << "Sorry, Article is Empty.";
    }else{
        articleAddress article = firstArticle(A);
        while(article != NULL){
            cout << infoArticle(article).title << " - " << infoArticle(article).desc << endl;
            article = nextArticle(article);
        }
    }
    pause();
}

void insertArticle(articleList &A, articleAddress ArticlePointer){
    if(isEmptyArticle(A)){
        firstArticle(A) = ArticlePointer;
        lastArticle(A)  = ArticlePointer;
    }else{
        prevArticle(ArticlePointer) = lastArticle(A);
        nextArticle(lastArticle(A)) = ArticlePointer;
        lastArticle(A)              = ArticlePointer;
    }
}

/*----------------------- TAG FUNCTION -----------------------*/
void createTagList(tagList &T){
    firstTag(T) = NULL;
    lastTag(T)  = NULL;
}

tagAddress AllocateTag(tagInfo data){
    tagAddress Tag = new tagElement;
    nextTag(Tag) and prevTag(Tag)   ==  NULL;
    infoTag(Tag).tagName   = data.tagName;
    infoTag(Tag).tagCount  = 1;

    return Tag;
}

tagAddress searchTag(tagList T, string tagName){
    tagAddress TagPointer = firstTag(T);
    while(TagPointer != NULL){
        if(infoTag(TagPointer).tagName == tagName) return TagPointer;
        else TagPointer = nextTag(TagPointer);
    }
}

bool isEmptyTag(tagList T){
    return firstTag(T) == NULL;
}

void insertTag(tagList &T, tagAddress TagPointer){
    if(isEmptyTag(T)){
        firstTag(T) = TagPointer;
        lastTag(T)  = TagPointer;
    }else{
        prevTag(TagPointer) = lastTag(T);
        nextTag(lastTag(T)) = TagPointer;
        lastTag(T)          = TagPointer;
    }
}

void viewTag(tagList T){
    cout << "=============================" << endl;
    cout << "         TAG LIST        " << endl;
    cout << "=============================" << endl;

    if(isEmptyTag(T)){
        cout << "Sorry, Tag is Empty.";
    }else{
        tagAddress tag = firstTag(T);
        while(tag != NULL){
            cout << infoTag(tag).tagName << " - " << infoTag(tag).tagCount << endl;
            tag = nextTag(tag);
        }
    }
    pause();
}

void addNewTag(articleList &A, tagList &T, pivotList &P){

    viewArticle(A);

    articleAddress articleSearch;
    tagAddress tagSearch, tags;
    pivotAddress pivots;

    articleInfo article;
    tagInfo tag;
    
    cout<<"Choose the article : ";
    cin>>article.title;
    cout<<endl;
    
    articleSearch = searchArticle(A, article.title);
    
    cout<<"insert new tag : ";
    cin>>tag.tagName;
    cout<<endl;
    
    tagSearch = searchTag(T, tag.tagName);
    
    if (tagSearch!=NULL){
        pivots = AllocatePivot(articleSearch, tagSearch);
        insertPivot(P, pivots);
    }else{
        tags = AllocateTag(tag);
        pivots = AllocatePivot(articleSearch, tags);
        insertPivot(P, pivots);
    }
}

/*----------------------- PIVOT FUNCTION -----------------------*/
void createPivotList(pivotList &P){
    firstPivot(P) = NULL;
    lastPivot(P)  = NULL;
}

bool isEmptyPivot(pivotList P){
    return firstPivot(P) == NULL;
}

pivotAddress AllocatePivot(articleAddress articleData, tagAddress tagData){
    pivotAddress Pivot = new pivotElement;
    nextPivot(Pivot) and prevPivot(Pivot) == NULL;
    articlePivot(Pivot) = articleData;
    tagPivot(Pivot)     = tagData;
    
    return Pivot;
}

void viewPivot(articleList A, tagList T, pivotList P){
    pivotAddress PivotPointer,NextPivotPointer;

    if(isEmptyPivot(P)){
        cout << "Sorry, Data is Empty!";
    }else{
        PivotPointer = firstPivot(P);

        //Show II : Bug Forever Loops! [FIXED 27/04/19]
        while(PivotPointer != NULL){
            cout << "---------------------" << endl;
            cout << "Article = " << infoArticle(articlePivot(PivotPointer)).title << endl;
            cout << "Desc    ="  << infoArticle(articlePivot(PivotPointer)).desc << endl;
            cout << "Tags    = " << infoTag(tagPivot(PivotPointer)).tagName << endl;
            cout << "---------------------" << endl;

            PivotPointer = nextPivot(PivotPointer);
        }
    }

    pause();
    
}

void insertPivot(pivotList &P, pivotAddress PivotPointer){
    if(isEmptyPivot(P)){
        firstPivot(P) = PivotPointer;
        lastPivot(P)  = PivotPointer;
    }else{
        prevPivot(PivotPointer) = lastPivot(P);
        nextPivot(lastPivot(P)) = PivotPointer;
        lastPivot(P)            = PivotPointer;
    }
}

/*----------------------- DATA HANDLER FUNCTION -----------------------*/
void getData(articleList &A, tagList &T, pivotList &P){
    articleAddress articles, articleSearch;
    tagAddress tags, tagSearch;
    pivotAddress pivots = NULL;

    cout << "=============================" << endl;
    cout << "       INSERT NEW ARTICLE    " << endl;
    cout << "=============================" << endl;

    articleInfo article;
    tagInfo tag;
    cout << "Masukkan Judul       = ";
    cin >> article.title;
    cout << "Masukkan Description = ";
    cin >> article.desc;
    cout << "Masukkan Tag         = ";
    cin >> tag.tagName;

    //Validation: Article is Exsist? Cannot Be Inserted : Insert Data;
    if(isEmptyArticle(A)){
        articles =  AllocateArticle(article);
        insertArticle(A, articles);
    }else{
        articleSearch = searchArticle(A,article.title);
        if(articleSearch != NULL){
            cout << "Article Already Exist!" << endl;
        }else{
            articles =  AllocateArticle(article);
            insertArticle(A, articles);
        }
    }

    //Validation: Tag is Exsist? Cannot Be Inserted and Counter++ : Insert Data;
    if(isEmptyTag(T)){
        tags     = AllocateTag(tag);
        insertTag(T,tags);
    }else{
        tagSearch = searchTag(T, tag.tagName);
        if(tagSearch != NULL){ 
            pivots = AllocatePivot(articles,tagSearch);
            infoTag(tagSearch).tagCount++;
        }else{
            tags     = AllocateTag(tag);
            insertTag(T,tags);
        }
    }
    
    //Merge Data: It Will Insert ArticlePointer & TagPointer into PivotListat
    mergeData(A,T,P,articles,tags,pivots);
}

void mergeData(articleList &A, tagList &T, pivotList &P, articleAddress ArticlePointer, tagAddress TagPointer, pivotAddress PivotPointer){
    if(PivotPointer != NULL){
        insertPivot(P,PivotPointer);
    }else{ 
        PivotPointer  = AllocatePivot(ArticlePointer, TagPointer);
        insertPivot(P,PivotPointer);
    }

    pause();
}

void deleteData(articleList &A, tagList &T, pivotList &P){
    int deleteOption;

    if(!isEmptyArticle(A)){
        cout << "Delete By : " << endl;
        cout << "1). Title   " << endl;
        cout << "2). Tags    " << endl;
        cout << "Your Answer? ";
        cin  >> deleteOption;

        if(deleteOption == 1){
            deleteArticleData(A,T,P);
        }else if(deleteOption == 2){
            deleteTagData(A,T,P);
        }else{
            cout << "Wrong Input!";
        }
    }else{
        cout << "Sorry! Data is Empty!";
    }
    pause();
}

void deletePivotFromArticle(pivotList &P, articleAddress ArticlePointer){
    pivotAddress PivotPointer, tempPivot;
    PivotPointer = firstPivot(P);

    while(PivotPointer != NULL){
        if(articlePivot(PivotPointer) == ArticlePointer){
            if(PivotPointer == firstPivot(P)){
                tempPivot = firstPivot(P);
                firstPivot(P) = nextPivot(tempPivot);
                nextPivot(tempPivot) = NULL;
                prevPivot(firstPivot(P)) = NULL;
            }else if(articlePivot(lastPivot(P)) == ArticlePointer){
                tempPivot    = lastPivot(P);
                lastPivot(P) = prevPivot(tempPivot);
                prevPivot(tempPivot)    = NULL;
                nextPivot(lastPivot(P)) = NULL;
            }else{
                tempPivot = PivotPointer;
                nextPivot(prevPivot(PivotPointer)) = nextPivot(tempPivot);
                prevPivot(nextPivot(PivotPointer)) = prevPivot(tempPivot);
                nextPivot(tempPivot) = NULL;
                prevPivot(tempPivot) = NULL;
            }
            delete tempPivot;
        }
        PivotPointer = nextPivot(PivotPointer);
    }
}

void deleteArticleData(articleList &A, tagList &T, pivotList &P){
    string titleName;
    articleAddress articleSearch;
    cout << "Insert Title = ";
    cin  >> titleName;

    articleSearch = searchArticle(A, titleName);
    if(articleSearch == NULL){
        cout << "Sorry, Article Not Found!";
    }else{
        deletePivotFromArticle(P,articleSearch);
    }
}

void deleteTagData(articleList &A, tagList &T, pivotList &P){
    string tagName;
    tagAddress tagSearch;
    cout << "Insert Tag = ";
    cin  >> tagName;

    tagSearch = searchTag(T, tagName);
    if(tagSearch == NULL){
        cout << "Sorry, Tags Not Found!";
    }else{
        deletePivotFromTag(P,tagSearch);
    }
}

void deletePivotFromTag(pivotList &P, tagAddress TagPointer){
    pivotAddress PivotPointer, tempPivot;
    PivotPointer = firstPivot(P);

    while(PivotPointer != NULL){
        if(tagPivot(PivotPointer) == TagPointer){
            if(PivotPointer == firstPivot(P)){
                cout << "ADA DIAWAL";
                tempPivot = firstPivot(P);
                firstPivot(P) = nextPivot(tempPivot);
                nextPivot(tempPivot) = NULL;
                prevPivot(firstPivot(P)) = NULL;
            }else if(tagPivot(lastPivot(P)) == TagPointer){
                cout << "ADA DITENGAH";
                tempPivot    = lastPivot(P);
                lastPivot(P) = prevPivot(tempPivot);
                prevPivot(tempPivot)    = NULL;
                nextPivot(lastPivot(P)) = NULL;
            }else{
                cout << "ADA DIAKHIR";
                tempPivot = PivotPointer;
                nextPivot(prevPivot(PivotPointer)) = nextPivot(tempPivot);
                prevPivot(nextPivot(PivotPointer)) = prevPivot(tempPivot);
                nextPivot(tempPivot) = NULL;
                prevPivot(tempPivot) = NULL;
            }
            delete tempPivot;
        }
        PivotPointer = nextPivot(PivotPointer);
    }
}