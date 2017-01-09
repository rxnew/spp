#pragma once

#include <cassert>
#include <limits>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "spp3/rectangular.hpp"
#include "util/priority_container.hpp"

namespace spp {
// 3次元ストリップパッキング問題 (3D SPP) ソルバ
class Spp3 {
 private:
  using RecPtr = std::shared_ptr<Rectangular>;
  using Vector = mathutils::Vector<3, int>;

 public:
  template <class RecPtrsT>
  auto solve(RecPtrsT&& rectangulars, RecPtr const& base)
    -> std::unordered_set<RecPtr> const&;
  template <class RecPtrsT>
  auto solve(RecPtrsT&& rectangulars, Rectangular const& base)
    -> std::unordered_set<RecPtr> const&;
  template <class RecPtrsT>
  auto solve(RecPtrsT&& rectangulars, Rectangular&& base)
    -> std::unordered_set<RecPtr> const&;
  template <class RecPtrsT>
  auto solve(RecPtrsT&& rectangulars, Vector const& base)
    -> std::unordered_set<RecPtr> const&;

 private:
  struct NfCompare {
    auto operator()(RecPtr const& lhs, RecPtr const& rhs) -> bool;
  };

  struct NbCompare {
    auto operator()(RecPtr const& lhs, RecPtr const& rhs) -> bool;
  };

  static constexpr int const INF = std::numeric_limits<int>::max() >> 1;

  int n_; // 直方体の数
  RecPtr container_back_surface_; // 容器の背面
  RecPtr container_front_surface_; // 容器の前面 (0, 0, INF)
  std::vector<RecPtr> sigma_;
  std::unordered_set<RecPtr> placed_;
  std::unordered_set<RecPtr> e_;
  PriorityContainer<RecPtr, NfCompare> nf_;
  PriorityContainer<RecPtr, NbCompare> nb_;
  int s_;
  RecPtr i_;
  Vector bl_; // Position
  unsigned int lf_;
  unsigned int lb_;
  RecPtr jf_;
  RecPtr jb_;
  int floor_;
  std::unordered_map<RecPtr, RecPtr> nfp_;
  Vector interim_bl_; // 暫定BL点, Position
  int x_end_; // 容器のx座標 - wi
  int y_end_; // 容器のy座標 - hi

  auto _solve() -> void;

  auto _step1() -> int;
  auto _step2() -> int;
  auto _step3() -> int;
  auto _step4() -> int;
  auto _step5() -> int;
  auto _step6() -> int;
  auto _step7() -> int;
  auto _step8() -> int;
  auto _step9() -> int;
  auto _step10() -> int;

  auto _find_2d_bl(std::unordered_set<RecPtr> const& rectangulars,
                   RecPtr const& surface) const -> Vector;
  // i: 既配置, j: これから配置
  auto _make_nfp(RecPtr const& i, RecPtr const& j) const
    -> RecPtr;
  auto _is_avairable(Vector const& point) const -> bool;
  // 2次元容器における容器のNFP (IFR) との交差判定
  auto _is_intersected_ifr(RecPtr const& rectangular,
                           RecPtr const& surface) const -> bool;
  static auto _front_surface(RecPtr const& rectangular) -> RecPtr;
  static auto _back_surface(RecPtr const& rectangular) -> RecPtr;
  template <class... Args>
  static auto _make_ptr(Args&&... args) -> RecPtr;
};
}

#include "spp3/spp3_impl.hpp"
