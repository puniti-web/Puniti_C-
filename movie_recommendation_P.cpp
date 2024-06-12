#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm> 
using namespace std; 
// Define structures for user, movie, and user rating 
struct User { 
    int id; 
    string username; 
    vector<string> genre_preferences; 
}; 
 
struct Movie { 
    int id; 
    string title; 
    string genre; 
    int release_year; 
}; 
 
struct UserRating { 
    int user_id; 
    int movie_id; 
    int rating; 
}; 
 
class MovieRecommendationSystem { 
private: 
    vector<User> users; 
    vector<Movie> movies; 
    vector<UserRating> userRatings; 
    int next_user_id; // Tracks the ID for the next user 
    int next_movie_id; // Tracks the ID for the next movie 
public: 
    // Constructor to initialize next_user_id and next_movie_id 
    MovieRecommendationSystem() : next_user_id(1), next_movie_id(1) {} 
 
    // Function to register a new user 
    void registerUser(string username, const vector<string>& genre_preferences) { 
         User temp; 
         temp.id=next_user_id++; 
    temp.username = username; 
    temp.genre_preferences = genre_preferences; 
    users.push_back(temp); 
    } 
 
    // Function to add a new movie 
    void addMovie(string title, string genre, int release_year) { 
       Movie temp; 
       temp.id=next_movie_id++; 
    temp.title = title; 
    temp.genre = genre; 
    temp.release_year = release_year; 
    movies.push_back(temp); 
    } 
 
    // Function to rate a movie 
    void rateMovie(int user_id, int movie_id, int rating) { 
       UserRating temp; 
    temp.user_id = user_id; 
    temp.movie_id = movie_id; 
    temp.rating = rating; 
    userRatings.push_back(temp); 
    } 
 
    // Function to recommend movies based on user's choice 
    vector<Movie> recommendMovies(int user_id) const { 
        vector<Movie> recommendedMovies; 
 
        // Getting registered user's preference 
        vector<string> genre_preferences = users[user_id - 1].genre_preferences; 
 
        // Recommend movies with matching genres 
        for (const auto& movie : movies) { 
            if (find(genre_preferences.begin(), genre_preferences.end(), 
movie.genre) != genre_preferences.end()) { 
                recommendedMovies.push_back(movie); 
            } 
        } 
 
        // Recommend movies similar to those highly rated by the user 
        vector<int> ratedMovies; 
        for (const auto& rating : userRatings) { 
            if (rating.user_id == user_id) 
                ratedMovies.push_back(rating.movie_id); 
        } 
        for (const auto& rating : userRatings) { 
            if (rating.rating >= 4 && find(ratedMovies.begin(), ratedMovies.end(), 
rating.movie_id) == ratedMovies.end()) { 
                recommendedMovies.push_back(movies[rating.movie_id - 1]); 
            } 
        } 
 
        return recommendedMovies; 
    } 
 
    // Function to print all movies 
    void printMovies() const { 
        cout << "Movies available for rating:\n"; 
        for (const auto& movie : movies) { 
            cout << "ID: " << movie.id << ", Title: " << movie.title << " (" << 
movie.release_year << "), Genre: " << movie.genre << endl; 
        } 
    } 
}; 
 
int main() { 
    int registered_user_id=1; 
    MovieRecommendationSystem system; 
 
    // Add some sample movies 
    system.addMovie("Inception", "Sci-Fi", 2010); 
    system.addMovie("The Shawshank Redemption", "Drama", 1994); 
    system.addMovie("The Dark Knight", "Action", 2008); 
    system.addMovie("12th Fail", "drama", 2023); // (movie_id, title, genre, year_released) 
    system.addMovie("The Dark Knight", "action", 2008); 
    system.addMovie("Inception", "action", 2010); 
    system.addMovie("Pulp Fiction", "crime", 1994); 
    system.addMovie("pk","comedy",2014); 
    system.addMovie("mr & mrs mahi","drama",2024); 
 
    // Welcome message 
    cout << "Welcome to Puniti's Movie Recommendation System" << endl; 
 
    int choice; 
    do { 
        // Display options 
        cout << "\nSelect an option:\n"; 
        cout << "1. Register a new user\n"; 
        cout << "2. Rate a movie\n"; 
        cout << "3. Get movie recommendations\n"; 
        cout << "4. Exit\n"; 
        cout << "Enter your choice: "; 
        cin >> choice; 
 
        switch (choice) { 
            case 1: { 
                string username; 
                string genre_pref; 
                vector<string> genre_preferences; 
 
                cout << "Enter username: "; 
                cin >> username; 
                cout << "Enter genre preferences (comma-separated): "; 
                cin.ignore(); 
                getline(cin, genre_pref); 
 
                // Split the genre preferences by comma 
                size_t pos = 0; 
                while ((pos = genre_pref.find(',')) != string::npos) { 
                    genre_preferences.push_back(genre_pref.substr(0, pos)); 
                    genre_pref.erase(0, pos + 1); 
                } 
                genre_preferences.push_back(genre_pref); 
 
                system.registerUser(username, genre_preferences); 
                 cout << "User registered successfully! User ID: " 
<<registered_user_id++<< endl; 
                break; 
            } 
            case 2: { 
                int user_id, movie_id, rating; 
                system.printMovies(); // Print available movies 
                cout << "Enter user ID: "; 
                cin >> user_id; 
                cout << "Enter movie ID to rate: "; 
                cin >> movie_id; 
                cout << "Enter rating (1-5): "; 
                cin >> rating; 
 
                system.rateMovie(user_id, movie_id, rating); 
                cout << "Rating added successfully!\n"; 
                break; 
            } 
            case 3: { 
                int user_id; 
                cout << "Enter user ID to get recommendations: "; 
                cin >> user_id; 
 
                cout << "Recommended movies for User " << user_id << ":\n"; 
                vector<Movie> recommendations = system.recommendMovies(user_id); 
                for (const auto& movie : recommendations) { 
                    cout << "- " << movie.title << " (" << movie.release_year << 
"), Genre: " << movie.genre << endl; 
                } 
                break; 
            } 
            case 4: 
                cout << "Exiting..."; 
                break; 
            default: 
                cout << "Invalid choice. Please try again.\n"; 
        } 
    } while (choice != 4); 
 
    return 0; 
}