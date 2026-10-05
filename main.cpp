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

            title = other.title;
            head = nullptr;

            //Copy reviews
            Review* current = other.head;

            while (current != nullptr) {
                addReview(current->rating, current->comment);
                current = current->next;
            }
        }

        return *this;
    }

    // Add review to head of list
    void addReview(double rating, string comment) {

        Review* newReview = new Review;
        newReview->rating = rating;
        newReview->comment = comment;
        newReview->next = head;

        head = newReview;
    }

    //Display movie title, reviews, and average
    void displayReviews() const {

        cout << "Movie Title: " << title << endl;

        Review* current = head;

        double totalRating = 0.0;
        int count = 0;

        while (current != nullptr) {
            
            cout << " > Review #" << count + 1 << ": "
                 << fixed << setprecision(1)
                 << current->rating << ": "
                 << current->comment << endl;
            
            totalRating += current->rating;
            count++;

            current = current->next;
        }

        // Calculate average
        double average = totalRating / count;

        cout << " > Average: "
             << fixed << setprecision(1)
             << average << endl;

        cout << endl;
    }
    
};

// function prototypes
bool readReviews(const string& filename, vector<string>& comments);
double getRandomRating();

int main() {

    // Store review comments
    vector<string> comments;

    // Read reviews from input file
    if (!readReviews("input.txt", comments)) {
        return 1;
    }

    // Check for enough reviews
    if (comments.size() < 12) {
        cout << "Error: file must contain at least 12 reviews." << endl;
        return 1;
    }

    // Create vector of Movie objects
    vector<Movie> movies;

    movies.push_back(Movie("Lord of the Rings"));
    movies.push_back(Movie("The Godfather"));
    movies.push_back(Movie("Star Wars"));
    movies.push_back(Movie("Jurassic Park"));

    // Add 3 reviews to each movie
    int commentIndex = 0;

    for (int i = 0; i < movie.size(); i++) {

        // Add reviews in reverse order because addReview() adds each to head
        for (int j = 2; j >= 0; j--) {

            double rating = getRandomRating();

            movies[i].addReview(rating,
                comments[commentIndex + j]
            );
        }

        commentIndex += 3;
    }


    return 0;
}