// SPDX-License-Identifier: Zlib
// Copyright (c) 2023 Julien Bernard
#ifndef XY_SIGNAL_H
#define XY_SIGNAL_H

#include <cassert>
#include <cstdint>

#include <functional>
#include <vector>

namespace xy {

  enum class SignalId : uint64_t;

  template<typename Signature>
  class Signal;

  template<typename... Args>
  class Signal<void(Args...)> {
  public:

    template<typename Func>
    SignalId connect(Func&& callback)
    {
      auto id = SignalId{ m_slots.size() };
      m_slots.emplace_back(std::forward<Func>(callback));
      return id;
    }

    void disconnect(SignalId id)
    {
      auto index = static_cast<std::size_t>(id);
      assert(index < m_slots.size());
      m_slots[index] = nullptr;
    }

    void emit(Args... args)
    {
      for (auto& slot : m_slots) {
        if (slot == nullptr) {
          continue;
        }

        slot(args...);
      }
    }

  private:
    std::vector<std::function<void(Args...)>> m_slots;
  };

}

#endif // XY_SIGNAL_H
