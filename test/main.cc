// main.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: test Wump app

#include <iostream>
#include <algorithm>
#include "3rdparty/test_helpers.h"

#include "labyrinth.h"
#include "room.h"
#include "subject.h"
#include "enemy.h"
#include "player.h"
#include "wump.h"
#include "pit.h"
#include "bat.h"

namespace anshub {

// Helper struct that place subject in concrete room not random

struct TestSubject : Subject
{
  TestSubject(Labyrinth* cave, int start)
  : Subject(cave)
  , start_room_{start}
  {
    curr_room_ = cave->GetRoom(start_room_);
  }
  int start_room_;
};

// Helper struct that make abstract class not abstract for test

struct TestEnemy : Enemy
{
  TestEnemy(Labyrinth* cave) : Enemy(cave) { }
  std::string FeelsRepresent() const override { return ""; }
};

// Helper struct that gives access to the rooms directly

struct TestCave : Labyrinth
{
  TestCave(int size) : Labyrinth(size) { }
  std::vector<Room*> GetAllRooms() const { return rooms_; }
};

void test_labyrinth_creating()
{
  constexpr int kCaveSize {20};
  Labyrinth cave(kCaveSize);
  
  std::cout << "Check rooms connecting:" << '\n';
  
  // First center to last center
  
  int num = 0;
  int assert = cave.GetSize() / 2 - 1;
  int fact = cave.GetRoom(num)->back_->num_;
  ResultMessage(1, assert, fact);

  // First center to first outer

  assert = cave.GetSize() / 2;
  fact = cave.GetRoom(num)->right_->num_;
  ResultMessage(2, assert, fact);  

  // Last center to first center

  num = cave.GetSize() / 2 - 1;
  assert = 0;
  fact = cave.GetRoom(num)->right_->num_;
  ResultMessage(3, assert, fact);

  // Last center to last inner

  assert = cave.GetSize() - 1;
  fact = cave.GetRoom(num)->left_->num_;
  ResultMessage(4, assert, fact);

  // First outer to first center

  num = cave.GetSize() / 2;
  assert = 0;
  fact = cave.GetRoom(num)->back_->num_;
  ResultMessage(5, assert, fact);  

  // First outer to last outer

  assert = cave.GetSize() - 2;
  fact = cave.GetRoom(num)->left_->num_;
  ResultMessage(6, assert, fact);  

  // Last inner to first inner

  num = cave.GetSize() - 1;
  assert = cave.GetSize() / 2 + 1;
  fact = cave.GetRoom(num)->right_->num_;
  ResultMessage(7, assert, fact);  

  // Last inner to last center

  assert = cave.GetSize() / 2 - 1;
  fact = cave.GetRoom(num)->back_->num_;
  ResultMessage(8, assert, fact);  

  // Random center room to back center room

  num = cave.GetSize() / 2 - cave.GetSize() / 4;
  assert = num - 1;
  fact = cave.GetRoom(num)->back_->num_;
  ResultMessage(9, assert, fact);  

  // Random main room to left main room

  num = cave.GetSize() / 2 - cave.GetSize() / 4 - 1;
  assert = cave.GetSize() / 2 + num;
  fact = cave.GetRoom(num)->right_->num_;
  ResultMessage(10, assert, fact);    
}

void test_subject_static_moving()
{
  constexpr int kCaveSize {20};
  constexpr int kStartRoom {0};

  Labyrinth cave(kCaveSize);
  TestSubject person(&cave, kStartRoom);

  std::cout << "Check subject static moving:" << '\n';

  TestPairs<int,std::string> tests;
  tests.push_back(12, "Succesfull");
  tests.push_back(2, "Succesfull");
  tests.push_back(1, "Succesfull");
  tests.push_back(43, "Wrong room number");

  int i = 0;
  do {
    int mock = tests.back_mock();
    std::string assume = tests.back_assume();
    
    std::string move_msg {};
    person.Move(mock, move_msg);
    
    ResultMessage(++i, assume, move_msg);
    tests.pop_back();
  } while (!tests.empty());
}

void test_subject_dynamic_moving()
{
  constexpr int kCaveSize {20};
  constexpr int kSteps {10000};
  Labyrinth cave(kCaveSize);
  TestEnemy person(&cave);

  std::cout << "Check dynamic moving:" << '\n';

  int i = 0;
  int k = 0;
  do {
    int curr_room = person.GetCurrRoomNum();
    std::vector<int> neighbors = cave.GetNeighbors(curr_room);
    int rand_direction = neighbors[GetRandomInt(0,2)];
    
    std::string assume {"Succesfull"};
    std::string fact {};

    person.Move(rand_direction, fact);
    if (assume != fact) {
      ResultMessage(i, assume, fact);
      ++k;
    }
  } while (++i <= kSteps);
  std::cout << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';
}

void test_subject_random_placing()
{
  std::cout << "Check traversal absents:" << '\n';
  
  constexpr int kCaveSize {20};
  constexpr int kSteps {10000};
  constexpr int kItems {10};

  int i = 0;
  int k = 0;
  do {
    Labyrinth cave(kCaveSize);
    
    // Fill labirint with subjects

    std::vector<Subject*> subjects;
    for (int m = 0; m < kItems; ++m) {
      subjects.push_back(new TestEnemy(&cave));
    }
    subjects.push_back(new Player(&cave));

    // Get nums of not empty rooms

    std::vector<int> uniq_rooms;
    for (auto g:subjects) {
      uniq_rooms.push_back(g->GetCurrRoomNum());
    }
    
    // Check if presens not uniq rooms
    
    auto i1 = std::adjacent_find(uniq_rooms.begin(), uniq_rooms.end());
    if (i1 != uniq_rooms.end()) {
      ResultMessage(i, false, true);
      ++k; 
    }

    // Clear subjects vector
    for (auto m:subjects) {
      delete m;
    }
  } while (++i <= kSteps);
  std::cout << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';  
}

void test_subject_examine_room()
{
  std::cout << "Subjects examine room:" << '\n';
  
  constexpr int kCaveSize {20};
  Labyrinth cave(kCaveSize);

  TestEnemy e1(&cave);
  TestEnemy e2(&cave);
  Player p1(&cave);

  int start_room = p1.GetCurrRoomNum();
  
  std::size_t assume = 0;
  std::size_t fact = p1.ExamineRoom().size();
  ResultMessage(1, assume, fact);
  
  fact = e1.ExamineRoom().size(); 
  ResultMessage(2, assume, fact);

  fact = e2.ExamineRoom().size();
  ResultMessage(3, assume, fact);

  std::string msg{};
  p1.Teleport(e2.GetCurrRoomNum(), msg);

  assume = 1;
  fact = p1.ExamineRoom().size();
  ResultMessage(4, assume, fact);

  if (fact == 1) {
    assume = Subject::ENEMY;
    fact = p1.ExamineRoom().at(0);
    ResultMessage(5, assume, fact);
  }

  assume = 0;
  fact = e1.ExamineRoom().size();
  ResultMessage(6, assume, fact);
  
  assume = 1;
  fact = e2.ExamineRoom().size();
  ResultMessage(7, assume, fact);
  
  if (fact == 1) { 
    assume = Subject::PLAYER;
    fact = e2.ExamineRoom().at(0);
    ResultMessage(8, assume, fact);
  }

  p1.Teleport(start_room, msg);
  e1.Teleport(start_room, msg);
  e2.Teleport(start_room, msg);
  
  assume = 2;
  fact = p1.ExamineRoom().size();
  ResultMessage(9, assume, fact);
}

void test_subject_check_in_and_out_1()
{
  std::cout << "Check check-ins and check-outs (part 1):" << '\n';
  
  constexpr int kCaveSize {20};
  constexpr int kSteps {10000};
  constexpr int kItems {10};
  constexpr int kTeleportsEach {10};

  int i = 0;
  int k = 0;
  
  do {
    TestCave cave(kCaveSize);
    
    // Fill labirint with subjects

    std::vector<Subject*> subjects;
    for (int m = 0; m < kItems; ++m) {
      subjects.push_back(new TestEnemy(&cave));
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
      ResultMessage(i, false, true);
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
      ResultMessage(i, false, true);
      ++k; 
    }

    // Clear subjects vector

    for (auto m:subjects) {
      delete m;
    }
  } while (++i <= kSteps);
  std::cout << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';  
}

void test_subject_check_in_and_out_2()
{
  constexpr int kCaveSize {20};
  constexpr int kSteps {10000};
  Labyrinth cave(kCaveSize);
  TestEnemy person(&cave);

  std::cout << "Check check-ins and check-outs (part 2):" << '\n';

  int i = 0;
  int k = 0;
  do {
    int curr_room = person.GetCurrRoomNum();
    std::vector<int> neighbors = cave.GetNeighbors(curr_room);
    int rand_direction = neighbors[GetRandomInt(0,2)];
    
    std::string msg {};
    person.Move(rand_direction, msg);
    
    // Сheck previous room

    bool assume = true;
    bool fact = cave.GetRoom(curr_room)->IsEmpty();
    
    if (assume != fact) {
      ResultMessage(i, assume, fact);
      ++k;
    }
    
    // Сheck current room 

    assume = false;
    fact = cave.GetRoom(person.GetCurrRoomNum())->IsEmpty();

    if (assume != fact) {
      ResultMessage(i, assume, fact);
      ++k;
    }

  } while (++i <= kSteps);
  std::cout << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';
}

void test_player_feels()
{
  std::cout << "Test feels of player:" << '\n';
  
  constexpr int kCaveSize {20};
  constexpr int kSteps {10000};
  
  Labyrinth cave(kCaveSize);

  int i = 0;
  int k = 0;
  do {
    Wump wump(&cave);
    Bat bat(&cave);
    Pit pit(&cave);
    Player player(&cave);
    Player::Persons result = player.Feels();
    for (auto const x:result) {
      if ((x < 4)) {
        ResultMessage(i, i ,x);
        ++k;
      }
    }
  } while (++i <= kSteps);
  std::cout << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';
}

void test_player_shot()
{
  std::cout << "Test player shots:" << '\n';
  
  constexpr int kCaveSize {20};
  
  Labyrinth cave(kCaveSize);
  Wump wump(&cave);
  Player player(&cave);

  std::string msg{""};
  wump.Teleport(0, msg);
  player.Teleport(1, msg);
  auto assume = Subject::WUMP;
  auto fact = player.Shot(0);
  ResultMessage(1, assume, fact);

  wump.Teleport(15, msg);
  assume = Subject::EMPTY;
  fact = player.Shot(0);
  ResultMessage(2, assume, fact);
}

}

int main()
{
  using namespace anshub;
  
  test_labyrinth_creating();
  test_subject_static_moving();
  test_subject_dynamic_moving();
  test_subject_random_placing();
  test_subject_examine_room();
  test_subject_check_in_and_out_1();
  test_subject_check_in_and_out_2();
  test_player_feels();
  test_player_shot();

  return 0;
}