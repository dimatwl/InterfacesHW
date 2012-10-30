#ifndef LIBRARY_H
#define LIBRARY_H

#include <QThreadPool>
#include <QList>
#include <QMutex>
#include "Book.h"

class Library {
    QThreadPool pool;

    QList<Book> shelve;
    QMutex shelveMutex;
public:
    Library();

    Book& getBook(quint32 bookNumber);
    void putBook(Book& book, bookNumber);
};

#endif // LIBRARY_H
