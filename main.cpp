#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

//Movie class
class Movie {
    private:

    // Linked list struct
    struct Review {
        double rating;
        string comment;
        Review* next;
    };

    string title;
    Review* head;

    public:

    //Constructor
    Movie(string movieTitle) {
        title = movieTitle;
        head = nullptr;
    }

    //Destructor
    ~Movie() {
        while (head != nullptr) {
            Review* temp = head;
            head = head->next;
            delete temp;
        }
    }

    //Copy Constructor
    Movie(const Movie& other) {
        title = other.title;
        head = nullptr;

        Review* current = other.head;

        while (current != nullptr) {
            addReview(current->rating, current->comment);
            current = current->next;
        }
    }

    //Copy assignment operator
    Movie& operator=(const Movie& other) {
        if (this != &other) {

            //delete reviews
            while (head != nullptr) {
                Review* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }
    
}


int main() {


    return 0;
}