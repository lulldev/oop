#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <iostream>

#include "../VolumeBodies/Helpers.h"
#include "../VolumeBodies/VolumeBodies.h"
#include "../ConsoleProgram/ConsoleProgram.h"

using testing::Eq;
using namespace std;

/* -------------------- Хелперы -------------------- */

TEST(TestHelpers, TestSimplePow)
{
    ASSERT_DOUBLE_EQ(pow(10, 2), SimplePow(10, 2));
    ASSERT_DOUBLE_EQ(pow(5, 3), SimplePow(5, 3));
    ASSERT_DOUBLE_EQ(pow(2.75, 2), SimplePow(2.75, 2));
}


/* -------------------- Сфера -------------------- */

class CSphereTestFixture : public ::testing::Test
{
public:
    CSphere sphere;

    CSphereTestFixture()
    :sphere(10.0, 20.0)
    {
    }

protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
        //delete sphere;
    }
};

TEST_F(CSphereTestFixture, InitClassWithNegativeDensity)
{
    ASSERT_THROW(CSphere sphere(-1, 10), std::invalid_argument);
}

TEST_F(CSphereTestFixture, InitClassWithNegativeRadius)
{
    ASSERT_THROW(CSphere sphere(1.0, -1), std::invalid_argument);
}

TEST_F(CSphereTestFixture, InitClassWithAllowParams)
{
    ASSERT_NO_THROW(CSphere sphere(1.0, 10.00));
}

TEST_F(CSphereTestFixture, CheckSphereType)
{
    ASSERT_TRUE(sphere.GetType() == TYPENAME_SPHERE);
}

TEST_F(CSphereTestFixture, TestBaseSphereMethods)
{
    ASSERT_EQ(sphere.GetDensity(), 10.0);
    ASSERT_EQ(sphere.GetRadius(), 20.0);
    ASSERT_EQ(sphere.GetVolume(), (4/3) * 3.14 * SimplePow(20.0, 3));
    ASSERT_EQ(sphere.GetMass(), sphere.GetDensity() * sphere.GetVolume());
}

TEST_F(CSphereTestFixture, ToStringSphere)
{
    std::string expectedString = "Type: sphere\n"
            "Density: 10.00\n"
            "Volume: 25120.00\n"
            "Mass: 251200.00\n"
            "Radius: 20.00\n";

    ASSERT_TRUE(sphere.ToString() == expectedString);
}

/* -------------------- Конус -------------------- */

class CConeTestFixture : public ::testing::Test
{
public:
    CCone cone;

    CConeTestFixture()
    :cone(10.0, 20.0, 5.0)
    {
    }

protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(CConeTestFixture, InitClassWithNegativeDensity)
{
    ASSERT_THROW(CCone cone(-1, 10, 5), std::invalid_argument);
}

TEST_F(CConeTestFixture, InitClassWithNegativeRadius)
{
    ASSERT_THROW(CCone cone(1.0, -1, 5), std::invalid_argument);
}

TEST_F(CConeTestFixture, InitClassWithNegativeHeight)
{
    ASSERT_THROW(CCone cone(1.0, 1, -5), std::invalid_argument);
}


TEST_F(CConeTestFixture, InitClassWithAllowParams)
{
    ASSERT_NO_THROW(CCone cone(1.0, 10.00, 5.00));
}

TEST_F(CConeTestFixture, CheckSphereType)
{
    ASSERT_TRUE(cone.GetType() == TYPENAME_CONE);
}

TEST_F(CConeTestFixture, TestBaseConeMethods)
{
    ASSERT_EQ(cone.GetDensity(), 10.0);
    ASSERT_EQ(cone.GetBaseRadius(), 20.0);
    ASSERT_EQ(cone.GetHeight(), 5.0);

    // test calculate cone volume
    // 2094.3999
    double expectedTesingVolume = (5.0 / 3) * (SimplePow(20.0, 2) * M_PI);
    ASSERT_FLOAT_EQ(cone.GetVolume(), expectedTesingVolume);
}

TEST_F(CConeTestFixture, ToStringCone)
{
    std::string expectedString = "Type: cone\n"
            "Density: 10.00\n"
            "Volume: 2094.40\n"
            "Mass: 20943.95\n"
            "Radius: 20.00\n"
            "Height: 5.00\n";

    ASSERT_TRUE(cone.ToString() == expectedString);
}

/* -------------------- Параллелепипед -------------------- */

class CParallelepipedTestFixture : public ::testing::Test
{
public:
    CParallelepiped parallelepiped;

    CParallelepipedTestFixture()
    :parallelepiped(10.0, 20.0, 5.0, 15.0)
    {
    }

protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
//        delete parallelepiped;
    }
};

TEST_F(CParallelepipedTestFixture, InitClassWithNegativeDensity)
{
    ASSERT_THROW(CParallelepiped parallelepiped(-1, 10, 5, 100), std::invalid_argument);
}

TEST_F(CParallelepipedTestFixture, InitClassWithNegativeWidth)
{
    ASSERT_THROW(CParallelepiped parallelepiped(1, -10, 5, 100), std::invalid_argument);
}

TEST_F(CParallelepipedTestFixture, InitClassWithNegativeHeight)
{
    ASSERT_THROW(CParallelepiped parallelepiped(1, 10, -5, 100), std::invalid_argument);
}

TEST_F(CParallelepipedTestFixture, InitClassWithNegativeDepth)
{
    ASSERT_THROW(CParallelepiped parallelepiped(1, 10, 4, -1.0), std::invalid_argument);
}

TEST_F(CParallelepipedTestFixture, InitClassWithAllowParams)
{
    ASSERT_NO_THROW(CParallelepiped parallelepiped(1, 10, 4, 1.0));
}

TEST_F(CParallelepipedTestFixture, CheckParallelepipedType)
{
    ASSERT_TRUE(parallelepiped.GetType() == TYPENAME_PARALLELEPIPED);
}

TEST_F(CParallelepipedTestFixture, TestBaseParallelepipedMethods)
{
    ASSERT_EQ(parallelepiped.GetDensity(), 10.0);
    ASSERT_EQ(parallelepiped.GetWidth(), 20.0);
    ASSERT_EQ(parallelepiped.GetHeight(), 5.0);
    ASSERT_EQ(parallelepiped.GetDepth(), 15.0);

    ASSERT_FLOAT_EQ(parallelepiped.GetVolume(), 20.0 * 5.0 * 15.0); // 1500
    ASSERT_FLOAT_EQ(parallelepiped.GetMass(), (20.0 * 5.0 * 15.0) * 10); // 15000
}


TEST_F(CParallelepipedTestFixture, ToStringParallelepiped)
{
    std::string expectedString = "Type: parallelepiped\n"
            "Density: 10.00\n"
            "Volume: 1500.00\n"
            "Mass: 15000.00\n"
            "Width: 20.00\n"
            "Height: 5.00\n"
            "Depth: 15.00\n";

    ASSERT_TRUE(parallelepiped.ToString() == expectedString);
}

/* -------------------- Цилиндр -------------------- */

class CCylinderTestFixture : public ::testing::Test
{
public:
    CCylinder cylinder;

    CCylinderTestFixture()
    :cylinder(10.0, 20.0, 5.0)
    {
    }
};

TEST_F(CCylinderTestFixture, InitClassWithNegativeDensity)
{
    ASSERT_THROW(CCylinder cylinder(-1, 10, 5), std::invalid_argument);
}

TEST_F(CCylinderTestFixture, InitClassWithNegativeRadius)
{
    ASSERT_THROW(CCylinder cylinder(1.0, -1, 5), std::invalid_argument);
}

TEST_F(CCylinderTestFixture, InitClassWithNegativeHeight)
{
    ASSERT_THROW(CCylinder cylinder(1.0, 1, -5), std::invalid_argument);
}

TEST_F(CCylinderTestFixture, InitClassWithAllowParams)
{
    ASSERT_NO_THROW(CCylinder cylinder(1.0, 10.00, 5.00));
}

TEST_F(CCylinderTestFixture, CheckSphereType)
{
    ASSERT_TRUE(cylinder.GetType() == TYPENAME_CYLINDER);
}

TEST_F(CCylinderTestFixture, TestBaseConeMethods)
{
    ASSERT_EQ(cylinder.GetDensity(), 10.0);
    ASSERT_EQ(cylinder.GetBaseRadius(), 20.0);
    ASSERT_EQ(cylinder.GetHeight(), 5.0);

    // test calculate cylinder volume
    ASSERT_FLOAT_EQ(cylinder.GetVolume(), M_PI * SimplePow(20.0, 3) * 5.0);
}

TEST_F(CCylinderTestFixture, ToStringCylinder)
{
    std::string expectedString = "Type: cylinder\n"
            "Density: 10.00\n"
            "Volume: 125663.71\n"
            "Mass: 1256637.06\n"
            "Radius: 20.00\n";

    ASSERT_TRUE(cylinder.ToString() == expectedString);
}

/* -------------------- Составное тело -------------------- */

class CCompoundTestFixture : public ::testing::Test
{
public:
    CCylinder cylinder;
    CCone cone;
    CParallelepiped parallelepiped;
    CSphere sphere;
    CCompound compound;

    shared_ptr<CBody> cylinderPtr;
    shared_ptr<CBody> conePtr;
    shared_ptr<CBody> parallelepipedPtr;
    shared_ptr<CBody> spherePtr;
    shared_ptr<CBody> compoundPtr;

    CCompoundTestFixture()
        :cylinder(1, 1, 2),
         cone(10, 2, 1),
         parallelepiped(2, 2, 2, 2),
         sphere(1, 2),
         compound()
    {
        cylinderPtr = make_shared<CCylinder>(cylinder);
        conePtr = make_shared<CCone>(cone);
        parallelepipedPtr = make_shared<CParallelepiped>(parallelepiped);
        spherePtr = make_shared<CSphere>(sphere);
        compoundPtr = make_shared<CCompound>(compound);
    }
};

TEST_F(CCompoundTestFixture, TestSelfAddToChild)
{
//    ASSERT_THROW(compound.AddChildBody(compoundPtr), std::invalid_argument); todo
    ASSERT_NO_THROW(compound.AddChildBody(spherePtr));
}

TEST_F(CCompoundTestFixture, TestAddValidSimpleBodiesChilds)
{
    ASSERT_TRUE(compound.AddChildBody(cylinderPtr));
    ASSERT_TRUE(compound.AddChildBody(conePtr));
    ASSERT_TRUE(compound.AddChildBody(parallelepipedPtr));
    ASSERT_TRUE(compound.AddChildBody(spherePtr));
}


TEST_F(CCompoundTestFixture, TestAddCompoundToChilds)
{
    CCompound testingCompound;
    shared_ptr<CBody> testingCompoundPtr = make_shared<CCompound>(testingCompound);

    ASSERT_TRUE(testingCompound.AddChildBody(cylinderPtr));
    ASSERT_TRUE(testingCompound.AddChildBody(conePtr));
    ASSERT_TRUE(compound.AddChildBody(testingCompoundPtr));
}

TEST_F(CCompoundTestFixture, TestGetMassOnEmptyBodiesArray)
{
    ASSERT_DOUBLE_EQ(compound.GetMass(), 0);
}

TEST_F(CCompoundTestFixture, TestGetMassOnFillBodiesArray)
{
    compound.AddChildBody(cylinderPtr);
    ASSERT_DOUBLE_EQ(compound.GetMass(), cylinder.GetMass());

    compound.AddChildBody(conePtr);
    ASSERT_DOUBLE_EQ(compound.GetMass(), cone.GetMass() + cylinder.GetMass());
}

TEST_F(CCompoundTestFixture, TestCompoundVolume)
{
    ASSERT_DOUBLE_EQ(compound.GetVolume(), 0);

    compound.AddChildBody(parallelepipedPtr);
    ASSERT_DOUBLE_EQ(compound.GetVolume(), parallelepiped.GetVolume());

    compound.AddChildBody(cylinderPtr);
    ASSERT_DOUBLE_EQ(compound.GetVolume(), parallelepiped.GetVolume() + cylinder.GetVolume());
}

TEST_F(CCompoundTestFixture, TestCompoundDensity)
{
    ASSERT_DOUBLE_EQ(compound.GetDensity(), 0);

    compound.AddChildBody(parallelepipedPtr);
    ASSERT_DOUBLE_EQ(compound.GetDensity(), parallelepiped.GetDensity());

    compound.AddChildBody(cylinderPtr);
    double expectedDensity = (parallelepiped.GetMass() + cylinder.GetMass())
                             / (parallelepiped.GetVolume() + cylinder.GetVolume());
    ASSERT_DOUBLE_EQ(compound.GetDensity(), expectedDensity);
}

TEST_F(CCompoundTestFixture, TestEmptyCompoundToString)
{
    std::string expectedString =
            "Type: compound\n"
            "Density: 0.00\n"
            "Volume: 0.00\n"
            "Mass: 0.00\n"
            "Childs (0):\n"
            "No childs\n";

    ASSERT_TRUE(compound.ToString() == expectedString);
}

TEST_F(CCompoundTestFixture, TestCompoundToString)
{
    compound.AddChildBody(spherePtr);

    std::string expectedString =
        "Type: compound\n"
        "Density: 1.00\n"
        "Volume: 25.12\n"
        "Mass: 25.12\n"
        "Childs (1):\n"
        "Type: sphere\n"
        "Density: 1.00\n"
        "Volume: 25.12\n"
        "Mass: 25.12\n"
        "Radius: 2.00\n\n";

    ASSERT_TRUE(compound.ToString() == expectedString);

    compound.AddChildBody(cylinderPtr);

    expectedString =
            "Type: compound\n"
                    "Density: 1.00\n"
                    "Volume: 31.40\n"
                    "Mass: 31.40\n"
                    "Childs (2):\n"
                    "Type: sphere\n"
                    "Density: 1.00\n"
                    "Volume: 25.12\n"
                    "Mass: 25.12\n"
                    "Radius: 2.00\n\n"
                    "Type: cylinder\n"
                    "Density: 1.00\n"
                    "Volume: 6.28\n"
                    "Mass: 6.28\n"
                    "Radius: 1.00\n\n";

    ASSERT_TRUE(compound.ToString() == expectedString);
}



/* -------------------- Консольная программа -------------------- */

std::vector<std::shared_ptr<CBody>> bodiesArray;

class ConsoleProgramTestFixture : public ::testing::Test
{
public:
    ConsoleProgram *program;
    std::vector<std::shared_ptr<CBody>> bodiesArray;

    ConsoleProgramTestFixture()
    {
        program = new ConsoleProgram(std::cin, std::cout, bodiesArray);
    }

    std::string GetOutput()
    {
        testing::internal::CaptureStdout();
        return testing::internal::GetCapturedStdout();
    }

protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
        std::cout.clear();
    }
};

TEST_F(ConsoleProgramTestFixture, TestWrongCommandCall)
{
    //ASSERT_THROW(program->ProcessInputCommand(""), invalid_argument);
    ASSERT_THROW(program->ProcessInputCommand("test"), invalid_argument);
}

TEST_F(ConsoleProgramTestFixture, TestUnknowCommandCall)
{
    ASSERT_THROW(program->ProcessInputCommand("command 10 10 10"), invalid_argument);

    try
    {
        program->ProcessInputCommand("command 10 10 10");
    }
    catch (const std::exception& ex)
    {
        EXPECT_STREQ("Unknow command", ex.what());
    }
}

TEST_F(ConsoleProgramTestFixture, TestCallSphereWithInvalidParameters)
{
    ASSERT_THROW(program->ProcessInputCommand("sphere 10"), invalid_argument);
    ASSERT_THROW(program->ProcessInputCommand("sphere string"), invalid_argument);

    try
    {
        program->ProcessInputCommand("sphere 10 d");
    }
    catch (const std::exception& e)
    {
        EXPECT_STREQ("Sphere invalid parameters", e.what());
    }

}

TEST_F(ConsoleProgramTestFixture, TestCallSphereWithValidParameters)
{
    ASSERT_NO_THROW(program->ProcessInputCommand("sphere 10 10"));
    ASSERT_NO_THROW(program->ProcessInputCommand("sphere 23.23 5.55"));
}

TEST_F(ConsoleProgramTestFixture, TestCallConeWithInvalidParameters)
{
    ASSERT_THROW(program->ProcessInputCommand("cone 10"), invalid_argument);
    ASSERT_THROW(program->ProcessInputCommand("cone string"), invalid_argument);

    try
    {
        program->ProcessInputCommand("cone dsf 12 11");
    }
    catch (const std::exception& e)
    {
        EXPECT_STREQ("Cone invalid parameters", e.what());
    }

}

TEST_F(ConsoleProgramTestFixture, TestCallConeWithValidParameters)
{
    ASSERT_NO_THROW(program->ProcessInputCommand("cone 10 10 30"));
    ASSERT_NO_THROW(program->ProcessInputCommand("cone 23.23 5.55 0.24"));
}

TEST_F(ConsoleProgramTestFixture, TestCallParallelepipedWithInvalidParameters)
{
    ASSERT_THROW(program->ProcessInputCommand("parallelepiped 10"), invalid_argument);
    ASSERT_THROW(program->ProcessInputCommand("parallelepiped string"), invalid_argument);

    try
    {
        program->ProcessInputCommand("parallelepiped dsf 12 11");
    }
    catch (const std::exception& e)
    {
        EXPECT_STREQ("Invalid count parameters", e.what());
    }

}

TEST_F(ConsoleProgramTestFixture, TestCallParallelepipedWithValidParameters)
{
    ASSERT_NO_THROW(program->ProcessInputCommand("parallelepiped 10 100 300 20"));
    ASSERT_NO_THROW(program->ProcessInputCommand("parallelepiped 23.23 5.55 0.24 10"));
}

TEST_F(ConsoleProgramTestFixture, TestCallCylinderWithInvalidParameters)
{
    ASSERT_THROW(program->ProcessInputCommand("cylinder 10"), invalid_argument);
    ASSERT_THROW(program->ProcessInputCommand("cylinder string"), invalid_argument);

    try
    {
        program->ProcessInputCommand("cylinder dsf 12 11");
    }
    catch (const std::exception& e)
    {
        EXPECT_STREQ("Cylinder invalid parameters", e.what());
    }
}

TEST_F(ConsoleProgramTestFixture, TestCallCylinderWithValidParameters)
{
    ASSERT_NO_THROW(program->ProcessInputCommand("cylinder 10 100 300"));
    ASSERT_NO_THROW(program->ProcessInputCommand("cylinder 23.23 5.55 0.24"));
}

/* -------------------- Вывод макс/мин тела -------------------- */

TEST_F(ConsoleProgramTestFixture, TestCallMaxMassBodyWithEmptyBodiesArray)
{
    ASSERT_THROW(program->GetMaxMassBody(), invalid_argument);
    program->ProcessInputCommand("cylinder 10 10 10");
    ASSERT_NO_THROW(program->GetMaxMassBody());
}

TEST_F(ConsoleProgramTestFixture, TestCallMinWeightBodyWithEmptyBodiesArray)
{
    ASSERT_THROW(program->GetMaxMassBody(), invalid_argument);
    program->ProcessInputCommand("cone 5 10 5");
    ASSERT_NO_THROW(program->GetMaxMassBody());
}

TEST_F(ConsoleProgramTestFixture, TestCallMaxMassBody)
{
    program->ProcessInputCommand("cylinder 10 10 10");
    program->ProcessInputCommand("sphere 20 20");

    ASSERT_TRUE(program->GetMaxMassBody()->GetType() == TYPENAME_SPHERE);
}

TEST_F(ConsoleProgramTestFixture, TestCallMinWeightBody)
{
    program->ProcessInputCommand("cylinder 10 10 10");
    program->ProcessInputCommand("parallelepiped 5 5 5 5");

    ASSERT_TRUE(program->GetMinWeightBody()->GetType() == TYPENAME_CYLINDER);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}