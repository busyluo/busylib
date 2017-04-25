#include <busylib/base/logger.h>
#include <busylib/util/unit_test.h>

using namespace busylib;

TEST_CASE("vectors can be sized and resized", "[vector]")
{
  logInfo("Test format string: 5 = %d", 5);
  logInfo("Test append string: 5 = ") << 5;
}
