//
//  Battle.cpp
//  KKGame
//
//  Created by hailong11 on 2017/12/15.
//  Copyright © 2017年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "Battle.hpp"

namespace kk {
    
    namespace battle {
        
        BTSceneElement::~BTSceneElement() {

        }
        
        kk::gl::vec2& BTSceneElement::size() {
            return _size;
        }
        
        void BTSceneElement::setSize(kk::gl::vec2& v) {
            _size = v;
        }
        
        void BTSceneElement::init() {
            kk::game::GMSceneElement::init();
            _size = kk::gl::vec2(0);
        }
        
        IMP_CLASS(BTSceneElement, kk::game::GMSceneElement, NULL, NULL)
        
    }
    
}
