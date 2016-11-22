#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CarTesting

#include <boost/test/unit_test.hpp>

#include <iostream>

#include "Car.h"

struct CarFixture
{
    CCar car;
};

// todo extend

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

    // получение допустимой скорости по передаче
    BOOST_AUTO_TEST_CASE(get_available_speed_by_gear)
    {
        // wrong gear
        RangeSpeed getSpeed = car.GetAvailableSpeedByGear(10);
        BOOST_CHECK(getSpeed.first == 0 && getSpeed.second == 0);
        
        // gear = -1 => 0-20 km/h
        getSpeed = car.GetAvailableSpeedByGear(-1);
        BOOST_CHECK(getSpeed.first == 0 && getSpeed.second == 20);
        
        // gear = 0 => no limits
        getSpeed = car.GetAvailableSpeedByGear(0);
        BOOST_CHECK(getSpeed.first == 0 && getSpeed.second == 150);
        
        // gear = 1 => 0-20 km/h
        getSpeed = car.GetAvailableSpeedByGear(3);
        BOOST_CHECK(getSpeed.first == 30 && getSpeed.second == 60);
    }

    // проверка передачи при текущей скорости
    BOOST_AUTO_TEST_CASE(is_current_speed_correspond_gear)
    {
        // wrong gear
        BOOST_CHECK(!car.IsSpeedCorrespondGear(20, 10));
        
        // gear = -1
        BOOST_CHECK(!car.IsSpeedCorrespondGear(30, -1)); // wrong
        BOOST_CHECK(car.IsSpeedCorrespondGear(15, -1)); // good
        
        // gear = 0 => no speed limit
        BOOST_CHECK(!car.IsSpeedCorrespondGear(200, 0)); // wrong
        BOOST_CHECK(car.IsSpeedCorrespondGear(0, 0)); // good
        
        // gear = 2
        BOOST_CHECK(!car.IsSpeedCorrespondGear(80, 2)); // wrong
        BOOST_CHECK(car.IsSpeedCorrespondGear(30, 2)); // good
        
    }

    // TODO: write fixture
    // проверка переключения передачи

    // проверка на выключенном двигателе
    BOOST_AUTO_TEST_CASE(set_gear_on_turnoff_engine)
    {
        // пытаемся включить несуществующую передачу
        BOOST_CHECK(car.SetGear(10) == false);

        car.TurnOffEngine();

        BOOST_CHECK(car.SetGear(0) == true);

        BOOST_CHECK(car.SetGear(4) == false);
        BOOST_CHECK(car.SetGear(-1) == false);

    }

    // проверка при включенном двигателе
    BOOST_AUTO_TEST_CASE(set_gear_on_turnon_engine)
    {
        // автомобиль стоит заводим двигатель..
        car.TurnOnEngine();
        
        BOOST_CHECK(car.SetGear(1) == true); // на первую можно
        BOOST_CHECK(car.SetGear(-1) == true); // на заднюю можно
        BOOST_CHECK(car.SetGear(3) == false); // на все остальные нельзя
    }

    // проверка при скорости
    BOOST_AUTO_TEST_CASE(set_gear_on_speed)
    {
        car.TurnOnEngine();
        
        // имитируем разгон и понижение передачи
        car.SetGear(1);
        car.SetSpeed(10);
        BOOST_CHECK(car.SetGear(2) == false); // при 10 нельзя

        car.SetSpeed(25);
        BOOST_CHECK(car.SetGear(2) == true); // при 25 на 2 можно
        
        car.SetSpeed(40);
        BOOST_CHECK(car.SetGear(3) == true); // при 40 на 3 можно
        BOOST_CHECK(car.SetGear(1) == false); // при 40 на 1 нельзя
        BOOST_CHECK(car.SetGear(-1) == false); // при 40 на -1 нельзя
        BOOST_CHECK(car.SetGear(-1) == false); // при 40 на -1 нельзя

//        car.SetSpeed(0);
//        BOOST_CHECK(car.SetGear(0) == true); // при 0 на нейтраль

//        BOOST_CHECK(car.SetGear(0) == true); // при 25 можно // todo
    }

    //
    BOOST_AUTO_TEST_CASE(set_speed)
    {
        car.TurnOnEngine();
        car.SetGear(1);
        BOOST_CHECK(car.SetSpeed(-10) == false); // неверное
        BOOST_CHECK(car.SetSpeed(10) == true);
        car.SetGear(-1);
        BOOST_CHECK(car.SetSpeed(10) == true);
        BOOST_CHECK(car.SetSpeed(30) == false);


    }

BOOST_AUTO_TEST_SUITE_END()
