#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CarTesting

#include <boost/test/unit_test.hpp>

#include "car.h"

struct CarFixture
{
    CCar car;
};

// todo doc it

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

    // изначально автомобиль не заведен
    BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
    {
        BOOST_CHECK(!car.IsEngineTurnOn());
    }

    // проверяем заводится ли
    BOOST_AUTO_TEST_CASE(can_be_turned_on)
    {
        car.TurnOnEngine();
        BOOST_CHECK(car.IsEngineTurnOn());
    }

    // глушится ли
    BOOST_AUTO_TEST_CASE(can_be_turned_off)
    {
        car.TurnOffEngine();
        BOOST_CHECK(!car.IsEngineTurnOn());
    }

    BOOST_AUTO_TEST_CASE(get_available_speed_by_gear)
    {
        // wrong gear
        rangeSpeedMap getSpeed = car.GetAvailableSpeedByGear(10);
        BOOST_CHECK(getSpeed.first == -1 && getSpeed.second == -1);
        
        // gear = -1 => 0-20 km/h
        getSpeed = car.GetAvailableSpeedByGear(-1);
        BOOST_CHECK(getSpeed.first == 0 && getSpeed.second == 20);
        
        // gear = 0 => no limits
        getSpeed = car.GetAvailableSpeedByGear(0);
        BOOST_CHECK(getSpeed.first == 0 && getSpeed.second == 0);
        
        // gear = 1 => 0-20 km/h
        getSpeed = car.GetAvailableSpeedByGear(3);
        BOOST_CHECK(getSpeed.first == 30 && getSpeed.second == 60);
    }

    BOOST_AUTO_TEST_CASE(is_current_speed_correspond_gear)
    {
        // wrong gear
        BOOST_CHECK(!car.IsCurrentSpeedCorrespondGear(20, 10));
        
        // gear = -1
        BOOST_CHECK(!car.IsCurrentSpeedCorrespondGear(30, -1)); // wrong
        BOOST_CHECK(car.IsCurrentSpeedCorrespondGear(15, -1)); // good
        
        // gear = 0 => no speed limit
        BOOST_CHECK(!car.IsCurrentSpeedCorrespondGear(100, 0)); // wrong
        BOOST_CHECK(car.IsCurrentSpeedCorrespondGear(0, 0)); // good
        
        // gear = 2
        BOOST_CHECK(!car.IsCurrentSpeedCorrespondGear(80, 2)); // wrong
        BOOST_CHECK(car.IsCurrentSpeedCorrespondGear(30, 2)); // good
        
    }

    // глушится ли
//    BOOST_AUTO_TEST_CASE(can_be_turned_off)
//    {
//        car.TurnOffEngine();
//        BOOST_CHECK(!car.IsEngineTurnOn());
//    }



BOOST_AUTO_TEST_SUITE_END()
