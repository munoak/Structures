#include "book.hh"

Book::Book()
{

}

Book::~Book()
{

}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    // check if book already exists
    if (chapters_.find(id) != chapters_.end())
    {
        std::cout<<"Error: Already exists."<<std::endl;
    }

    // Add new chapter
    // allocating memory
    Chapter *new_chapter = new Chapter {id, fullName, length};

    // Add to datat structure
    chapters_.insert({new_chapter->id_,
                      new_chapter});

}

void Book::addRelation(const std::string &subchapter, const std::string &parentChapter)
{
    // check if chapter exist
    if(chapters_.find(subchapter) == chapters_.end()
            || chapters_.find(parentChapter) == chapters_.end())
    {
        std::cout<<"Error: Already exists."<<std::endl;
    }

    // Fetch the sub chapter
    Chapter *sub_ptr = chapters_.at(subchapter),
            *parent_ptr = chapters_.at(parentChapter);

    // Add subchapter to parent
    parent_ptr->subchapters_.push_back(sub_ptr);
    sub_ptr->parentChapter_ = parent_ptr;
}

void Book::printIds(Params params) const
{

}

void Book::printContents(Params params) const
{

}

void Book::close(Params params) const
{

}

void Book::open(Params params) const
{

}

void Book::openAll(Params params) const
{

}

void Book::printParentsN(Params params) const
{

}

void Book::printSubchaptersN(Params params) const
{

}

void Book::printSiblingChapters(Params params) const
{

}

void Book::printTotalLength(Params params) const
{

}

void Book::printLongestInHierarchy(Params params) const
{

}

void Book::printShortestInHierarchy(Params params) const
{

}

void Book::printParent(Params params) const
{

}

void Book::printSubchapters(Params params) const
{

}

Chapter *Book::findChapter(const std::string &id) const
{
    Chapter *chapter_ptr = nullptr;
    // check if chapter is in the book
    Data::const_iterator iter = chapters_.find(id);
    if (iter != chapters_.end())
    {
        chapter_ptr = chapters_.at(id);
    }
    return chapter_ptr;
}

void Book::printGroup(const std::string &id, const std::string &group, const IdSet &container) const
{

}

IdSet Book::vectorToIdSet(const std::vector<Chapter *> &container) const
{
    IdSet idSet = {};
    for (const Chapter *p : container)
    {
        idSet.insert(p->id_);
    }
    return idSet;
}

void Book::printChapterRecursively(const Chapter *ptr, const std::string indents)
{
    // head recursive

    // trivial case is when chapert does not have subchapter
    char sign = ptr->isOpen_? '-' : '+';
}
