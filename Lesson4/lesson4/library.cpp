#include "library.h"

Library::Library() {
}

Book &Library::getBook(quint32 bookNumber) {
    shelveMutex.lock();

    shelveMutex.unlock();
}

void Library::putBook(Book &book, bookNumber) {
    shelveMutex.lock();

    shelveMutex.unlock();
}
