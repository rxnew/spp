#pragma once

#include <cassert>
#include <limits>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "mathutils/vector.hpp"

#include "util/priority_container.hpp"

namespace spp {
// 3次元ストリップパッキング問題 (3D SPP) ソルバ
template <class Real = int>
class Spp3 {
 public:
  using Box = mathutils::Hyperrectangle<3, Real>;
  using Vector = mathutils::Vector<3, Real>;

 private:
  using BoxPtr = std::shared_ptr<Box>;

 public:
  template <class BoxPtrsT>
  auto solve(BoxPtrsT&& boxes, BoxPtr const& base, char axis = '\0')
    -> std::unordered_set<BoxPtr> const&;
  template <class BoxPtrsT>
  auto solve(BoxPtrsT&& boxes, Box const& base, char axis = '\0')
    -> std::unordered_set<BoxPtr> const&;
  template <class BoxPtrsT>
  auto solve(BoxPtrsT&& boxes, Box&& base, char axis = '\0')
    -> std::unordered_set<BoxPtr> const&;
  template <class BoxPtrsT>
  auto solve(BoxPtrsT&& boxes, Vector const& base, char axis = '\0')
    -> std::unordered_set<BoxPtr> const&;

 private:
  struct NfCompare {
    auto operator()(BoxPtr const& lhs, BoxPtr const& rhs) -> bool;
  };

  struct NbCompare {
    auto operator()(BoxPtr const& lhs, BoxPtr const& rhs) -> bool;
  };

  static constexpr Real const INF = std::numeric_limits<Real>::max() >> 1;

  static auto _front_surface(BoxPtr const& rectangular) -> BoxPtr;
  static auto _back_surface(BoxPtr const& rectangular) -> BoxPtr;
  template <class... Args>
  static auto _make_ptr(Args&&... args) -> BoxPtr;
  static auto _get_axis(BoxPtr const& base) -> char;
  static auto _swap_axis(BoxPtr const& box, char axis) -> void;
  template <template <class...> class U>
  static auto _swap_axis(U<BoxPtr> const& boxes, char axis) -> void;

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

  auto _find_2d_bl(std::unordered_set<BoxPtr> const& boxes,
                   BoxPtr const& surface) const -> Vector;
  // i: 既配置, j: これから配置
  auto _make_nfp(BoxPtr const& i, BoxPtr const& j) const -> BoxPtr;
  auto _is_avairable(Vector const& position) const -> bool;
  // 2次元容器における容器のNFP (IFR) との交差判定
  auto _is_intersected_ifr(BoxPtr const& rectangular,
                           BoxPtr const& surface) const -> bool;

  int n_; // 直方体の数
  BoxPtr container_back_surface_; // 容器の背面
  BoxPtr container_front_surface_; // 容器の前面 (0, 0, INF)
  std::vector<BoxPtr> sigma_;
  std::unordered_set<BoxPtr> placed_;
  std::unordered_set<BoxPtr> e_;
  PriorityContainer<BoxPtr, NfCompare> nf_;
  PriorityContainer<BoxPtr, NbCompare> nb_;
  int s_;
  BoxPtr i_;
  Vector bl_; // Position
  unsigned int lf_;
  unsigned int lb_;
  BoxPtr jf_;
  BoxPtr jb_;
  int floor_;
  std::unordered_map<BoxPtr, BoxPtr> nfp_;
  Vector interim_bl_; // 暫定BL点, Position
  Real x_end_; // 容器のx座標 - wi
  Real y_end_; // 容器のy座標 - hi
};
}

#include "spp3/spp3_impl.hpp"
