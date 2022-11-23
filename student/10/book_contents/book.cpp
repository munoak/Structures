#include "book.hh"

Book::Book()
{

}

Book::~Book()
{
    // deallocate memory
    for (std::pair<std::string, Chapter*> ch : chapters_)
    {
        delete ch.second;
    }
}

void Book::addNewChapter(const std::string &id, const std::string &fullName, int length)
{
    // check if book already exists
    if (chapters_.find(id) != chapters_.end())
        std::cout << "Error: Already exists." << std::endl;

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
        return;

    // Fetch the sub chapter
    Chapter *sub_ptr = chapters_.at(subchapter),
            *parent_ptr = chapters_.at(parentChapter);

    // Add subchapter to parent
    parent_ptr->subchapters_.push_back(sub_ptr);
    sub_ptr->parentChapter_ = parent_ptr;
}

void Book::printIds(Params) const
{
    std::map<std:: string, std::string> mp_ids = {};
    std::cout << "Book has " << chapters_.size() << " chapters:" << std::endl;
    for (auto &ch : chapters_)
    {
        mp_ids.insert({ch.second->fullName_, ch.second->id_});
    }
    for (auto itr = mp_ids.begin(); itr != mp_ids.end(); ++itr)
    {
        std::cout   << itr->first << " --- "
                    << itr->second
                    << std::endl;
    }
}

void Book::printContents(Params) const
{
    // avoid repetetive prints finding the top chapter first
    std::set<Chapter*> topmost = {};

    for (auto &ch : chapters_)
    {
        // top most chapters ----- > Doesn't have parent chapter
        if(ch.second->parentChapter_ == nullptr)
        {
            topmost.insert(ch.second);
        }
    }
    int counter = 1;
    for (Chapter *ch : topmost )
    {
        printChapterRecursively(ch, "",counter++);
    }
}

void Book::close(Params params) const
{
    Chapter *chptr = findChapter(params[0]);
    if (chptr != nullptr)
    {
        chptr->isOpen_=false;
    }
    else{
        std::cout << "Error: Not found: " << params[0] << std::endl;
    }
}

void Book::open(Params params) const
{
    Chapter *chptr = findChapter(params[0]);
    if (chptr != nullptr)
    {
        chptr->isOpen_=true;
    }
    else{
        std::cout << "Error: Not found: " << params[0] << std::endl;
    }
}

void Book::openAll(Params) const
{
    for (auto &ch : chapters_)
    {
        ch.second->isOpen_=true;
    }
}

void Book::printParentsN(Params) const
{

}

void Book::printSubchaptersN(Params) const
{

}

void Book::printSiblingChapters(Params) const
{

}

void Book::printTotalLength(Params params) const
{
    int size =0;
    Chapter *chptr = findChapter(params[0]);
    for(auto &ch : chapters_)
    {
        if (ch.second->id_ == chptr->id_ || ch.second->parentChapter_ == chptr)
            size += ch.second->length_;
    }
    std::cout << "Total length of " << params[0] << " is " << size << std::endl;

}

void Book::printLongestInHierarchy(Params params) const
{
    int size =0;
    Chapter *chptr = findChapter(params[0]);
    for(auto &ch : chapters_)
    {
        if (ch.second->id_ == chptr->id_){

            for(uint i=0; i< ch.second->subchapters_.size() ; i++){
                if(ch.second->subchapters_.at(i)->length_ > chptr->length_)
                {
                    size= ch.second->subchapters_.at(i)->length_;
                }
            }
        }
    }
        std::cout << "With the length of " << size << params[0] << " is " << size << std::endl;

}
void Book::printShortestInHierarchy(Params) const
{

}

void Book::printParent(Params) const
{

}

void Book::printSubchapters(Params) const
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

void Book::printGroup(const std::string &, const std::string &, const IdSet &) const
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

void Book::printChapterRecursively(const Chapter *ptr,
                                   const std::string &indents,
                                   int index) const
{
    // head recursive

    // trivial case is when chapert does not have subchapter
    char sign = ptr->isOpen_? '-' : '+';
    std::cout  << sign << " " << indents << index << ". "<<
                  ptr->fullName_ << " ( " << ptr->length_ << " ) " <<
                  std::endl;

    // Check if opened
    if (ptr->isOpen_)
    {
        int counter = 1;
        for (Chapter *ch : ptr->subchapters_)
        {
            printChapterRecursively(ch,
                                    indents + "  ",
                                    counter++);
        }
    }
}
