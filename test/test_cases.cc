// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of test-cases of wumpus_game

#include "test_cases.h"

namespace anshub {

TestSubject::TestSubject(const Labyrinth& cave, int start)
: Subject(cave)
, start_room_{start}
{
  curr_room_ = cave.GetRoom(start_room_);
}

namespace test_labyrinth_behavior {

  int creating()
  {
    constexpr int kCaveSize {20};
    Labyrinth cave(kCaveSize);
    
    std::cerr << "Check rooms connecting:" << '\n';
    
    // First center to last center
    
    int num{0};
    int assume = cave.GetSize() / 2 - 1;
    int actual = cave.GetRoom(num)->back_->num_;
    int result = test_toolkit::message(1, assume, actual);

    // First center to first outer

    assume = cave.GetSize() / 2;
    actual = cave.GetRoom(num)->right_->num_;
    result += test_toolkit::message(2, assume, actual);  

    // Last center to first center

    num = cave.GetSize() / 2 - 1;
    assume = 0;
    actual = cave.GetRoom(num)->right_->num_;
    result += test_toolkit::message(3, assume, actual);

    // Last center to last inner

    assume = cave.GetSize() - 1;
    actual = cave.GetRoom(num)->left_->num_;
    result += test_toolkit::message(4, assume, actual);

    // First outer to first center

    num = cave.GetSize() / 2;
    assume = 0;
    actual = cave.GetRoom(num)->back_->num_;
    result += test_toolkit::message(5, assume, actual);  

    // First outer to last outer

    assume = cave.GetSize() - 2;
    actual = cave.GetRoom(num)->left_->num_;
    result += test_toolkit::message(6, assume, actual);  

    // Last inner to first inner

    num = cave.GetSize() - 1;
    assume = cave.GetSize() / 2 + 1;
    actual = cave.GetRoom(num)->right_->num_;
    result += test_toolkit::message(7, assume, actual);  

    // Last inner to last center

    assume = cave.GetSize() / 2 - 1;
    actual = cave.GetRoom(num)->back_->num_;
    result += test_toolkit::message(8, assume, actual);  

    // Random center room to back center room

    num = cave.GetSize() / 2 - cave.GetSize() / 4;
    assume = num - 1;
    actual = cave.GetRoom(num)->back_->num_;
    result += test_toolkit::message(9, assume, actual);  

    // Random main room to left main room

    num = cave.GetSize() / 2 - cave.GetSize() / 4 - 1;
    assume = cave.GetSize() / 2 + num;
    actual = cave.GetRoom(num)->right_->num_;
    result += test_toolkit::message(10, assume, actual);

    return result;
  }

}  // namespace test_labyrinth_behavior

namespace test_subject_behavior {

  int static_moving()
  {
    constexpr int kCaveSize {20};
    constexpr int kStartRoom {0};

    Labyrinth cave(kCaveSize);
    TestSubject person(cave, kStartRoom);

    std::cerr << "Check subject static moving:" << '\n';

    test_toolkit::TestPairs<int,std::string> tests;
    tests.push_back(12, "Succesfull");
    tests.push_back(2, "Succesfull");
    tests.push_back(1, "Succesfull");
    tests.push_back(43, "Wrong room number");

    int i{0};
    int result{0};

    do {
      int mock = tests.back_mock();
      std::string assume = tests.back_assume();
      
      std::string move_msg {};
      person.Move(mock, move_msg);
      
      result += test_toolkit::message(++i, assume, move_msg);
      tests.pop_back();
    } while (!tests.empty());

    return result;
  }

  int dynamic_moving()
  {
    constexpr int kCaveSize {20};
    constexpr int kSteps {10000};
    Labyrinth cave(kCaveSize);
    TestEnemy person(cave);

    std::cerr << "Check dynamic moving:" << '\n';

    int i{0};
    int k{0};
    int result{0};

    do {
      int curr_room = person.GetCurrRoomNum();
      std::vector<int> neighbors = labyrinth::get_neighboring_rooms(curr_room, cave);
      int rand_direction = neighbors[rand_toolkit::get_rand(0,2)];
      
      std::string assume {"Succesfull"};
      std::string actual {};

      person.Move(rand_direction, actual);
      if (assume != actual) {
        result += test_toolkit::message(i, assume, actual);
        ++k;
      }
    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';

    return result;
  }

  int random_placing()
  {
    std::cerr << "Check traversal absents:" << '\n';
    
    constexpr int kCaveSize {20};
    constexpr int kSteps {10000};
    constexpr int kItems {10};

    int i{0};
    int k{0};
    int result{0};

    do {
      Labyrinth cave(kCaveSize);
      
      // Fill labirint with subjects

      std::vector<Subject*> subjects;
      for (int m = 0; m < kItems; ++m) {
        subjects.push_back(new TestEnemy(cave));
      }
      subjects.push_back(new Player(cave));

      // Get nums of not empty rooms

      std::vector<int> uniq_rooms;
      for (auto g:subjects) {
        uniq_rooms.push_back(g->GetCurrRoomNum());
      }
      
      // Check if presens not uniq rooms
      
      auto i1 = std::adjacent_find(uniq_rooms.begin(), uniq_rooms.end());
      if (i1 != uniq_rooms.end()) {
        result += test_toolkit::message(i, false, true);
        ++k; 
      }

      // Clear subjects vector
      for (auto m:subjects) {
        delete m;
      }
    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';

    return result;
  }

  int examine_room()
  {
    std::cerr << "Subjects examine room:" << '\n';
    
    constexpr int kCaveSize {20};
    Labyrinth cave(kCaveSize);

    TestEnemy e1(cave);
    TestEnemy e2(cave);
    Player p1(cave);

    int start_room = p1.GetCurrRoomNum();
    
    std::size_t assume {0};
    std::size_t actual = p1.ExamineRoom().size();
    int result = test_toolkit::message(1, assume, actual);
    
    actual = e1.ExamineRoom().size(); 
    result += test_toolkit::message(2, assume, actual);

    actual = e2.ExamineRoom().size();
    result += test_toolkit::message(3, assume, actual);

    std::string msg{};
    p1.Teleport(e2.GetCurrRoomNum(), msg);

    assume = 1;
    actual = p1.ExamineRoom().size();
    result += test_toolkit::message(4, assume, actual);

    if (actual == 1) {
      assume = Subject::ENEMY;
      actual = p1.ExamineRoom().at(0);
      result += test_toolkit::message(5, assume, actual);
    }

    assume = 0;
    actual = e1.ExamineRoom().size();
    result += test_toolkit::message(6, assume, actual);
    
    assume = 1;
    actual = e2.ExamineRoom().size();
    result += test_toolkit::message(7, assume, actual);
    
    if (actual == 1) { 
      assume = Subject::PLAYER;
      actual = e2.ExamineRoom().at(0);
      result += test_toolkit::message(8, assume, actual);
    }

    p1.Teleport(start_room, msg);
    e1.Teleport(start_room, msg);
    e2.Teleport(start_room, msg);
    
    assume = 2;
    actual = p1.ExamineRoom().size();
    result += test_toolkit::message(9, assume, actual);

    return result;
  }

  int check_in_and_out_1()
  {
    std::cerr << "Check check-ins and check-outs (part 1):" << '\n';
    
    constexpr int kCaveSize {20};
    constexpr int kSteps {10000};
    constexpr int kItems {10};
    constexpr int kTeleportsEach {10};

    int i{0};
    int k{0};
    int result{0};
    
    do {
      TestCave cave(kCaveSize);
      
      // Fill labirint with subjects

      std::vector<Subject*> subjects;
      for (int m = 0; m < kItems; ++m) {
        subjects.push_back(new TestEnemy(cave));
      }

      // Move them randomly
      
      for (int v = 0; v < kTeleportsEach; ++v) {
        for (auto g:subjects) {
          g->TeleportRandom();
        }
      }

      // Check if total of checked-in subjects in cave more or less than kItems  
      
      int cnt{0};
      for (auto const r:cave.GetAllRooms()) {
        cnt += r->persons_.size();
      }
      if (cnt != kItems) {
        result += test_toolkit::message(i, false, true);
        ++k; 
      }
      
      // Get nums of not empty rooms

      std::vector<int> uniq_rooms;
      for (auto g:subjects) {
        uniq_rooms.push_back(g->GetCurrRoomNum());
      }
      
      // Check if presens not uniq rooms
      
      auto i1 = std::adjacent_find(uniq_rooms.begin(), uniq_rooms.end());
      if (i1 != uniq_rooms.end()) {
        result += test_toolkit::message(i, false, true);
        ++k; 
      }

      // Clear subjects vector

      for (auto m:subjects) {
        delete m;
      }
    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';  

    return result;
  }

  int check_in_and_out_2()
  {
    constexpr int kCaveSize {20};
    constexpr int kSteps {10000};
    Labyrinth cave(kCaveSize);
    TestEnemy person(cave);

    std::cerr << "Check check-ins and check-outs (part 2):" << '\n';

    int i{0};
    int k{0};
    int result{0};

    do {
      int curr_room = person.GetCurrRoomNum();
      std::vector<int> neighbors = labyrinth::get_neighboring_rooms(curr_room, cave);
      int rand_direction = neighbors[rand_toolkit::get_rand(0,2)];
      
      std::string msg {};
      person.Move(rand_direction, msg);
      
      // Сheck previous room

      bool assume = true;
      bool actual = cave.GetRoom(curr_room)->IsEmpty();
      
      if (assume != actual) {
        result += test_toolkit::message(i, assume, actual);
        ++k;
      }
      
      // Сheck current room 

      assume = false;
      actual = cave.GetRoom(person.GetCurrRoomNum())->IsEmpty();

      if (assume != actual) {
        result += test_toolkit::message(i, assume, actual);
        ++k;
      }

    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';

    return result;
  }

}  // namespace test_subject_behavior

namespace test_player_behavior {

  int feels()
  {
    std::cerr << "Test feels of player:" << '\n';
    
    constexpr int kCaveSize {20};
    constexpr int kSteps {10000};
    
    Labyrinth cave(kCaveSize);

    int i{0};
    int k{0};
    int result{0};
    
    do {
      Wump wump(cave);
      Bat bat(cave);
      Pit pit(cave);
      Player player(cave);
      Player::Persons feels = player.Feels();
      for (auto const x:feels) {
        if ((x < 4)) {
          result += test_toolkit::message(i, i ,x);
          ++k;
        }
      }
    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';

    return result;
  }

  int shot()
  {
    std::cerr << "Test player shots:" << '\n';
    
    constexpr int kCaveSize {20};
    
    Labyrinth cave(kCaveSize);
    Wump wump(cave);
    Player player(cave);

    std::string msg{""};
    wump.Teleport(0, msg);
    player.Teleport(1, msg);
    auto assume = Subject::WUMP;
    auto actual = player.Shot(0);
    int result = test_toolkit::message(1, assume, actual);

    wump.Teleport(15, msg);
    assume = Subject::EMPTY;
    actual = player.Shot(0);
    result += test_toolkit::message(2, assume, actual);
  
    return result;
  }

}  // namespace test_player_behavior 

}  // namespace anshub