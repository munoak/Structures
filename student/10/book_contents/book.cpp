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
    Chapter *ch = findChapter(params[0]);
    if (ch != nullptr)
    {
        ch->isOpen_=true;
        for (auto sub_ch : ch->subchapters_)
        {
            if(sub_ch->subchapters_.size() !=0)
                sub_ch->isOpen_=false;
        }
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

void Book::printSiblingChapters(Params params) const
{
    std::set<std::string> siblings;
    Chapter *chptr = findChapter(params[0]);
    int total_siblings = 0;
    if (chptr != nullptr)
    {
        if (chptr->parentChapter_ != nullptr)
        {
            std::string parent = chptr->parentChapter_->id_;
            for (auto &chptr_i : chapters_)
            {
                if (chptr_i.second->parentChapter_ != nullptr &&
                        chptr_i.second->parentChapter_->id_ == parent &&
                        chptr_i.first != params[0])
                {
                    total_siblings++;
                    siblings.insert(chptr_i.first);
                }
            }
            std::cout<< params[0] <<" has " << total_siblings
                                 << " sibling chapters:" << std::endl;
            for(auto &sib_i: siblings){
                std::cout << sib_i << std::endl;
            }
        }
        else{
            std::cout<< params[0] <<" has no sibling chapters."<< std::endl;
        }

    }
    else{
        std::cout << "Error: Not found: " << params[0] << std::endl;
    }
}

void Book::printTotalLength(Params params) const
{
    int size =0;
    //std::string new_parent;
    //Chapter *new_parent = nullptr;
    Chapter *chptr = findChapter(params[0]);
    if(chptr !=nullptr)
    {
        for(auto &ch : chapters_)
        {
            if (ch.second->id_ == chptr->id_){
                size += ch.second->length_;
                for(auto sub_ch: ch.second->subchapters_)
                {
                    size += sub_ch->length_;
                    for(auto sub_2_ch : sub_ch->subchapters_)
                    {
                        size += sub_2_ch->length_;
                        for(auto sub_3_ch: sub_2_ch->subchapters_)
                        {
                            size += sub_3_ch->length_;
                        }
                    }
                }
            }
        }
        std::cout << "Total length of " << params[0]
                  << " is " << size << "." << std::endl;
    }
    else
        std::cout << "Error: Not found: " << params[0] << std::endl;

}

void Book::printLongestInHierarchy(Params params) const
{
    Chapter *chptr = findChapter(params[0]);
    int length =0;
    std::string longest_id = "";
    if (chptr != nullptr)
    {
        std::vector<Chapter*> param_name;
        param_name.push_back(chptr);
        while (param_name.size() != 0)
        {
            if( length < param_name.at(0)->length_)
            {
                length = param_name.at(0)->length_ ;
                longest_id = param_name.at(0)->id_;
            }

            param_name.insert( param_name.end(), param_name.at(0)->subchapters_.begin(), ch_vec.at(0)->subchapters_.end());
            param_name.erase(param_name.begin());
        }
        if (longest_id != params[0])
            std::cout << "With the length of " << length
                      << ", " << longest_id
                      << " is the longest chapter in "
                      << params[0] << "'s hierarchy." <<std::endl;
        else
            std::cout << "With the length of " << length
                      << ", " << longest_id
                      << " is the longest chapter in their hierarchy."
                      <<std::endl;
    }
    else {
        std::cout << "Error: Not found: " << params[0] << std::endl;
    }

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
