#include "Events/Events.h"
#include "Events/EventDispatcher.h"

#include "Events/WindowEvents.h"
#include <fmt/base.h>

bool closedWindow(const WindowClosedEvent& event)
{
  fmt::println("Window closed");
  return true;
}

bool windowResized(const WindowResizeEvent& event)
{
  fmt::println(
    "New window size, X: {}, Y: {}",
    event.GetWidth(),
    event.GetHeight()
  );

  return true;
}

int main()
{
  WindowClosedEvent event;
  EventDispatcher dipatch(event);

  dipatch.Dispatch<EventType::WINDOW_RESIZED, WindowResizeEvent>(windowResized);
  dipatch.Dispatch<EventType::WINDOW_CLOSED, WindowClosedEvent>(closedWindow);

  return 0;
}
