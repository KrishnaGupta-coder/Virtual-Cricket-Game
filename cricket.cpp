#include <iostream>
#include <string>
#include <vector>
#include <limits>   // Required for numeric_limits
#include <algorithm> // Required for std::find
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <unistd.h> // For usleep() (Note: For Windows, you might use <windows.h> and Sleep() instead)

// --- Player Class Definition ---
class Player {
public:
    std::string name;
    int id;
    int runsScored;
    int ballsPlayed;
    int ballsBowled;
    int runsGiven;
    int wicketsTaken;
    bool isOut;

    // Constructor
    Player(std::string name, int id) :
        name(name),
        id(id),
        runsScored(0),
        ballsPlayed(0),
        ballsBowled(0),
        runsGiven(0),
        wicketsTaken(0),
        isOut(false) {}

    // Displays player's current stats
    void displayStats() const {
        std::cout << "\t" << name
                  << "\t\tRuns: " << runsScored
                  << "\tBalls: " << ballsPlayed
                  << "\tWickets: " << wicketsTaken
                  << "\tRuns Given: " << runsGiven
                  << "\n";
    }
};

// --- Team Class Definition ---
class Team {
public:
    std::string name;
    std::vector<Player> players; // List of players in the team
    int totalRuns;
    int totalWicketsLost;
    int totalBallsBowled;

    // Constructor
    Team(std::string name) :
        name(name),
        totalRuns(0),
        totalWicketsLost(0),
        totalBallsBowled(0) {}

    // Adds a player to the team
    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    // Displays all players in the team
    void displayTeamPlayers() const {
        std::cout << "\t" << name << " Players:\n";
        for (const auto& player : players) {
            std::cout << "\t\t" << player.name << "\n";
        }
        std::cout << "\n";
    }
};

// --- Game Class Definition ---
class Game {
public:
    Team teamA;
    Team teamB;
    int playersPerTeam;
    int maxDeliveries;
    int inningsNum;

    // Pointers for current game state
    Team* battingTeam;
    Team* bowlingTeam;
    Player* currentBatsman;
    Player* currentBowler;

    std::vector<Player> allPlayers; // Pool of all 11 players
    std::vector<int> selectedPlayerIds; // To keep track of selected player IDs

    // Constructor
    Game() :
        teamA("TeamA"),
        teamB("TeamB"),
        playersPerTeam(4),
        maxDeliveries(6),
        inningsNum(0),
        battingTeam(nullptr),
        bowlingTeam(nullptr),
        currentBatsman(nullptr),
        currentBowler(nullptr)
    {
        // Initialize the pool of 11 players
        allPlayers.push_back(Player("Virat", 1));
        allPlayers.push_back(Player("Rohit", 2));
        allPlayers.push_back(Player("Dhawan", 3));
        allPlayers.push_back(Player("Rahul", 4));
        allPlayers.push_back(Player("Hardik", 5));
        allPlayers.push_back(Player("Jadeja", 6));
        allPlayers.push_back(Player("Bumrah", 7));
        allPlayers.push_back(Player("Shami", 8));
        allPlayers.push_back(Player("Yuzvendra", 9));
        allPlayers.push_back(Player("Kuldeep", 10));
        allPlayers.push_back(Player("Rishabh", 11));

        // Seed the random number generator
        srand(time(0));
    }

    // Displays welcome message and instructions
    void welcome() {
        std::cout << "\n\n\t\t----------------------------------------\n";
        std::cout << "\t\t|        WELCOME TO CRICKET GAME!      |\n";
        std::cout << "\t\t----------------------------------------\n\n";

        std::cout << "Instructions:\n";
        std::cout << "1. Two teams (TeamA and TeamB) will play.\n";
        std::cout << "2. Each team will have " << playersPerTeam << " players selected by you.\n";
        std::cout << "3. Each innings will be of " << maxDeliveries << " balls.\n";
        std::cout << "4. If a batsman scores 0 runs in a delivery, they are OUT.\n";
        std::cout << "5. The team with more runs wins. If scores are tied, it's a DRAW.\n\n";

        usleep(3000000); // 3 seconds pause
    }

    // Displays the pool of 11 players
    void displayAllPlayers() const {
        std::cout << "\t----------------------------------\n";
        std::cout << "\t|         Pool of Players        |\n";
        std::cout << "\t----------------------------------\n";
        for (const auto& player : allPlayers) {
            std::cout << "\t" << player.id << ". " << player.name << "\n";
        }
        std::cout << "\t----------------------------------\n\n";
        usleep(2000000); // 2 seconds pause
    }

    // Utility to take safe integer input
    int takeIntegerInput() {
        int choice;
        while (!(std::cin >> choice)) {
            std::cout << "\tInvalid input. Please enter a number: ";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        return choice;
    }

    // Validates if player is already selected or if ID is valid
    bool checkPlayerSelection(int playerId) {
        // Check if player ID is valid (1-11)
        if (playerId < 1 || playerId > allPlayers.size()) {
            return false;
        }

        // Check if player is already selected
        for (int selectedId : selectedPlayerIds) {
            if (selectedId == playerId) {
                return false;
            }
        }
        return true; // Player is valid and not yet selected
    }

    // Allows user to select players for both teams
    void selectPlayers() {
        std::cout << "\t----------------------------------\n";
        std::cout << "\t|         Team Selection         |\n";
        std::cout << "\t----------------------------------\n";

        // Select players for TeamA
        std::cout << "\tSelect " << playersPerTeam << " players for TeamA:\n";
        for (int i = 0; i < playersPerTeam; ++i) {
            int playerId;
            while (true) {
                std::cout << "\tPlayer " << (i + 1) << " (TeamA) - Enter player ID: ";
                playerId = takeIntegerInput();
                if (checkPlayerSelection(playerId)) {
                    teamA.addPlayer(allPlayers[playerId - 1]); // Add selected player to TeamA
                    selectedPlayerIds.push_back(playerId);     // Mark as selected
                    std::cout << "\t" << allPlayers[playerId - 1].name << " added to TeamA.\n";
                    break;
                } else {
                    std::cout << "\tInvalid selection! Player ID must be between 1-" << allPlayers.size() << " and not already selected. Try again.\n";
                }
            }
        }
        std::cout << "\n";
        usleep(1000000); // 1 second pause

        // Select players for TeamB
        std::cout << "\tSelect " << playersPerTeam << " players for TeamB:\n";
        for (int i = 0; i < playersPerTeam; ++i) {
            int playerId;
            while (true) {
                std::cout << "\tPlayer " << (i + 1) << " (TeamB) - Enter player ID: ";
                playerId = takeIntegerInput();
                if (checkPlayerSelection(playerId)) {
                    teamB.addPlayer(allPlayers[playerId - 1]); // Add selected player to TeamB
                    selectedPlayerIds.push_back(playerId);     // Mark as selected
                    std::cout << "\t" << allPlayers[playerId - 1].name << " added to TeamB.\n";
                    break;
                } else {
                    std::cout << "\tInvalid selection! Player ID must be between 1-" << allPlayers.size() << " and not already selected. Try again.\n";
                }
            }
        }
        std::cout << "\n";
        usleep(1000000); // 1 second pause

        // Display selected teams
        teamA.displayTeamPlayers();
        teamB.displayTeamPlayers();
        usleep(2000000); // 2 seconds pause
    }

    // Handles the toss functionality
    void toss() {
        std::cout << "\t----------------------------------\n";
        std::cout << "\t|          TOSS TIME!            |\n";
        std::cout << "\t----------------------------------\n";

        std::cout << "\tPress 1 for TeamA or 2 for TeamB to call (Heads/Tails):\n";
        std::cout << "\t(Any number other than 1 or 2 will be considered random choice)\n";
        int call = takeIntegerInput();
        std::cout << "\n";

        // Simulate toss: 0 for heads, 1 for tails
        int tossResult = rand() % 2; // 0 or 1

        std::string winningTeamName;
        bool teamAWonToss = false;

        // Determine which team won the toss based on call and result
        if ((tossResult == 0 && call == 1) || (tossResult == 1 && call == 2)) {
            winningTeamName = (call == 1) ? teamA.name : teamB.name;
            teamAWonToss = (call == 1);
        } else {
            // Random winner or incorrect call
            if (tossResult == 0) { // Heads
                winningTeamName = teamA.name;
                teamAWonToss = true;
            } else { // Tails
                winningTeamName = teamB.name;
                teamAWonToss = false;
            }
        }

        std::cout << "\tIt's " << (tossResult == 0 ? "Heads" : "Tails") << "! Team " << winningTeamName << " wins the toss!\n";
        usleep(2000000); // 2 seconds pause

        std::cout << "\t" << winningTeamName << ", what do you choose?\n";
        std::cout << "\t1. Bat\n";
        std::cout << "\t2. Bowl\n";
        int choice = takeIntegerInput();

        if (teamAWonToss) {
            if (choice == 1) { // TeamA bats
                battingTeam = &teamA;
                bowlingTeam = &teamB;
            } else { // TeamA bowls
                battingTeam = &teamB;
                bowlingTeam = &teamA;
            }
        } else { // TeamB won toss
            if (choice == 1) { // TeamB bats
                battingTeam = &teamB;
                bowlingTeam = &teamA;
            } else { // TeamB bowls
                battingTeam = &teamA;
                bowlingTeam = &teamB;
            }
        }

        std::cout << "\t" << battingTeam->name << " will bat first and " << bowlingTeam->name << " will bowl first.\n\n";
        usleep(3000000); // 3 seconds pause
    }

    // Starts an innings
    void startInnings(int inningsNumber) {
        inningsNum = inningsNumber;
        std::cout << "\t----------------------------------\n";
        std::cout << "\t|         INNINGS " << inningsNum << " BEGINS         |\n";
        std::cout << "\t----------------------------------\n\n";
        usleep(2000000); // 2 seconds pause

        // Swap batting and bowling teams for the second innings
        if (inningsNum == 2) {
            Team* temp = battingTeam;
            battingTeam = bowlingTeam;
            bowlingTeam = temp;

            // Reset player states for the new innings (especially isOut)
            for (auto& player : teamA.players) {
                player.isOut = false;
            }
            for (auto& player : teamB.players) {
                player.isOut = false;
            }
        }

        // Initialize batsman and bowler for the innings
        int batsmanIndex = 0;
        while (batsmanIndex < battingTeam->players.size() && battingTeam->players[batsmanIndex].isOut) {
            batsmanIndex++; // Find the first not-out batsman
        }
        currentBatsman = (batsmanIndex < battingTeam->players.size()) ? &battingTeam->players[batsmanIndex] : nullptr;

        currentBowler = &bowlingTeam->players[0]; // First player to bowl

        std::cout << "\t" << battingTeam->name << " is batting.\n";
        std::cout << "\t" << bowlingTeam->name << " is bowling.\n";

        if (currentBatsman) {
            std::cout << "\t" << currentBatsman->name << " is on strike.\n";
        } else {
            std::cout << "\tAll batsmen are out for " << battingTeam->name << "!\n";
        }
        std::cout << "\t" << currentBowler->name << " is bowling.\n\n";

        usleep(3000000); // 3 seconds pause
        playInnings(); // Start playing the current innings
    }

    // Plays one innings
    void playInnings() {
        int currentBall = 0;
        int batsmanIndex = 0;

        // Find the starting batsman
        while (batsmanIndex < battingTeam->players.size() && battingTeam->players[batsmanIndex].isOut) {
            batsmanIndex++;
        }
        if (batsmanIndex < battingTeam->players.size()) {
            currentBatsman = &battingTeam->players[batsmanIndex];
        } else {
            // All batsmen already out (shouldn't happen at start of innings 1, but for innings 2 it's possible)
            std::cout << "\tNo batsmen left to bat for " << battingTeam->name << ".\n";
            return;
        }

        // The first bowler always bowls all 6 deliveries
        currentBowler = &bowlingTeam->players[0];

        while (currentBall < maxDeliveries && battingTeam->totalWicketsLost < playersPerTeam) {
            std::cout << "\t" << currentBatsman->name << " on strike. " << currentBowler->name << " bowling.\n";
            std::cout << "\tBall " << (currentBall + 1) << " of " << maxDeliveries << "...\n";
            usleep(1500000); // 1.5 seconds pause

            // Simulate runs (0-6)
            int runsScored = rand() % 7; // Generates 0 to 6

            std::cout << "\t" << currentBatsman->name << " scores " << runsScored << " runs!\n";
            usleep(1000000); // 1 second pause

            // Update player and team stats
            currentBatsman->runsScored += runsScored;
            currentBatsman->ballsPlayed++;
            battingTeam->totalRuns += runsScored;

            currentBowler->ballsBowled++;
            currentBowler->runsGiven += runsScored;

            // Update balls bowled for the batting team's innings, and for the bowling team's overall stats
            battingTeam->totalBallsBowled++;
            // Note: Bowling team's totalBallsBowled increments each ball across both innings
            // If you want per-innings, you'd need to reset it, but problem implies cumulative for bowler.

            // Check for OUT criteria (0 runs)
            if (runsScored == 0) {
                currentBatsman->isOut = true;
                battingTeam->totalWicketsLost++;
                currentBowler->wicketsTaken++;
                std::cout << "\t" << currentBatsman->name << " is OUT!\n";
                usleep(1500000); // 1.5 seconds pause

                // Move to next batsman if available and not out
                batsmanIndex++;
                while (batsmanIndex < battingTeam->players.size() && battingTeam->players[batsmanIndex].isOut) {
                    batsmanIndex++;
                }

                if (batsmanIndex < battingTeam->players.size()) {
                    currentBatsman = &battingTeam->players[batsmanIndex];
                    std::cout << "\tNext batsman: " << currentBatsman->name << "\n";
                    usleep(1500000); // 1.5 seconds pause
                } else {
                    std::cout << "\tAll batsmen are out for " << battingTeam->name << "!\n";
                    usleep(1500000);
                }
            }
            currentBall++;
            displayScoreCard();
            usleep(2000000); // 2 seconds pause

            // Check if innings is over based on runs, wickets, or balls
            if (inningsNum == 2) {
                // In second innings, check if target is reached or wickets/balls are finished
                if (battingTeam->totalRuns > bowlingTeam->totalRuns || // Target chased
                    currentBall == maxDeliveries ||                      // Overs finished
                    battingTeam->totalWicketsLost == playersPerTeam) {   // All out
                    break; // End innings
                }
            } else { // First innings
                if (currentBall == maxDeliveries ||                      // Overs finished
                    battingTeam->totalWicketsLost == playersPerTeam) {   // All out
                    break; // End innings
                }
            }
        }
        std::cout << "\t----------------------------------\n";
        std::cout << "\t|         INNINGS " << inningsNum << " OVER!         |\n";
        std::cout << "\t----------------------------------\n\n";
        usleep(2000000); // 2 seconds pause
    }

    // Displays the current game scorecard
    void displayScoreCard() const {
        std::cout << "\n\t----------------------------------\n";
        std::cout << "\t|         SCORECARD              |\n";
        std::cout << "\t----------------------------------\n";
        std::cout << "\t" << teamA.name << " Score: " << teamA.totalRuns << "/" << teamA.totalWicketsLost << "\tBalls: " << teamA.totalBallsBowled << "/" << maxDeliveries << "\n";
        std::cout << "\t" << teamB.name << " Score: " << teamB.totalRuns << "/" << teamB.totalWicketsLost << "\tBalls: " << teamB.totalBallsBowled << "/" << maxDeliveries << "\n";

        // Display target if it's the second innings
        if (inningsNum == 2) {
            std::cout << "\tTarget for " << battingTeam->name << ": " << (bowlingTeam->totalRuns + 1) << " runs.\n";
            std::cout << "\t" << battingTeam->name << " needs " << ((bowlingTeam->totalRuns + 1) - battingTeam->totalRuns) << " runs to win.\n";
        }

        std::cout << "\n\tBatsman Stats (" << teamA.name << "):\n";
        std::cout << "\t---------------\n";
        for (const auto& player : teamA.players) {
            player.displayStats();
        }
        std::cout << "\n\tBatsman Stats (" << teamB.name << "):\n";
        std::cout << "\t---------------\n";
        for (const auto& player : teamB.players) {
            player.displayStats();
        }
        std::cout << "\t----------------------------------\n\n";
    }

    // Displays the match summary at the end
    void displayMatchSummary() const {
        std::cout << "\n\n\t----------------------------------------\n";
        std::cout << "\t|           MATCH SUMMARY              |\n";
        std::cout << "\t----------------------------------------\n";
        displayScoreCard(); // Show final scorecard

        std::cout << "\tFinal Scores:\n";
        std::cout << "\t" << teamA.name << ": " << teamA.totalRuns << "/" << teamA.totalWicketsLost << " (" << teamA.totalBallsBowled << " balls)\n";
        std::cout << "\t" << teamB.name << ": " << teamB.totalRuns << "/" << teamB.totalWicketsLost << " (" << teamB.totalBallsBowled << " balls)\n\n";

        if (teamA.totalRuns > teamB.totalRuns) {
            std::cout << "\t----------------------------------\n";
            std::cout << "\t|          TEAM A WINS!          |\n";
            std::cout << "\t----------------------------------\n\n";
        } else if (teamB.totalRuns > teamA.totalRuns) {
            std::cout << "\t----------------------------------\n";
            std::cout << "\t|          TEAM B WINS!          |\n";
            std::cout << "\t----------------------------------\n\n";
        } else {
            std::cout << "\t----------------------------------\n";
            std::cout << "\t|          MATCH DRAW!           |\n";
            std::cout << "\t----------------------------------\n\n";
        }

        std::cout << "\tThank you for playing!\n\n";
    }
};

// --- Main Function ---
int main() {
    Game game; // Create a Game object

    game.welcome();           // Display welcome message and instructions
    game.displayAllPlayers(); // Show the pool of available players
    game.selectPlayers();     // Allow user to select players for teams
    game.toss();              // Perform the toss and decide batting/bowling order

    // First Innings
    game.startInnings(1); // Start and play the first innings

    // Second Innings
    game.startInnings(2); // Start and play the second innings

    game.displayMatchSummary(); // Display the final match summary

    return 0;
}