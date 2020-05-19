#include <unordered_set>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include "competitor.h"
#include "route.h"

struct CompetitorHasher
{
  size_t
  operator()(const Competitor & obj) const
  {
    return std::hash<std::string>()(obj.getName());
  }
};

struct CompetitorComparator
{
  bool
  operator()(const Competitor & obj1, const Competitor & obj2) const
  {
    if (obj1.getName() == obj2.getName())
      return true;
    return false;
  }
};

int main(int argc, const char* argv[]) {

    // store all competitors in unordered set
    std::unordered_set<Competitor, CompetitorHasher, CompetitorComparator> setOfCompetitors;
    std::ofstream tofile;

    std::string name, attempts, grade, date, line;

    // basically this parses unnecessary empty lines out and stores that into other files
    std::string rawfilename, tofilename;
    for (int i = 1 ; i < 11 ; i++) {
        rawfilename = "routes/raw"+std::to_string(i);
        tofilename = "routes/route"+std::to_string(i)+".txt";
        std::ifstream myfile(rawfilename);

        tofile.open(tofilename);
        if (myfile.is_open() ) {
            while ( getline (myfile, line) ) {
                if (line.length() > 0) {
                    // std::cout << line << '\n';
                    tofile << line << '\n';
                }
            }
            myfile.close();
        }
        else {
            std::cout << "unable to open file";
        }
        tofile.close();
    }

    // read the comp files routeX.txt and store the data into Classes Competitor and Route
    std::string compfile;
    for (int i = 1 ; i < 11 ; i++) {
        compfile = "routes/route"+std::to_string(i)+".txt";
        std::ifstream rawfile(compfile);

        int counter = 0;
        if (rawfile.is_open() ) {
            while (getline (rawfile, line) ) {
                counter++;
                name = line;
                if( getline(rawfile,line) ) {
                    attempts = line;
                    // This removes comments essentially
                    if ( attempts != "Flashed" && attempts != "more than 3 tries" &&
                            attempts != "Project" && attempts != "2nd try" && attempts != "3rd try" ) {
                        name = attempts;
                        if (getline(rawfile,line) ) {
                            attempts = line;
                        }
                    }
                }
                if (getline(rawfile, line) ) {grade = line; }
                if (getline(rawfile, line) ) {
                    if (line.size() < 10 ||line.substr(0,9) != "Climbed: ") {
                        std::cout << "ERROR at " << compfile << '\n'
                            << name << "\n" << attempts << "\n"
                            << grade << "\n"<< line << "'" << "\nERROR\n"; }
                    date = line.substr(9); } // Removes 'Climbed: ' at the start of line

                // insert new competitor if not already there, and add new route if not already 
                auto res = setOfCompetitors.insert(Competitor(name) );
                auto search = setOfCompetitors.find(Competitor(name) );
                Route newRoute(i,search->getAttempts(attempts),grade,date);
                search->addRoute(newRoute );
            }
            rawfile.close();
        }
        else {
            std::cout << "unable to open file";
        }
    }

    // lets calculate results and put them into results file
    std::ofstream resultsfile;
    resultsfile.open("routes/results.txt");
    for (Competitor cmp: setOfCompetitors) {
        resultsfile << cmp.getResults() << '\n';
    }
    resultsfile.close();

    // other interesting statistics into stats file
    std::ofstream statsfile;
    statsfile.open("routes/stats.txt");
    int stats[12][10] = {};
    int routeStats[2][10] = {};
    int attemptStats[4][10] = {};
    
    for (Competitor cmp: setOfCompetitors) {
        cmp.editGradeOpinions(stats);
        cmp.editTotalRouteStats(routeStats);
        cmp.editAttemptStats(attemptStats);
    }
    // grade opinions to statsfile
    for (int x = 0; x < 12 ; x++) {
        for (int y = 0 ; y < 10 ; y++) {
            statsfile << std::to_string(stats[x][y]) << "\t";
        }
        statsfile << '\n';
    }
    statsfile << '\n';
    // how many climbers climbed routes and how many attempts it took
    for (int x = 0; x < 2 ; x++) {
        for (int y = 0 ; y < 10 ; y++) {
            statsfile << std::to_string(routeStats[x][y]) << "\t";
        }
        statsfile << '\n';
    }
    statsfile << '\n';
    // how many tries climbers took to finish a route
    for (int x = 0; x < 4 ; x++) {
        for (int y = 0; y < 10 ; y++) {
           statsfile << std::to_string(attemptStats[x][y]) << "\t";
       }
       statsfile << '\n';
    }
    statsfile << '\n';
    // how many climbs were done per day
    std::pair <std::string, int> ascentsPerDay;
    std::vector< std::pair< std::string, int> > test;

    std::vector<std::string> ascentDates;
    for (Competitor cmp: setOfCompetitors) {
        ascentDates = cmp.getAscentDates();
       
        //std::cout << "" << ascentDates.size();
        for (std::string s: ascentDates){
            int foundAt = -1;
            for (int i = 0 ; i < test.size() ; i++) {
                // std::cout << test.at(i).first << "=?=" << s << "\n";
               if (test.at(i).first == s) {
                   foundAt = i;
                  test.at(i).second += 1;
                  break; }

            }
           if (foundAt != -1) { 
              //<F2> test.at(i).second += 1;
            //std::cout << "new ascent at date: " << s << "\n";
           } else {

               test.push_back( std::make_pair(s,1) ); 
                //std::cout << "new date" << s << "\n";
           }
        }

    }
    
    std::ofstream datesfile;
    datesfile.open("routes/dates.txt");
    for (int i = 0; i < test.size() ; i++){
        datesfile << test.at(i).first << "\t" << std::to_string( test.at(i).second ) << "\n";
        // std::cout <<"'" <<  test.at(i).first << "' " << test.at(i).second << "\n";
    }
    datesfile.close();
    statsfile.close();

    return 0;
}
