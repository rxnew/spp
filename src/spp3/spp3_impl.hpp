#pragma once

#include "mathutils/vector/util.hpp"

namespace spp {
template <class Real>
auto Spp3<Real>::NfCompare::operator()(BoxPtr const& lhs, BoxPtr const& rhs)
  -> bool {
  return
    _front_surface(lhs)->get_position() < _front_surface(rhs)->get_position();
}

template <class Real>
auto Spp3<Real>::NbCompare::operator()(BoxPtr const& lhs, BoxPtr const& rhs)
  -> bool {
  return
    _back_surface(lhs)->get_position() < _back_surface(rhs)->get_position();
}

template <class Real>
constexpr Real const Spp3<Real>::INF;

template <class Real>
template <class BoxPtrsT>
auto Spp3<Real>::solve(BoxPtrsT&& boxes, BoxPtr const& base)
  -> std::unordered_set<BoxPtr> const& {
  sigma_ = std::forward<BoxPtrsT>(boxes);
  container_back_surface_ = base;
  auto size = base->get_size();
  auto position = base->get_position();
  position[2] = INF;
  container_front_surface_ = _make_ptr(size, position);
  _solve();
  return placed_;
}

template <class Real>
template <class BoxPtrsT>
auto Spp3<Real>::solve(BoxPtrsT&& boxes, Box const& base)
  -> std::unordered_set<BoxPtr> const& {
  return solve(std::forward<BoxPtrsT>(boxes), _make_ptr(base));
}

template <class Real>
template <class BoxPtrsT>
auto Spp3<Real>::solve(BoxPtrsT&& boxes, Box&& base)
  -> std::unordered_set<BoxPtr> const& {
  return solve(std::forward<BoxPtrsT>(boxes), _make_ptr(std::move(base)));
}

template <class Real>
template <class BoxPtrsT>
auto Spp3<Real>::solve(BoxPtrsT&& boxes, Vector const& base)
  -> std::unordered_set<BoxPtr> const& {
  return solve(std::forward<BoxPtrsT>(boxes), _make_ptr(base));
}

template <class Real>
auto Spp3<Real>::_front_surface(BoxPtr const& box) -> BoxPtr {
  auto size = box->get_size();
  auto position = box->get_position();
  position[2] += size[2];
  size[2] = 0;
  return _make_ptr(std::move(size), std::move(position));
}

template <class Real>
auto Spp3<Real>::_back_surface(BoxPtr const& box) -> BoxPtr {
  auto size = box->get_size();
  auto position = box->get_position();
  size[2] = 0;
  return _make_ptr(std::move(size), std::move(position));
}

template <class Real>
template <class... Args>
inline auto Spp3<Real>::_make_ptr(Args&&... args) -> BoxPtr {
  return std::make_shared<Box>(std::forward<Args>(args)...);
}

template <class Real>
auto Spp3<Real>::_solve() -> void {
  auto status = _step1();

  while(true) {
    switch(status) {
      case 0:  return;
      case 1:  status = _step1();  break;
      case 2:  status = _step2();  break;
      case 3:  status = _step3();  break;
      case 4:  status = _step4();  break;
      case 5:  status = _step5();  break;
      case 6:  status = _step6();  break;
      case 7:  status = _step7();  break;
      case 8:  status = _step8();  break;
      case 9:  status = _step9();  break;
      case 10: status = _step10(); break;
      default: assert(false);      break;
    }
  }
}

template <class Real>
auto Spp3<Real>::_step1() -> int {
  n_ = sigma_.size();
  placed_.clear();
  e_.clear();
  nf_.clear();
  nb_.clear();
  nf_.insert(container_front_surface_);
  nb_.insert(container_front_surface_);
  placed_.insert(container_front_surface_);
  s_ = 0;
  return 2;
}

template <class Real>
auto Spp3<Real>::_step2() -> int {
  using namespace mathutils::vector_accessors;

  if(s_ == n_) return 10; // goto Step 10
  i_ = sigma_[s_];
  ++s_;
  bl_ = Vector(INF, INF, INF); // Position
  lf_ = 0;
  lb_ = 0;
  jf_ = nf_[lf_];
  jb_ = nb_[lb_];
  floor_ = 0;
  interim_bl_ = Vector(INF, INF, INF); // Position
  x_end_ = get_x(*container_back_surface_) +
    get_w(*container_back_surface_) - get_w(*i_);
  y_end_ = get_y(*container_back_surface_) +
    get_h(*container_back_surface_) - get_h(*i_);
  return 3;
}

template <class Real>
auto Spp3<Real>::_step3() -> int {
  nfp_.clear();
  for(auto const& j : placed_) {
    nfp_[j] = _make_nfp(j, i_);
  }
  return 4;
}

template <class Real>
auto Spp3<Real>::_step4() -> int {
  using namespace mathutils::vector_accessors;

  if(floor_ == 0) {
    if(get_z(*_back_surface(nfp_[jb_])) < get_z(*container_back_surface_)) {
      return 5; // goto Step 5
    }
    else {
      return 8; // goto Step 8
    }
  }
  else if(floor_ == 1) {
    if(get_z(*_back_surface(nfp_[jb_])) < get_z(*_front_surface(nfp_[jf_]))) {
      return 5; // goto Step 5
    }
    else {
      return 6; // goto Step 6
    }
  }
  return -1;
}

template <class Real>
auto Spp3<Real>::_step5() -> int {
  if(lb_ == placed_.size() - 1) return 6; // goto Step 6
  e_.insert(jb_);
  ++lb_;
  jb_ = nb_[lb_];
  return 4; // goto Step 4
}

template <class Real>
auto Spp3<Real>::_step6() -> int {
  e_.erase(jf_);
  auto ed = std::unordered_set<BoxPtr>();
  auto front = _front_surface(nfp_[jf_]);
  for(auto const& j : nfp_) {
    if(j.first == jf_) {
      continue;
    }
    if(front->is_intersected(*j.second)) {
      ed.insert(j.first);
    }
  }
  auto bl = _find_2d_bl(ed, front);
  if(_is_avairable(bl)) interim_bl_ = std::min(interim_bl_, bl);
  return 7;
}

template <class Real>
auto Spp3<Real>::_step7() -> int {
  if(nf_.size() <= lf_ - 1 &&
     _front_surface(_make_nfp(nf_[lf_ + 1], i_))->get_position() < bl_) {
    ++lf_;
    jf_ = nf_[lf_];
    return 4; // goto Step 4
  }
  bl_ = interim_bl_;
  return 9; // goto Step 9
}

template <class Real>
auto Spp3<Real>::_step8() -> int {
  auto bl = _find_2d_bl(e_, container_back_surface_);
  floor_ = 1;
  if(!_is_avairable(bl)) return 4; // goto Step4
  bl_ = bl;
  return 9; // goto Step 9
}

template <class Real>
auto Spp3<Real>::_step9() -> int {
  i_->set_position(bl_);
  placed_.insert(i_);
  nf_.insert(i_);
  nb_.insert(i_);
  return 2; // goto Step 2
}

template <class Real>
auto Spp3<Real>::_step10() -> int {
  return 0;
}

template <class Real>
auto Spp3<Real>::_find_2d_bl(std::unordered_set<BoxPtr> const& boxes,
                             BoxPtr const& surface) const -> Vector {
  using namespace mathutils::vector_accessors;

  auto x_begin = std::max(get_x(*container_back_surface_), get_x(*surface));
  auto y_begin = std::max(get_y(*container_back_surface_), get_y(*surface));
  auto x_end = std::min(x_end_, get_x(*surface) + get_w(*surface));
  auto y_end = y_end_;
  for(auto sweep_line = y_begin; sweep_line <= y_end; ++sweep_line) {
    for(auto x = x_begin; x <= x_end; ++x) {
      auto const point = mathutils::Vector<2, Real>(x, sweep_line);
      auto non_intersected = true;
      for(auto const& box : boxes) {
        non_intersected &=
          !nfp_.at(box)->reduce_dimension().is_intersected(point);
        if(!non_intersected) break;
      }
      if(non_intersected) return Vector(x, sweep_line, get_z(*surface));
    }
  }
  return Vector(INF, INF, INF);
}

template <class Real>
auto Spp3<Real>::_make_nfp(BoxPtr const& i, BoxPtr const& j) const -> BoxPtr {
  using namespace mathutils::vector_accessors;

  auto x = get_x(*i) - get_w(*j);
  auto y = get_y(*i) - get_h(*j);
  auto z = get_z(*i) - get_d(*j);

  auto w = get_w(*i) + get_w(*j);
  auto h = get_h(*i) + get_h(*j);
  auto d = get_d(*i) + get_d(*j);

  return _make_ptr(w, h, d, x, y, z);
}

template <class Real>
auto Spp3<Real>::_is_avairable(Vector const& point) const -> bool {
  static auto const no_avairable_point = Vector(INF, INF, INF);
  return point != no_avairable_point;
}
}
