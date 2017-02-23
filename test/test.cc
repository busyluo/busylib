#include <busynet/busynet.h>
#include <busynet/event.h>

using namespace busynet;

int main(int argc, char *argv[])
{
  int fd = 0;
  EventLoop loop;
  Event ev(fd);
  loop.loop();
  return 0;
}
