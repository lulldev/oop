#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CarControlTesting

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <iostream>

#include "Car.h"
#include "CarControl.h"

using namespace std;

struct CarControlDependencies
{
    CCar car;
    CCarControl carControl;
    
    CarControlDependencies()
        : carControl(car)
    {
    }
    
    void VerifyCommandAction(const string & command, const string & expectedOutput)
    {
        istringstream input(command);
        ostringstream output;
        BOOST_CHECK(carControl.ReadAndActionCommand(input, output));
        BOOST_CHECK(input.eof());
        BOOST_CHECK_EQUAL(output.str(), expectedOutput);
    }
};

BOOST_FIXTURE_TEST_SUITE(CarControl, CarControlDependencies)

    BOOST_AUTO_TEST_CASE(test_unknow_commands)
    {
        VerifyCommandAction("Test", "Unknow command\n");
    }

    BOOST_AUTO_TEST_CASE(can_engine_on)
    {
        VerifyCommandAction("EngineOn", "Car engine is turn ON!\n");
    }

    BOOST_AUTO_TEST_CASE(can_engine_off)
    {
        VerifyCommandAction("EngineOff", "Engine already OFF!\n");
    }

    BOOST_AUTO_TEST_CASE(can_set_gear)
    {
        VerifyCommandAction("SetGear", "Gear number is wrong!\n");
        VerifyCommandAction("SetGear 1", "Set 1 gear is complete!\n");
        VerifyCommandAction("SetGear -1", "Set 1 gear is complete!\n");
    }

BOOST_AUTO_TEST_SUITE_END()
