
TestUnit::TestUnit(const std::string& suite, const std::string& name) 
: suite_(suite)
, name_(name) 
{
}

void Fail(const std::string& suite, const std::string& test, const std::string& file, long line, 
          const std::string& msg)
{
    std::cout<<"Suite: "<<suite<<std::endl;
    std::cout<<"Test : "<<test<<std::endl;
    std::cout<<"Fail : "<<msg<<std::endl;
    std::cout<<"File : "<<file<<std::endl;
    std::cout<<"Line : "<<line<<std::endl;
    std::cout<<std::endl;
}

template <class T1, class T2>
void Fail(const std::string& suite, const std::string& test, const std::string& file, long line,
          const T1& expected, const T2& actual)
{
    std::stringstream msg;
    msg<<"expected ["<<expected<<"] but was ["<<actual<<"]";
    Fail(suite, test, file, line, msg.str());
}

#define TEST_SUITE DefaultSuite
#define TEST(name) TEST_UNIT(TEST_SUITE, name)
#define TEST_UNIT(suite, name) TEST_UNIT_IMPL(suite, name)

#define TEST_UNIT_IMPL(suite, name) \
class TestUnit_##suite##_##name : public TestUnit \
{ \
public: \
    TestUnit_##suite##_##name() : TestUnit(#suite, #name) { Run(); } \
    \
    virtual void Run(); \
} kTestUnit_##suite##_##name; \
\
void TestUnit_##suite##_##name::Run() 

#define CHECK(condition) \
{ \
    if (!(condition)) \
        Fail(suite_, name_, __FILE__, __LINE__, #condition); \
}

#define CHECK_EQUAL(expected, actual) \
{ \
    if ((expected) != (actual)) \
        Fail(suite_, name_, __FILE__, __LINE__, expected, actual); \
}

#define FAIL(text) \
{ \
    Fail(suite_, name_, __FILE__, __LINE__, #text); \
}

