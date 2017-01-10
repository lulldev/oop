#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../VolumeBodies/CSphere.h"
#include "../VolumeBodies/CCone.h"
#include "../VolumeBodies/CParallelepiped.h"
#include "../VolumeBodies/CCylinder.h"

using testing::Eq;

/* -------------------- Сфера -------------------- */

class CSphereTestFixture : public ::testing::Test
{
public:
    CSphere *sphere;

    CSphereTestFixture()
    {
        sphere = new CSphere(10.0, 20.0);
    }

protected:
    void SetUp() override
    {
    }

    void TearDown()
    {
        delete sphere;
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
    ASSERT_TRUE(sphere->m_type == TYPENAME_SPHERE);
}

TEST_F(CSphereTestFixture, TestBaseSphereMethods)
{
    ASSERT_EQ(sphere->GetDensity(), 10.0);
    ASSERT_EQ(sphere->GetRadius(), 20.0);
    ASSERT_EQ(sphere->GetVolume(), (4/3) * 3.14 * pow(20.0, 3));
    ASSERT_EQ(sphere->GetMass(), sphere->GetDensity() * sphere->GetVolume());
}

/* -------------------- Конус -------------------- */

class CConeTestFixture : public ::testing::Test
{
public:
    CCone *cone;

    CConeTestFixture()
    {
        cone = new CCone(10.0, 20.0, 5.0);
    }

protected:
    void SetUp() override
    {
    }

    void TearDown()
    {
        delete cone;
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
    ASSERT_TRUE(cone->m_type == TYPENAME_CONE);
}

TEST_F(CConeTestFixture, TestBaseConeMethods)
{
    ASSERT_EQ(cone->GetDensity(), 10.0);
    ASSERT_EQ(cone->GetBaseRadius(), 20.0);
    ASSERT_EQ(cone->GetHeight(), 5.0);

    // test calculate cone volume
    // 2094.3999
    double expectedTesingVolume = (5.0 / 3) * (pow(20.0, 2) * M_PI);
    ASSERT_FLOAT_EQ(cone->GetVolume(), expectedTesingVolume);
}

/* -------------------- Параллелепипед -------------------- */

class CParallelepipedTestFixture : public ::testing::Test
{
public:
    CParallelepiped *parallelepiped;

    CParallelepipedTestFixture()
    {
        parallelepiped = new CParallelepiped(10.0, 20.0, 5.0, 15.0);
    }

protected:
    void SetUp() override
    {
    }

    void TearDown()
    {
        delete parallelepiped;
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
    ASSERT_TRUE(parallelepiped->m_type == TYPENAME_PARALLELEPIPED);
}

TEST_F(CParallelepipedTestFixture, TestBaseParallelepipedMethods)
{
    ASSERT_EQ(parallelepiped->GetDensity(), 10.0);
    ASSERT_EQ(parallelepiped->GetWidth(), 20.0);
    ASSERT_EQ(parallelepiped->GetHeight(), 5.0);
    ASSERT_EQ(parallelepiped->GetDepth(), 15.0);

    ASSERT_FLOAT_EQ(parallelepiped->GetVolume(), 20.0 * 5.0 * 15.0); // 1500
    ASSERT_FLOAT_EQ(parallelepiped->GetMass(), (20.0 * 5.0 * 15.0) * 10); // 15000
}

/* -------------------- Цилиндр -------------------- */

class CCylinderTestFixture : public ::testing::Test
{
public:
    CCylinder *cylinder;

    CCylinderTestFixture()
    {
        cylinder = new CCylinder(10.0, 20.0, 5.0);
    }

protected:
    void SetUp() override
    {
    }

    void TearDown()
    {
        delete cylinder;
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
    ASSERT_TRUE(cylinder->m_type == TYPENAME_CYLINDER);
}

TEST_F(CCylinderTestFixture, TestBaseConeMethods)
{
    ASSERT_EQ(cylinder->GetDensity(), 10.0);
    ASSERT_EQ(cylinder->GetBaseRadius(), 20.0);
    ASSERT_EQ(cylinder->GetHeight(), 5.0);

    // test calculate cylinder volume
    ASSERT_FLOAT_EQ(cylinder->GetVolume(), M_PI * pow(20.0, 3) * 5.0);
}


/* -------------------- Проверка ToString -------------------- */

class CBodiesTestFixture : public ::testing::Test
{
public:
    CSphere *sphere;
    CCone *cone;
    CParallelepiped *parallelepiped;
    CCylinder *cylinder;

    CBodiesTestFixture()
    {
        sphere = new CSphere(10.0, 20.0);
        cone = new CCone(10.0, 20.0, 5.0);
        parallelepiped = new CParallelepiped(10.0, 20.0, 5.0, 10);
        cylinder = new CCylinder(10.0, 20.0, 5.0);
    }

protected:
    void SetUp() override
    {
    }

    void TearDown()
    {
        delete sphere;
        delete cone;
        delete parallelepiped;
        delete cylinder;
    }
};

TEST_F(CBodiesTestFixture, ToStringSphere)
{
    std::string expectedString = "Type: sphere\n"
            "Density: 10.000000\n"
            "Volume: 25120.000000\n"
            "Mass: 251200.000000\n"
            "Radius: 20.000000\n";

    ASSERT_TRUE(sphere->ToString() == expectedString);
}

TEST_F(CBodiesTestFixture, ToStringParallelepiped)
{
    std::cout << parallelepiped->ToString();
    std::string expectedString = "Type: parallelepiped\n"
            "Density: 10.000000\n"
            "Volume: 1000.000000\n"
            "Mass: 10000.000000\n"
            "Width: 20.000000\n"
            "Height: 5.000000\n"
            "Depth: 10.000000\n";

    ASSERT_TRUE(parallelepiped->ToString() == expectedString);
}

TEST_F(CBodiesTestFixture, ToStringCone)
{
    std::string expectedString = "Type: cone\n"
            "Density: 10.000000\n"
            "Volume: 2094.395102\n"
            "Mass: 20943.951024\n"
            "Radius: 20.000000\n"
            "Height: 5.000000\n";

    ASSERT_TRUE(cone->ToString() == expectedString);
}
TEST_F(CBodiesTestFixture, ToStringCylinder)
{
    std::string expectedString = "Type: cylinder\n"
            "Density: 10.000000\n"
            "Volume: 125663.706144\n"
            "Mass: 1256637.061436\n"
            "Radius: 20.000000\n";

    ASSERT_TRUE(cylinder->ToString() == expectedString);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    //return 0;
}