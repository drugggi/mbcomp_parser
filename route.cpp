#include "route.h"
#include <iostream>

Route::Route(int routeNumber, int attempts, std::string grade, std::string date):
mRouteNumber(routeNumber), mAttempts(attempts), mGrade(grade), mDate(date)
{

}

Route::~Route() {

}
std::string Route::addRouteAttempts(int nro) const {

    if (nro == mRouteNumber) {
        return std::to_string(mAttempts);
    }
    return "";

}
void Route::printRouteInfo(int nro) const {

    if ( nro == mRouteNumber) {
    std::cout << "\t" <<  std::to_string(mRouteNumber) << ":" << std::to_string(mAttempts);
    }
    else {
        std::cout << "\t";
    }
}

int Route::getAttempts() const {
    return mAttempts;
}
int Route::getRouteNumber() const {
    return mRouteNumber;
}
std::string Route::getDate() const{
    return mDate;
}

int Route::getGradeOpinion() const {
    //std::cout << "_" << mDate << "_";
    if (mGrade == "Grade: 6B+") { return 0; }
    else if (mGrade == "Grade: 6C") { return 1; }
    else if (mGrade == "Grade: 6C+") { return 2; }
    else if (mGrade == "Grade: 7A") { return 3; }
    else if (mGrade == "Grade: 7A+") { return 4; }
    else if (mGrade == "Grade: 7B") { return 5; }
    else if (mGrade == "Grade: 7B+") { return 6; }
    else if (mGrade == "Grade: 7C") { return 7; }
    else if (mGrade == "Grade: 7C+") { return 8; }
    else if (mGrade == "Grade: 8A") { return 9; }
    else if (mGrade == "Grade: 8A+") { return 10; }
    else if (mGrade == "Grade: 8B") { return 11; }
    else { return 11; }
}
