#include "core/serialize/serialize.h"
#include "gtest/gtest.h"

using namespace std;

namespace ruby_typer {
namespace core {
namespace serialize {

TEST(SerializeTest, U4) { // NOLINT
    GlobalStateSerializer::Pickler p;
    p.putU4(0);
    p.putU4(1);
    p.putU4(4294967295);
    GlobalStateSerializer::UnPickler u(p.result().data());
    EXPECT_EQ(u.getU4(), 0);
    EXPECT_EQ(u.getU4(), 1);
    EXPECT_EQ(u.getU4(), 4294967295);
}

TEST(SerializeTest, U4U1) { // NOLINT
    GlobalStateSerializer::Pickler p;
    p.putU4(0);
    p.putU4(0);
    p.putStr("aaaaa");
    p.putU4(0);
    p.putU4(0);
    p.putU1(1);
    p.putU4(1);
    p.putU1(0);
    p.putU4(4294967295);
    GlobalStateSerializer::UnPickler u(p.result().data());
    EXPECT_EQ(u.getU4(), 0);
    EXPECT_EQ(u.getU4(), 0);
    EXPECT_EQ(u.getStr(), "aaaaa");
    EXPECT_EQ(u.getU4(), 0);
    EXPECT_EQ(u.getU4(), 0);
    EXPECT_EQ(u.getU1(), 1);
    EXPECT_EQ(u.getU4(), 1);
    EXPECT_EQ(u.getU1(), 0);
    EXPECT_EQ(u.getU4(), 4294967295);
}

TEST(SerializeTest, U8) { // NOLINT
    GlobalStateSerializer::Pickler p;
    p.putS8(0);
    p.putS8(1);
    p.putS8(-1);
    p.putS8(9223372036854775807);
    GlobalStateSerializer::UnPickler u(p.result().data());
    EXPECT_EQ(u.getS8(), 0);
    EXPECT_EQ(u.getS8(), 1);
    EXPECT_EQ(u.getS8(), -1);
    EXPECT_EQ(u.getS8(), 9223372036854775807);
}

TEST(SerializeTest, Strings) { // NOLINT
    GlobalStateSerializer::Pickler p;
    p.putStr("");
    p.putStr("a");
    p.putStr("aaaaa");
    p.putStr("1");
    p.putStr("Z");
    p.putStr("НЯ");
    p.putStr("\0\0\0\t\n\f\rНЯЯЯЯЯ");
    GlobalStateSerializer::UnPickler u(p.result().data());
    EXPECT_EQ(u.getStr(), "");
    EXPECT_EQ(u.getStr(), "a");
    EXPECT_EQ(u.getStr(), "aaaaa");
    EXPECT_EQ(u.getStr(), "1");
    EXPECT_EQ(u.getStr(), "Z");
    EXPECT_EQ(u.getStr(), "НЯ");
    EXPECT_EQ(u.getStr(), "\0\0\0\t\n\f\rНЯЯЯЯЯ");
}

} // namespace serialize

} // namespace core
} // namespace ruby_typer
