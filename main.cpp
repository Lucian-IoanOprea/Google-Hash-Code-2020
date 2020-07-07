#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream in("f_libraries_of_the_world.txt");
ofstream out("outf.txt");

struct Book
{
    long long id;
    long long score;
};

struct Library
{
    long long nr_books;
    long long signup_time;
    long long books_per_day;
    long long lib_id;
    Book *books;
    double potential;
};


bool cmp_libraries(Library x, Library y)
{
    return x.potential > y.potential;
}

bool cmp_books(Book x, Book y)
{
    return x.score > y.score;
}


int main(void)
{
    long long total_books;
    long long nr_libraries;
    long long total_days;
    
    in >> total_books >> nr_libraries >> total_days;
    //cout << total_books << " " << nr_libraries << " " << total_days << " ";
    long long book_scores[total_books];

    for(long long i = 0; i < total_books; ++i) {
        in >> book_scores[i];
    }
    
    Library libraries[nr_libraries];
    
    long long max_books;
    double sum;
    bool *used;
    long long t;
        
    for(long long j = 0; j < nr_libraries; ++j)
    {
        libraries[j].nr_books = 0;
        in >> max_books >> libraries[j].signup_time >> libraries[j].books_per_day;
        libraries[j].books = new Book[max_books];
        libraries[j].lib_id = j;
        sum = 0.0;
        //used = new bool[max_books];
        
        for(long long i = 0; i < max_books; ++i)
        {
            in >> t;
            libraries[j].books[libraries[j].nr_books].id = t;
            libraries[j].books[libraries[j].nr_books].score = book_scores[t];
            libraries[j].nr_books++;
            sum += book_scores[t];
                //used[t] = true;
            
        }
        sum /= libraries[j].nr_books;
        sum *= libraries[j].books_per_day;
        sum /= libraries[j].signup_time;
        libraries[j].potential = sum;
        
        // delete used;
        
        sort(libraries[j].books, libraries[j].books + libraries[j].nr_books, cmp_books);
    }
    
    sort(libraries, libraries + nr_libraries, cmp_libraries);
    
        
    long long current_day = 0;
    long long cnt_libraries = 0;
    long long cnt_books;
    
    
    for(long long j = 0; j < nr_libraries; ++j)
    {
        if(current_day + libraries[j].signup_time < total_days)
        {
            current_day += libraries[j].signup_time;
            cnt_libraries++;
        }
    }
    
    out << cnt_libraries << "\n";
    
    current_day = 0;
    
    for(long long j = 0; j < nr_libraries; ++j)
    {
        if(current_day + libraries[j].signup_time < total_days)
        {
            current_day += libraries[j].signup_time;
            if(libraries[j].books_per_day * (total_days - current_day) % libraries[j].nr_books == 0) 
                cnt_books = libraries[j].nr_books;
            else
                cnt_books = (libraries[j].books_per_day * (total_days - current_day)) % libraries[j].nr_books;
            out << libraries[j].lib_id << " " << cnt_books << "\n";
            for(long long i = 0; i < cnt_books; ++i)
                out << libraries[j].books[i].id << " ";
            out << "\n";
        }
    }
}
