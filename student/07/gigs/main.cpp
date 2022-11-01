/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * EXAMPLE SOLUTION
 * ===========================
 *
 *  Acts as a simple gig calendar with n commands:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 *
 *  The data file's lines should be in format
 * artist_name;date;town_name;stage_name.
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * */
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <tuple>


// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
            (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
         (day <= month_sizes.at(stoi(month) - 1) or
          (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isFormatValid(std::ifstream & file_obj)
{
    std::string line;
    while (getline(file_obj, line)) {
        int count = 0;
        for(uint i=0; i<line.size();i++)
        {
            if(line[i] == ';' && line[i+1]==';')
                return false;
            if(line[i] == ';')
                count++;
        }
        if(count!= 3)
            return false;
    }
    file_obj.close();
    return true;
}

struct Gig{
    std::string artist,
    date,
    city,
    stage;
    bool operator< (const Gig& other) const
    {
        return std::tie(artist, date, city, stage)
                < std::tie(other.artist, other.date, other.city, other.stage);
    }
};


void readDataFromFile(std::ifstream & file_obj, std::vector<Gig>& data)
{
    std::vector<std::string> data_items;
    std::string line;
    char delim = ';';
    while (getline(file_obj, line)) {
        data_items = split(line, delim);
        Gig gig = {data_items.at(0),
                   data_items.at(1),
                   data_items.at(2),
                   data_items.at(3)
                  };
        //Save data to Gig
        data.push_back(gig);
    }
    file_obj.close();
}

void printGig(Gig const &gig)
{
    std::cout << "Artists: " << gig.artist << "date: "
                             << gig.date << "city: "
                             << gig.city << "stage: "
                             << gig.stage << std::endl;
}

std::set <std::string> artistsName (std::ifstream & file_obj)
{
    std::set <std::string> artistsData;
    std::string line;
    std::vector <std::string> artistsItems;
    char delim = ';';
    while(getline(file_obj, line))
    {
        artistsItems = split(line, delim);
        artistsData.insert(artistsItems.at(0));
    }
    return artistsData;
}

//std::set <std::string> stageData (std::ifstream & file_obj)
//{
//    map<stdstring, set<int>> words;
//    string line;
//    vector<string> line_words;
//    vector<string>::iterator words_itr;

//    std::set <std::string> stagesData;
//    std::string line;
//    std::vector <std::string> stageItems;
//    char delim = ';';
//    while(getline(file_obj, line))
//    {
//        stageItems = split(line, delim);
//        stagesData.insert(stageItems.at(2));
//        stagesData.insert(stageItems.at(3));
//    }
//    return stagesData;
//}
void print_artist(std::set<std::string> & gig_data)
{
    std::cout << "All artists in alphabetical order:" <<std::endl;
    for(auto& a: gig_data)
    {
        std::cout << a << std::endl;
    }

}
void print_stages(std::set<Gig> & gig_data)
{
    std::cout << "All gig places in alphabetical order:" <<std::endl;
    for(auto & b: gig_data)
    {
        std::cout << b.city << ", " << b.stage << std::endl;
    }

}
void printArtistgigs(std::string artistname, std::set<Gig> & gig_data)
{
    std::cout <<
    "Artist Elastinen has the following gigs in the order they are listed:"
    << std::endl;
    for(auto & b: gig_data)
    {
        if(b.artist == artistname)
        std::cout << " - " << b.date
                  <<" : " << b.city
                  <<", "  << b.stage
                  << std::endl;
    }
}
std::set<Gig> convertToSet(std::vector<Gig> gig_vector)
{
    // Declaring the set
    std::set<Gig> Gig_set;

    // Traverse the Vector
    for (auto & x : gig_vector) {

        // Insert each element
        // into the Set
        Gig_set.insert(x);
    }
    gig_vector.assign( Gig_set.begin(), Gig_set.end() );
    // Return the resultant Set
    return Gig_set;
}
std::string artistpresent(std::vector<std::string> & commandParts,
                          std::set<std::string> & artistData)
{
//    std::string secpos = commandParts.at(1);
//    secpos.erase(remove(secpos.begin(), secpos.end(), '"'));
    std::string artistname;
    for(auto & artist_i : artistData)
    {
        if(commandParts.at(1) == artist_i)
            artistname = artist_i;
    }
    return artistname;
}
void checkCommand(std::string & command, std::set<Gig> gig_data,
                  std::set<std::string> artistsData)
{

    std::vector<std::string> commandParts;
    char delim = ' ';
    commandParts = split(command, delim);
    if(commandParts.size() < 1)
    {
        std::cout << "Error: Invalid input." << std::endl;
    }
    if(commandParts.size() == 1)
    {
        if(commandParts.at(0) != "ARTISTS" && commandParts.at(0) != "STAGES" )
        {
            std::cout << "Error: Invalid input." << std::endl;
        }
    }
    if (commandParts.size()== 1 && commandParts.at(0) == "ARTISTS")
    {
        print_artist(artistsData);
    }
    if (commandParts.size()== 1 && commandParts.at(0) == "STAGES")
    {
        print_stages(gig_data);
    }
    if(commandParts.size() == 2)
    {
        std::string artistname= artistpresent(commandParts, artistsData);
        if(commandParts.at(0) == "ARTIST"
                && commandParts.at(1) == artistname )
        {
            printArtistgigs(artistname, gig_data);
        }
    }

    else std::cout << "Error: Not found." << std::endl;

    //    if(commandParts.size() == 2)
    //    {
    //        if(commandParts.at(0) == "STAGE" && commandParts.at(1) !=  gig2.stage)
    //        {
    //            std::cout << "Error: Not found." << std::endl;
    //        }
    //    }

    commandParts.clear();
}
int main()
{
    std::vector<Gig> gig_data;
    std::set<Gig> finalData;
    std::set<std::string> artistsData;
    std::set<std::string> stagesData;
    std::string file_name = "";
    std::cout << "Give a name for input file: ";
    getline(std::cin, file_name);
    std::ifstream file_obj(file_name);
    //Checking either file is opening or not.
    if (!file_obj)
    {
        std::cout << "Error: File could not be read." << std::endl;
        return EXIT_FAILURE;
    }
    //Checking either file has correct format
    if(!isFormatValid(file_obj))
    {
        std::cout << "Error: Invalid format in file." << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream file_objt(file_name);
    readDataFromFile(file_objt, gig_data);
    std::ifstream file_object(file_name);
    artistsData= artistsName(file_object);
    std::ifstream file_objectt(file_name);
    //stagesData= stageData(file_objectt);
    finalData= convertToSet(gig_data);
    //printGig(gig_data.at(0));


    std::string command;
    while (command != "QUIT")
    {
        std::cout << "gigs> ";
        getline(std::cin, command);
        //        for (auto & c: command)
        //        {
        //            c = toupper(c);
        //        }
        checkCommand(command, finalData, artistsData);


    }

    return EXIT_SUCCESS;
}


