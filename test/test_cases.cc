// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementations of test-cases of wumpus_game

#include "test_cases.h"

namespace wumpus_game {

TestSubject::TestSubject(Map* cave, int start)
: Subject(cave)
{
  std::string msg{""};
  Teleport(start, msg);
}

namespace test_map_behavior {

  int creating()
  {
    constexpr int kCaveSize {5};
    Map cave(kCaveSize);
    
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
    if (assume%2 == 0) {
      actual = cave.GetRoom(num)->right_->num_;
    }
    else {
      actual = cave.GetRoom(num)->left_->num_;      
    }
    result += test_toolkit::message(10, assume, actual);

    return result;
  }

  int move_semantic()
  {   
    std::cerr << "Check Map move semantic:" << '\n';

    constexpr int kCaveSize {5};    
    
    Map cave(kCaveSize);
    TestSubject subj1(&cave, 3);
    TestSubject subj2(&cave, 7);
    
    Map cave2(std::move(cave));

    int assume = 2;
    int actual = test_helpers::persons_in_cave(&cave2, Subject::UNKNOWN);
    return test_toolkit::message(1, assume, actual);
    return 0;
}

}  // namespace test_map_behavior

namespace test_level_behavior {

  int creating()
  {
    std::cerr << "Check level creating:" << '\n';
    
    constexpr int kSteps {100};
    constexpr int kCaveSize {5};
    
    int i{0};
    int result{0};

    do {
      int kArrows = 5;
      int kWumpsCnt = rand_toolkit::get_rand(1, kCaveSize/4);
      int kBatsCnt = rand_toolkit::get_rand(1, kCaveSize/4);
      int kPitsCnt = rand_toolkit::get_rand(1, kCaveSize/4);
      Level lvl(kCaveSize, kArrows, kWumpsCnt, kBatsCnt, kPitsCnt);

      int wumps_total = test_helpers::persons_in_cave(lvl.cave_.get(), Subject::WUMP);
      int bats_total  = test_helpers::persons_in_cave(lvl.cave_.get(), Subject::BAT);
      int pits_total  = test_helpers::persons_in_cave(lvl.cave_.get(), Subject::PIT);

      result += kWumpsCnt - wumps_total;
      result += kBatsCnt - bats_total;
      result += kPitsCnt - pits_total;
    } while(++i <= kSteps);

    std::cerr << " " << kSteps-result << " out of " << kSteps << ".....Ok" << '\n';
    return result;
  }

  int move_semantic()
  {   
    std::cerr << "Check Level move semantic:" << '\n';   

    // constexpr int kCaveSize {5};
    constexpr int kArrows {5};
    int wumps_cnt{rand_toolkit::get_rand(1,3)};
    int bats_cnt{rand_toolkit::get_rand(1,3)};
    int pits_cnt{rand_toolkit::get_rand(1,3)};

    int result{0};

    Level level(5, 5, 4, 2, 3);
    level = Level(6, kArrows, wumps_cnt, pits_cnt, bats_cnt);  // make 2 loops with diff moves
    Level level_1 {Level(6, kArrows, wumps_cnt, bats_cnt, pits_cnt)};

    int assume = wumps_cnt;
    int actual = test_helpers::persons_in_cave(level_1.cave_.get(), Subject::WUMP);
    result += test_toolkit::message(1, assume, actual);

    assume = 1;
    actual = test_helpers::persons_in_cave(level_1.cave_.get(), Subject::PLAYER);    
    result += test_toolkit::message(2, assume, actual);

    assume = bats_cnt;
    actual = test_helpers::persons_in_cave(level_1.cave_.get(), Subject::BAT);    
    result += test_toolkit::message(3, assume, actual);

    assume = pits_cnt;
    actual = test_helpers::persons_in_cave(level_1.cave_.get(), Subject::PIT);    
    result += test_toolkit::message(4, assume, actual);

    assume = 0;
    actual = test_helpers::persons_in_cave(level_1.cave_.get(), Subject::UNKNOWN);    
    result += test_toolkit::message(5, assume, actual);

    Subject* p = level_1.wumps_[wumps_cnt-1].get();
    assume = p->GetCurrRoomNum();
    actual = test_helpers::find_person_in_cave(level_1.cave_.get(), p);   
    result += test_toolkit::message(6, assume, actual);

    return result; 
  }

}

namespace test_subject_behavior {

  int creating_and_placing()
  {
    std::cerr << "Check Subject creating and placing:" << '\n';

    using SubjectPtr = std::unique_ptr<TestSubject>;
    using SubjectVec = std::vector<SubjectPtr>;
    constexpr int kCaveSize {5};
    int subj_cnt = rand_toolkit::get_rand(0, kCaveSize*2);

    int i{0};
    Map cave(kCaveSize);
    SubjectVec v;

    while (i++ < subj_cnt) {
      int room = rand_toolkit::get_rand(0, kCaveSize-1);
      v.push_back(SubjectPtr{new TestSubject(&cave, room)});
    }
    int assume = subj_cnt;
    int actual = test_helpers::persons_in_cave(&cave, Subject::UNKNOWN);
    return test_toolkit::message(1, assume, actual);
  }

  int move_semantic()
  {
    std::cerr << "Check Subject class move semantic:" << '\n';

    constexpr int kCaveSize {5};
    constexpr int kStartRoom_1 {3};
    constexpr int kStartRoom_2 {4};
    constexpr int kStartRoom_3 {7};
    constexpr int kStartRoom_4 {12};
    
    Map cave(kCaveSize);

    TestSubject subj(&cave, kStartRoom_1);
    TestSubject subj2(&cave, kStartRoom_2);
    subj = TestSubject(&cave, kStartRoom_3);
    TestSubject subj3(TestSubject(&cave, kStartRoom_4));

    // Check total subjects count in cave

    int assume = 3;
    int actual = test_helpers::persons_in_cave(&cave, Subject::UNKNOWN);
    return test_toolkit::message(1, assume, actual);

    // Check concrete rooms where subject placed
    // auto rooms = test_helpers::rooms_with_persons(cave, Subject::UNKNOWN);
    // paranoya!!!
  }

  int static_moving()
  {
    constexpr int kCaveSize {5};
    constexpr int kStartRoom {0};

    Map cave(kCaveSize);
    TestSubject person(&cave, kStartRoom);

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
    constexpr int kCaveSize {5};
    constexpr int kSteps {100};
    Map cave(kCaveSize);
    TestEnemy person(&cave);

    std::cerr << "Check dynamic moving:" << '\n';

    int i{0};
    int k{0};
    int result{0};

    do {
      int curr_room = person.GetCurrRoomNum();
      std::vector<int> neighbors = map_helpers::GetNeighboringRooms(curr_room, &cave);
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
    
    constexpr int kCaveSize {5};
    constexpr int kArrows {5};
    constexpr int kSteps {100};
    constexpr int kItems {10};

    int i{0};
    int k{0};
    int result{0};

    do {
      Map cave(kCaveSize);
      
      // Fill labirint with subjects

      std::vector<Subject*> subjects;
      for (int m = 0; m < kItems; ++m) {
        subjects.push_back(new TestEnemy(&cave));
      }
      subjects.push_back(new Player(&cave, kArrows));

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
    
    constexpr int kCaveSize {5};
    constexpr int kArrows {5};
    Map cave(kCaveSize);

    TestEnemy e1(&cave);
    TestEnemy e2(&cave);
    Player p1(&cave, kArrows);

    int start_room = p1.GetCurrRoomNum();

    std::size_t assume {0};
    std::size_t actual = test_helpers::neighboring_subjects(p1, &cave).size();
    int result = test_toolkit::message(1, assume, actual);
    
    actual = test_helpers::neighboring_subjects(e1, &cave).size(); 
    result += test_toolkit::message(2, assume, actual);

    actual =  test_helpers::neighboring_subjects(e2, &cave).size();
    result += test_toolkit::message(3, assume, actual);

    std::string msg{};
    p1.Teleport(e2.GetCurrRoomNum(), msg);

    assume = 1;
    actual = test_helpers::neighboring_subjects(p1, &cave).size();
    result += test_toolkit::message(4, assume, actual);

    if (actual == 1) {
      assume = Subject::ENEMY;
      actual = test_helpers::neighboring_subjects(p1, &cave).at(0)->GetType();
      result += test_toolkit::message(5, assume, actual);
    }

    assume = 0;
    actual = test_helpers::neighboring_subjects(e1, &cave).size();
    result += test_toolkit::message(6, assume, actual);
    
    assume = 1;
    actual = test_helpers::neighboring_subjects(e2, &cave).size();
    result += test_toolkit::message(7, assume, actual);
    
    if (actual == 1) { 
      assume = Subject::PLAYER;
      actual = test_helpers::neighboring_subjects(e2, &cave).at(0)->GetType();
      result += test_toolkit::message(8, assume, actual);
    }

    p1.Teleport(start_room, msg);
    e1.Teleport(start_room, msg);
    e2.Teleport(start_room, msg);
    
    assume = 2;
    actual = test_helpers::neighboring_subjects(p1, &cave).size();
    result += test_toolkit::message(9, assume, actual);

    return result;
    // return 0;
  }

  int check_in_and_out_1()
  {
    std::cerr << "Check check-ins and check-outs (part 1):" << '\n';
    
    constexpr int kCaveSize {5};
    constexpr int kSteps {100};
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
        cnt += r->subjects_.size();
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
    constexpr int kCaveSize {5};
    constexpr int kSteps {100};
    Map cave(kCaveSize);
    TestEnemy person(&cave);

    std::cerr << "Check check-ins and check-outs (part 2):" << '\n';

    int i{0};
    int k{0};
    int result{0};

    do {
      int curr_room = person.GetCurrRoomNum();
      std::vector<int> neighbors = map_helpers::GetNeighboringRooms(curr_room, &cave);
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

  int move_semantic()
  {
    std::cerr << "Test move semantic of player:" << '\n';
    constexpr int kArrows {5};
    
    Map cave(20);
    Player player{Player(&cave, kArrows)};
    Map cave2 {std::move(cave)};
    
    int assume {1};
    int actual = test_helpers::persons_in_cave(&cave2, Subject::PLAYER);
    return test_toolkit::message(1, assume, actual);
  }

  int feels()
  {
    std::cerr << "Test feels of player:" << '\n';
    
    constexpr int kCaveSize {5};
    constexpr int kArrows {5};
    constexpr int kSteps {100};
    
    Map cave(kCaveSize);

    int i{0};
    int k{0};
    int result{0};
    
    do {
      Wump wump(&cave);
      Bat bat(&cave);
      Pit pit(&cave);
      Player player(&cave, kArrows);
      auto feels = player.Feels();
      for (auto const x:feels) {
        if (x < 4) {
          result += test_toolkit::message(i, i ,x)  ;
          ++k;
        }
      }
    } while (++i <= kSteps);
    std::cerr << " " << kSteps-k << " out of " << kSteps << ".....Ok" << '\n';

    return result;
  }

}  // namespace test_player_behavior 

namespace test_logic_behavior {

  int init()
  {
    std::cerr << "Test logic creating and resetting:" << '\n';
    
    constexpr int kSteps{20};
    
    Logic logic{};
    int i{1};
    do {
      logic.NewLevel(i);  // check here if one subj in one room and not unkn
    } while (++i <= kSteps);
    
    return 0;
  }

  int for_exceptions()
  {
    std::cerr << "Test logic process for exceptions via AiController:" << '\n';
    
    constexpr int kLevel {5};
    constexpr int kSteps {100};
    
    Logic logic{};
    AiController ctrl {logic, kLevel, kSteps};
    
    int result{0};
    try {
      ctrl.RunModel();
    }
    catch (...) {
      ++result;
    }
    std::cerr << " " << kSteps - result << " out of " << kSteps << ".....Ok" << '\n';    
    return result;
  }
  
}  // namespace test_logic_behavior

namespace test_leaks {
  
void images_class()
{
  std::cerr << "Test create and destroy of Images instance" << '\n';  
  Images img{};
}
  
void audio_out_class()
{
  std::cerr << "Test create, using and destroy of AudioOut instance" << '\n';    
  anshub::AudioOut audio{};
  audio.Play("../src/resources/sounds/wump_killed.wav");
  audio.Play("../src/resources/sounds/wump_killed.wav");
 }
  
}  // namespace test_leaks

}  // namespace wumpus_game