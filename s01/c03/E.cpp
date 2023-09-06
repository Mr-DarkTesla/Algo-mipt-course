#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Solver {
 public:
  void Read() {
    std::cin >> number_n_ >> number_y_ >> number_x_;
    int x, y1, y2;
    for (int i = 0; i < number_n_; ++i) {
      std::cin >> x >> y1 >> y2;
      events_.push_back(Event{x, y1, i});
      events_.push_back(Event{x, y2, i, -1});
    }
    std::sort(events_.begin(), events_.end(), Comparator);
    set_1_.insert({0, -1});
    set_1_.insert({number_x_, number_n_});
    set_2_.insert({number_x_, -1});
  }

  void Process() {
    size_t event_iter = 0;
    for (int track_iter = 0; track_iter <= number_y_; ++track_iter) {
      PreProcess(set_1_, set_2_, event_iter, events_, track_iter);
      std::cout << (prev(set_2_.end())->first) << '\n';
      PostProcess(set_1_, set_2_, event_iter, events_, track_iter);
    }
  }

 private:
  struct Event {
    int x_coordinate = 0;
    int y_coordinate = 0;
    int iter = 1;
    int time = 1;
  };

  void PreProcess(std::set<std::pair<int, int>>& set_1,
                  std::set<std::pair<int, int>>& set_2, size_t& event_iter,
                  std::vector<Event>& events, int& track_iter) {
    while (event_iter < events.size() &&
           events[event_iter].y_coordinate == track_iter &&
           events[event_iter].time == 1) {
      auto iterator = set_1
                          .insert({events[event_iter].x_coordinate,
                                   events[event_iter].iter})
                          .first;

      auto left = prev(iterator);
      auto right = next(iterator);
      int a = (right->first) - (left->first);
      set_2.erase({a, left->second});
      a = (iterator->first) - (left->first);
      set_2.insert({a, left->second});
      a = (right->first) - (iterator->first);
      set_2.insert({a, iterator->second});
      ++event_iter;
    }
  }

  void PostProcess(std::set<std::pair<int, int>>& set_1,
                   std::set<std::pair<int, int>>& set_2, size_t& event_iter,
                   std::vector<Event>& events, int& track_iter) {
    while (event_iter < events.size() &&
           events[event_iter].y_coordinate == track_iter &&
           events[event_iter].time == -1) {
      auto iterator = set_1.find(
          {events[event_iter].x_coordinate, events[event_iter].iter});
      auto left = prev(iterator);
      auto right = next(iterator);
      int a = (iterator->first) - (left->first);
      set_2.erase({a, left->second});
      a = (right->first) - (iterator->first);
      set_2.erase({a, iterator->second});
      a = (right->first) - (left->first);
      set_2.insert({a, left->second});
      set_1.erase(iterator);
      ++event_iter;
    }
  }

  static bool Comparator(Event& event_1, Event& event_2) {
    if (event_1.y_coordinate != event_2.y_coordinate) {
      return event_1.y_coordinate < event_2.y_coordinate;
    }
    if (event_1.time != event_2.time) {
      return event_1.time > event_2.time;
    }
    if (event_1.x_coordinate != event_2.x_coordinate) {
      return event_1.x_coordinate < event_2.x_coordinate;
    }
    return event_1.iter < event_2.iter;
  }

  int number_n_, number_y_, number_x_;
  std::vector<Event> events_;
  std::set<std::pair<int, int>> set_1_;
  std::set<std::pair<int, int>> set_2_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  auto solver = Solver();
  solver.Read();
  solver.Process();
}