#include "../spp3.hpp"

namespace spp {
auto Spp3::NfCompare::operator()(RecPtr const& lhs, RecPtr const& rhs)
  -> bool {
  return lhs->front_surface() < rhs->front_surface();
}

auto Spp3::NbCompare::operator()(RecPtr const& lhs, RecPtr const& rhs)
  -> bool {
  return lhs->back_surface() < rhs->back_surface();
}

constexpr int const Spp3::INF;

auto Spp3::_solve() -> void {
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

auto Spp3::_step1() -> int {
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

auto Spp3::_step2() -> int {
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
  x_end_ = container_back_surface_->x + container_back_surface_->w - i_->w;
  y_end_ = container_back_surface_->y + container_back_surface_->h - i_->h;
  return 3;
}

auto Spp3::_step3() -> int {
  nfp_.clear();
  for(auto const& j : placed_) {
    nfp_[j] = _make_nfp(j, i_);
  }
  return 4;
}

auto Spp3::_step4() -> int {
  if(floor_ == 0) {
    if(_back_surface(nfp_[jb_])->z < container_back_surface_->z) {
      return 5; // goto Step 5
    }
    else {
      return 8; // goto Step 8
    }
  }
  else if(floor_ == 1) {
    if(_back_surface(nfp_[jb_])->z < nfp_[jf_]->front_surface().z) {
      return 5; // goto Step 5
    }
    else {
      return 6; // goto Step 6
    }
  }
  return -1;
}

auto Spp3::_step5() -> int {
  if(lb_ == placed_.size() - 1) return 6; // goto Step 6
  e_.insert(jb_);
  ++lb_;
  jb_ = nb_[lb_];
  return 4; // goto Step 4
}

auto Spp3::_step6() -> int {
  e_.erase(jf_);
  auto ed = std::unordered_set<RecPtr>();
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

auto Spp3::_step7() -> int {
  if(nf_.size() <= lf_ - 1 &&
     _front_surface(_make_nfp(nf_[lf_ + 1], i_))->get_position() < bl_) {
    ++lf_;
    jf_ = nf_[lf_];
    return 4; // goto Step 4
  }
  bl_ = interim_bl_;
  return 9; // goto Step 9
}

auto Spp3::_step8() -> int {
  auto bl = _find_2d_bl(e_, container_back_surface_);
  floor_ = 1;
  if(!_is_avairable(bl)) return 4; // goto Step4
  bl_ = bl;
  return 9; // goto Step 9
}

auto Spp3::_step9() -> int {
  i_->set_position(bl_);
  placed_.insert(i_);
  nf_.insert(i_);
  nb_.insert(i_);
  return 2; // goto Step 2
}

auto Spp3::_step10() -> int {
  return 0;
}

auto Spp3::_find_2d_bl(std::unordered_set<RecPtr> const& rectangulars,
                       RecPtr const& surface) const -> Vector {
  auto x_begin = std::max(container_back_surface_->x, surface->x);
  auto y_begin = std::max(container_back_surface_->y, surface->y);
  auto x_end = std::min(x_end_, surface->x + surface->w);
  auto y_end = y_end_;
  for(auto sweep_line = y_begin; sweep_line <= y_end; ++sweep_line) {
    for(auto x = x_begin; x <= x_end; ++x) {
      auto const point = mathutils::Vector<2, int>(x, sweep_line);
      auto non_intersected = true;
      for(auto const& rectangular : rectangulars) {
        non_intersected &=
          !nfp_.at(rectangular)->reduce_dimension().is_intersected(point);
        if(!non_intersected) break;
      }
      if(non_intersected) return Vector(x, sweep_line, surface->z);
    }
  }
  return Vector(INF, INF, INF);
}

auto Spp3::_make_nfp(RecPtr const& i, RecPtr const& j) const
  -> RecPtr {
  auto x = i->x - j->w;
  auto y = i->y - j->h;
  auto z = i->z - j->d;

  auto w = i->w + j->w;
  auto h = i->h + j->h;
  auto d = i->d + j->d;

  return std::make_shared<Rectangular>(w, h, d, x, y, z);
}

auto Spp3::_is_avairable(Vector const& point) const -> bool {
  static auto const no_avairable_point = Vector(INF, INF, INF);
  return point != no_avairable_point;
}
}
