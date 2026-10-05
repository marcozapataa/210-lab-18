#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

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
        Review* tail = nullptr;

        while (current != nullptr) {
            
            //Create a new review
            Review* newReview = new Review;
            newReview->rating = current->rating;
            newReview->comment = current->comment;
            newReview->next = nullptr;

            // if first review
            if (head == nullptr) {
                head = newReview;
                tail = newReview;
            }
            else {
                // Add review to end of list
                tail->next = newReview;
                tail = newReview;
            }

            current = current->next;
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
            Review* tail = nullptr;

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

    srand(time(0));

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

    for (int i = 0; i < movies.size(); i++) {

        // Add reviews in reverse order because addReview() adds each to head
        for (int j = 2; j >= 0; j--) {

            double rating = getRandomRating();

            movies[i].addReview(rating,
                comments[commentIndex + j]
            );
        }

        commentIndex += 3;
    }

    // Display movies
    for (int i = 0; i < movies.size(); i++) {
        movies[i].displayReviews();
    }


    return 0;
}

// -----Function Definitions---------

//Definition for readReviews
bool readReviews(const string& filename, vector<string>& comments) {

    ifstream inFile(filename);

    // check if file opened
    if (!inFile) {
        cout << "Error: Could not open input file " << filename << endl;
        return false;
    }

    string line;

    // Read one comment per line
    while (getline(inFile, line)) {

        if (!line.empty()) {
            comments.push_back(line);
        }
    }

    inFile.close();

    return true;
}

// Definition for getRandomRating
double getRandomRating() {

    double rating = 1.0 + (rand() % 41) / 10.0;
    return rating;

}