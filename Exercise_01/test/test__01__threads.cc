#include <catch2/catch_test_macros.hpp>

///////////////////////////
//                       //
// BEGIN MODIFYABLE CODE //
//                       //
///////////////////////////

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

TEST_CASE("each thread output appears exactly once and intact")
{
  //
  // Launch N_threads threads and collect their outputs.
  //

  int32_t const N_threads = 10;
  vector<thread> threads;

  ostringstream ostr;
  for (int32_t idx=0; idx<N_threads; ++idx)
  {
    threads.push_back(
      thread(
        [&ostr, &idx] () {
          ostr << "This is the output for thread idx=" << idx << endl;
        }
      )
    );
  }

  //
  // LOOP A
  //
  for (auto & t : threads) {
    t.join();
  }

  string program_output_str = ostr.str();

  /////////////////////////
  //                     //
  // END MODIFYABLE CODE //
  //                     //
  /////////////////////////

  //
  // Verify that the output for each thread appears
  // exactly once and intact.
  //
  for (int32_t idx=0; idx<N_threads; ++idx)
  {
    ostringstream target_ostr;
    target_ostr << "This is the output for thread idx=" << idx << endl;
    auto target_str = target_ostr.str();

    //
    // LOOP B
    //
    int32_t N_matches = 0;
    size_t pos = program_output_str.find(target_str, 0);
    while (pos != string::npos) {
      ++N_matches;
      pos = program_output_str.find(target_str, pos+1);
    }

    CHECK(N_matches == 1); // LINE C
  }
}


