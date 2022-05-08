/*
 * VLS (http://vilaversoftware.dk/)
 * Author: Mikkel Nøhr Løvgreen (ml@vilaversoftware.dk)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma warning(push, 0)
#include "gtest/gtest.h"
#pragma warning(pop)

#include "VLS/DateTime.h"

 #include "VLS/Variant/Val.h"

using namespace VLS::Variant;

 TEST(VLSVariantCRef, Constructor)
 {
     CRef value1;
     Ref value2;
     Val value3;
 }

 TEST(VLSVariantCRef, constructors)
 {
     CRef cEmpty;
     EXPECT_EQ(cEmpty.type(), Type::Undefined);

     char* c = "Test";
     CRef cCStr(c);
     EXPECT_EQ(cCStr.type(), Type::Char);

     std::string s = "Test";
     CRef cStr(s);
     EXPECT_EQ(cStr.type(), Type::String);

     bool b = true;
     CRef cBool(b);
     EXPECT_EQ(cBool.type(), Type::Bool);

     int i = 0;
     CRef cInt(i);
     EXPECT_EQ(cInt.type(), Type::Integer);

     double d = 1.0;
     CRef cDouble(d);
     EXPECT_EQ(cDouble.type(), Type::Double);

     VLS::DateTime dt;
     CRef cDT(dt);
     EXPECT_EQ(cDT.type(), Type::DateTime);
 }

 TEST(VLSVariantCRef, operator_assignment)
 {
     //char* c = "Test";
     //Reference cCStr(c);
     //EXPECT_EQ(cCStr.type(), Type::Char);

     std::string s = "Test";
     Ref cStr(s);
     EXPECT_EQ(cStr, "Test");
     cStr = "Test2";
     EXPECT_EQ(s, "Test2");

     bool b = true;
     Ref cBool(b);
     EXPECT_EQ(cBool, true);
     cBool = false;
     EXPECT_EQ(cBool, false);
     EXPECT_EQ(b, false);

     int i = 0;
     Ref cInt(i);
     EXPECT_EQ(cInt, 0);
     cInt = 42;
     EXPECT_EQ(cInt, 42);
     EXPECT_EQ(i, 42);


     double d = 1.0;
     Ref cDouble(d);
     EXPECT_EQ(cDouble, 1.0);
     cDouble = -42.42;
     EXPECT_EQ(cDouble, -42.42);
     EXPECT_EQ(d, -42.42);

     VLS::DateTime dt;
     Ref cDT(dt);
     EXPECT_EQ(cDT, VLS::DateTime());
     cDT = VLS::DateTime(1982, 2, 9, 6, 36, 25);
     EXPECT_EQ(cDT, VLS::DateTime(1982, 2, 9, 6, 36, 25));
     EXPECT_EQ(dt, VLS::DateTime(1982, 2, 9, 6, 36, 25));
 }

 TEST(VLSVariantCRef, operator_compare_string)
 {
     std::string str = "1234";
     CRef ref1(str);
     const char* cStr = "abcd";
     CRef ref2(cStr);

     // operator ==
     EXPECT_TRUE(ref1 == "1234");
     EXPECT_TRUE(ref1 == std::string("1234"));
     EXPECT_TRUE(ref2 == "abcd");
     EXPECT_TRUE(ref2 == std::string("abcd"));
     EXPECT_FALSE(ref1 == "123");
     EXPECT_FALSE(ref1 == std::string("123"));
     EXPECT_FALSE(ref2 == "abc");
     EXPECT_FALSE(ref2 == std::string("abc"));

     // operator != 
     EXPECT_TRUE(ref1 != "123");
     EXPECT_TRUE(ref1 != std::string("123"));
     EXPECT_TRUE(ref2 != "abc");
     EXPECT_TRUE(ref2 != std::string("abc"));
     EXPECT_FALSE(ref1 != "1234");
     EXPECT_FALSE(ref1 != std::string("1234"));
     EXPECT_FALSE(ref2 != "abcd");
     EXPECT_FALSE(ref2 != std::string("abcd"));

     // operator >
     EXPECT_TRUE(ref1 > "0");
     EXPECT_FALSE(ref1 > "1234");
     EXPECT_FALSE(ref1 > "2");

     // operator >=
     EXPECT_TRUE(ref1 >= "0");
     EXPECT_TRUE(ref1 >= "1234");
     EXPECT_FALSE(ref1 >= "2");

     // operator <
     EXPECT_FALSE(ref1 < "0");
     EXPECT_FALSE(ref1 < "1234");
     EXPECT_TRUE(ref1 < "2");

     // operator <=
     EXPECT_FALSE(ref1 <= "0");
     EXPECT_TRUE(ref1 <= "1234");
     EXPECT_TRUE(ref1 <= "2");
 }

 TEST(VLSVariantCRef, operator_compare_bool)
 {
     bool b = true;
     CRef ref(b);

     // operator ==
     EXPECT_TRUE(ref == true);
     EXPECT_FALSE(ref == false);

     // operator != 
     EXPECT_FALSE(ref != true);
     EXPECT_TRUE(ref != false);

     // operator >
     EXPECT_FALSE(ref > true);
     EXPECT_TRUE(ref > false);

     // operator >=
     EXPECT_TRUE(ref >= true);
     EXPECT_TRUE(ref >= false);

     // operator <
     EXPECT_TRUE(ref <= true);
     EXPECT_FALSE(ref <= false);

     // operator <=
     EXPECT_TRUE(ref == true);
     EXPECT_FALSE(ref == false);
 }

 TEST(VLSVariantCRef, operator_compare_int)
 {
     int i = 42;
     CRef ref(i);

     // operator ==
     EXPECT_TRUE(ref == 42);
     EXPECT_FALSE(ref == 43);

     // operator != 
     EXPECT_TRUE(ref != 43);
     EXPECT_FALSE(ref != 42);

     // operator >
     EXPECT_TRUE(ref > 41);
     EXPECT_FALSE(ref > 42);
     EXPECT_FALSE(ref > 43);

     // operator >=
     EXPECT_TRUE(ref >= 41);
     EXPECT_TRUE(ref >= 42);
     EXPECT_FALSE(ref >= 43);

     // operator <
     EXPECT_FALSE(ref < 41);
     EXPECT_FALSE(ref < 42);
     EXPECT_TRUE(ref < 43);

     // operator <=
     EXPECT_FALSE(ref <= 41);
     EXPECT_TRUE(ref <= 42);
     EXPECT_TRUE(ref <= 43);
 }

 TEST(VLSVariantCRef, operator_compare_double)
 {
     double i = 42.0;
     CRef ref(i);
     EXPECT_EQ(ref, 42.0);
     EXPECT_NE(ref, 43.0);

     // operator ==
     EXPECT_TRUE(ref == 42.0);
     EXPECT_FALSE(ref == 43.0);

     // operator != 
     EXPECT_TRUE(ref != 43.0);
     EXPECT_FALSE(ref != 42.0);

     // operator >
     EXPECT_TRUE(ref > 41.0);
     EXPECT_FALSE(ref > 42.0);
     EXPECT_FALSE(ref > 43.0);

     // operator >=
     EXPECT_TRUE(ref >= 41.0);
     EXPECT_TRUE(ref >= 42.0);
     EXPECT_FALSE(ref >= 43.0);

     // operator <
     EXPECT_FALSE(ref < 41.0);
     EXPECT_FALSE(ref < 42.0);
     EXPECT_TRUE(ref < 43.0);

     // operator <=
     EXPECT_FALSE(ref <= 41.0);
     EXPECT_TRUE(ref <= 42.0);
     EXPECT_TRUE(ref <= 43.0);
 }

 TEST(VLSVariantCRef, operator_compare_DateTime)
 {
     VLS::DateTime dt(1982, 2, 9, 6, 38, 42);
     CRef ref(dt);

     // operator == 
     EXPECT_FALSE(ref == VLS::DateTime(1982, 2, 9, 6, 38, 41));
     EXPECT_TRUE(ref == VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_FALSE(ref == VLS::DateTime(1982, 2, 9, 6, 38, 43));

     // operator != 
     EXPECT_TRUE(ref != VLS::DateTime(1982, 2, 9, 6, 37, 42));
     EXPECT_FALSE(ref != VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_TRUE(ref != VLS::DateTime(1982, 2, 9, 6, 39, 42));

     // operator >
     EXPECT_TRUE(ref > VLS::DateTime(1982, 2, 9, 5, 38, 42));
     EXPECT_FALSE(ref > VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_FALSE(ref > VLS::DateTime(1982, 2, 9, 7, 38, 42));

     // operator >=
     EXPECT_TRUE(ref >= VLS::DateTime(1982, 2, 8, 6, 38, 42));
     EXPECT_TRUE(ref >= VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_FALSE(ref >= VLS::DateTime(1982, 2, 10, 6, 38, 42));

     // operator <
     EXPECT_FALSE(ref < VLS::DateTime(1982, 1, 9, 6, 38, 42));
     EXPECT_FALSE(ref < VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_TRUE(ref < VLS::DateTime(1982, 3, 9, 6, 38, 42));

     // operator <=
     EXPECT_FALSE(ref <= VLS::DateTime(1981, 2, 9, 5, 38, 42));
     EXPECT_TRUE(ref <= VLS::DateTime(1982, 2, 9, 6, 38, 42));
     EXPECT_TRUE(ref <= VLS::DateTime(1983, 2, 9, 7, 38, 42));
 }

 TEST(VLSVariantCRef, compare_string)
 {
     VLS::Convert::Settings* settings = VLS::Convert::Settings::globalDefault();

     char* c = "42";
     CRef cCStr(c);
     EXPECT_EQ(cCStr.compare(42, true, settings), 0);
 }