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
 * Program authors
 * Student 1.
 * Name: Noman Akbar
 * Student number: 150596134
 * UserID: mknoak
 * E-Mail: noman.akbar@tuni.fi
 * Student 2.
 * NAME: Talha Mansoor
 * Student number: 150595685
 * UserID: vxtama
 * E-Mail: talha.mansoor@tuni.fi
 * Andrew gergis was working on this project with us,
 * we made logics together might end up with same outputs.
 * */
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <tuple>

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

//checking the format of file
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


//reading data from file and storing it into the vector
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

//This function checks either date is in correct
bool checkingDate (std::set<Gig> & gig_data)
{
    std::string dateData;

    for(auto & a : gig_data)
    {
        dateData = a.date;
        if(!is_valid_date(dateData))
        {
            return false;
        }
    }
    return true;
}

//This function prints Aartists names on ARTISTS command
void print_artist(std::vector<Gig> & gig_data)
{
    std::set <std::string> gig;
    std::cout << "All artists in alphabetical order:" <<std::endl;
    for (uint i=0; i<gig_data.size();i++)
    {
        gig.insert(gig_data.at(i).artist);
    }
    for (auto & itr : gig)
    {
        std::cout << itr << std::endl;
    }
}
//This function prints cities and stage on STAGES command
void print_stages(std::vector<Gig> & gig_data)
{
    std::cout << "All gig places in alphabetical order:" <<std::endl;
    std::map<std::string,std::string> gig;

    for (uint i=0; i<gig_data.size();i++)
    {
        gig.insert({gig_data.at(i).city, gig_data.at(i).stage});
    }
    for (std::pair<std::string, std::string> itr : gig)
    {
        std::cout << itr.first << ", " << itr.second <<std::endl;
    }
}

//This function prints gigs against entered artist
void printArtistgigs(std::string artistname, std::set<Gig> & gig_data)
{
    std::cout << "Artist "
              << artistname
              << " has the following gigs in the order they are listed:"
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

//This function prints artist performing on specified stage
void printStagegigs(std::string stageName, std::set<Gig> & gig_data)
{
    std::cout << "Stage "
              << stageName
              << " has gigs of the following artists:"
              << std::endl;
    for(auto & stageGig: gig_data)
    {
        if(stageName == stageGig.stage)
            std::cout << " - " << stageGig.artist
                      << std::endl;
    }
}

//converting vector of structure to set of struct GIg
std::set<Gig> convertToSet(std::vector<Gig> gig_vector)
{
    // Declaring the set
    std::set<Gig> Gig_set;
    for (auto & x : gig_vector) {
        Gig_set.insert(x);
    }
    gig_vector.assign( Gig_set.begin(), Gig_set.end() );
    // Return the resultant Set
    return Gig_set;
}

//This function verifies either artist entered in command is present in the file
std::string artistpresent(std::vector<std::string> & commandParts,
                          std::set<Gig> & artistData)
{
    std::string secpos = commandParts.at(1);
    secpos.erase(remove(secpos.begin(), secpos.end(), '"'), secpos.end());
    std::string artistname;
    for(auto & artist_i : artistData)
    {
        if(secpos == artist_i.artist)
            artistname = secpos;
    }
    return artistname;
}
//This function verifies either stage entered in command is present in the file
std::string stagePresent(std::vector<std::string> & commandParts,
                         std::set<Gig> & finalData)
{
    std::string command = commandParts.at(1);
    std::string stageName;
    for(auto & artist_i : finalData)
    {
        if(command == artist_i.stage)
            stageName = command;

    }
    return stageName;
}
//checking bookings of the the arist
bool checkPlans(std::vector<std::string> artistPlans,std::string artistGigs )
{
    for(uint i=0;i<artistPlans.size();i++)
    {
        if (artistPlans.at(i)==artistGigs)
        {
            return true;
        }
    }
    return false;
}


bool checkBookings (std::vector <Gig> &gig_data)
{
    std::map<std::string, std::vector<std::string>> artistGigs;
    for(uint i=0; i < gig_data.size() ; i++){
        std::vector<std::string> artistGigsList;
        if(artistGigs.count(gig_data.at(i).artist)){

            artistGigsList = artistGigs.at(gig_data.at(i).artist);
            if(checkPlans(artistGigsList,gig_data.at(i).date))
                return false;
        }
        artistGigsList.push_back(gig_data.at(i).date);
        artistGigs.clear();
        artistGigs.insert({gig_data.at(i).artist,artistGigsList});
    }
    return true;
}

//commands execution is implemented in this function
void checkCommand(std::string & command,
                  std::vector<Gig> gig_data,
                  std::set<Gig> finalData)
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
        if (commandParts.at(0) == "ARTISTS")
        {
            print_artist(gig_data);
        }
        if (commandParts.at(0) == "STAGES")
        {
            print_stages(gig_data);
        }
        if (commandParts.at(0) == "QUIT")
        {
            exit(0);
        }
        if(commandParts.at(0) != "ARTISTS" &&
                commandParts.at(0) != "STAGES" && commandParts.at(0) != "QUIT")
        {
            std::cout << "Error: Invalid input." << std::endl;
        }
    }
    if(commandParts.size() == 2)
    {
        std::string artistname= artistpresent(commandParts, finalData);
        if(commandParts.at(0) == "ARTIST"
                && commandParts.at(1) == artistname )
        {
            printArtistgigs(artistname, finalData);
        }
        if(commandParts.at(0) == "ARTIST" && commandParts.at(1) != artistname)
            std::cout << "Error: Not found." << std::endl;
        std::string stageName= stagePresent(commandParts, finalData);
        if((commandParts.at(0) == "STAGE" || commandParts.at(0) == "stage")
                && commandParts.at(1) == stageName )
        {
            printStagegigs(stageName, finalData);
        }
        if((commandParts.at(0) == "STAGE" || commandParts.at(0) == "stage")
           && commandParts.at(1) != stageName)
            std::cout << "Error: Not found." << std::endl;
    }
    commandParts.clear();
}


int main()
{
    std::vector<Gig> gig_data;
    std::set<Gig> finalData;
    std::string file_name = "";
    std::cout << "Give a name for input file: ";
    //reading data from fil
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
    //storing read data in vector
    std::ifstream file_objt(file_name);
    readDataFromFile(file_objt, gig_data);
    //calling conversion function to chenge vector to set
    finalData= convertToSet(gig_data);
    if (!checkingDate(finalData))
    {
        std::cout << "Error: Invalid date."<< std::endl;
        return EXIT_FAILURE;
    }

    //duplicate bookings
    if(!checkBookings(gig_data))
    {
        std::cout << "Error: Already exists." << std::endl;
        return EXIT_FAILURE;
    }

    //Starts taking commands and permorms the execution accordingly
    std::string command;
    while (command != "QUIT" || command != "quit")
    {
        std::cout << "gigs> ";
        getline(std::cin, command);
        checkCommand(command, gig_data, finalData);
    }
    return EXIT_SUCCESS;
}


